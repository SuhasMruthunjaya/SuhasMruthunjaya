/*******************************************************************************
* File Name: FR_QuadDec_INT.c
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

#include "FR_QuadDec.h"
#include "FR_QuadDec_PVT.h"


volatile int32 FR_QuadDec_count32SoftPart = 0;


/*******************************************************************************
* FUNCTION NAME: void FR_QuadDec_ISR
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
*  FR_QuadDec_count32SoftPart - modified to update hi 16 bit for current
*  value of the 32-bit counter, when Counter size equal 32-bit.
*  FR_QuadDec_swStatus - modified with the updated values of STATUS
*  register.
*
*******************************************************************************/
CY_ISR( FR_QuadDec_ISR )
{
   uint8 FR_QuadDec_swStatus;

   FR_QuadDec_swStatus = FR_QuadDec_STATUS_REG;

    #ifdef FR_QuadDec_ISR_ENTRY_CALLBACK
        FR_QuadDec_ISR_EntryCallback();
    #endif /* FR_QuadDec_ISR_ENTRY_CALLBACK */

    /* User code required at start of ISR */
    /* `#START FR_QuadDec_ISR_START` */

    /* `#END` */

    if (0u != (FR_QuadDec_swStatus & FR_QuadDec_COUNTER_OVERFLOW))
    {
        FR_QuadDec_count32SoftPart += (int32) FR_QuadDec_COUNTER_MAX_VALUE;
    }
    else if (0u != (FR_QuadDec_swStatus & FR_QuadDec_COUNTER_UNDERFLOW))
    {
        FR_QuadDec_count32SoftPart -= (int32) FR_QuadDec_COUNTER_INIT_VALUE;
    }
    else
    {
        /* Nothing to do here */
    }
    
    if (0u != (FR_QuadDec_swStatus & FR_QuadDec_COUNTER_RESET))
    {
        FR_QuadDec_count32SoftPart = 0;
    }
    
    /* User code required at end of ISR */
    /* `#START FR_QuadDec_ISR_END` */

    /* `#END` */

    #ifdef FR_QuadDec_ISR_EXIT_CALLBACK
        FR_QuadDec_ISR_ExitCallback();
    #endif /* FR_QuadDec_ISR_EXIT_CALLBACK */
}


/* [] END OF FILE */
