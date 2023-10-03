/*******************************************************************************
* File Name: FL_QuadDec_Cnt16_PM.c  
* Version 3.0
*
*  Description:
*    This file provides the power management source code to API for the
*    Counter.  
*
*   Note:
*     None
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "FL_QuadDec_Cnt16.h"

static FL_QuadDec_Cnt16_backupStruct FL_QuadDec_Cnt16_backup;


/*******************************************************************************
* Function Name: FL_QuadDec_Cnt16_SaveConfig
********************************************************************************
* Summary:
*     Save the current user configuration
*
* Parameters:  
*  void
*
* Return: 
*  void
*
* Global variables:
*  FL_QuadDec_Cnt16_backup:  Variables of this global structure are modified to 
*  store the values of non retention configuration registers when Sleep() API is 
*  called.
*
*******************************************************************************/
void FL_QuadDec_Cnt16_SaveConfig(void) 
{
    #if (!FL_QuadDec_Cnt16_UsingFixedFunction)

        FL_QuadDec_Cnt16_backup.CounterUdb = FL_QuadDec_Cnt16_ReadCounter();

        #if(!FL_QuadDec_Cnt16_ControlRegRemoved)
            FL_QuadDec_Cnt16_backup.CounterControlRegister = FL_QuadDec_Cnt16_ReadControlRegister();
        #endif /* (!FL_QuadDec_Cnt16_ControlRegRemoved) */

    #endif /* (!FL_QuadDec_Cnt16_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: FL_QuadDec_Cnt16_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the current user configuration.
*
* Parameters:  
*  void
*
* Return: 
*  void
*
* Global variables:
*  FL_QuadDec_Cnt16_backup:  Variables of this global structure are used to 
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void FL_QuadDec_Cnt16_RestoreConfig(void) 
{      
    #if (!FL_QuadDec_Cnt16_UsingFixedFunction)

       FL_QuadDec_Cnt16_WriteCounter(FL_QuadDec_Cnt16_backup.CounterUdb);

        #if(!FL_QuadDec_Cnt16_ControlRegRemoved)
            FL_QuadDec_Cnt16_WriteControlRegister(FL_QuadDec_Cnt16_backup.CounterControlRegister);
        #endif /* (!FL_QuadDec_Cnt16_ControlRegRemoved) */

    #endif /* (!FL_QuadDec_Cnt16_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: FL_QuadDec_Cnt16_Sleep
********************************************************************************
* Summary:
*     Stop and Save the user configuration
*
* Parameters:  
*  void
*
* Return: 
*  void
*
* Global variables:
*  FL_QuadDec_Cnt16_backup.enableState:  Is modified depending on the enable 
*  state of the block before entering sleep mode.
*
*******************************************************************************/
void FL_QuadDec_Cnt16_Sleep(void) 
{
    #if(!FL_QuadDec_Cnt16_ControlRegRemoved)
        /* Save Counter's enable state */
        if(FL_QuadDec_Cnt16_CTRL_ENABLE == (FL_QuadDec_Cnt16_CONTROL & FL_QuadDec_Cnt16_CTRL_ENABLE))
        {
            /* Counter is enabled */
            FL_QuadDec_Cnt16_backup.CounterEnableState = 1u;
        }
        else
        {
            /* Counter is disabled */
            FL_QuadDec_Cnt16_backup.CounterEnableState = 0u;
        }
    #else
        FL_QuadDec_Cnt16_backup.CounterEnableState = 1u;
        if(FL_QuadDec_Cnt16_backup.CounterEnableState != 0u)
        {
            FL_QuadDec_Cnt16_backup.CounterEnableState = 0u;
        }
    #endif /* (!FL_QuadDec_Cnt16_ControlRegRemoved) */
    
    FL_QuadDec_Cnt16_Stop();
    FL_QuadDec_Cnt16_SaveConfig();
}


/*******************************************************************************
* Function Name: FL_QuadDec_Cnt16_Wakeup
********************************************************************************
*
* Summary:
*  Restores and enables the user configuration
*  
* Parameters:  
*  void
*
* Return: 
*  void
*
* Global variables:
*  FL_QuadDec_Cnt16_backup.enableState:  Is used to restore the enable state of 
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void FL_QuadDec_Cnt16_Wakeup(void) 
{
    FL_QuadDec_Cnt16_RestoreConfig();
    #if(!FL_QuadDec_Cnt16_ControlRegRemoved)
        if(FL_QuadDec_Cnt16_backup.CounterEnableState == 1u)
        {
            /* Enable Counter's operation */
            FL_QuadDec_Cnt16_Enable();
        } /* Do nothing if Counter was disabled before */    
    #endif /* (!FL_QuadDec_Cnt16_ControlRegRemoved) */
    
}


/* [] END OF FILE */
