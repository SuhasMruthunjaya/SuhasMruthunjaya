/*******************************************************************************
* File Name: ENGINE_DECODER_INT.c
* Version 3.0
*
* Description:
*  This file contains the Interrupt Service Routine (ISR) for the Quadrature
*  Decoder component.
*
* Note:
*  None.
*
********************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "ENGINE_DECODER.h"
#include "ENGINE_DECODER_PVT.h"
#include "cyapicallbacks.h"

volatile int32 ENGINE_DECODER_count32SoftPart = 0;


/*******************************************************************************
* FUNCTION NAME: void ENGINE_DECODER_ISR
********************************************************************************
*
* Summary:
*  Interrupt Service Routine for Quadrature Decoder Component.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global variables:
*  ENGINE_DECODER_count32SoftPart - modified to update hi 16 bit for current
*  value of the 32-bit counter, when Counter size equal 32-bit.
*  ENGINE_DECODER_swStatus - modified with the updated values of STATUS
*  register.
*
*******************************************************************************/
CY_ISR( ENGINE_DECODER_ISR )
{
   uint8 ENGINE_DECODER_swStatus;

   ENGINE_DECODER_swStatus = ENGINE_DECODER_STATUS_REG;

    #ifdef ENGINE_DECODER_ISR_ENTRY_CALLBACK
        ENGINE_DECODER_ISR_EntryCallback();
    #endif /* ENGINE_DECODER_ISR_ENTRY_CALLBACK */

    /* User code required at start of ISR */
    /* `#START ENGINE_DECODER_ISR_START` */

    /* `#END` */

    if (0u != (ENGINE_DECODER_swStatus & ENGINE_DECODER_COUNTER_OVERFLOW))
    {
        ENGINE_DECODER_count32SoftPart += (int32) ENGINE_DECODER_COUNTER_MAX_VALUE;
    }
    else if (0u != (ENGINE_DECODER_swStatus & ENGINE_DECODER_COUNTER_UNDERFLOW))
    {
        ENGINE_DECODER_count32SoftPart -= (int32) ENGINE_DECODER_COUNTER_INIT_VALUE;
    }
    else
    {
        /* Nothing to do here */
    }
    
    if (0u != (ENGINE_DECODER_swStatus & ENGINE_DECODER_COUNTER_RESET))
    {
        ENGINE_DECODER_count32SoftPart = 0;
    }
    
    /* User code required at end of ISR */
    /* `#START ENGINE_DECODER_ISR_END` */

    /* `#END` */

    #ifdef ENGINE_DECODER_ISR_EXIT_CALLBACK
        ENGINE_DECODER_ISR_ExitCallback();
    #endif /* ENGINE_DECODER_ISR_EXIT_CALLBACK */
}


/* [] END OF FILE */
