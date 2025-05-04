/**
  EMG Signal Processing Header file 

  @File Name
    signal_processing.h

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


// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef _SIGNAL_PROCESSING_H
#define	_SIGNAL_PROCESSING_H

/*******************************************************************************************************/
/*******************************************************************************************************/


/**
  Section: Included Files
*/
#include <xc.h> // include processor files - each processor file is guarded.  
#include "mcc_generated_files/mcc.h"
#include "signal_buffer.h"
#include "signal_buffer.h"


/*******************************************************************************************************/
/*******************************************************************************************************/

/**
 Section: Function definitions
*/

/**
  @Function
    get_neutral_peaktopeak
 
  @Description
    Returns the Neutral Peak value for every data point inserted in a window of fixed length. 
    Neutral Value is the Average of the highest and lowest peaks in the given window

  @Param
    Type: uint16_t
    Value: New data point acquired from the EMG Signals for neutral peak calculation 

  @Returns
    Type: uint16_t
    Value: Neutral Peak 

 */
uint16_t get_neutral_peaktopeak(uint16_t datapoint);


/*******************************************************************************************************/
/*******************************************************************************************************/

/**
  @Function
    get_moving_average
 
  @Description
    Returns the Moving Average value for every data point inserted in a window of fixed length. 
    The sum is updated for every new data point added(or/and removed)

  @Param
    Type: uint16_t
    Value: New data point acquired from the EMG Signals to calculate a Moving Average for

  @Returns
    Type: float
    Value: Moving Average value

 */
float get_moving_average(uint16_t datapoint);


#endif	/* _SIGNAL_PROCESSING_H */
/**
 End of File
*/
