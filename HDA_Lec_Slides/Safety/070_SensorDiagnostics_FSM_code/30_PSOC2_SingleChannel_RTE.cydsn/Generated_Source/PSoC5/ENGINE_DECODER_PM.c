/*******************************************************************************
* File Name: ENGINE_DECODER_PM.c
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

#include "ENGINE_DECODER.h"

static ENGINE_DECODER_BACKUP_STRUCT ENGINE_DECODER_backup = {0u};


/*******************************************************************************
* Function Name: ENGINE_DECODER_SaveConfig
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
void ENGINE_DECODER_SaveConfig(void) 
{
    #if (ENGINE_DECODER_COUNTER_SIZE == ENGINE_DECODER_COUNTER_SIZE_8_BIT)
        ENGINE_DECODER_Cnt8_SaveConfig();
    #else 
        /* (ENGINE_DECODER_COUNTER_SIZE == ENGINE_DECODER_COUNTER_SIZE_16_BIT) || 
         * (ENGINE_DECODER_COUNTER_SIZE == ENGINE_DECODER_COUNTER_SIZE_32_BIT)
         */
        ENGINE_DECODER_Cnt16_SaveConfig();
    #endif /* (ENGINE_DECODER_COUNTER_SIZE == ENGINE_DECODER_COUNTER_SIZE_8_BIT) */
}


/*******************************************************************************
* Function Name: ENGINE_DECODER_RestoreConfig
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
void ENGINE_DECODER_RestoreConfig(void) 
{
    #if (ENGINE_DECODER_COUNTER_SIZE == ENGINE_DECODER_COUNTER_SIZE_8_BIT)
        ENGINE_DECODER_Cnt8_RestoreConfig();
    #else 
        /* (ENGINE_DECODER_COUNTER_SIZE == ENGINE_DECODER_COUNTER_SIZE_16_BIT) || 
         * (ENGINE_DECODER_COUNTER_SIZE == ENGINE_DECODER_COUNTER_SIZE_32_BIT) 
         */
        ENGINE_DECODER_Cnt16_RestoreConfig();
    #endif /* (ENGINE_DECODER_COUNTER_SIZE == ENGINE_DECODER_COUNTER_SIZE_8_BIT) */
}


/*******************************************************************************
* Function Name: ENGINE_DECODER_Sleep
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
*  ENGINE_DECODER_backup - modified when non-retention registers are saved.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void ENGINE_DECODER_Sleep(void) 
{
    if (0u != (ENGINE_DECODER_SR_AUX_CONTROL & ENGINE_DECODER_INTERRUPTS_ENABLE))
    {
        ENGINE_DECODER_backup.enableState = 1u;
    }
    else /* The Quadrature Decoder Component is disabled */
    {
        ENGINE_DECODER_backup.enableState = 0u;
    }

    ENGINE_DECODER_Stop();
    ENGINE_DECODER_SaveConfig();
}


/*******************************************************************************
* Function Name: ENGINE_DECODER_Wakeup
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
*  ENGINE_DECODER_backup - used when non-retention registers are restored.
*
*******************************************************************************/
void ENGINE_DECODER_Wakeup(void) 
{
    ENGINE_DECODER_RestoreConfig();

    if (ENGINE_DECODER_backup.enableState != 0u)
    {
        #if (ENGINE_DECODER_COUNTER_SIZE == ENGINE_DECODER_COUNTER_SIZE_8_BIT)
            ENGINE_DECODER_Cnt8_Enable();
        #else 
            /* (ENGINE_DECODER_COUNTER_SIZE == ENGINE_DECODER_COUNTER_SIZE_16_BIT) || 
            *  (ENGINE_DECODER_COUNTER_SIZE == ENGINE_DECODER_COUNTER_SIZE_32_BIT) 
            */
            ENGINE_DECODER_Cnt16_Enable();
        #endif /* (ENGINE_DECODER_COUNTER_SIZE == ENGINE_DECODER_COUNTER_SIZE_8_BIT) */

        /* Enable component's operation */
        ENGINE_DECODER_Enable();
    } /* Do nothing if component's block was disabled before */
}


/* [] END OF FILE */

