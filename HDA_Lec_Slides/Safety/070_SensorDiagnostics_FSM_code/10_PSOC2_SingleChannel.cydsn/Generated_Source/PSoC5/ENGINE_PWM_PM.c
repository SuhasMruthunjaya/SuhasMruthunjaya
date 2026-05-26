/*******************************************************************************
* File Name: ENGINE_PWM_PM.c
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

#include "ENGINE_PWM.h"

static ENGINE_PWM_backupStruct ENGINE_PWM_backup;


/*******************************************************************************
* Function Name: ENGINE_PWM_SaveConfig
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
*  ENGINE_PWM_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void ENGINE_PWM_SaveConfig(void) 
{

    #if(!ENGINE_PWM_UsingFixedFunction)
        #if(!ENGINE_PWM_PWMModeIsCenterAligned)
            ENGINE_PWM_backup.PWMPeriod = ENGINE_PWM_ReadPeriod();
        #endif /* (!ENGINE_PWM_PWMModeIsCenterAligned) */
        ENGINE_PWM_backup.PWMUdb = ENGINE_PWM_ReadCounter();
        #if (ENGINE_PWM_UseStatus)
            ENGINE_PWM_backup.InterruptMaskValue = ENGINE_PWM_STATUS_MASK;
        #endif /* (ENGINE_PWM_UseStatus) */

        #if(ENGINE_PWM_DeadBandMode == ENGINE_PWM__B_PWM__DBM_256_CLOCKS || \
            ENGINE_PWM_DeadBandMode == ENGINE_PWM__B_PWM__DBM_2_4_CLOCKS)
            ENGINE_PWM_backup.PWMdeadBandValue = ENGINE_PWM_ReadDeadTime();
        #endif /*  deadband count is either 2-4 clocks or 256 clocks */

        #if(ENGINE_PWM_KillModeMinTime)
             ENGINE_PWM_backup.PWMKillCounterPeriod = ENGINE_PWM_ReadKillTime();
        #endif /* (ENGINE_PWM_KillModeMinTime) */

        #if(ENGINE_PWM_UseControl)
            ENGINE_PWM_backup.PWMControlRegister = ENGINE_PWM_ReadControlRegister();
        #endif /* (ENGINE_PWM_UseControl) */
    #endif  /* (!ENGINE_PWM_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: ENGINE_PWM_RestoreConfig
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
*  ENGINE_PWM_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void ENGINE_PWM_RestoreConfig(void) 
{
        #if(!ENGINE_PWM_UsingFixedFunction)
            #if(!ENGINE_PWM_PWMModeIsCenterAligned)
                ENGINE_PWM_WritePeriod(ENGINE_PWM_backup.PWMPeriod);
            #endif /* (!ENGINE_PWM_PWMModeIsCenterAligned) */

            ENGINE_PWM_WriteCounter(ENGINE_PWM_backup.PWMUdb);

            #if (ENGINE_PWM_UseStatus)
                ENGINE_PWM_STATUS_MASK = ENGINE_PWM_backup.InterruptMaskValue;
            #endif /* (ENGINE_PWM_UseStatus) */

            #if(ENGINE_PWM_DeadBandMode == ENGINE_PWM__B_PWM__DBM_256_CLOCKS || \
                ENGINE_PWM_DeadBandMode == ENGINE_PWM__B_PWM__DBM_2_4_CLOCKS)
                ENGINE_PWM_WriteDeadTime(ENGINE_PWM_backup.PWMdeadBandValue);
            #endif /* deadband count is either 2-4 clocks or 256 clocks */

            #if(ENGINE_PWM_KillModeMinTime)
                ENGINE_PWM_WriteKillTime(ENGINE_PWM_backup.PWMKillCounterPeriod);
            #endif /* (ENGINE_PWM_KillModeMinTime) */

            #if(ENGINE_PWM_UseControl)
                ENGINE_PWM_WriteControlRegister(ENGINE_PWM_backup.PWMControlRegister);
            #endif /* (ENGINE_PWM_UseControl) */
        #endif  /* (!ENGINE_PWM_UsingFixedFunction) */
    }


/*******************************************************************************
* Function Name: ENGINE_PWM_Sleep
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
*  ENGINE_PWM_backup.PWMEnableState:  Is modified depending on the enable
*  state of the block before entering sleep mode.
*
*******************************************************************************/
void ENGINE_PWM_Sleep(void) 
{
    #if(ENGINE_PWM_UseControl)
        if(ENGINE_PWM_CTRL_ENABLE == (ENGINE_PWM_CONTROL & ENGINE_PWM_CTRL_ENABLE))
        {
            /*Component is enabled */
            ENGINE_PWM_backup.PWMEnableState = 1u;
        }
        else
        {
            /* Component is disabled */
            ENGINE_PWM_backup.PWMEnableState = 0u;
        }
    #endif /* (ENGINE_PWM_UseControl) */

    /* Stop component */
    ENGINE_PWM_Stop();

    /* Save registers configuration */
    ENGINE_PWM_SaveConfig();
}


/*******************************************************************************
* Function Name: ENGINE_PWM_Wakeup
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
*  ENGINE_PWM_backup.pwmEnable:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void ENGINE_PWM_Wakeup(void) 
{
     /* Restore registers values */
    ENGINE_PWM_RestoreConfig();

    if(ENGINE_PWM_backup.PWMEnableState != 0u)
    {
        /* Enable component's operation */
        ENGINE_PWM_Enable();
    } /* Do nothing if component's block was disabled before */

}


/* [] END OF FILE */
