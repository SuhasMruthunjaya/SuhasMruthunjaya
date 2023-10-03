/*******************************************************************************
* File Name: ADC_VtgDiv_PM.c
* Version 3.30
*
* Description:
*  This file provides the power manager source code to the API for the
*  Delta-Sigma ADC Component.
*
* Note:
*
********************************************************************************
* Copyright 2008-2017, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "ADC_VtgDiv.h"

static ADC_VtgDiv_BACKUP_STRUCT ADC_VtgDiv_backup =
{
    ADC_VtgDiv_DISABLED,
    ADC_VtgDiv_CFG1_DEC_CR
};


/*******************************************************************************
* Function Name: ADC_VtgDiv_SaveConfig
********************************************************************************
*
* Summary:
*  Save the register configuration which are not retention.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  ADC_VtgDiv_backup:  This global structure variable is used to store
*  configuration registers which are non retention whenever user wants to go
*  sleep mode by calling Sleep() API.
*
*******************************************************************************/
void ADC_VtgDiv_SaveConfig(void) 
{
    ADC_VtgDiv_backup.deccr = ADC_VtgDiv_DEC_CR_REG;
}


/*******************************************************************************
* Function Name: ADC_VtgDiv_RestoreConfig
********************************************************************************
*
* Summary:
*  Restore the register configurations which are not retention.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  ADC_VtgDiv_backup:  This global structure variable is used to restore
*  configuration registers which are non retention whenever user wants to switch
*  to active power mode by calling Wakeup() API.
*
*******************************************************************************/
void ADC_VtgDiv_RestoreConfig(void) 
{
    ADC_VtgDiv_DEC_CR_REG = ADC_VtgDiv_backup.deccr;
}


/*******************************************************************************
* Function Name: ADC_VtgDiv_Sleep
********************************************************************************
*
* Summary:
*  Stops the operation of the block and saves the user configuration.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  ADC_VtgDiv_backup:  The structure field 'enableState' is modified
*  depending on the enable state of the block before entering to sleep mode.
*
*******************************************************************************/
void ADC_VtgDiv_Sleep(void) 
{
    /* Save ADC enable state */
    if((ADC_VtgDiv_ACT_PWR_DEC_EN == (ADC_VtgDiv_PWRMGR_DEC_REG & ADC_VtgDiv_ACT_PWR_DEC_EN)) &&
       (ADC_VtgDiv_ACT_PWR_DSM_EN == (ADC_VtgDiv_PWRMGR_DSM_REG & ADC_VtgDiv_ACT_PWR_DSM_EN)))
    {
        /* Component is enabled */
        ADC_VtgDiv_backup.enableState = ADC_VtgDiv_ENABLED;
        if((ADC_VtgDiv_DEC_CR_REG & ADC_VtgDiv_DEC_START_CONV) != 0u)
        {   
            /* Conversion is started */
            ADC_VtgDiv_backup.enableState |= ADC_VtgDiv_STARTED;
        }
		
        /* Stop the configuration */
        ADC_VtgDiv_Stop();
    }
    else
    {
        /* Component is disabled */
        ADC_VtgDiv_backup.enableState = ADC_VtgDiv_DISABLED;
    }

    /* Save the user configuration */
    ADC_VtgDiv_SaveConfig();
}


/*******************************************************************************
* Function Name: ADC_VtgDiv_Wakeup
********************************************************************************
*
* Summary:
*  Restores the user configuration and enables the power to the block.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  ADC_VtgDiv_backup:  The structure field 'enableState' is used to
*  restore the enable state of block after wakeup from sleep mode.
*
*******************************************************************************/
void ADC_VtgDiv_Wakeup(void) 
{
    /* Restore the configuration */
    ADC_VtgDiv_RestoreConfig();

    /* Enables the component operation */
    if(ADC_VtgDiv_backup.enableState != ADC_VtgDiv_DISABLED)
    {
        ADC_VtgDiv_Enable();
        if((ADC_VtgDiv_backup.enableState & ADC_VtgDiv_STARTED) != 0u)
        {
            ADC_VtgDiv_StartConvert();
        }
    } /* Do nothing if component was disable before */
}


/* [] END OF FILE */
