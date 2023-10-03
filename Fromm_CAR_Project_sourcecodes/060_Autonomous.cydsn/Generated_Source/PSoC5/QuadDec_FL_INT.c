/*******************************************************************************
* File Name: QuadDec_FL_INT.c
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

#include "QuadDec_FL.h"
#include "QuadDec_FL_PVT.h"


volatile int32 QuadDec_FL_count32SoftPart = 0;


/*******************************************************************************
* FUNCTION NAME: void QuadDec_FL_ISR
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
*  QuadDec_FL_count32SoftPart - modified to update hi 16 bit for current
*  value of the 32-bit counter, when Counter size equal 32-bit.
*  QuadDec_FL_swStatus - modified with the updated values of STATUS
*  register.
*
*******************************************************************************/
CY_ISR( QuadDec_FL_ISR )
{
   uint8 QuadDec_FL_swStatus;

   QuadDec_FL_swStatus = QuadDec_FL_STATUS_REG;

    #ifdef QuadDec_FL_ISR_ENTRY_CALLBACK
        QuadDec_FL_ISR_EntryCallback();
    #endif /* QuadDec_FL_ISR_ENTRY_CALLBACK */

    /* User code required at start of ISR */
    /* `#START QuadDec_FL_ISR_START` */

    /* `#END` */

    if (0u != (QuadDec_FL_swStatus & QuadDec_FL_COUNTER_OVERFLOW))
    {
        QuadDec_FL_count32SoftPart += (int32) QuadDec_FL_COUNTER_MAX_VALUE;
    }
    else if (0u != (QuadDec_FL_swStatus & QuadDec_FL_COUNTER_UNDERFLOW))
    {
        QuadDec_FL_count32SoftPart -= (int32) QuadDec_FL_COUNTER_INIT_VALUE;
    }
    else
    {
        /* Nothing to do here */
    }
    
    if (0u != (QuadDec_FL_swStatus & QuadDec_FL_COUNTER_RESET))
    {
        QuadDec_FL_count32SoftPart = 0;
    }
    
    /* User code required at end of ISR */
    /* `#START QuadDec_FL_ISR_END` */

    /* `#END` */

    #ifdef QuadDec_FL_ISR_EXIT_CALLBACK
        QuadDec_FL_ISR_ExitCallback();
    #endif /* QuadDec_FL_ISR_EXIT_CALLBACK */
}


/* [] END OF FILE */
