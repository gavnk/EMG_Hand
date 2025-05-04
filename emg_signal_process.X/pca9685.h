/* 
 * File:   pca9685.h
 * Author: M73267
 *
 * Created on 19 April 2023, 09:44
 */
#include <xc.h>



void set_pwm_freq(float freq);

void set_pwm(uint8_t channel, uint16_t on_time, uint16_t off_time);

void set_servo_angle(uint8_t channel, float angle);

void pca_init(unsigned int addr);

void pca_write(unsigned int ledn, unsigned int on_count, unsigned int off_count);


void pca9685_init(void) ;

uint8_t readPrescale(void);

void writeMicroseconds (uint8_t num, uint16_t Microseconds);

uint8_t readPrescale(void) ;

uint8_t read8(uint8_t addr);

uint16_t read_Servo(uint8_t servo);










#ifndef PCA9685_H
#define	PCA9685_H

#ifdef	__cplusplus
extern "C" {
#endif




#ifdef	__cplusplus
}
#endif

#endif	/* PCA9685_H */

