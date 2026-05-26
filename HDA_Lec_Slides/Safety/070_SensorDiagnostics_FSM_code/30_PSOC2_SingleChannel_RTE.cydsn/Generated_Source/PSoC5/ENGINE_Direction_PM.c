/*******************************************************************************
* File Name: ENGINE_Direction_PM.c
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

#include "ENGINE_Direction.h"

/* Check for removal by optimization */
#if !defined(ENGINE_Direction_Sync_ctrl_reg__REMOVED)

static ENGINE_Direction_BACKUP_STRUCT  ENGINE_Direction_backup = {0u};

    
/*******************************************************************************
* Function Name: ENGINE_Direction_SaveConfig
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
void ENGINE_Direction_SaveConfig(void) 
{
    ENGINE_Direction_backup.controlState = ENGINE_Direction_Control;
}


/*******************************************************************************
* Function Name: ENGINE_Direction_RestoreConfig
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
void ENGINE_Direction_RestoreConfig(void) 
{
     ENGINE_Direction_Control = ENGINE_Direction_backup.controlState;
}


/*******************************************************************************
* Function Name: ENGINE_Direction_Sleep
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
void ENGINE_Direction_Sleep(void) 
{
    ENGINE_Direction_SaveConfig();
}


/*******************************************************************************
* Function Name: ENGINE_Direction_Wakeup
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
void ENGINE_Direction_Wakeup(void)  
{
    ENGINE_Direction_RestoreConfig();
}

#endif /* End check for removal by optimization */


/* [] END OF FILE */
