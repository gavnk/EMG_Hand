/**
  EMG Signal Buffer file 

  @File Name
    signal_buffer.c

  @Description
    This is the implementation file for processing of EMG Signal data from an EMG click by MikroElektronika.
    This file buffers and performs operations on the EMG data as it is being acquired and sampled.
 
  @References
   https://www.mikroe.com/emg-click
   https://en.wikipedia.org/wiki/Circular_buffer
   https://github.com/cancui/EMG-Signal-Processing-Library 
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

/*******************************************************************************************************/
/*******************************************************************************************************/

/**
  Section: Included Files
*/
#include "signal_buffer.h"
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>

/*******************************************************************************************************/
/*******************************************************************************************************/

/**
  Section: Circular Buffer Functions
*/

// Returns true if Circular Buffer is full
bool sbuf_isfull(void) 
{
    if ((sb_front == sb_rear + 1) || (sb_front == 0 && sb_rear == SB_DATA_WINDOW - 1))
        return true;
    else
        return false;
}

// Returns true if Circular Buffer is empty
bool sbuf_isempty(void) 
{
    if (sb_front == -1)
        return true;
    else
        return false;
}

// Inserts element into the Circular Buffer
bool sbuf_insert(uint16_t element) 
{
    if (sbuf_isfull()) {
        // Can't insert data since buffer is full
        return false;
    } 
	
	else {
		
        if (sb_front == -1)
            sb_front = 0;
		
        sb_rear = (sb_rear + 1) % SB_DATA_WINDOW;
        sb_data[sb_rear] = element;
        return true;
    }
}

// Removes element from the Circular Buffer
bool sbuf_remove(void) 
{
    uint16_t element;
	
    if (sbuf_isempty()) {
        return false;
    } 
	
	else {
        element = sb_data[sb_front];
        if (sb_front == sb_rear) {
            sb_front = -1;
            sb_rear = -1;
        } else {
            sb_front = (sb_front + 1) % SB_DATA_WINDOW;
        }
        return true;
    }
}

// Returns the first inserted element (FIFO) from the Circular Buffer
uint16_t sbuf_peek(void)
{
  return sb_data[sb_front];
}
/**
 End of File
*/