/*******************************************************************************
* File Name: ENGINE_OnOff_PM.c
* Version 1.80
*
* Description:
*  This file contains the setup, control, and status commands to support 
*  the component operation in the low power mode. 
*
* Note:
*
********************************************************************************
* Copyright 2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "ENGINE_OnOff.h"

/* Check for removal by optimization */
#if !defined(ENGINE_OnOff_Sync_ctrl_reg__REMOVED)

static ENGINE_OnOff_BACKUP_STRUCT  ENGINE_OnOff_backup = {0u};

    
/*******************************************************************************
* Function Name: ENGINE_OnOff_SaveConfig
********************************************************************************
*
* Summary:
*  Saves the control register value.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void ENGINE_OnOff_SaveConfig(void) 
{
    ENGINE_OnOff_backup.controlState = ENGINE_OnOff_Control;
}


/*******************************************************************************
* Function Name: ENGINE_OnOff_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the control register value.
*
* Parameters:
*  None
*
* Return:
*  None
*
*
*******************************************************************************/
void ENGINE_OnOff_RestoreConfig(void) 
{
     ENGINE_OnOff_Control = ENGINE_OnOff_backup.controlState;
}


/*******************************************************************************
* Function Name: ENGINE_OnOff_Sleep
********************************************************************************
*
* Summary:
*  Prepares the component for entering the low power mode.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void ENGINE_OnOff_Sleep(void) 
{
    ENGINE_OnOff_SaveConfig();
}


/*******************************************************************************
* Function Name: ENGINE_OnOff_Wakeup
********************************************************************************
*
* Summary:
*  Restores the component after waking up from the low power mode.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void ENGINE_OnOff_Wakeup(void)  
{
    ENGINE_OnOff_RestoreConfig();
}

#endif /* End check for removal by optimization */


/* [] END OF FILE */
