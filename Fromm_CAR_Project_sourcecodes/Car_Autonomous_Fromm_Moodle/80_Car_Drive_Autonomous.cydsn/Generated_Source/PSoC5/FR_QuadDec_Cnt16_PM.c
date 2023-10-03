/*******************************************************************************
* File Name: FR_QuadDec_Cnt16_PM.c  
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

#include "FR_QuadDec_Cnt16.h"

static FR_QuadDec_Cnt16_backupStruct FR_QuadDec_Cnt16_backup;


/*******************************************************************************
* Function Name: FR_QuadDec_Cnt16_SaveConfig
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
*  FR_QuadDec_Cnt16_backup:  Variables of this global structure are modified to 
*  store the values of non retention configuration registers when Sleep() API is 
*  called.
*
*******************************************************************************/
void FR_QuadDec_Cnt16_SaveConfig(void) 
{
    #if (!FR_QuadDec_Cnt16_UsingFixedFunction)

        FR_QuadDec_Cnt16_backup.CounterUdb = FR_QuadDec_Cnt16_ReadCounter();

        #if(!FR_QuadDec_Cnt16_ControlRegRemoved)
            FR_QuadDec_Cnt16_backup.CounterControlRegister = FR_QuadDec_Cnt16_ReadControlRegister();
        #endif /* (!FR_QuadDec_Cnt16_ControlRegRemoved) */

    #endif /* (!FR_QuadDec_Cnt16_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: FR_QuadDec_Cnt16_RestoreConfig
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
*  FR_QuadDec_Cnt16_backup:  Variables of this global structure are used to 
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void FR_QuadDec_Cnt16_RestoreConfig(void) 
{      
    #if (!FR_QuadDec_Cnt16_UsingFixedFunction)

       FR_QuadDec_Cnt16_WriteCounter(FR_QuadDec_Cnt16_backup.CounterUdb);

        #if(!FR_QuadDec_Cnt16_ControlRegRemoved)
            FR_QuadDec_Cnt16_WriteControlRegister(FR_QuadDec_Cnt16_backup.CounterControlRegister);
        #endif /* (!FR_QuadDec_Cnt16_ControlRegRemoved) */

    #endif /* (!FR_QuadDec_Cnt16_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: FR_QuadDec_Cnt16_Sleep
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
*  FR_QuadDec_Cnt16_backup.enableState:  Is modified depending on the enable 
*  state of the block before entering sleep mode.
*
*******************************************************************************/
void FR_QuadDec_Cnt16_Sleep(void) 
{
    #if(!FR_QuadDec_Cnt16_ControlRegRemoved)
        /* Save Counter's enable state */
        if(FR_QuadDec_Cnt16_CTRL_ENABLE == (FR_QuadDec_Cnt16_CONTROL & FR_QuadDec_Cnt16_CTRL_ENABLE))
        {
            /* Counter is enabled */
            FR_QuadDec_Cnt16_backup.CounterEnableState = 1u;
        }
        else
        {
            /* Counter is disabled */
            FR_QuadDec_Cnt16_backup.CounterEnableState = 0u;
        }
    #else
        FR_QuadDec_Cnt16_backup.CounterEnableState = 1u;
        if(FR_QuadDec_Cnt16_backup.CounterEnableState != 0u)
        {
            FR_QuadDec_Cnt16_backup.CounterEnableState = 0u;
        }
    #endif /* (!FR_QuadDec_Cnt16_ControlRegRemoved) */
    
    FR_QuadDec_Cnt16_Stop();
    FR_QuadDec_Cnt16_SaveConfig();
}


/*******************************************************************************
* Function Name: FR_QuadDec_Cnt16_Wakeup
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
*  FR_QuadDec_Cnt16_backup.enableState:  Is used to restore the enable state of 
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void FR_QuadDec_Cnt16_Wakeup(void) 
{
    FR_QuadDec_Cnt16_RestoreConfig();
    #if(!FR_QuadDec_Cnt16_ControlRegRemoved)
        if(FR_QuadDec_Cnt16_backup.CounterEnableState == 1u)
        {
            /* Enable Counter's operation */
            FR_QuadDec_Cnt16_Enable();
        } /* Do nothing if Counter was disabled before */    
    #endif /* (!FR_QuadDec_Cnt16_ControlRegRemoved) */
    
}


/* [] END OF FILE */
