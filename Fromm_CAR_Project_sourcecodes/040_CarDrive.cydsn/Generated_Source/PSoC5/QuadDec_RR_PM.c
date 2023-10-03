/*******************************************************************************
* File Name: QuadDec_RR_PM.c
* Version 3.0
*
* Description:
*  This file contains the setup, control and status commands to support 
*  component operations in low power mode.  
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

static QuadDec_RR_BACKUP_STRUCT QuadDec_RR_backup = {0u};


/*******************************************************************************
* Function Name: QuadDec_RR_SaveConfig
********************************************************************************
* Summary:
*  Saves the current user configuration of the component.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void QuadDec_RR_SaveConfig(void) 
{
    #if (QuadDec_RR_COUNTER_SIZE == QuadDec_RR_COUNTER_SIZE_8_BIT)
        QuadDec_RR_Cnt8_SaveConfig();
    #else 
        /* (QuadDec_RR_COUNTER_SIZE == QuadDec_RR_COUNTER_SIZE_16_BIT) || 
         * (QuadDec_RR_COUNTER_SIZE == QuadDec_RR_COUNTER_SIZE_32_BIT)
         */
        QuadDec_RR_Cnt16_SaveConfig();
    #endif /* (QuadDec_RR_COUNTER_SIZE == QuadDec_RR_COUNTER_SIZE_8_BIT) */
}


/*******************************************************************************
* Function Name: QuadDec_RR_RestoreConfig
********************************************************************************
* Summary:
*  Restores the current user configuration of the component.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void QuadDec_RR_RestoreConfig(void) 
{
    #if (QuadDec_RR_COUNTER_SIZE == QuadDec_RR_COUNTER_SIZE_8_BIT)
        QuadDec_RR_Cnt8_RestoreConfig();
    #else 
        /* (QuadDec_RR_COUNTER_SIZE == QuadDec_RR_COUNTER_SIZE_16_BIT) || 
         * (QuadDec_RR_COUNTER_SIZE == QuadDec_RR_COUNTER_SIZE_32_BIT) 
         */
        QuadDec_RR_Cnt16_RestoreConfig();
    #endif /* (QuadDec_RR_COUNTER_SIZE == QuadDec_RR_COUNTER_SIZE_8_BIT) */
}


/*******************************************************************************
* Function Name: QuadDec_RR_Sleep
********************************************************************************
* 
* Summary:
*  Prepare Quadrature Decoder Component goes to sleep.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  QuadDec_RR_backup - modified when non-retention registers are saved.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void QuadDec_RR_Sleep(void) 
{
    if (0u != (QuadDec_RR_SR_AUX_CONTROL & QuadDec_RR_INTERRUPTS_ENABLE))
    {
        QuadDec_RR_backup.enableState = 1u;
    }
    else /* The Quadrature Decoder Component is disabled */
    {
        QuadDec_RR_backup.enableState = 0u;
    }

    QuadDec_RR_Stop();
    QuadDec_RR_SaveConfig();
}


/*******************************************************************************
* Function Name: QuadDec_RR_Wakeup
********************************************************************************
*
* Summary:
*  Prepare Quadrature Decoder Component to wake up.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  QuadDec_RR_backup - used when non-retention registers are restored.
*
*******************************************************************************/
void QuadDec_RR_Wakeup(void) 
{
    QuadDec_RR_RestoreConfig();

    if (QuadDec_RR_backup.enableState != 0u)
    {
        #if (QuadDec_RR_COUNTER_SIZE == QuadDec_RR_COUNTER_SIZE_8_BIT)
            QuadDec_RR_Cnt8_Enable();
        #else 
            /* (QuadDec_RR_COUNTER_SIZE == QuadDec_RR_COUNTER_SIZE_16_BIT) || 
            *  (QuadDec_RR_COUNTER_SIZE == QuadDec_RR_COUNTER_SIZE_32_BIT) 
            */
            QuadDec_RR_Cnt16_Enable();
        #endif /* (QuadDec_RR_COUNTER_SIZE == QuadDec_RR_COUNTER_SIZE_8_BIT) */

        /* Enable component's operation */
        QuadDec_RR_Enable();
    } /* Do nothing if component's block was disabled before */
}


/* [] END OF FILE */

