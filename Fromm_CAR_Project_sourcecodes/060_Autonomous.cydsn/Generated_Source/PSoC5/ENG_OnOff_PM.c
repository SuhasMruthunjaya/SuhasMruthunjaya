/*******************************************************************************
* File Name: ENG_OnOff_PM.c
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

#include "ENG_OnOff.h"

/* Check for removal by optimization */
#if !defined(ENG_OnOff_Sync_ctrl_reg__REMOVED)

static ENG_OnOff_BACKUP_STRUCT  ENG_OnOff_backup = {0u};

    
/*******************************************************************************
* Function Name: ENG_OnOff_SaveConfig
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
void ENG_OnOff_SaveConfig(void) 
{
    ENG_OnOff_backup.controlState = ENG_OnOff_Control;
}


/*******************************************************************************
* Function Name: ENG_OnOff_RestoreConfig
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
void ENG_OnOff_RestoreConfig(void) 
{
     ENG_OnOff_Control = ENG_OnOff_backup.controlState;
}


/*******************************************************************************
* Function Name: ENG_OnOff_Sleep
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
void ENG_OnOff_Sleep(void) 
{
    ENG_OnOff_SaveConfig();
}


/*******************************************************************************
* Function Name: ENG_OnOff_Wakeup
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
void ENG_OnOff_Wakeup(void)  
{
    ENG_OnOff_RestoreConfig();
}

#endif /* End check for removal by optimization */


/* [] END OF FILE */
