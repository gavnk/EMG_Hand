



#include <xc.h> // include processor files - each processor file is guarded.  


#define _XTAL_FREQ 4000000



void i2c_init(void);
uint8_t i2c_write( uint8_t i2cWriteData );
uint8_t i2c_read( uint8_t ack );
void i2c_stop(void);
void i2c_repStart(void);
void i2c_start(void);
void i2c_waitForIdle(void);