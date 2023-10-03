/*******************************************************************************
* File Name: RR_QuadDec_PM.c
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

#include "RR_QuadDec.h"

static RR_QuadDec_BACKUP_STRUCT RR_QuadDec_backup = {0u};


/*******************************************************************************
* Function Name: RR_QuadDec_SaveConfig
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
void RR_QuadDec_SaveConfig(void) 
{
    #if (RR_QuadDec_COUNTER_SIZE == RR_QuadDec_COUNTER_SIZE_8_BIT)
        RR_QuadDec_Cnt8_SaveConfig();
    #else 
        /* (RR_QuadDec_COUNTER_SIZE == RR_QuadDec_COUNTER_SIZE_16_BIT) || 
         * (RR_QuadDec_COUNTER_SIZE == RR_QuadDec_COUNTER_SIZE_32_BIT)
         */
        RR_QuadDec_Cnt16_SaveConfig();
    #endif /* (RR_QuadDec_COUNTER_SIZE == RR_QuadDec_COUNTER_SIZE_8_BIT) */
}


/*******************************************************************************
* Function Name: RR_QuadDec_RestoreConfig
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
void RR_QuadDec_RestoreConfig(void) 
{
    #if (RR_QuadDec_COUNTER_SIZE == RR_QuadDec_COUNTER_SIZE_8_BIT)
        RR_QuadDec_Cnt8_RestoreConfig();
    #else 
        /* (RR_QuadDec_COUNTER_SIZE == RR_QuadDec_COUNTER_SIZE_16_BIT) || 
         * (RR_QuadDec_COUNTER_SIZE == RR_QuadDec_COUNTER_SIZE_32_BIT) 
         */
        RR_QuadDec_Cnt16_RestoreConfig();
    #endif /* (RR_QuadDec_COUNTER_SIZE == RR_QuadDec_COUNTER_SIZE_8_BIT) */
}


/*******************************************************************************
* Function Name: RR_QuadDec_Sleep
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
*  RR_QuadDec_backup - modified when non-retention registers are saved.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void RR_QuadDec_Sleep(void) 
{
    if (0u != (RR_QuadDec_SR_AUX_CONTROL & RR_QuadDec_INTERRUPTS_ENABLE))
    {
        RR_QuadDec_backup.enableState = 1u;
    }
    else /* The Quadrature Decoder Component is disabled */
    {
        RR_QuadDec_backup.enableState = 0u;
    }

    RR_QuadDec_Stop();
    RR_QuadDec_SaveConfig();
}


/*******************************************************************************
* Function Name: RR_QuadDec_Wakeup
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
*  RR_QuadDec_backup - used when non-retention registers are restored.
*
*******************************************************************************/
void RR_QuadDec_Wakeup(void) 
{
    RR_QuadDec_RestoreConfig();

    if (RR_QuadDec_backup.enableState != 0u)
    {
        #if (RR_QuadDec_COUNTER_SIZE == RR_QuadDec_COUNTER_SIZE_8_BIT)
            RR_QuadDec_Cnt8_Enable();
        #else 
            /* (RR_QuadDec_COUNTER_SIZE == RR_QuadDec_COUNTER_SIZE_16_BIT) || 
            *  (RR_QuadDec_COUNTER_SIZE == RR_QuadDec_COUNTER_SIZE_32_BIT) 
            */
            RR_QuadDec_Cnt16_Enable();
        #endif /* (RR_QuadDec_COUNTER_SIZE == RR_QuadDec_COUNTER_SIZE_8_BIT) */

        /* Enable component's operation */
        RR_QuadDec_Enable();
    } /* Do nothing if component's block was disabled before */
}


/* [] END OF FILE */

