/*******************************************************************************
* File Name: ENGINE_DECODER_Cnt16_PM.c  
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

#include "ENGINE_DECODER_Cnt16.h"

static ENGINE_DECODER_Cnt16_backupStruct ENGINE_DECODER_Cnt16_backup;


/*******************************************************************************
* Function Name: ENGINE_DECODER_Cnt16_SaveConfig
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
*  ENGINE_DECODER_Cnt16_backup:  Variables of this global structure are modified to 
*  store the values of non retention configuration registers when Sleep() API is 
*  called.
*
*******************************************************************************/
void ENGINE_DECODER_Cnt16_SaveConfig(void) 
{
    #if (!ENGINE_DECODER_Cnt16_UsingFixedFunction)

        ENGINE_DECODER_Cnt16_backup.CounterUdb = ENGINE_DECODER_Cnt16_ReadCounter();

        #if(!ENGINE_DECODER_Cnt16_ControlRegRemoved)
            ENGINE_DECODER_Cnt16_backup.CounterControlRegister = ENGINE_DECODER_Cnt16_ReadControlRegister();
        #endif /* (!ENGINE_DECODER_Cnt16_ControlRegRemoved) */

    #endif /* (!ENGINE_DECODER_Cnt16_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: ENGINE_DECODER_Cnt16_RestoreConfig
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
*  ENGINE_DECODER_Cnt16_backup:  Variables of this global structure are used to 
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void ENGINE_DECODER_Cnt16_RestoreConfig(void) 
{      
    #if (!ENGINE_DECODER_Cnt16_UsingFixedFunction)

       ENGINE_DECODER_Cnt16_WriteCounter(ENGINE_DECODER_Cnt16_backup.CounterUdb);

        #if(!ENGINE_DECODER_Cnt16_ControlRegRemoved)
            ENGINE_DECODER_Cnt16_WriteControlRegister(ENGINE_DECODER_Cnt16_backup.CounterControlRegister);
        #endif /* (!ENGINE_DECODER_Cnt16_ControlRegRemoved) */

    #endif /* (!ENGINE_DECODER_Cnt16_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: ENGINE_DECODER_Cnt16_Sleep
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
*  ENGINE_DECODER_Cnt16_backup.enableState:  Is modified depending on the enable 
*  state of the block before entering sleep mode.
*
*******************************************************************************/
void ENGINE_DECODER_Cnt16_Sleep(void) 
{
    #if(!ENGINE_DECODER_Cnt16_ControlRegRemoved)
        /* Save Counter's enable state */
        if(ENGINE_DECODER_Cnt16_CTRL_ENABLE == (ENGINE_DECODER_Cnt16_CONTROL & ENGINE_DECODER_Cnt16_CTRL_ENABLE))
        {
            /* Counter is enabled */
            ENGINE_DECODER_Cnt16_backup.CounterEnableState = 1u;
        }
        else
        {
            /* Counter is disabled */
            ENGINE_DECODER_Cnt16_backup.CounterEnableState = 0u;
        }
    #else
        ENGINE_DECODER_Cnt16_backup.CounterEnableState = 1u;
        if(ENGINE_DECODER_Cnt16_backup.CounterEnableState != 0u)
        {
            ENGINE_DECODER_Cnt16_backup.CounterEnableState = 0u;
        }
    #endif /* (!ENGINE_DECODER_Cnt16_ControlRegRemoved) */
    
    ENGINE_DECODER_Cnt16_Stop();
    ENGINE_DECODER_Cnt16_SaveConfig();
}


/*******************************************************************************
* Function Name: ENGINE_DECODER_Cnt16_Wakeup
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
*  ENGINE_DECODER_Cnt16_backup.enableState:  Is used to restore the enable state of 
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void ENGINE_DECODER_Cnt16_Wakeup(void) 
{
    ENGINE_DECODER_Cnt16_RestoreConfig();
    #if(!ENGINE_DECODER_Cnt16_ControlRegRemoved)
        if(ENGINE_DECODER_Cnt16_backup.CounterEnableState == 1u)
        {
            /* Enable Counter's operation */
            ENGINE_DECODER_Cnt16_Enable();
        } /* Do nothing if Counter was disabled before */    
    #endif /* (!ENGINE_DECODER_Cnt16_ControlRegRemoved) */
    
}


/* [] END OF FILE */
