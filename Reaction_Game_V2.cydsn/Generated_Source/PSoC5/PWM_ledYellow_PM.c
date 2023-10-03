/*******************************************************************************
* File Name: PWM_ledYellow_PM.c
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

#include "PWM_ledYellow.h"

static PWM_ledYellow_backupStruct PWM_ledYellow_backup;


/*******************************************************************************
* Function Name: PWM_ledYellow_SaveConfig
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
*  PWM_ledYellow_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void PWM_ledYellow_SaveConfig(void) 
{

    #if(!PWM_ledYellow_UsingFixedFunction)
        #if(!PWM_ledYellow_PWMModeIsCenterAligned)
            PWM_ledYellow_backup.PWMPeriod = PWM_ledYellow_ReadPeriod();
        #endif /* (!PWM_ledYellow_PWMModeIsCenterAligned) */
        PWM_ledYellow_backup.PWMUdb = PWM_ledYellow_ReadCounter();
        #if (PWM_ledYellow_UseStatus)
            PWM_ledYellow_backup.InterruptMaskValue = PWM_ledYellow_STATUS_MASK;
        #endif /* (PWM_ledYellow_UseStatus) */

        #if(PWM_ledYellow_DeadBandMode == PWM_ledYellow__B_PWM__DBM_256_CLOCKS || \
            PWM_ledYellow_DeadBandMode == PWM_ledYellow__B_PWM__DBM_2_4_CLOCKS)
            PWM_ledYellow_backup.PWMdeadBandValue = PWM_ledYellow_ReadDeadTime();
        #endif /*  deadband count is either 2-4 clocks or 256 clocks */

        #if(PWM_ledYellow_KillModeMinTime)
             PWM_ledYellow_backup.PWMKillCounterPeriod = PWM_ledYellow_ReadKillTime();
        #endif /* (PWM_ledYellow_KillModeMinTime) */

        #if(PWM_ledYellow_UseControl)
            PWM_ledYellow_backup.PWMControlRegister = PWM_ledYellow_ReadControlRegister();
        #endif /* (PWM_ledYellow_UseControl) */
    #endif  /* (!PWM_ledYellow_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: PWM_ledYellow_RestoreConfig
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
*  PWM_ledYellow_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void PWM_ledYellow_RestoreConfig(void) 
{
        #if(!PWM_ledYellow_UsingFixedFunction)
            #if(!PWM_ledYellow_PWMModeIsCenterAligned)
                PWM_ledYellow_WritePeriod(PWM_ledYellow_backup.PWMPeriod);
            #endif /* (!PWM_ledYellow_PWMModeIsCenterAligned) */

            PWM_ledYellow_WriteCounter(PWM_ledYellow_backup.PWMUdb);

            #if (PWM_ledYellow_UseStatus)
                PWM_ledYellow_STATUS_MASK = PWM_ledYellow_backup.InterruptMaskValue;
            #endif /* (PWM_ledYellow_UseStatus) */

            #if(PWM_ledYellow_DeadBandMode == PWM_ledYellow__B_PWM__DBM_256_CLOCKS || \
                PWM_ledYellow_DeadBandMode == PWM_ledYellow__B_PWM__DBM_2_4_CLOCKS)
                PWM_ledYellow_WriteDeadTime(PWM_ledYellow_backup.PWMdeadBandValue);
            #endif /* deadband count is either 2-4 clocks or 256 clocks */

            #if(PWM_ledYellow_KillModeMinTime)
                PWM_ledYellow_WriteKillTime(PWM_ledYellow_backup.PWMKillCounterPeriod);
            #endif /* (PWM_ledYellow_KillModeMinTime) */

            #if(PWM_ledYellow_UseControl)
                PWM_ledYellow_WriteControlRegister(PWM_ledYellow_backup.PWMControlRegister);
            #endif /* (PWM_ledYellow_UseControl) */
        #endif  /* (!PWM_ledYellow_UsingFixedFunction) */
    }


/*******************************************************************************
* Function Name: PWM_ledYellow_Sleep
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
*  PWM_ledYellow_backup.PWMEnableState:  Is modified depending on the enable
*  state of the block before entering sleep mode.
*
*******************************************************************************/
void PWM_ledYellow_Sleep(void) 
{
    #if(PWM_ledYellow_UseControl)
        if(PWM_ledYellow_CTRL_ENABLE == (PWM_ledYellow_CONTROL & PWM_ledYellow_CTRL_ENABLE))
        {
            /*Component is enabled */
            PWM_ledYellow_backup.PWMEnableState = 1u;
        }
        else
        {
            /* Component is disabled */
            PWM_ledYellow_backup.PWMEnableState = 0u;
        }
    #endif /* (PWM_ledYellow_UseControl) */

    /* Stop component */
    PWM_ledYellow_Stop();

    /* Save registers configuration */
    PWM_ledYellow_SaveConfig();
}


/*******************************************************************************
* Function Name: PWM_ledYellow_Wakeup
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
*  PWM_ledYellow_backup.pwmEnable:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void PWM_ledYellow_Wakeup(void) 
{
     /* Restore registers values */
    PWM_ledYellow_RestoreConfig();

    if(PWM_ledYellow_backup.PWMEnableState != 0u)
    {
        /* Enable component's operation */
        PWM_ledYellow_Enable();
    } /* Do nothing if component's block was disabled before */

}


/* [] END OF FILE */
