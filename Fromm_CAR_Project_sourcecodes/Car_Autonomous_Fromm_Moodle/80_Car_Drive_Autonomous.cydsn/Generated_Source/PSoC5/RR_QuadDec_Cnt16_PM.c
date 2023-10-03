/*******************************************************************************
* File Name: RR_QuadDec_Cnt16_PM.c  
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

#include "RR_QuadDec_Cnt16.h"

static RR_QuadDec_Cnt16_backupStruct RR_QuadDec_Cnt16_backup;


/*******************************************************************************
* Function Name: RR_QuadDec_Cnt16_SaveConfig
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
*  RR_QuadDec_Cnt16_backup:  Variables of this global structure are modified to 
*  store the values of non retention configuration registers when Sleep() API is 
*  called.
*
*******************************************************************************/
void RR_QuadDec_Cnt16_SaveConfig(void) 
{
    #if (!RR_QuadDec_Cnt16_UsingFixedFunction)

        RR_QuadDec_Cnt16_backup.CounterUdb = RR_QuadDec_Cnt16_ReadCounter();

        #if(!RR_QuadDec_Cnt16_ControlRegRemoved)
            RR_QuadDec_Cnt16_backup.CounterControlRegister = RR_QuadDec_Cnt16_ReadControlRegister();
        #endif /* (!RR_QuadDec_Cnt16_ControlRegRemoved) */

    #endif /* (!RR_QuadDec_Cnt16_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: RR_QuadDec_Cnt16_RestoreConfig
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
*  RR_QuadDec_Cnt16_backup:  Variables of this global structure are used to 
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void RR_QuadDec_Cnt16_RestoreConfig(void) 
{      
    #if (!RR_QuadDec_Cnt16_UsingFixedFunction)

       RR_QuadDec_Cnt16_WriteCounter(RR_QuadDec_Cnt16_backup.CounterUdb);

        #if(!RR_QuadDec_Cnt16_ControlRegRemoved)
            RR_QuadDec_Cnt16_WriteControlRegister(RR_QuadDec_Cnt16_backup.CounterControlRegister);
        #endif /* (!RR_QuadDec_Cnt16_ControlRegRemoved) */

    #endif /* (!RR_QuadDec_Cnt16_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: RR_QuadDec_Cnt16_Sleep
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
*  RR_QuadDec_Cnt16_backup.enableState:  Is modified depending on the enable 
*  state of the block before entering sleep mode.
*
*******************************************************************************/
void RR_QuadDec_Cnt16_Sleep(void) 
{
    #if(!RR_QuadDec_Cnt16_ControlRegRemoved)
        /* Save Counter's enable state */
        if(RR_QuadDec_Cnt16_CTRL_ENABLE == (RR_QuadDec_Cnt16_CONTROL & RR_QuadDec_Cnt16_CTRL_ENABLE))
        {
            /* Counter is enabled */
            RR_QuadDec_Cnt16_backup.CounterEnableState = 1u;
        }
        else
        {
            /* Counter is disabled */
            RR_QuadDec_Cnt16_backup.CounterEnableState = 0u;
        }
    #else
        RR_QuadDec_Cnt16_backup.CounterEnableState = 1u;
        if(RR_QuadDec_Cnt16_backup.CounterEnableState != 0u)
        {
            RR_QuadDec_Cnt16_backup.CounterEnableState = 0u;
        }
    #endif /* (!RR_QuadDec_Cnt16_ControlRegRemoved) */
    
    RR_QuadDec_Cnt16_Stop();
    RR_QuadDec_Cnt16_SaveConfig();
}


/*******************************************************************************
* Function Name: RR_QuadDec_Cnt16_Wakeup
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
*  RR_QuadDec_Cnt16_backup.enableState:  Is used to restore the enable state of 
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void RR_QuadDec_Cnt16_Wakeup(void) 
{
    RR_QuadDec_Cnt16_RestoreConfig();
    #if(!RR_QuadDec_Cnt16_ControlRegRemoved)
        if(RR_QuadDec_Cnt16_backup.CounterEnableState == 1u)
        {
            /* Enable Counter's operation */
            RR_QuadDec_Cnt16_Enable();
        } /* Do nothing if Counter was disabled before */    
    #endif /* (!RR_QuadDec_Cnt16_ControlRegRemoved) */
    
}


/* [] END OF FILE */
