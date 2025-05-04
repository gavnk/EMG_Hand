/*
 * File:   pca9685.c
 * Author: M73267
 *
 * Created on 19 April 2023, 09:43
 */


#include <xc.h>
#include "i2c.h"
#include "pca9685.h"

#define PCA9685_ADDR 0x80
#define MODE1_REG    0x00
#define PRESCALE_REG 0xFE
#define LED0_ON_L    0x06
#define LED0_ON_H    0x07
#define LED0_OFF_L   0x08
#define LED0_OFF_H   0x09


void pca_init(unsigned int addr);
void pca_write(unsigned int ledn, unsigned int on_count, unsigned int off_count);
void set_pwm_freq(float freq);
void set_pwm(uint8_t channel, uint16_t on_time, uint16_t off_time);
void set_servo_angle(uint8_t channel, float angle);
void pca9685_init(void) ;
uint8_t readPrescale(void);
void writeMicroseconds (uint8_t num, uint16_t Microseconds);
uint8_t readPrescale(void) ;
uint8_t read8(uint8_t addr);
uint16_t read_Servo(uint8_t servo);

//void pca_init(unsigned int addr)
//{
//    uint8_t pca_addr=0x80;                     //Assigning global variable with slave address
//    
//    TRISBbits.TRISB2=0;
//    PORTBbits.RB2=0;                    //Enabling PCA9685 with OE=0
//    
//   // i2c_init();                 //Initializing I2C communication at 100KHz
//    i2c_start();                        //Start signal
//    i2c_write(pca_addr);                //Specifying slave address in write mode
//    i2c_write(0x00);                    //Control register set to address 00h
//    i2c_write(0x21);                    //Mode 1 configured to with AI=1 and ALLCALL=1
//    i2c_stop();                         //Stop signal
//    
//}

//void pca_write(unsigned int ledn, unsigned int on_count, unsigned int off_count)
//{
//    uint8_t pca_addr=0x80;                     //Assigning global variable with slave address
//   // if(ledn>15)                         //Checking for invalid output pin number
//    //    return;    
//    
//    
//  
//    i2c_start();                        //Start signal
//    i2c_write(pca_addr);                //Specifying slave address in write mode
//    i2c_write(0x06);              //Control register set to address LEDn_ON_L
//    i2c_write(on_count&0xFF);           //Writing 8 LSB bits of ON count
//    i2c_write((on_count&0xF00)>>8);     //Writing 4 MSB bits of ON count
//    i2c_write(off_count&0xFF);          //Writing 8 LSB bits of OFF count
//    i2c_write((off_count&0xF00)>>8);    //Writing 4 MSB bits of ON count    
//    i2c_stop();                         //Stop signal
//}

void pca9685_init(void) {
    // Reset PCA9685
       
   
//    i2c_start();
//    i2c_write(PCA9685_ADDR );
//    i2c_write(MODE1_REG);
//    i2c_write(0x21);
//    i2c_stop();
    // Set PWM frequency to 50Hz
   // set_pwm_freq(49.11);
  
   // Set the mode1 register to sleep mode
    i2c_start();
    i2c_write(PCA9685_ADDR);
    i2c_write(MODE1_REG);
    i2c_write(0x10);
    i2c_stop();

    // Set the prescaler value for a 50Hz frequency
    i2c_start();
    i2c_write(PCA9685_ADDR );
    i2c_write(PRESCALE_REG);
    i2c_write(125); // Prescaler = round(25000000 / (4096 * 50)) - 1
    i2c_stop();

    // Set the mode1 register to normal mode
    i2c_start();
    i2c_write(PCA9685_ADDR );
    i2c_write(MODE1_REG);
    i2c_write(0x21);
    i2c_stop();
  
}

void set_pwm_freq(float freq) {
    uint8_t prescale_value = (uint8_t)(25000000.0 / (4096.0 * freq) - 1.0);
    i2c_start();
    i2c_write(PCA9685_ADDR );
    i2c_write(MODE1_REG);
    i2c_write(0x10);   // set SLEEP to logic one to write prescale value
    i2c_stop();
    
    i2c_start();
    i2c_write(PCA9685_ADDR );
    i2c_write(PRESCALE_REG);
    i2c_write(prescale_value);  // write prescale value for 50Hz
    i2c_stop();
    NOP();
   
    i2c_start();
    i2c_write(PCA9685_ADDR );
    i2c_write(MODE1_REG);
    i2c_write(0x01);    // clear SLEEP for osc on
    i2c_stop();
}

void set_pwm(uint8_t channel, uint16_t on_time, uint16_t off_time) {
    i2c_start();
    i2c_write(PCA9685_ADDR );
    i2c_write(LED0_ON_L + 4 * channel);
    i2c_write(on_time & 0xFF);
    i2c_write(on_time >> 8);
    i2c_write(off_time & 0xFF);
    i2c_write(off_time >> 8);
    i2c_stop();
}

void set_servo_angle(uint8_t channel, float angle) {
    float pulse_length = (0.5 + angle) / 180.0;
    uint16_t pwm_value = (uint16_t)(pulse_length * 4096.0);
    set_pwm(channel, 0, pwm_value);
}


void writeMicroseconds(uint8_t num, uint16_t Microseconds){

 
  float pulse = Microseconds;
  float pulselength;
  pulselength = 1000000; // 1,000,000 us per second

  // Read prescale
  uint16_t prescale = 125;


  // Calculate the pulse for PWM based on Equation 1 from the datasheet section
  // 7.3.5
  prescale += 1;
  pulselength *= prescale;
  pulselength /= 25000000;

  pulse /= pulselength;

  set_pwm(num, 0, (uint16_t)pulse);
  

}

uint8_t readPrescale(void) {
  return read8(PRESCALE_REG);
}

//uint8_t read8(uint8_t addr) {
//  i2c_start();
//  i2c_write(PCA9685_ADDR );
//  i2c_write(addr);
//  i2c_stop();
//
//  
//  return i2c_read(1);
//}

uint16_t read_Servo(uint8_t servo){
  uint16_t onTime=0;
  uint16_t offTime=0;
  uint16_t value =0;
  
  
  
  i2c_start();
  i2c_write(PCA9685_ADDR);
  i2c_write(LED0_ON_L + 4 * servo);
  i2c_stop();
  
  i2c_start();
  i2c_write(PCA9685_ADDR | 0x01);
  i2c_write(LED0_ON_L + 4 * servo);
  onTime = i2c_read(1);
  offTime = i2c_read(0);
 // onTime = (i2c_read(1)) | (i2c_read(0) <<8);
 // offTime = (i2c_read(1)) | (i2c_read(0) <<8);
  i2c_stop();
  
  value = (offTime << 8) | onTime;
  
  return value;
  
}