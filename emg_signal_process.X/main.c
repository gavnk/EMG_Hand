

/**
 * 
 *   FIRST SET THE MODE BY USING THE BUTTONS OR THE HAND WILL NOT WORK! 
 * 
 *   // Mode 0 -- Flex and Release for Motor ON and Motor OFF (LED_RA7 OFF) 
     // Mode 1 -- Flex and Flex for Motor ON and Motor OFF (LED_RA7 ON)  
 * 
 * 
 * 
  Generated Main Source File

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    This is the main file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  Description:
    This header file provides implementations for driver APIs for all modules selected in the GUI.
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.81.8
        Device            :  PIC16F18875
        Driver Version    :  2.00
*/

/*
    (c) 2018 Microchip Technology Inc. and its subsidiaries. 
    
    Subject to your compliance with these terms, you may use Microchip software and any 
    derivatives exclusively with Microchip products. It is your responsibility to comply with third party 
    license terms applicable to your use of third party software (including open source software) that 
    may accompany Microchip software.
    
    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER 
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY 
    IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS 
    FOR A PARTICULAR PURPOSE.
    
    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP 
    HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO 
    THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL 
    CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT 
    OF FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS 
    SOFTWARE.
*/

#include "mcc_generated_files/mcc.h"
#include "peak_filter.h"
#include "moving_avg_filter.h"
#include "signal_buffer.h" 
#include "signal_processing.h"
#include <stdio.h> 
#include <stdint.h> 
#include <stdbool.h> 
#include <stdlib.h>
#include <math.h>
#include <xc.h>
#include "i2c.h"
#include <stdio.h>
#include "pca9685.h"


#define SERVOMIN  120 // This is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX  500 // This is the 'maximum' pulse length count (out of 4096)

// Flag that starts data acquisition  
uint8_t start_flag = 0; 
 
// Index for looping elements  
uint8_t i; 
 
// Flags to indicate the character sent over UART to the Slave PIC  
uint8_t sent_1 = 0;  
uint8_t sent_0 = 0; 


void TMR6_EMG_InterruptHandler(void) 
{  
    if (start_flag == 1) 
    { 
        //Uncomment the line below if you need to test Analog Channel with a Potentiometer 
        //ADCC_StartConversion(POT_RA0);  
 
        //ADC Channel selected to be the EMG Click 
        //Make sure to insert the EMG Click on Curiosity HPC MikroBus Slot #2  
        ADCC_StartConversion(EMG_RA2);  
 
        adc_result_t adval = ADCC_GetConversionResult(); 
 
        // Every new sample point is added to the "Signal Circular Buffer" 
        // Data is "buffered" (until the limit of 50 data points) so the  
        // main loop can get the first inserted element (FIFO) 
        // whenever it is free and process it.  
        sbuf_insert(adval / 100);  
    }  
}  


/*
                         Main application
 */
void main(void)
{
    int count = 0; //Counter for number of data points in signal buffer  
    uint16_t datapoint;  
    uint16_t neutral_datapoint, result;  
    uint8_t mode = 0; //Mode of Action of Prosthetic prototype  
    double time_elapsed;   
    uint8_t flex_flag, motor_started; //Flags set after events 
    //Initialize flags  
    flex_flag = 0;  
    motor_started = 0; 
      
    // initialize the device
    SYSTEM_Initialize();
    i2c_init();
    pca9685_init();
     

    // When using interrupts, you need to set the Global and Peripheral Interrupt Enable bits
    // Use the following macros to:

    // Enable the Global Interrupts
    INTERRUPT_GlobalInterruptEnable();

    // Enable the Peripheral Interrupts
    INTERRUPT_PeripheralInterruptEnable();

    // Disable the Global Interrupts
    //INTERRUPT_GlobalInterruptDisable();

    // Disable the Peripheral Interrupts
    //INTERRUPT_PeripheralInterruptDisable();
    
   TMR6_SetInterruptHandler(TMR6_EMG_InterruptHandler);  
   TMR6_Start();
    
   // Mode 0 -- Flex and Release for Motor ON and Motor OFF (LED_RA7 OFF) 
   // Mode 1 -- Flex and Flex for Motor ON and Motor OFF (LED_RA7 ON)  
    LED_RA7_SetLow(); //Initialize Mode
    
    while (1) 
    { 
       // Press Switch-1 to toggle the Mode (Reset Microcontroller after every  //  Mode change)  
        if (MODE_RB4_GetValue() == 0) 
        {  
            mode ^= 1;  
            LED_RA7_Toggle();  
            __delay_ms(700);  
        } 

       // When the flag is cleared and Switch-2 is pressed, the process starts  
        if (START_RC5_GetValue() == 0 && start_flag == 0) 
        {
            //Uncomment the line below for sending data to MikroPlot                
            //printf("START\r\n");  
            start_flag = 1;  
            __delay_ms(700);  

            break;  
        }  
    } 
    
    while (1) 
    {  
        if (start_flag == 1) 
        { 
            // Count the number of data points present in signal buffer  
            for (i = sb_front; i != sb_rear; i = (i + 1) % SB_DATA_WINDOW) 
            {  
                count++;  
            }  

            if (count > 0){ 
                // Get the first inserted data point (in FIFO order)  
                datapoint = sbuf_peek(); 

                // Calculates the neutral peak by passing the data point to the Peak Filter  
                neutral_datapoint = get_neutral_peaktopeak(datapoint); 

                // Uses the neutral point to subtract from the current data point 
                // Signal is rectified by taking absolute difference between the two points 
                // Moving Average filter is applied to the obtained peak values   

                result = get_moving_average(abs(datapoint - neutral_datapoint));  
                
                
              
              if (mode == 0) 
              { 
                  // Turn motor at muscle flex & Turn back motor at muscle release  
                 // if (result >= 25 && sent_1 == 0) 
                  if (result >= 15 )  
                  {   
                      //Send Character '1' over UART to SLAVE MCU to turn motor Clockwise  
                    //  printf("1"); 
                    LATAbits.LATA4 =1;
                  //  __delay_ms(1000);  
                    set_pwm(0, 0, SERVOMIN );
                    set_pwm(1, 0, SERVOMIN );
                    set_pwm(2, 0, SERVOMIN );
                    set_pwm(3, 0, SERVOMIN );
                    set_pwm(4, 0, SERVOMIN );
                    __delay_ms(50);  
                      //Set and Reset flags   
                     // sent_1 = 1;  
                    //  sent_0 = 0;  
                  } 
                  else if (result < 15 )
                  { 
                      //Send Character '0' over UART to SLAVE MCU to turn motor Counter-Clockwise  
                    //  printf("0"); 
                     LATAbits.LATA4 =0;
                    // __delay_ms(1000);  
                     set_pwm(0, 0, SERVOMAX );
                     set_pwm(1, 0, SERVOMAX );
                     set_pwm(2, 0, SERVOMAX );
                     set_pwm(3, 0, SERVOMAX );
                     set_pwm(4, 0, SERVOMAX );
                    // __delay_ms(2000); 
                      //Set and Reset flags  
                    //  sent_0 = 1;  
                    //  sent_1 = 0;  
                  }  
              } 

              else //Mode 1  
              { 
                  // Turn motor at Muscle flex & Turn back motor at next muscle flex  
                  if (result >= 25 && flex_flag == 0) 
                  {  
                      flex_flag = 1;
                 
                      if (motor_started == 1) 
                      {  
                     //   LATAbits.LATA4 =1;
                          motor_started = 0;  
                         // printf("0");  
                          LATAbits.LATA4 =1;
                          set_pwm(0, 0, SERVOMIN );
                          set_pwm(1, 0, SERVOMIN );
                          set_pwm(2, 0, SERVOMIN );
                          set_pwm(3, 0, SERVOMIN );
                          set_pwm(4, 0, SERVOMIN );
                        
                      } 

                      else
                      {  
                           set_pwm(0, 0, SERVOMAX );
                           set_pwm(1, 0, SERVOMAX );
                           set_pwm(2, 0, SERVOMAX );
                           set_pwm(3, 0, SERVOMAX );
                           set_pwm(4, 0, SERVOMAX );
                           LATAbits.LATA4 =0;
                           motor_started = 1;  
                        //  printf("1");  
                      }  
                  } 

                  else if (result < 25 && flex_flag == 1) 
                  {  
                      flex_flag = 0;  
                  }  
              }
                // Remove the first element (in FIFO order) since it has already been processed  
                sbuf_remove();  

                time_elapsed += 5.0;  

            }  
            count = 0;  
        }  
    } 
    
}
/**
 End of File
*/