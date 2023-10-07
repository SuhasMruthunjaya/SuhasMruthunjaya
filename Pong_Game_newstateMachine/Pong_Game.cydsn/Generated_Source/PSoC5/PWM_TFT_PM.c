/*******************************************************************************
* File Name: PWM_TFT_PM.c
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

#include "PWM_TFT.h"

static PWM_TFT_backupStruct PWM_TFT_backup;


/*******************************************************************************
* Function Name: PWM_TFT_SaveConfig
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
*  PWM_TFT_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void PWM_TFT_SaveConfig(void) 
{

    #if(!PWM_TFT_UsingFixedFunction)
        #if(!PWM_TFT_PWMModeIsCenterAligned)
            PWM_TFT_backup.PWMPeriod = PWM_TFT_ReadPeriod();
        #endif /* (!PWM_TFT_PWMModeIsCenterAligned) */
        PWM_TFT_backup.PWMUdb = PWM_TFT_ReadCounter();
        #if (PWM_TFT_UseStatus)
            PWM_TFT_backup.InterruptMaskValue = PWM_TFT_STATUS_MASK;
        #endif /* (PWM_TFT_UseStatus) */

        #if(PWM_TFT_DeadBandMode == PWM_TFT__B_PWM__DBM_256_CLOCKS || \
            PWM_TFT_DeadBandMode == PWM_TFT__B_PWM__DBM_2_4_CLOCKS)
            PWM_TFT_backup.PWMdeadBandValue = PWM_TFT_ReadDeadTime();
        #endif /*  deadband count is either 2-4 clocks or 256 clocks */

        #if(PWM_TFT_KillModeMinTime)
             PWM_TFT_backup.PWMKillCounterPeriod = PWM_TFT_ReadKillTime();
        #endif /* (PWM_TFT_KillModeMinTime) */

        #if(PWM_TFT_UseControl)
            PWM_TFT_backup.PWMControlRegister = PWM_TFT_ReadControlRegister();
        #endif /* (PWM_TFT_UseControl) */
    #endif  /* (!PWM_TFT_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: PWM_TFT_RestoreConfig
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
*  PWM_TFT_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void PWM_TFT_RestoreConfig(void) 
{
        #if(!PWM_TFT_UsingFixedFunction)
            #if(!PWM_TFT_PWMModeIsCenterAligned)
                PWM_TFT_WritePeriod(PWM_TFT_backup.PWMPeriod);
            #endif /* (!PWM_TFT_PWMModeIsCenterAligned) */

            PWM_TFT_WriteCounter(PWM_TFT_backup.PWMUdb);

            #if (PWM_TFT_UseStatus)
                PWM_TFT_STATUS_MASK = PWM_TFT_backup.InterruptMaskValue;
            #endif /* (PWM_TFT_UseStatus) */

            #if(PWM_TFT_DeadBandMode == PWM_TFT__B_PWM__DBM_256_CLOCKS || \
                PWM_TFT_DeadBandMode == PWM_TFT__B_PWM__DBM_2_4_CLOCKS)
                PWM_TFT_WriteDeadTime(PWM_TFT_backup.PWMdeadBandValue);
            #endif /* deadband count is either 2-4 clocks or 256 clocks */

            #if(PWM_TFT_KillModeMinTime)
                PWM_TFT_WriteKillTime(PWM_TFT_backup.PWMKillCounterPeriod);
            #endif /* (PWM_TFT_KillModeMinTime) */

            #if(PWM_TFT_UseControl)
                PWM_TFT_WriteControlRegister(PWM_TFT_backup.PWMControlRegister);
            #endif /* (PWM_TFT_UseControl) */
        #endif  /* (!PWM_TFT_UsingFixedFunction) */
    }


/*******************************************************************************
* Function Name: PWM_TFT_Sleep
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
*  PWM_TFT_backup.PWMEnableState:  Is modified depending on the enable
*  state of the block before entering sleep mode.
*
*******************************************************************************/
void PWM_TFT_Sleep(void) 
{
    #if(PWM_TFT_UseControl)
        if(PWM_TFT_CTRL_ENABLE == (PWM_TFT_CONTROL & PWM_TFT_CTRL_ENABLE))
        {
            /*Component is enabled */
            PWM_TFT_backup.PWMEnableState = 1u;
        }
        else
        {
            /* Component is disabled */
            PWM_TFT_backup.PWMEnableState = 0u;
        }
    #endif /* (PWM_TFT_UseControl) */

    /* Stop component */
    PWM_TFT_Stop();

    /* Save registers configuration */
    PWM_TFT_SaveConfig();
}


/*******************************************************************************
* Function Name: PWM_TFT_Wakeup
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
*  PWM_TFT_backup.pwmEnable:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void PWM_TFT_Wakeup(void) 
{
     /* Restore registers values */
    PWM_TFT_RestoreConfig();

    if(PWM_TFT_backup.PWMEnableState != 0u)
    {
        /* Enable component's operation */
        PWM_TFT_Enable();
    } /* Do nothing if component's block was disabled before */

}


/* [] END OF FILE */
