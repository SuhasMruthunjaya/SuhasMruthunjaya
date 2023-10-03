/*******************************************************************************
* File Name: RL_QuadDec_Cnt16_PM.c  
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

#include "RL_QuadDec_Cnt16.h"

static RL_QuadDec_Cnt16_backupStruct RL_QuadDec_Cnt16_backup;


/*******************************************************************************
* Function Name: RL_QuadDec_Cnt16_SaveConfig
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
*  RL_QuadDec_Cnt16_backup:  Variables of this global structure are modified to 
*  store the values of non retention configuration registers when Sleep() API is 
*  called.
*
*******************************************************************************/
void RL_QuadDec_Cnt16_SaveConfig(void) 
{
    #if (!RL_QuadDec_Cnt16_UsingFixedFunction)

        RL_QuadDec_Cnt16_backup.CounterUdb = RL_QuadDec_Cnt16_ReadCounter();

        #if(!RL_QuadDec_Cnt16_ControlRegRemoved)
            RL_QuadDec_Cnt16_backup.CounterControlRegister = RL_QuadDec_Cnt16_ReadControlRegister();
        #endif /* (!RL_QuadDec_Cnt16_ControlRegRemoved) */

    #endif /* (!RL_QuadDec_Cnt16_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: RL_QuadDec_Cnt16_RestoreConfig
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
*  RL_QuadDec_Cnt16_backup:  Variables of this global structure are used to 
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void RL_QuadDec_Cnt16_RestoreConfig(void) 
{      
    #if (!RL_QuadDec_Cnt16_UsingFixedFunction)

       RL_QuadDec_Cnt16_WriteCounter(RL_QuadDec_Cnt16_backup.CounterUdb);

        #if(!RL_QuadDec_Cnt16_ControlRegRemoved)
            RL_QuadDec_Cnt16_WriteControlRegister(RL_QuadDec_Cnt16_backup.CounterControlRegister);
        #endif /* (!RL_QuadDec_Cnt16_ControlRegRemoved) */

    #endif /* (!RL_QuadDec_Cnt16_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: RL_QuadDec_Cnt16_Sleep
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
*  RL_QuadDec_Cnt16_backup.enableState:  Is modified depending on the enable 
*  state of the block before entering sleep mode.
*
*******************************************************************************/
void RL_QuadDec_Cnt16_Sleep(void) 
{
    #if(!RL_QuadDec_Cnt16_ControlRegRemoved)
        /* Save Counter's enable state */
        if(RL_QuadDec_Cnt16_CTRL_ENABLE == (RL_QuadDec_Cnt16_CONTROL & RL_QuadDec_Cnt16_CTRL_ENABLE))
        {
            /* Counter is enabled */
            RL_QuadDec_Cnt16_backup.CounterEnableState = 1u;
        }
        else
        {
            /* Counter is disabled */
            RL_QuadDec_Cnt16_backup.CounterEnableState = 0u;
        }
    #else
        RL_QuadDec_Cnt16_backup.CounterEnableState = 1u;
        if(RL_QuadDec_Cnt16_backup.CounterEnableState != 0u)
        {
            RL_QuadDec_Cnt16_backup.CounterEnableState = 0u;
        }
    #endif /* (!RL_QuadDec_Cnt16_ControlRegRemoved) */
    
    RL_QuadDec_Cnt16_Stop();
    RL_QuadDec_Cnt16_SaveConfig();
}


/*******************************************************************************
* Function Name: RL_QuadDec_Cnt16_Wakeup
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
*  RL_QuadDec_Cnt16_backup.enableState:  Is used to restore the enable state of 
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void RL_QuadDec_Cnt16_Wakeup(void) 
{
    RL_QuadDec_Cnt16_RestoreConfig();
    #if(!RL_QuadDec_Cnt16_ControlRegRemoved)
        if(RL_QuadDec_Cnt16_backup.CounterEnableState == 1u)
        {
            /* Enable Counter's operation */
            RL_QuadDec_Cnt16_Enable();
        } /* Do nothing if Counter was disabled before */    
    #endif /* (!RL_QuadDec_Cnt16_ControlRegRemoved) */
    
}


/* [] END OF FILE */
