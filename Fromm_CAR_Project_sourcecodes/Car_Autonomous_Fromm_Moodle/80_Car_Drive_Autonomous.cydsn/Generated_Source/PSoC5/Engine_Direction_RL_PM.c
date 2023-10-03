/*******************************************************************************
* File Name: Engine_Direction_RL_PM.c
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

#include "Engine_Direction_RL.h"

/* Check for removal by optimization */
#if !defined(Engine_Direction_RL_Sync_ctrl_reg__REMOVED)

static Engine_Direction_RL_BACKUP_STRUCT  Engine_Direction_RL_backup = {0u};

    
/*******************************************************************************
* Function Name: Engine_Direction_RL_SaveConfig
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
void Engine_Direction_RL_SaveConfig(void) 
{
    Engine_Direction_RL_backup.controlState = Engine_Direction_RL_Control;
}


/*******************************************************************************
* Function Name: Engine_Direction_RL_RestoreConfig
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
void Engine_Direction_RL_RestoreConfig(void) 
{
     Engine_Direction_RL_Control = Engine_Direction_RL_backup.controlState;
}


/*******************************************************************************
* Function Name: Engine_Direction_RL_Sleep
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
void Engine_Direction_RL_Sleep(void) 
{
    Engine_Direction_RL_SaveConfig();
}


/*******************************************************************************
* Function Name: Engine_Direction_RL_Wakeup
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
void Engine_Direction_RL_Wakeup(void)  
{
    Engine_Direction_RL_RestoreConfig();
}

#endif /* End check for removal by optimization */


/* [] END OF FILE */
