/*******************************************************************************
* File Name: SYSCOUNTER_PM.c  
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

#include "SYSCOUNTER.h"

static SYSCOUNTER_backupStruct SYSCOUNTER_backup;


/*******************************************************************************
* Function Name: SYSCOUNTER_SaveConfig
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
*  SYSCOUNTER_backup:  Variables of this global structure are modified to 
*  store the values of non retention configuration registers when Sleep() API is 
*  called.
*
*******************************************************************************/
void SYSCOUNTER_SaveConfig(void) 
{
    #if (!SYSCOUNTER_UsingFixedFunction)

        SYSCOUNTER_backup.CounterUdb = SYSCOUNTER_ReadCounter();

        #if(!SYSCOUNTER_ControlRegRemoved)
            SYSCOUNTER_backup.CounterControlRegister = SYSCOUNTER_ReadControlRegister();
        #endif /* (!SYSCOUNTER_ControlRegRemoved) */

    #endif /* (!SYSCOUNTER_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: SYSCOUNTER_RestoreConfig
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
*  SYSCOUNTER_backup:  Variables of this global structure are used to 
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void SYSCOUNTER_RestoreConfig(void) 
{      
    #if (!SYSCOUNTER_UsingFixedFunction)

       SYSCOUNTER_WriteCounter(SYSCOUNTER_backup.CounterUdb);

        #if(!SYSCOUNTER_ControlRegRemoved)
            SYSCOUNTER_WriteControlRegister(SYSCOUNTER_backup.CounterControlRegister);
        #endif /* (!SYSCOUNTER_ControlRegRemoved) */

    #endif /* (!SYSCOUNTER_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: SYSCOUNTER_Sleep
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
*  SYSCOUNTER_backup.enableState:  Is modified depending on the enable 
*  state of the block before entering sleep mode.
*
*******************************************************************************/
void SYSCOUNTER_Sleep(void) 
{
    #if(!SYSCOUNTER_ControlRegRemoved)
        /* Save Counter's enable state */
        if(SYSCOUNTER_CTRL_ENABLE == (SYSCOUNTER_CONTROL & SYSCOUNTER_CTRL_ENABLE))
        {
            /* Counter is enabled */
            SYSCOUNTER_backup.CounterEnableState = 1u;
        }
        else
        {
            /* Counter is disabled */
            SYSCOUNTER_backup.CounterEnableState = 0u;
        }
    #else
        SYSCOUNTER_backup.CounterEnableState = 1u;
        if(SYSCOUNTER_backup.CounterEnableState != 0u)
        {
            SYSCOUNTER_backup.CounterEnableState = 0u;
        }
    #endif /* (!SYSCOUNTER_ControlRegRemoved) */
    
    SYSCOUNTER_Stop();
    SYSCOUNTER_SaveConfig();
}


/*******************************************************************************
* Function Name: SYSCOUNTER_Wakeup
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
*  SYSCOUNTER_backup.enableState:  Is used to restore the enable state of 
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void SYSCOUNTER_Wakeup(void) 
{
    SYSCOUNTER_RestoreConfig();
    #if(!SYSCOUNTER_ControlRegRemoved)
        if(SYSCOUNTER_backup.CounterEnableState == 1u)
        {
            /* Enable Counter's operation */
            SYSCOUNTER_Enable();
        } /* Do nothing if Counter was disabled before */    
    #endif /* (!SYSCOUNTER_ControlRegRemoved) */
    
}


/* [] END OF FILE */
