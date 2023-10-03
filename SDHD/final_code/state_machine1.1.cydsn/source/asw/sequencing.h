/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#ifndef SEQUENCING_H
#define SEQUENCING_H

    
#include "project.h"
#include "stdlib.h"
#include "uart_bsw.h"
/*****************************************************************************/
/* Global pre-processor symbols/macros and type declarations                 */
/*****************************************************************************/
#define  BUTTON_PRESSED    1
#define  BUTTON_NOTPRESSED 0
    
    
    
//Defining enum for the states 
typedef enum{
    IDLE,
    SAMPLING,
    UART_TRANSFER
}SEQUENCING_t;




/*****************************************************************************/
/* Extern global variables                                                   */
/*****************************************************************************/

extern uint16_t global_count;


/*****************************************************************************/
/* API functions                                                             */
/*****************************************************************************/
/******************* Debugging Aid*******************************/
/**
 * Function consists of State Machine logic to send ADC values to Matlab via UART communication
 * @param SEQUENCING_t* state - IN State of the Sequence passed as address
 * @return RC_SUCCESS if all ok
 */
RC_t State_Machine(SEQUENCING_t* state);

/**
 * Read ADC values and store it in an uint16 array of size 1024
 * @param uint16_t *ADC_array - IN To store the ADC values
 * @return RC_SUCCESS if all ok
 */
RC_t ReadAndStoreADC(uint16_t *ADC_array);


#endif /* FILE_H */