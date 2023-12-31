/*******************************************************************************
* File Name: PWM_Rear_PM.c
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

#include "PWM_Rear.h"

static PWM_Rear_backupStruct PWM_Rear_backup;


/*******************************************************************************
* Function Name: PWM_Rear_SaveConfig
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
*  PWM_Rear_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void PWM_Rear_SaveConfig(void) 
{

    #if(!PWM_Rear_UsingFixedFunction)
        #if(!PWM_Rear_PWMModeIsCenterAligned)
            PWM_Rear_backup.PWMPeriod = PWM_Rear_ReadPeriod();
        #endif /* (!PWM_Rear_PWMModeIsCenterAligned) */
        PWM_Rear_backup.PWMUdb = PWM_Rear_ReadCounter();
        #if (PWM_Rear_UseStatus)
            PWM_Rear_backup.InterruptMaskValue = PWM_Rear_STATUS_MASK;
        #endif /* (PWM_Rear_UseStatus) */

        #if(PWM_Rear_DeadBandMode == PWM_Rear__B_PWM__DBM_256_CLOCKS || \
            PWM_Rear_DeadBandMode == PWM_Rear__B_PWM__DBM_2_4_CLOCKS)
            PWM_Rear_backup.PWMdeadBandValue = PWM_Rear_ReadDeadTime();
        #endif /*  deadband count is either 2-4 clocks or 256 clocks */

        #if(PWM_Rear_KillModeMinTime)
             PWM_Rear_backup.PWMKillCounterPeriod = PWM_Rear_ReadKillTime();
        #endif /* (PWM_Rear_KillModeMinTime) */

        #if(PWM_Rear_UseControl)
            PWM_Rear_backup.PWMControlRegister = PWM_Rear_ReadControlRegister();
        #endif /* (PWM_Rear_UseControl) */
    #endif  /* (!PWM_Rear_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: PWM_Rear_RestoreConfig
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
*  PWM_Rear_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void PWM_Rear_RestoreConfig(void) 
{
        #if(!PWM_Rear_UsingFixedFunction)
            #if(!PWM_Rear_PWMModeIsCenterAligned)
                PWM_Rear_WritePeriod(PWM_Rear_backup.PWMPeriod);
            #endif /* (!PWM_Rear_PWMModeIsCenterAligned) */

            PWM_Rear_WriteCounter(PWM_Rear_backup.PWMUdb);

            #if (PWM_Rear_UseStatus)
                PWM_Rear_STATUS_MASK = PWM_Rear_backup.InterruptMaskValue;
            #endif /* (PWM_Rear_UseStatus) */

            #if(PWM_Rear_DeadBandMode == PWM_Rear__B_PWM__DBM_256_CLOCKS || \
                PWM_Rear_DeadBandMode == PWM_Rear__B_PWM__DBM_2_4_CLOCKS)
                PWM_Rear_WriteDeadTime(PWM_Rear_backup.PWMdeadBandValue);
            #endif /* deadband count is either 2-4 clocks or 256 clocks */

            #if(PWM_Rear_KillModeMinTime)
                PWM_Rear_WriteKillTime(PWM_Rear_backup.PWMKillCounterPeriod);
            #endif /* (PWM_Rear_KillModeMinTime) */

            #if(PWM_Rear_UseControl)
                PWM_Rear_WriteControlRegister(PWM_Rear_backup.PWMControlRegister);
            #endif /* (PWM_Rear_UseControl) */
        #endif  /* (!PWM_Rear_UsingFixedFunction) */
    }


/*******************************************************************************
* Function Name: PWM_Rear_Sleep
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
*  PWM_Rear_backup.PWMEnableState:  Is modified depending on the enable
*  state of the block before entering sleep mode.
*
*******************************************************************************/
void PWM_Rear_Sleep(void) 
{
    #if(PWM_Rear_UseControl)
        if(PWM_Rear_CTRL_ENABLE == (PWM_Rear_CONTROL & PWM_Rear_CTRL_ENABLE))
        {
            /*Component is enabled */
            PWM_Rear_backup.PWMEnableState = 1u;
        }
        else
        {
            /* Component is disabled */
            PWM_Rear_backup.PWMEnableState = 0u;
        }
    #endif /* (PWM_Rear_UseControl) */

    /* Stop component */
    PWM_Rear_Stop();

    /* Save registers configuration */
    PWM_Rear_SaveConfig();
}


/*******************************************************************************
* Function Name: PWM_Rear_Wakeup
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
*  PWM_Rear_backup.pwmEnable:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void PWM_Rear_Wakeup(void) 
{
     /* Restore registers values */
    PWM_Rear_RestoreConfig();

    if(PWM_Rear_backup.PWMEnableState != 0u)
    {
        /* Enable component's operation */
        PWM_Rear_Enable();
    } /* Do nothing if component's block was disabled before */

}


/* [] END OF FILE */
