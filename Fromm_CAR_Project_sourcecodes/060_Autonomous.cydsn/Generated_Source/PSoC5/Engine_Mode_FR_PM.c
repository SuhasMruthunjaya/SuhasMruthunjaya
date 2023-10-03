/*******************************************************************************
* File Name: Engine_Mode_FR_PM.c
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

#include "Engine_Mode_FR.h"

/* Check for removal by optimization */
#if !defined(Engine_Mode_FR_Sync_ctrl_reg__REMOVED)

static Engine_Mode_FR_BACKUP_STRUCT  Engine_Mode_FR_backup = {0u};

    
/*******************************************************************************
* Function Name: Engine_Mode_FR_SaveConfig
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
void Engine_Mode_FR_SaveConfig(void) 
{
    Engine_Mode_FR_backup.controlState = Engine_Mode_FR_Control;
}


/*******************************************************************************
* Function Name: Engine_Mode_FR_RestoreConfig
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
void Engine_Mode_FR_RestoreConfig(void) 
{
     Engine_Mode_FR_Control = Engine_Mode_FR_backup.controlState;
}


/*******************************************************************************
* Function Name: Engine_Mode_FR_Sleep
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
void Engine_Mode_FR_Sleep(void) 
{
    Engine_Mode_FR_SaveConfig();
}


/*******************************************************************************
* Function Name: Engine_Mode_FR_Wakeup
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
void Engine_Mode_FR_Wakeup(void)  
{
    Engine_Mode_FR_RestoreConfig();
}

#endif /* End check for removal by optimization */


/* [] END OF FILE */
