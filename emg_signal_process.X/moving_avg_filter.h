/**
  EMG Moving Average Filter Header file 

  @File Name
    moving_avg_filter.h

  @Description
    This is the implementation file for processing of EMG Signal data from an EMG click by MikroElektronika       
    This file buffers and performs operations on the ma_data Circular Buffer 
    The ma_data buffer is helpful in calculating a moving average value for a certain window of acquired samples
*/

/* Microchip Technology Inc. and its subsidiaries.  You may use this software 
 * and any derivatives exclusively with Microchip products. 
 * 
 * THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS".  NO WARRANTIES, WHETHER 
 * EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED 
 * WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A 
 * PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION 
 * WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION. 
 *
 * IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
 * INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
 * WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS 
 * BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE.  TO THE 
 * FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS 
 * IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF 
 * ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 *
 * MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE 
 * TERMS. 
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef _MOVING_AVERAGE_H
#define	_MOVING_AVERAGE_H

/*******************************************************************************************************/
/*******************************************************************************************************/


/**
  Section: Included Files
*/
#include <xc.h> // include processor files - each processor file is guarded.  
#include "mcc_generated_files/mcc.h"
#include "signal_buffer.h"


/*******************************************************************************************************/
/*******************************************************************************************************/

/**
 Section: Macro Definitions
*/

// Size of (circular) buffer for Moving Average Filter. Considers last 0.5 seconds of data for Moving Average 
//#define MA_DATA_WINDOW ((int)(SAMPLE_FREQUENCY * 0.5)+1)
#define MA_DATA_WINDOW 26

/*******************************************************************************************************/
/*******************************************************************************************************/


/**
 Section: Variable Declarations
*/

// Buffer for Moving Average Filter and indices for the Circular Buffer
uint16_t ma_data[MA_DATA_WINDOW];

/*
 Arrays in C start from the Index 0. A 0 index on the circular buffer indicates there is already an element present in Array[0] 
 Hence we begin the front and rear pointers of each circular buffer with '-1', so that every advance in the pointer indicates the buffer has an element
 This implementation is used for all three circular buffers used : sb_data (Signal Buffer), pk_data (Peak to Peak Filter) and, ma_data (Moving Average Filter) 
 */
int8_t ma_front = -1;
int8_t ma_rear = -1;

uint16_t ma_window_sum = 0;


/*******************************************************************************************************/
/*******************************************************************************************************/


/**
  Section: Function definitions
*/ 

/**
  @Function
    madata_isfull
  
  @Description
    Boolean function returns true if the Moving Avg Buffer is Full by checking the position of the front and rear pointers of the buffer

  @Param
    None

  @Returns
    Type: Boolean 

 */
bool madata_isfull(void);



/*******************************************************************************************************/
/*******************************************************************************************************/



/**
  @Function
    madata_isempty
  
  @Description
    Boolean function returns true if the Moving Avg Buffer is Empty by checking the position of the front and rear pointers of the buffer

  @Param
    None

  @Returns
    Type: Boolean 

 */
bool madata_isempty(void);



/*******************************************************************************************************/
/*******************************************************************************************************/



/**
  @Function
    madata_insert
  
  @Description
    Inserts the passed data element into the last index of the Moving Avg Buffer.
    Boolean function returns false if the Moving Avg Buffer is full and new data cannot be inserted.
    Returns true if new data passed has been successfully inserted into the Moving Avg Buffer.

  @Param
    Type : uint16_t
    Value: Data to be inserted into the Buffer 

  @Returns
    Type: Boolean 

 */
bool madata_insert(uint16_t element);



/*******************************************************************************************************/
/*******************************************************************************************************/



/**
  @Function
    madata_remove
  
  @Description
    Removes the first element from the Circular Buffer(FIFO).
    Boolean function returns false if the Moving Avg Buffer is Empty and there is no data to remove.
    Returns true if the first element has been successfully removed from the Moving Avg Buffer.

  @Param
    None
 
  @Returns
    Boolean Value

 */
bool madata_remove(void);

#endif	/* _MOVING_AVERAGE_H */
/**
 End of File
*/
