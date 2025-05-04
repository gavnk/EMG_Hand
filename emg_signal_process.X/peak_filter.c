/**
  EMG Peak to Peak Filter file 

  @File Name
    peak_filter.c

  @Description
    This is the implementation file for processing of EMG Signal data from an EMG click by MikroElektronika       
    This file buffers and performs operations on the pk_data Circular Buffer 
    The pk_data buffer is helpful in calculating a neutral peak value for a certain window of acquired samples
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
#include "peak_filter.h"
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>

/*******************************************************************************************************/
/*******************************************************************************************************/

/**
  Section: Circular Buffer Functions
*/

// Returns true if Circular Buffer is full
bool pkdata_isfull(void)
{
    if ((pk_front == pk_rear + 1) || (pk_front == 0 && pk_rear == PK_DATA_WINDOW - 1))
        return true;
    else
        return false;
}

// Returns true if Circular Buffer is empty
bool pkdata_isempty(void)
{
    if (pk_front == -1)
        return true;
    else
        return false;
}

// Inserts element into the Circular Buffer
bool pkdata_insert(uint16_t element) 
{
    if (pkdata_isfull()) {
        // Can't insert data because buffer is full
        return false;
    } else {
        if (pk_front == -1)
            pk_front = 0;
        pk_rear = (pk_rear + 1) % PK_DATA_WINDOW;
        pk_data[pk_rear] = element;
        return true;
    }
}

// Removes element from the Circular Buffer
bool pkdata_remove(void)
{
    uint16_t element;
    if (pkdata_isempty()) {
        return false;
    } else {
        element = pk_data[pk_front];
        if (pk_front == pk_rear) {
            pk_front = -1;
            pk_rear = -1;
        } else {
            pk_front = (pk_front + 1) % PK_DATA_WINDOW;
        }
        return true;
    }
}
/**
 End of File
*/