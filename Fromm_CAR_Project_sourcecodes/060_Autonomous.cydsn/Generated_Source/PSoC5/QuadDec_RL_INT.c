/*******************************************************************************
* File Name: QuadDec_RL_INT.c
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

#include "QuadDec_RL.h"
#include "QuadDec_RL_PVT.h"


volatile int32 QuadDec_RL_count32SoftPart = 0;


/*******************************************************************************
* FUNCTION NAME: void QuadDec_RL_ISR
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
*  QuadDec_RL_count32SoftPart - modified to update hi 16 bit for current
*  value of the 32-bit counter, when Counter size equal 32-bit.
*  QuadDec_RL_swStatus - modified with the updated values of STATUS
*  register.
*
*******************************************************************************/
CY_ISR( QuadDec_RL_ISR )
{
   uint8 QuadDec_RL_swStatus;

   QuadDec_RL_swStatus = QuadDec_RL_STATUS_REG;

    #ifdef QuadDec_RL_ISR_ENTRY_CALLBACK
        QuadDec_RL_ISR_EntryCallback();
    #endif /* QuadDec_RL_ISR_ENTRY_CALLBACK */

    /* User code required at start of ISR */
    /* `#START QuadDec_RL_ISR_START` */

    /* `#END` */

    if (0u != (QuadDec_RL_swStatus & QuadDec_RL_COUNTER_OVERFLOW))
    {
        QuadDec_RL_count32SoftPart += (int32) QuadDec_RL_COUNTER_MAX_VALUE;
    }
    else if (0u != (QuadDec_RL_swStatus & QuadDec_RL_COUNTER_UNDERFLOW))
    {
        QuadDec_RL_count32SoftPart -= (int32) QuadDec_RL_COUNTER_INIT_VALUE;
    }
    else
    {
        /* Nothing to do here */
    }
    
    if (0u != (QuadDec_RL_swStatus & QuadDec_RL_COUNTER_RESET))
    {
        QuadDec_RL_count32SoftPart = 0;
    }
    
    /* User code required at end of ISR */
    /* `#START QuadDec_RL_ISR_END` */

    /* `#END` */

    #ifdef QuadDec_RL_ISR_EXIT_CALLBACK
        QuadDec_RL_ISR_ExitCallback();
    #endif /* QuadDec_RL_ISR_EXIT_CALLBACK */
}


/* [] END OF FILE */