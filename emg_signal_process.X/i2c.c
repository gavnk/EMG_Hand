
/* 
 * File:   
 * Author: 
 * Comments:
 * Revision history: 
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef XC_HEADER_TEMPLATE_H
#define	XC_HEADER_TEMPLATE_H

#include <xc.h> // include processor files - each processor file is guarded.  


#define _XTAL_FREQ 4000000
unsigned char data[20];


void i2c_init(void);
unsigned char i2c_write( uint8_t i2cWriteData );
uint8_t i2c_read( uint8_t ack );
void i2c_stop(void);
void i2c_repStart(void);
void i2c_start(void);
void i2c_waitForIdle(void);



/******************************************************************************************/

void i2c_waitForIdle(void){
  
 while (( SSP1CON2 & 0x1F ) | SSP1STATbits.R_nW ) {}; // wait for idle and not writing
}
/******************************************************************************************/
void i2c_start(void){
  
 i2c_waitForIdle();
 SSP1CON2bits.SEN=1;
}
/******************************************************************************************/
void i2c_repStart(void){
  
 i2c_waitForIdle();
 SSP1CON2bits.RSEN=1;
}
/******************************************************************************************/
void i2c_stop(void){
  
 i2c_waitForIdle();
 SSP1CON2bits.PEN=1;
}
/******************************************************************************************/

uint8_t i2c_read( uint8_t ack ){
  
uint8_t i2cReadData;
 i2c_waitForIdle();
 SSP1CON2bits.RCEN=1;  // enable i2c receive bit
 i2c_waitForIdle();
 i2cReadData = SSP1BUF;
 i2c_waitForIdle();
 
 if ( ack ) {
   SSP1CON2bits.ACKDT=0;				//ACK
 }
 else{
   SSP1CON2bits.ACKDT=1;				//NACK
 }
 SSP1CON2bits.ACKEN=1;               // send acknowledge sequence
  
 return( i2cReadData );
}
/******************************************************************************************/

uint8_t i2c_write( uint8_t i2cWriteData ){
  
 i2c_waitForIdle();
 SSP1BUF = i2cWriteData;
 
 return ( ! SSP1CON2bits.ACKSTAT  ); // function returns '1' if transmission is acknowledged
}
/******************************************************************************************/


void i2c_init(void){
  
 // Do in main code TRISC = 0b00011000;       // set SCL and SDA pins as inputs
 SSP1CON1 = 0x38;            //  I2C Host mode, clock = FOSC / (4 * (SSPxADD+1))  ,  SSPEN enabled
 SSP1CON2 = 0x00;
 SSP1ADD = 0x09;            // 100k at 4Mhz clock
 SSP1STATbits.CKE=1;        // use I2C levels      
 SSP1STATbits.SMP=1;        // disable slew rate control  

}

/*****************************************************************************************/


#ifdef	__cplusplus
extern "C" {
#endif /* __cplusplus */

    // TODO If C++ is being used, regular C code needs function names to have C 
    // linkage so the functions can be used by the c code. 

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif	/* XC_HEADER_TEMPLATE_H */

