/*******************************************************************************
* File Name: US_Fire_PM.c
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

#include "US_Fire.h"

/* Check for removal by optimization */
#if !defined(US_Fire_Sync_ctrl_reg__REMOVED)

static US_Fire_BACKUP_STRUCT  US_Fire_backup = {0u};

    
/*******************************************************************************
* Function Name: US_Fire_SaveConfig
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
void US_Fire_SaveConfig(void) 
{
    US_Fire_backup.controlState = US_Fire_Control;
}


/*******************************************************************************
* Function Name: US_Fire_RestoreConfig
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
void US_Fire_RestoreConfig(void) 
{
     US_Fire_Control = US_Fire_backup.controlState;
}


/*******************************************************************************
* Function Name: US_Fire_Sleep
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
void US_Fire_Sleep(void) 
{
    US_Fire_SaveConfig();
}


/*******************************************************************************
* Function Name: US_Fire_Wakeup
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
void US_Fire_Wakeup(void)  
{
    US_Fire_RestoreConfig();
}

#endif /* End check for removal by optimization */


/* [] END OF FILE */
