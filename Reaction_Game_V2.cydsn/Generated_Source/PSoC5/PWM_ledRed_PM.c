/*******************************************************************************
* File Name: PWM_ledRed_PM.c
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

#include "PWM_ledRed.h"

static PWM_ledRed_backupStruct PWM_ledRed_backup;


/*******************************************************************************
* Function Name: PWM_ledRed_SaveConfig
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
*  PWM_ledRed_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void PWM_ledRed_SaveConfig(void) 
{

    #if(!PWM_ledRed_UsingFixedFunction)
        #if(!PWM_ledRed_PWMModeIsCenterAligned)
            PWM_ledRed_backup.PWMPeriod = PWM_ledRed_ReadPeriod();
        #endif /* (!PWM_ledRed_PWMModeIsCenterAligned) */
        PWM_ledRed_backup.PWMUdb = PWM_ledRed_ReadCounter();
        #if (PWM_ledRed_UseStatus)
            PWM_ledRed_backup.InterruptMaskValue = PWM_ledRed_STATUS_MASK;
        #endif /* (PWM_ledRed_UseStatus) */

        #if(PWM_ledRed_DeadBandMode == PWM_ledRed__B_PWM__DBM_256_CLOCKS || \
            PWM_ledRed_DeadBandMode == PWM_ledRed__B_PWM__DBM_2_4_CLOCKS)
            PWM_ledRed_backup.PWMdeadBandValue = PWM_ledRed_ReadDeadTime();
        #endif /*  deadband count is either 2-4 clocks or 256 clocks */

        #if(PWM_ledRed_KillModeMinTime)
             PWM_ledRed_backup.PWMKillCounterPeriod = PWM_ledRed_ReadKillTime();
        #endif /* (PWM_ledRed_KillModeMinTime) */

        #if(PWM_ledRed_UseControl)
            PWM_ledRed_backup.PWMControlRegister = PWM_ledRed_ReadControlRegister();
        #endif /* (PWM_ledRed_UseControl) */
    #endif  /* (!PWM_ledRed_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: PWM_ledRed_RestoreConfig
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
*  PWM_ledRed_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void PWM_ledRed_RestoreConfig(void) 
{
        #if(!PWM_ledRed_UsingFixedFunction)
            #if(!PWM_ledRed_PWMModeIsCenterAligned)
                PWM_ledRed_WritePeriod(PWM_ledRed_backup.PWMPeriod);
            #endif /* (!PWM_ledRed_PWMModeIsCenterAligned) */

            PWM_ledRed_WriteCounter(PWM_ledRed_backup.PWMUdb);

            #if (PWM_ledRed_UseStatus)
                PWM_ledRed_STATUS_MASK = PWM_ledRed_backup.InterruptMaskValue;
            #endif /* (PWM_ledRed_UseStatus) */

            #if(PWM_ledRed_DeadBandMode == PWM_ledRed__B_PWM__DBM_256_CLOCKS || \
                PWM_ledRed_DeadBandMode == PWM_ledRed__B_PWM__DBM_2_4_CLOCKS)
                PWM_ledRed_WriteDeadTime(PWM_ledRed_backup.PWMdeadBandValue);
            #endif /* deadband count is either 2-4 clocks or 256 clocks */

            #if(PWM_ledRed_KillModeMinTime)
                PWM_ledRed_WriteKillTime(PWM_ledRed_backup.PWMKillCounterPeriod);
            #endif /* (PWM_ledRed_KillModeMinTime) */

            #if(PWM_ledRed_UseControl)
                PWM_ledRed_WriteControlRegister(PWM_ledRed_backup.PWMControlRegister);
            #endif /* (PWM_ledRed_UseControl) */
        #endif  /* (!PWM_ledRed_UsingFixedFunction) */
    }


/*******************************************************************************
* Function Name: PWM_ledRed_Sleep
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
*  PWM_ledRed_backup.PWMEnableState:  Is modified depending on the enable
*  state of the block before entering sleep mode.
*
*******************************************************************************/
void PWM_ledRed_Sleep(void) 
{
    #if(PWM_ledRed_UseControl)
        if(PWM_ledRed_CTRL_ENABLE == (PWM_ledRed_CONTROL & PWM_ledRed_CTRL_ENABLE))
        {
            /*Component is enabled */
            PWM_ledRed_backup.PWMEnableState = 1u;
        }
        else
        {
            /* Component is disabled */
            PWM_ledRed_backup.PWMEnableState = 0u;
        }
    #endif /* (PWM_ledRed_UseControl) */

    /* Stop component */
    PWM_ledRed_Stop();

    /* Save registers configuration */
    PWM_ledRed_SaveConfig();
}


/*******************************************************************************
* Function Name: PWM_ledRed_Wakeup
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
*  PWM_ledRed_backup.pwmEnable:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void PWM_ledRed_Wakeup(void) 
{
     /* Restore registers values */
    PWM_ledRed_RestoreConfig();

    if(PWM_ledRed_backup.PWMEnableState != 0u)
    {
        /* Enable component's operation */
        PWM_ledRed_Enable();
    } /* Do nothing if component's block was disabled before */

}


/* [] END OF FILE */
