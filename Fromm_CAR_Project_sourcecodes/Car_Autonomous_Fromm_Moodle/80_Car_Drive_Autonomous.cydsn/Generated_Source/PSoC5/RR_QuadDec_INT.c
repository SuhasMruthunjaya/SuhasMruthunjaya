/*******************************************************************************
* File Name: RR_QuadDec_INT.c
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

#include "RR_QuadDec.h"
#include "RR_QuadDec_PVT.h"


volatile int32 RR_QuadDec_count32SoftPart = 0;


/*******************************************************************************
* FUNCTION NAME: void RR_QuadDec_ISR
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
*  RR_QuadDec_count32SoftPart - modified to update hi 16 bit for current
*  value of the 32-bit counter, when Counter size equal 32-bit.
*  RR_QuadDec_swStatus - modified with the updated values of STATUS
*  register.
*
*******************************************************************************/
CY_ISR( RR_QuadDec_ISR )
{
   uint8 RR_QuadDec_swStatus;

   RR_QuadDec_swStatus = RR_QuadDec_STATUS_REG;

    #ifdef RR_QuadDec_ISR_ENTRY_CALLBACK
        RR_QuadDec_ISR_EntryCallback();
    #endif /* RR_QuadDec_ISR_ENTRY_CALLBACK */

    /* User code required at start of ISR */
    /* `#START RR_QuadDec_ISR_START` */

    /* `#END` */

    if (0u != (RR_QuadDec_swStatus & RR_QuadDec_COUNTER_OVERFLOW))
    {
        RR_QuadDec_count32SoftPart += (int32) RR_QuadDec_COUNTER_MAX_VALUE;
    }
    else if (0u != (RR_QuadDec_swStatus & RR_QuadDec_COUNTER_UNDERFLOW))
    {
        RR_QuadDec_count32SoftPart -= (int32) RR_QuadDec_COUNTER_INIT_VALUE;
    }
    else
    {
        /* Nothing to do here */
    }
    
    if (0u != (RR_QuadDec_swStatus & RR_QuadDec_COUNTER_RESET))
    {
        RR_QuadDec_count32SoftPart = 0;
    }
    
    /* User code required at end of ISR */
    /* `#START RR_QuadDec_ISR_END` */

    /* `#END` */

    #ifdef RR_QuadDec_ISR_EXIT_CALLBACK
        RR_QuadDec_ISR_ExitCallback();
    #endif /* RR_QuadDec_ISR_EXIT_CALLBACK */
}


/* [] END OF FILE */
