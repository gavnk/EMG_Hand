/**
  EMG Signal Processing file 

  @File Name
    signal_processing.c

  @Description
    This is the implementation file for processing of EMG Signal data on an EMG click by MikroElektronika       
    This file performs the signal processing operations on the values obtained from the three Circular Buffer Operations
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
#include "moving_avg_filter.h"
#include "signal_buffer.h"
#include "peak_filter.h"
#include "signal_processing.h"
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>

/*******************************************************************************************************/
/*******************************************************************************************************/

/**
  Section: Processing Modules
*/


// Peak Filter returns the neutral_datapoint calculated using (highest_peak+lowest_peak)/2. 
// Highest & Lowest peaks are the maximum and minimum among the elements present in the "Peak Filter Buffer" (pk_data[PK_DATA_WINDOW])
uint16_t get_neutral_peaktopeak(uint16_t datapoint) 
{
    // Insert every new data point into the Peak Filter Buffer
    pkdata_insert(datapoint);

    // If buffer is full, remove the first inserted data (FIFO)
    if (pkdata_isfull()) 
    {
        pkdata_remove();
    }

    // Start off with first data point for highest peak
    uint16_t highest_peak = pk_data[pk_front];
    uint16_t lowest_peak = pk_data[pk_front];
    uint16_t neutral;
    
    uint8_t i;
    
    // Running through only the valid elements of the array
    for (i = pk_front; i != pk_rear; i = (i + 1) % PK_DATA_WINDOW) {
        if (pk_data[i] > highest_peak)
        {
            // Reassign variable highest_peak if a new highest is found among elements of "Peak Filter buffer"
            highest_peak = pk_data[i];
        }
        if (pk_data[i] < lowest_peak) 
        {
            // Reassign variable lowest_peak if a new lowest is found among elements of "Peak Filter buffer"
            lowest_peak = pk_data[i];
        }
    }

    // Calculate neutral and return
    neutral = (highest_peak + lowest_peak) / 2;
    return neutral;
}

/*******************************************************************************************************/
/*******************************************************************************************************/

// Moving Average Filter returns the average of data points present in the "Moving Average Buffer"
// The sum is updated for every new data point added(or/and removed)
float get_moving_average(uint16_t datapoint)
{
    madata_insert(datapoint);
    
    // ma_window_sum starts at 0 and every new data point is added to this sum
    ma_window_sum += datapoint;

    if (madata_isfull()) 
    {
        // When the buffer is full, the last element is subtracted from the sum and then removed from the buffer
        ma_window_sum -= ma_data[ma_front];
        madata_remove();
    }

    // MA_DATA_WINDOW is 1 more than intended Moving Average Window
    return ma_window_sum / (MA_DATA_WINDOW-1);
}
/**
 End of File
*/