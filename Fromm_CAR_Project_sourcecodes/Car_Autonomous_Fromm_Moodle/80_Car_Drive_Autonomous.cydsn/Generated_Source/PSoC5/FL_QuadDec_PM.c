/*******************************************************************************
* File Name: FL_QuadDec_PM.c
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

#include "FL_QuadDec.h"

static FL_QuadDec_BACKUP_STRUCT FL_QuadDec_backup = {0u};


/*******************************************************************************
* Function Name: FL_QuadDec_SaveConfig
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
void FL_QuadDec_SaveConfig(void) 
{
    #if (FL_QuadDec_COUNTER_SIZE == FL_QuadDec_COUNTER_SIZE_8_BIT)
        FL_QuadDec_Cnt8_SaveConfig();
    #else 
        /* (FL_QuadDec_COUNTER_SIZE == FL_QuadDec_COUNTER_SIZE_16_BIT) || 
         * (FL_QuadDec_COUNTER_SIZE == FL_QuadDec_COUNTER_SIZE_32_BIT)
         */
        FL_QuadDec_Cnt16_SaveConfig();
    #endif /* (FL_QuadDec_COUNTER_SIZE == FL_QuadDec_COUNTER_SIZE_8_BIT) */
}


/*******************************************************************************
* Function Name: FL_QuadDec_RestoreConfig
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
void FL_QuadDec_RestoreConfig(void) 
{
    #if (FL_QuadDec_COUNTER_SIZE == FL_QuadDec_COUNTER_SIZE_8_BIT)
        FL_QuadDec_Cnt8_RestoreConfig();
    #else 
        /* (FL_QuadDec_COUNTER_SIZE == FL_QuadDec_COUNTER_SIZE_16_BIT) || 
         * (FL_QuadDec_COUNTER_SIZE == FL_QuadDec_COUNTER_SIZE_32_BIT) 
         */
        FL_QuadDec_Cnt16_RestoreConfig();
    #endif /* (FL_QuadDec_COUNTER_SIZE == FL_QuadDec_COUNTER_SIZE_8_BIT) */
}


/*******************************************************************************
* Function Name: FL_QuadDec_Sleep
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
*  FL_QuadDec_backup - modified when non-retention registers are saved.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void FL_QuadDec_Sleep(void) 
{
    if (0u != (FL_QuadDec_SR_AUX_CONTROL & FL_QuadDec_INTERRUPTS_ENABLE))
    {
        FL_QuadDec_backup.enableState = 1u;
    }
    else /* The Quadrature Decoder Component is disabled */
    {
        FL_QuadDec_backup.enableState = 0u;
    }

    FL_QuadDec_Stop();
    FL_QuadDec_SaveConfig();
}


/*******************************************************************************
* Function Name: FL_QuadDec_Wakeup
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
*  FL_QuadDec_backup - used when non-retention registers are restored.
*
*******************************************************************************/
void FL_QuadDec_Wakeup(void) 
{
    FL_QuadDec_RestoreConfig();

    if (FL_QuadDec_backup.enableState != 0u)
    {
        #if (FL_QuadDec_COUNTER_SIZE == FL_QuadDec_COUNTER_SIZE_8_BIT)
            FL_QuadDec_Cnt8_Enable();
        #else 
            /* (FL_QuadDec_COUNTER_SIZE == FL_QuadDec_COUNTER_SIZE_16_BIT) || 
            *  (FL_QuadDec_COUNTER_SIZE == FL_QuadDec_COUNTER_SIZE_32_BIT) 
            */
            FL_QuadDec_Cnt16_Enable();
        #endif /* (FL_QuadDec_COUNTER_SIZE == FL_QuadDec_COUNTER_SIZE_8_BIT) */

        /* Enable component's operation */
        FL_QuadDec_Enable();
    } /* Do nothing if component's block was disabled before */
}


/* [] END OF FILE */

