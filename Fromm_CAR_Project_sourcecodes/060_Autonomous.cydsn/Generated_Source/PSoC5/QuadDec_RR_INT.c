/*******************************************************************************
* File Name: QuadDec_RR_INT.c
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

#include "QuadDec_RR.h"
#include "QuadDec_RR_PVT.h"


volatile int32 QuadDec_RR_count32SoftPart = 0;


/*******************************************************************************
* FUNCTION NAME: void QuadDec_RR_ISR
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
*  QuadDec_RR_count32SoftPart - modified to update hi 16 bit for current
*  value of the 32-bit counter, when Counter size equal 32-bit.
*  QuadDec_RR_swStatus - modified with the updated values of STATUS
*  register.
*
*******************************************************************************/
CY_ISR( QuadDec_RR_ISR )
{
   uint8 QuadDec_RR_swStatus;

   QuadDec_RR_swStatus = QuadDec_RR_STATUS_REG;

    #ifdef QuadDec_RR_ISR_ENTRY_CALLBACK
        QuadDec_RR_ISR_EntryCallback();
    #endif /* QuadDec_RR_ISR_ENTRY_CALLBACK */

    /* User code required at start of ISR */
    /* `#START QuadDec_RR_ISR_START` */

    /* `#END` */

    if (0u != (QuadDec_RR_swStatus & QuadDec_RR_COUNTER_OVERFLOW))
    {
        QuadDec_RR_count32SoftPart += (int32) QuadDec_RR_COUNTER_MAX_VALUE;
    }
    else if (0u != (QuadDec_RR_swStatus & QuadDec_RR_COUNTER_UNDERFLOW))
    {
        QuadDec_RR_count32SoftPart -= (int32) QuadDec_RR_COUNTER_INIT_VALUE;
    }
    else
    {
        /* Nothing to do here */
    }
    
    if (0u != (QuadDec_RR_swStatus & QuadDec_RR_COUNTER_RESET))
    {
        QuadDec_RR_count32SoftPart = 0;
    }
    
    /* User code required at end of ISR */
    /* `#START QuadDec_RR_ISR_END` */

    /* `#END` */

    #ifdef QuadDec_RR_ISR_EXIT_CALLBACK
        QuadDec_RR_ISR_ExitCallback();
    #endif /* QuadDec_RR_ISR_EXIT_CALLBACK */
}


/* [] END OF FILE */
