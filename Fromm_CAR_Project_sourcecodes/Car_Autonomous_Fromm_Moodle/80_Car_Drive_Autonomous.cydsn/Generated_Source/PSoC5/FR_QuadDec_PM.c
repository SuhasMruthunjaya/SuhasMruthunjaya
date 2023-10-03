/*******************************************************************************
* File Name: FR_QuadDec_PM.c
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

#include "FR_QuadDec.h"

static FR_QuadDec_BACKUP_STRUCT FR_QuadDec_backup = {0u};


/*******************************************************************************
* Function Name: FR_QuadDec_SaveConfig
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
void FR_QuadDec_SaveConfig(void) 
{
    #if (FR_QuadDec_COUNTER_SIZE == FR_QuadDec_COUNTER_SIZE_8_BIT)
        FR_QuadDec_Cnt8_SaveConfig();
    #else 
        /* (FR_QuadDec_COUNTER_SIZE == FR_QuadDec_COUNTER_SIZE_16_BIT) || 
         * (FR_QuadDec_COUNTER_SIZE == FR_QuadDec_COUNTER_SIZE_32_BIT)
         */
        FR_QuadDec_Cnt16_SaveConfig();
    #endif /* (FR_QuadDec_COUNTER_SIZE == FR_QuadDec_COUNTER_SIZE_8_BIT) */
}


/*******************************************************************************
* Function Name: FR_QuadDec_RestoreConfig
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
void FR_QuadDec_RestoreConfig(void) 
{
    #if (FR_QuadDec_COUNTER_SIZE == FR_QuadDec_COUNTER_SIZE_8_BIT)
        FR_QuadDec_Cnt8_RestoreConfig();
    #else 
        /* (FR_QuadDec_COUNTER_SIZE == FR_QuadDec_COUNTER_SIZE_16_BIT) || 
         * (FR_QuadDec_COUNTER_SIZE == FR_QuadDec_COUNTER_SIZE_32_BIT) 
         */
        FR_QuadDec_Cnt16_RestoreConfig();
    #endif /* (FR_QuadDec_COUNTER_SIZE == FR_QuadDec_COUNTER_SIZE_8_BIT) */
}


/*******************************************************************************
* Function Name: FR_QuadDec_Sleep
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
*  FR_QuadDec_backup - modified when non-retention registers are saved.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void FR_QuadDec_Sleep(void) 
{
    if (0u != (FR_QuadDec_SR_AUX_CONTROL & FR_QuadDec_INTERRUPTS_ENABLE))
    {
        FR_QuadDec_backup.enableState = 1u;
    }
    else /* The Quadrature Decoder Component is disabled */
    {
        FR_QuadDec_backup.enableState = 0u;
    }

    FR_QuadDec_Stop();
    FR_QuadDec_SaveConfig();
}


/*******************************************************************************
* Function Name: FR_QuadDec_Wakeup
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
*  FR_QuadDec_backup - used when non-retention registers are restored.
*
*******************************************************************************/
void FR_QuadDec_Wakeup(void) 
{
    FR_QuadDec_RestoreConfig();

    if (FR_QuadDec_backup.enableState != 0u)
    {
        #if (FR_QuadDec_COUNTER_SIZE == FR_QuadDec_COUNTER_SIZE_8_BIT)
            FR_QuadDec_Cnt8_Enable();
        #else 
            /* (FR_QuadDec_COUNTER_SIZE == FR_QuadDec_COUNTER_SIZE_16_BIT) || 
            *  (FR_QuadDec_COUNTER_SIZE == FR_QuadDec_COUNTER_SIZE_32_BIT) 
            */
            FR_QuadDec_Cnt16_Enable();
        #endif /* (FR_QuadDec_COUNTER_SIZE == FR_QuadDec_COUNTER_SIZE_8_BIT) */

        /* Enable component's operation */
        FR_QuadDec_Enable();
    } /* Do nothing if component's block was disabled before */
}


/* [] END OF FILE */

