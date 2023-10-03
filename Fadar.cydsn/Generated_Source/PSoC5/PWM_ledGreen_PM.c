/*******************************************************************************
* File Name: PWM_ledGreen_PM.c
* Version 3.30
*
* Description:
*  This file provides the power management source code to API for the
*  PWM.
*
* Note:
*
********************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "PWM_ledGreen.h"

static PWM_ledGreen_backupStruct PWM_ledGreen_backup;


/*******************************************************************************
* Function Name: PWM_ledGreen_SaveConfig
********************************************************************************
*
* Summary:
*  Saves the current user configuration of the component.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  PWM_ledGreen_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void PWM_ledGreen_SaveConfig(void) 
{

    #if(!PWM_ledGreen_UsingFixedFunction)
        #if(!PWM_ledGreen_PWMModeIsCenterAligned)
            PWM_ledGreen_backup.PWMPeriod = PWM_ledGreen_ReadPeriod();
        #endif /* (!PWM_ledGreen_PWMModeIsCenterAligned) */
        PWM_ledGreen_backup.PWMUdb = PWM_ledGreen_ReadCounter();
        #if (PWM_ledGreen_UseStatus)
            PWM_ledGreen_backup.InterruptMaskValue = PWM_ledGreen_STATUS_MASK;
        #endif /* (PWM_ledGreen_UseStatus) */

        #if(PWM_ledGreen_DeadBandMode == PWM_ledGreen__B_PWM__DBM_256_CLOCKS || \
            PWM_ledGreen_DeadBandMode == PWM_ledGreen__B_PWM__DBM_2_4_CLOCKS)
            PWM_ledGreen_backup.PWMdeadBandValue = PWM_ledGreen_ReadDeadTime();
        #endif /*  deadband count is either 2-4 clocks or 256 clocks */

        #if(PWM_ledGreen_KillModeMinTime)
             PWM_ledGreen_backup.PWMKillCounterPeriod = PWM_ledGreen_ReadKillTime();
        #endif /* (PWM_ledGreen_KillModeMinTime) */

        #if(PWM_ledGreen_UseControl)
            PWM_ledGreen_backup.PWMControlRegister = PWM_ledGreen_ReadControlRegister();
        #endif /* (PWM_ledGreen_UseControl) */
    #endif  /* (!PWM_ledGreen_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: PWM_ledGreen_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the current user configuration of the component.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  PWM_ledGreen_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void PWM_ledGreen_RestoreConfig(void) 
{
        #if(!PWM_ledGreen_UsingFixedFunction)
            #if(!PWM_ledGreen_PWMModeIsCenterAligned)
                PWM_ledGreen_WritePeriod(PWM_ledGreen_backup.PWMPeriod);
            #endif /* (!PWM_ledGreen_PWMModeIsCenterAligned) */

            PWM_ledGreen_WriteCounter(PWM_ledGreen_backup.PWMUdb);

            #if (PWM_ledGreen_UseStatus)
                PWM_ledGreen_STATUS_MASK = PWM_ledGreen_backup.InterruptMaskValue;
            #endif /* (PWM_ledGreen_UseStatus) */

            #if(PWM_ledGreen_DeadBandMode == PWM_ledGreen__B_PWM__DBM_256_CLOCKS || \
                PWM_ledGreen_DeadBandMode == PWM_ledGreen__B_PWM__DBM_2_4_CLOCKS)
                PWM_ledGreen_WriteDeadTime(PWM_ledGreen_backup.PWMdeadBandValue);
            #endif /* deadband count is either 2-4 clocks or 256 clocks */

            #if(PWM_ledGreen_KillModeMinTime)
                PWM_ledGreen_WriteKillTime(PWM_ledGreen_backup.PWMKillCounterPeriod);
            #endif /* (PWM_ledGreen_KillModeMinTime) */

            #if(PWM_ledGreen_UseControl)
                PWM_ledGreen_WriteControlRegister(PWM_ledGreen_backup.PWMControlRegister);
            #endif /* (PWM_ledGreen_UseControl) */
        #endif  /* (!PWM_ledGreen_UsingFixedFunction) */
    }


/*******************************************************************************
* Function Name: PWM_ledGreen_Sleep
********************************************************************************
*
* Summary:
*  Disables block's operation and saves the user configuration. Should be called
*  just prior to entering sleep.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  PWM_ledGreen_backup.PWMEnableState:  Is modified depending on the enable
*  state of the block before entering sleep mode.
*
*******************************************************************************/
void PWM_ledGreen_Sleep(void) 
{
    #if(PWM_ledGreen_UseControl)
        if(PWM_ledGreen_CTRL_ENABLE == (PWM_ledGreen_CONTROL & PWM_ledGreen_CTRL_ENABLE))
        {
            /*Component is enabled */
            PWM_ledGreen_backup.PWMEnableState = 1u;
        }
        else
        {
            /* Component is disabled */
            PWM_ledGreen_backup.PWMEnableState = 0u;
        }
    #endif /* (PWM_ledGreen_UseControl) */

    /* Stop component */
    PWM_ledGreen_Stop();

    /* Save registers configuration */
    PWM_ledGreen_SaveConfig();
}


/*******************************************************************************
* Function Name: PWM_ledGreen_Wakeup
********************************************************************************
*
* Summary:
*  Restores and enables the user configuration. Should be called just after
*  awaking from sleep.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  PWM_ledGreen_backup.pwmEnable:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void PWM_ledGreen_Wakeup(void) 
{
     /* Restore registers values */
    PWM_ledGreen_RestoreConfig();

    if(PWM_ledGreen_backup.PWMEnableState != 0u)
    {
        /* Enable component's operation */
        PWM_ledGreen_Enable();
    } /* Do nothing if component's block was disabled before */

}


/* [] END OF FILE */
