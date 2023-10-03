/*******************************************************************************
* File Name: RL_QuadDec_INT.c
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

#include "RL_QuadDec.h"
#include "RL_QuadDec_PVT.h"


volatile int32 RL_QuadDec_count32SoftPart = 0;


/*******************************************************************************
* FUNCTION NAME: void RL_QuadDec_ISR
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
*  RL_QuadDec_count32SoftPart - modified to update hi 16 bit for current
*  value of the 32-bit counter, when Counter size equal 32-bit.
*  RL_QuadDec_swStatus - modified with the updated values of STATUS
*  register.
*
*******************************************************************************/
CY_ISR( RL_QuadDec_ISR )
{
   uint8 RL_QuadDec_swStatus;

   RL_QuadDec_swStatus = RL_QuadDec_STATUS_REG;

    #ifdef RL_QuadDec_ISR_ENTRY_CALLBACK
        RL_QuadDec_ISR_EntryCallback();
    #endif /* RL_QuadDec_ISR_ENTRY_CALLBACK */

    /* User code required at start of ISR */
    /* `#START RL_QuadDec_ISR_START` */

    /* `#END` */

    if (0u != (RL_QuadDec_swStatus & RL_QuadDec_COUNTER_OVERFLOW))
    {
        RL_QuadDec_count32SoftPart += (int32) RL_QuadDec_COUNTER_MAX_VALUE;
    }
    else if (0u != (RL_QuadDec_swStatus & RL_QuadDec_COUNTER_UNDERFLOW))
    {
        RL_QuadDec_count32SoftPart -= (int32) RL_QuadDec_COUNTER_INIT_VALUE;
    }
    else
    {
        /* Nothing to do here */
    }
    
    if (0u != (RL_QuadDec_swStatus & RL_QuadDec_COUNTER_RESET))
    {
        RL_QuadDec_count32SoftPart = 0;
    }
    
    /* User code required at end of ISR */
    /* `#START RL_QuadDec_ISR_END` */

    /* `#END` */

    #ifdef RL_QuadDec_ISR_EXIT_CALLBACK
        RL_QuadDec_ISR_ExitCallback();
    #endif /* RL_QuadDec_ISR_EXIT_CALLBACK */
}


/* [] END OF FILE */
