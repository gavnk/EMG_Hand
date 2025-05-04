/**
  @Generated Pin Manager Header File

  @Company:
    Microchip Technology Inc.

  @File Name:
    pin_manager.h

  @Summary:
    This is the Pin Manager file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  @Description
    This header file provides APIs for driver for .
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.81.8
        Device            :  PIC16F18875
        Driver Version    :  2.11
    The generated drivers are tested against the following:
        Compiler          :  XC8 2.36 and above
        MPLAB 	          :  MPLAB X 6.00	
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

#ifndef PIN_MANAGER_H
#define PIN_MANAGER_H

/**
  Section: Included Files
*/

#include <xc.h>

#define INPUT   1
#define OUTPUT  0

#define HIGH    1
#define LOW     0

#define ANALOG      1
#define DIGITAL     0

#define PULL_UP_ENABLED      1
#define PULL_UP_DISABLED     0

// get/set POT_RA0 aliases
#define POT_RA0_TRIS                 TRISAbits.TRISA0
#define POT_RA0_LAT                  LATAbits.LATA0
#define POT_RA0_PORT                 PORTAbits.RA0
#define POT_RA0_WPU                  WPUAbits.WPUA0
#define POT_RA0_OD                   ODCONAbits.ODCA0
#define POT_RA0_ANS                  ANSELAbits.ANSA0
#define POT_RA0_SetHigh()            do { LATAbits.LATA0 = 1; } while(0)
#define POT_RA0_SetLow()             do { LATAbits.LATA0 = 0; } while(0)
#define POT_RA0_Toggle()             do { LATAbits.LATA0 = ~LATAbits.LATA0; } while(0)
#define POT_RA0_GetValue()           PORTAbits.RA0
#define POT_RA0_SetDigitalInput()    do { TRISAbits.TRISA0 = 1; } while(0)
#define POT_RA0_SetDigitalOutput()   do { TRISAbits.TRISA0 = 0; } while(0)
#define POT_RA0_SetPullup()          do { WPUAbits.WPUA0 = 1; } while(0)
#define POT_RA0_ResetPullup()        do { WPUAbits.WPUA0 = 0; } while(0)
#define POT_RA0_SetPushPull()        do { ODCONAbits.ODCA0 = 0; } while(0)
#define POT_RA0_SetOpenDrain()       do { ODCONAbits.ODCA0 = 1; } while(0)
#define POT_RA0_SetAnalogMode()      do { ANSELAbits.ANSA0 = 1; } while(0)
#define POT_RA0_SetDigitalMode()     do { ANSELAbits.ANSA0 = 0; } while(0)

// get/set EMG_RA2 aliases
#define EMG_RA2_TRIS                 TRISAbits.TRISA2
#define EMG_RA2_LAT                  LATAbits.LATA2
#define EMG_RA2_PORT                 PORTAbits.RA2
#define EMG_RA2_WPU                  WPUAbits.WPUA2
#define EMG_RA2_OD                   ODCONAbits.ODCA2
#define EMG_RA2_ANS                  ANSELAbits.ANSA2
#define EMG_RA2_SetHigh()            do { LATAbits.LATA2 = 1; } while(0)
#define EMG_RA2_SetLow()             do { LATAbits.LATA2 = 0; } while(0)
#define EMG_RA2_Toggle()             do { LATAbits.LATA2 = ~LATAbits.LATA2; } while(0)
#define EMG_RA2_GetValue()           PORTAbits.RA2
#define EMG_RA2_SetDigitalInput()    do { TRISAbits.TRISA2 = 1; } while(0)
#define EMG_RA2_SetDigitalOutput()   do { TRISAbits.TRISA2 = 0; } while(0)
#define EMG_RA2_SetPullup()          do { WPUAbits.WPUA2 = 1; } while(0)
#define EMG_RA2_ResetPullup()        do { WPUAbits.WPUA2 = 0; } while(0)
#define EMG_RA2_SetPushPull()        do { ODCONAbits.ODCA2 = 0; } while(0)
#define EMG_RA2_SetOpenDrain()       do { ODCONAbits.ODCA2 = 1; } while(0)
#define EMG_RA2_SetAnalogMode()      do { ANSELAbits.ANSA2 = 1; } while(0)
#define EMG_RA2_SetDigitalMode()     do { ANSELAbits.ANSA2 = 0; } while(0)

// get/set IO_RA4 aliases
#define IO_RA4_TRIS                 TRISAbits.TRISA4
#define IO_RA4_LAT                  LATAbits.LATA4
#define IO_RA4_PORT                 PORTAbits.RA4
#define IO_RA4_WPU                  WPUAbits.WPUA4
#define IO_RA4_OD                   ODCONAbits.ODCA4
#define IO_RA4_ANS                  ANSELAbits.ANSA4
#define IO_RA4_SetHigh()            do { LATAbits.LATA4 = 1; } while(0)
#define IO_RA4_SetLow()             do { LATAbits.LATA4 = 0; } while(0)
#define IO_RA4_Toggle()             do { LATAbits.LATA4 = ~LATAbits.LATA4; } while(0)
#define IO_RA4_GetValue()           PORTAbits.RA4
#define IO_RA4_SetDigitalInput()    do { TRISAbits.TRISA4 = 1; } while(0)
#define IO_RA4_SetDigitalOutput()   do { TRISAbits.TRISA4 = 0; } while(0)
#define IO_RA4_SetPullup()          do { WPUAbits.WPUA4 = 1; } while(0)
#define IO_RA4_ResetPullup()        do { WPUAbits.WPUA4 = 0; } while(0)
#define IO_RA4_SetPushPull()        do { ODCONAbits.ODCA4 = 0; } while(0)
#define IO_RA4_SetOpenDrain()       do { ODCONAbits.ODCA4 = 1; } while(0)
#define IO_RA4_SetAnalogMode()      do { ANSELAbits.ANSA4 = 1; } while(0)
#define IO_RA4_SetDigitalMode()     do { ANSELAbits.ANSA4 = 0; } while(0)

// get/set LED_RA7 aliases
#define LED_RA7_TRIS                 TRISAbits.TRISA7
#define LED_RA7_LAT                  LATAbits.LATA7
#define LED_RA7_PORT                 PORTAbits.RA7
#define LED_RA7_WPU                  WPUAbits.WPUA7
#define LED_RA7_OD                   ODCONAbits.ODCA7
#define LED_RA7_ANS                  ANSELAbits.ANSA7
#define LED_RA7_SetHigh()            do { LATAbits.LATA7 = 1; } while(0)
#define LED_RA7_SetLow()             do { LATAbits.LATA7 = 0; } while(0)
#define LED_RA7_Toggle()             do { LATAbits.LATA7 = ~LATAbits.LATA7; } while(0)
#define LED_RA7_GetValue()           PORTAbits.RA7
#define LED_RA7_SetDigitalInput()    do { TRISAbits.TRISA7 = 1; } while(0)
#define LED_RA7_SetDigitalOutput()   do { TRISAbits.TRISA7 = 0; } while(0)
#define LED_RA7_SetPullup()          do { WPUAbits.WPUA7 = 1; } while(0)
#define LED_RA7_ResetPullup()        do { WPUAbits.WPUA7 = 0; } while(0)
#define LED_RA7_SetPushPull()        do { ODCONAbits.ODCA7 = 0; } while(0)
#define LED_RA7_SetOpenDrain()       do { ODCONAbits.ODCA7 = 1; } while(0)
#define LED_RA7_SetAnalogMode()      do { ANSELAbits.ANSA7 = 1; } while(0)
#define LED_RA7_SetDigitalMode()     do { ANSELAbits.ANSA7 = 0; } while(0)

// get/set MODE_RB4 aliases
#define MODE_RB4_TRIS                 TRISBbits.TRISB4
#define MODE_RB4_LAT                  LATBbits.LATB4
#define MODE_RB4_PORT                 PORTBbits.RB4
#define MODE_RB4_WPU                  WPUBbits.WPUB4
#define MODE_RB4_OD                   ODCONBbits.ODCB4
#define MODE_RB4_ANS                  ANSELBbits.ANSB4
#define MODE_RB4_SetHigh()            do { LATBbits.LATB4 = 1; } while(0)
#define MODE_RB4_SetLow()             do { LATBbits.LATB4 = 0; } while(0)
#define MODE_RB4_Toggle()             do { LATBbits.LATB4 = ~LATBbits.LATB4; } while(0)
#define MODE_RB4_GetValue()           PORTBbits.RB4
#define MODE_RB4_SetDigitalInput()    do { TRISBbits.TRISB4 = 1; } while(0)
#define MODE_RB4_SetDigitalOutput()   do { TRISBbits.TRISB4 = 0; } while(0)
#define MODE_RB4_SetPullup()          do { WPUBbits.WPUB4 = 1; } while(0)
#define MODE_RB4_ResetPullup()        do { WPUBbits.WPUB4 = 0; } while(0)
#define MODE_RB4_SetPushPull()        do { ODCONBbits.ODCB4 = 0; } while(0)
#define MODE_RB4_SetOpenDrain()       do { ODCONBbits.ODCB4 = 1; } while(0)
#define MODE_RB4_SetAnalogMode()      do { ANSELBbits.ANSB4 = 1; } while(0)
#define MODE_RB4_SetDigitalMode()     do { ANSELBbits.ANSB4 = 0; } while(0)

// get/set RB7 procedures
#define RB7_SetHigh()            do { LATBbits.LATB7 = 1; } while(0)
#define RB7_SetLow()             do { LATBbits.LATB7 = 0; } while(0)
#define RB7_Toggle()             do { LATBbits.LATB7 = ~LATBbits.LATB7; } while(0)
#define RB7_GetValue()              PORTBbits.RB7
#define RB7_SetDigitalInput()    do { TRISBbits.TRISB7 = 1; } while(0)
#define RB7_SetDigitalOutput()   do { TRISBbits.TRISB7 = 0; } while(0)
#define RB7_SetPullup()             do { WPUBbits.WPUB7 = 1; } while(0)
#define RB7_ResetPullup()           do { WPUBbits.WPUB7 = 0; } while(0)
#define RB7_SetAnalogMode()         do { ANSELBbits.ANSB7 = 1; } while(0)
#define RB7_SetDigitalMode()        do { ANSELBbits.ANSB7 = 0; } while(0)

// get/set START_RC5 aliases
#define START_RC5_TRIS                 TRISCbits.TRISC5
#define START_RC5_LAT                  LATCbits.LATC5
#define START_RC5_PORT                 PORTCbits.RC5
#define START_RC5_WPU                  WPUCbits.WPUC5
#define START_RC5_OD                   ODCONCbits.ODCC5
#define START_RC5_ANS                  ANSELCbits.ANSC5
#define START_RC5_SetHigh()            do { LATCbits.LATC5 = 1; } while(0)
#define START_RC5_SetLow()             do { LATCbits.LATC5 = 0; } while(0)
#define START_RC5_Toggle()             do { LATCbits.LATC5 = ~LATCbits.LATC5; } while(0)
#define START_RC5_GetValue()           PORTCbits.RC5
#define START_RC5_SetDigitalInput()    do { TRISCbits.TRISC5 = 1; } while(0)
#define START_RC5_SetDigitalOutput()   do { TRISCbits.TRISC5 = 0; } while(0)
#define START_RC5_SetPullup()          do { WPUCbits.WPUC5 = 1; } while(0)
#define START_RC5_ResetPullup()        do { WPUCbits.WPUC5 = 0; } while(0)
#define START_RC5_SetPushPull()        do { ODCONCbits.ODCC5 = 0; } while(0)
#define START_RC5_SetOpenDrain()       do { ODCONCbits.ODCC5 = 1; } while(0)
#define START_RC5_SetAnalogMode()      do { ANSELCbits.ANSC5 = 1; } while(0)
#define START_RC5_SetDigitalMode()     do { ANSELCbits.ANSC5 = 0; } while(0)

// get/set RC6 procedures
#define RC6_SetHigh()            do { LATCbits.LATC6 = 1; } while(0)
#define RC6_SetLow()             do { LATCbits.LATC6 = 0; } while(0)
#define RC6_Toggle()             do { LATCbits.LATC6 = ~LATCbits.LATC6; } while(0)
#define RC6_GetValue()              PORTCbits.RC6
#define RC6_SetDigitalInput()    do { TRISCbits.TRISC6 = 1; } while(0)
#define RC6_SetDigitalOutput()   do { TRISCbits.TRISC6 = 0; } while(0)
#define RC6_SetPullup()             do { WPUCbits.WPUC6 = 1; } while(0)
#define RC6_ResetPullup()           do { WPUCbits.WPUC6 = 0; } while(0)
#define RC6_SetAnalogMode()         do { ANSELCbits.ANSC6 = 1; } while(0)
#define RC6_SetDigitalMode()        do { ANSELCbits.ANSC6 = 0; } while(0)

// get/set RC7 procedures
#define RC7_SetHigh()            do { LATCbits.LATC7 = 1; } while(0)
#define RC7_SetLow()             do { LATCbits.LATC7 = 0; } while(0)
#define RC7_Toggle()             do { LATCbits.LATC7 = ~LATCbits.LATC7; } while(0)
#define RC7_GetValue()              PORTCbits.RC7
#define RC7_SetDigitalInput()    do { TRISCbits.TRISC7 = 1; } while(0)
#define RC7_SetDigitalOutput()   do { TRISCbits.TRISC7 = 0; } while(0)
#define RC7_SetPullup()             do { WPUCbits.WPUC7 = 1; } while(0)
#define RC7_ResetPullup()           do { WPUCbits.WPUC7 = 0; } while(0)
#define RC7_SetAnalogMode()         do { ANSELCbits.ANSC7 = 1; } while(0)
#define RC7_SetDigitalMode()        do { ANSELCbits.ANSC7 = 0; } while(0)

/**
   @Param
    none
   @Returns
    none
   @Description
    GPIO and peripheral I/O initialization
   @Example
    PIN_MANAGER_Initialize();
 */
void PIN_MANAGER_Initialize (void);

/**
 * @Param
    none
 * @Returns
    none
 * @Description
    Interrupt on Change Handling routine
 * @Example
    PIN_MANAGER_IOC();
 */
void PIN_MANAGER_IOC(void);



#endif // PIN_MANAGER_H
/**
 End of File
*/