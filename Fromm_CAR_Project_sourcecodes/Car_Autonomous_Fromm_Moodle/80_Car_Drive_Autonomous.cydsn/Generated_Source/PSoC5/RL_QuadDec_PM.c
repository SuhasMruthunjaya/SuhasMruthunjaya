/*******************************************************************************
* File Name: RL_QuadDec_PM.c
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

#include "RL_QuadDec.h"

static RL_QuadDec_BACKUP_STRUCT RL_QuadDec_backup = {0u};


/*******************************************************************************
* Function Name: RL_QuadDec_SaveConfig
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
void RL_QuadDec_SaveConfig(void) 
{
    #if (RL_QuadDec_COUNTER_SIZE == RL_QuadDec_COUNTER_SIZE_8_BIT)
        RL_QuadDec_Cnt8_SaveConfig();
    #else 
        /* (RL_QuadDec_COUNTER_SIZE == RL_QuadDec_COUNTER_SIZE_16_BIT) || 
         * (RL_QuadDec_COUNTER_SIZE == RL_QuadDec_COUNTER_SIZE_32_BIT)
         */
        RL_QuadDec_Cnt16_SaveConfig();
    #endif /* (RL_QuadDec_COUNTER_SIZE == RL_QuadDec_COUNTER_SIZE_8_BIT) */
}


/*******************************************************************************
* Function Name: RL_QuadDec_RestoreConfig
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
void RL_QuadDec_RestoreConfig(void) 
{
    #if (RL_QuadDec_COUNTER_SIZE == RL_QuadDec_COUNTER_SIZE_8_BIT)
        RL_QuadDec_Cnt8_RestoreConfig();
    #else 
        /* (RL_QuadDec_COUNTER_SIZE == RL_QuadDec_COUNTER_SIZE_16_BIT) || 
         * (RL_QuadDec_COUNTER_SIZE == RL_QuadDec_COUNTER_SIZE_32_BIT) 
         */
        RL_QuadDec_Cnt16_RestoreConfig();
    #endif /* (RL_QuadDec_COUNTER_SIZE == RL_QuadDec_COUNTER_SIZE_8_BIT) */
}


/*******************************************************************************
* Function Name: RL_QuadDec_Sleep
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
*  RL_QuadDec_backup - modified when non-retention registers are saved.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void RL_QuadDec_Sleep(void) 
{
    if (0u != (RL_QuadDec_SR_AUX_CONTROL & RL_QuadDec_INTERRUPTS_ENABLE))
    {
        RL_QuadDec_backup.enableState = 1u;
    }
    else /* The Quadrature Decoder Component is disabled */
    {
        RL_QuadDec_backup.enableState = 0u;
    }

    RL_QuadDec_Stop();
    RL_QuadDec_SaveConfig();
}


/*******************************************************************************
* Function Name: RL_QuadDec_Wakeup
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
*  RL_QuadDec_backup - used when non-retention registers are restored.
*
*******************************************************************************/
void RL_QuadDec_Wakeup(void) 
{
    RL_QuadDec_RestoreConfig();

    if (RL_QuadDec_backup.enableState != 0u)
    {
        #if (RL_QuadDec_COUNTER_SIZE == RL_QuadDec_COUNTER_SIZE_8_BIT)
            RL_QuadDec_Cnt8_Enable();
        #else 
            /* (RL_QuadDec_COUNTER_SIZE == RL_QuadDec_COUNTER_SIZE_16_BIT) || 
            *  (RL_QuadDec_COUNTER_SIZE == RL_QuadDec_COUNTER_SIZE_32_BIT) 
            */
            RL_QuadDec_Cnt16_Enable();
        #endif /* (RL_QuadDec_COUNTER_SIZE == RL_QuadDec_COUNTER_SIZE_8_BIT) */

        /* Enable component's operation */
        RL_QuadDec_Enable();
    } /* Do nothing if component's block was disabled before */
}


/* [] END OF FILE */

