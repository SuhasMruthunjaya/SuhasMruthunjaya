/*******************************************************************************
* File Name: RL_QuadDec.c  
* Version 3.0
*
* Description:
*  This file provides the source code to the API for the Quadrature Decoder
*  component.
*
* Note:
*  None.
*   
********************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "RL_QuadDec.h"

#if (RL_QuadDec_COUNTER_SIZE == RL_QuadDec_COUNTER_SIZE_32_BIT)
    #include "RL_QuadDec_PVT.h"
#endif /* RL_QuadDec_COUNTER_SIZE == RL_QuadDec_COUNTER_SIZE_32_BIT */

uint8 RL_QuadDec_initVar = 0u;


/*******************************************************************************
* Function Name: RL_QuadDec_Init
********************************************************************************
*
* Summary:
*  Inits/Restores default QuadDec configuration provided with customizer.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void RL_QuadDec_Init(void) 
{
    #if (RL_QuadDec_COUNTER_SIZE == RL_QuadDec_COUNTER_SIZE_32_BIT)
        /* Disable Interrupt. */
        CyIntDisable(RL_QuadDec_ISR_NUMBER);
        /* Set the ISR to point to the RL_QuadDec_isr Interrupt. */
        (void) CyIntSetVector(RL_QuadDec_ISR_NUMBER, & RL_QuadDec_ISR);
        /* Set the priority. */
        CyIntSetPriority(RL_QuadDec_ISR_NUMBER, RL_QuadDec_ISR_PRIORITY);
    #endif /* RL_QuadDec_COUNTER_SIZE == RL_QuadDec_COUNTER_SIZE_32_BIT */
}


/*******************************************************************************
* Function Name: RL_QuadDec_Enable
********************************************************************************
*
* Summary:
*  This function enable interrupts from Component and also enable Component's
*  ISR in case of 32-bit counter.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void RL_QuadDec_Enable(void) 
{
    uint8 enableInterrupts;

    RL_QuadDec_SetInterruptMask(RL_QuadDec_INIT_INT_MASK);

    /* Clear pending interrupts. */
    (void) RL_QuadDec_GetEvents();
    
    enableInterrupts = CyEnterCriticalSection();

    /* Enable interrupts from Statusi register */
    RL_QuadDec_SR_AUX_CONTROL |= RL_QuadDec_INTERRUPTS_ENABLE;

    CyExitCriticalSection(enableInterrupts);        

    #if (RL_QuadDec_COUNTER_SIZE == RL_QuadDec_COUNTER_SIZE_32_BIT)
        /* Enable Component interrupts */
        CyIntEnable(RL_QuadDec_ISR_NUMBER);
    #endif /* RL_QuadDec_COUNTER_SIZE == RL_QuadDec_COUNTER_SIZE_32_BIT */
}


/*******************************************************************************
* Function Name: RL_QuadDec_Start
********************************************************************************
*
* Summary:
*  Initializes UDBs and other relevant hardware.
*  Resets counter, enables or disables all relevant interrupts.
*  Starts monitoring the inputs and counting.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global variables:
*  RL_QuadDec_initVar - used to check initial configuration, modified on
*  first function call.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void RL_QuadDec_Start(void) 
{
    #if (RL_QuadDec_COUNTER_SIZE == RL_QuadDec_COUNTER_SIZE_8_BIT)
        RL_QuadDec_Cnt8_Start();
        RL_QuadDec_Cnt8_WriteCounter(RL_QuadDec_COUNTER_INIT_VALUE);
    #else
        /* (RL_QuadDec_COUNTER_SIZE == RL_QuadDec_COUNTER_SIZE_16_BIT) || 
        *  (RL_QuadDec_COUNTER_SIZE == RL_QuadDec_COUNTER_SIZE_32_BIT) 
        */
        RL_QuadDec_Cnt16_Start();
        RL_QuadDec_Cnt16_WriteCounter(RL_QuadDec_COUNTER_INIT_VALUE);
    #endif /* RL_QuadDec_COUNTER_SIZE == RL_QuadDec_COUNTER_SIZE_8_BIT */
    
    #if (RL_QuadDec_COUNTER_SIZE == RL_QuadDec_COUNTER_SIZE_32_BIT)        
       RL_QuadDec_count32SoftPart = 0;
    #endif /* RL_QuadDec_COUNTER_SIZE == RL_QuadDec_COUNTER_SIZE_32_BIT */

    if (RL_QuadDec_initVar == 0u)
    {
        RL_QuadDec_Init();
        RL_QuadDec_initVar = 1u;
    }

    RL_QuadDec_Enable();
}


/*******************************************************************************
* Function Name: RL_QuadDec_Stop
********************************************************************************
*
* Summary:
*  Turns off UDBs and other relevant hardware.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void RL_QuadDec_Stop(void) 
{
    uint8 enableInterrupts;

    #if (RL_QuadDec_COUNTER_SIZE == RL_QuadDec_COUNTER_SIZE_8_BIT)
        RL_QuadDec_Cnt8_Stop();
    #else 
        /* (RL_QuadDec_COUNTER_SIZE == RL_QuadDec_COUNTER_SIZE_16_BIT) ||
        *  (RL_QuadDec_COUNTER_SIZE == RL_QuadDec_COUNTER_SIZE_32_BIT)
        */
        RL_QuadDec_Cnt16_Stop();    /* counter disable */
    #endif /* (RL_QuadDec_COUNTER_SIZE == RL_QuadDec_COUNTER_SIZE_8_BIT) */
 
    enableInterrupts = CyEnterCriticalSection();

    /* Disable interrupts interrupts from Statusi register */
    RL_QuadDec_SR_AUX_CONTROL &= (uint8) (~RL_QuadDec_INTERRUPTS_ENABLE);

    CyExitCriticalSection(enableInterrupts);

    #if (RL_QuadDec_COUNTER_SIZE == RL_QuadDec_COUNTER_SIZE_32_BIT)
        CyIntDisable(RL_QuadDec_ISR_NUMBER);    /* interrupt disable */
    #endif /* RL_QuadDec_COUNTER_SIZE == RL_QuadDec_COUNTER_SIZE_32_BIT */
}


/*******************************************************************************
* Function Name: RL_QuadDec_GetCounter
********************************************************************************
*
* Summary:
*  Reports the current value of the counter.
*
* Parameters:
*  None.
*
* Return:
*  The counter value. Return type is signed and per the counter size setting.
*  A positive value indicates clockwise movement (B before A).
*
* Global variables:
*  RL_QuadDec_count32SoftPart - used to get hi 16 bit for current value
*  of the 32-bit counter, when Counter size equal 32-bit.
*
*******************************************************************************/
int32 RL_QuadDec_GetCounter(void) 
{
    int32 count;
    uint16 tmpCnt;

    #if (RL_QuadDec_COUNTER_SIZE == RL_QuadDec_COUNTER_SIZE_32_BIT)
        int16 hwCount;

        CyIntDisable(RL_QuadDec_ISR_NUMBER);

        tmpCnt = RL_QuadDec_Cnt16_ReadCounter();
        hwCount = (int16) ((int32) tmpCnt - (int32) RL_QuadDec_COUNTER_INIT_VALUE);
        count = RL_QuadDec_count32SoftPart + hwCount;

        CyIntEnable(RL_QuadDec_ISR_NUMBER);
    #else 
        /* (RL_QuadDec_COUNTER_SIZE == RL_QuadDec_COUNTER_SIZE_8_BIT) || 
        *  (RL_QuadDec_COUNTER_SIZE == RL_QuadDec_COUNTER_SIZE_16_BIT)
        */
        #if (RL_QuadDec_COUNTER_SIZE == RL_QuadDec_COUNTER_SIZE_8_BIT)
            tmpCnt = RL_QuadDec_Cnt8_ReadCounter();
        #else /* (RL_QuadDec_COUNTER_SIZE == RL_QuadDec_COUNTER_SIZE_16_BIT) */
            tmpCnt = RL_QuadDec_Cnt16_ReadCounter();
        #endif  /* RL_QuadDec_COUNTER_SIZE == RL_QuadDec_COUNTER_SIZE_8_BIT */

        count = (int32) ((int32) tmpCnt -
                (int32) RL_QuadDec_COUNTER_INIT_VALUE);

    #endif /* RL_QuadDec_COUNTER_SIZE == RL_QuadDec_COUNTER_SIZE_32_BIT */ 

    return (count);
}


/*******************************************************************************
* Function Name: RL_QuadDec_SetCounter
********************************************************************************
*
* Summary:
*  Sets the current value of the counter.
*
* Parameters:
*  value:  The new value. Parameter type is signed and per the counter size
*  setting.
*
* Return:
*  None.
*
* Global variables:
*  RL_QuadDec_count32SoftPart - modified to set hi 16 bit for current
*  value of the 32-bit counter, when Counter size equal 32-bit.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void RL_QuadDec_SetCounter(int32 value) 
{
    #if ((RL_QuadDec_COUNTER_SIZE == RL_QuadDec_COUNTER_SIZE_8_BIT) || \
         (RL_QuadDec_COUNTER_SIZE == RL_QuadDec_COUNTER_SIZE_16_BIT))
        uint16 count;
        
        if (value >= 0)
        {
            count = (uint16) value + RL_QuadDec_COUNTER_INIT_VALUE;
        }
        else
        {
            count = RL_QuadDec_COUNTER_INIT_VALUE - (uint16)(-value);
        }
        #if (RL_QuadDec_COUNTER_SIZE == RL_QuadDec_COUNTER_SIZE_8_BIT)
            RL_QuadDec_Cnt8_WriteCounter(count);
        #else /* (RL_QuadDec_COUNTER_SIZE == RL_QuadDec_COUNTER_SIZE_16_BIT) */
            RL_QuadDec_Cnt16_WriteCounter(count);
        #endif  /* RL_QuadDec_COUNTER_SIZE == RL_QuadDec_COUNTER_SIZE_8_BIT */
    #else /* (RL_QuadDec_COUNTER_SIZE == RL_QuadDec_COUNTER_SIZE_32_BIT) */
        CyIntDisable(RL_QuadDec_ISR_NUMBER);

        RL_QuadDec_Cnt16_WriteCounter(RL_QuadDec_COUNTER_INIT_VALUE);
        RL_QuadDec_count32SoftPart = value;

        CyIntEnable(RL_QuadDec_ISR_NUMBER);
    #endif  /* (RL_QuadDec_COUNTER_SIZE == RL_QuadDec_COUNTER_SIZE_8_BIT) ||
             * (RL_QuadDec_COUNTER_SIZE == RL_QuadDec_COUNTER_SIZE_16_BIT)
             */
}


/*******************************************************************************
* Function Name: RL_QuadDec_GetEvents
********************************************************************************
* 
* Summary:
*   Reports the current status of events. This function clears the bits of the 
*   status register.
*
* Parameters:
*  None.
*
* Return:
*  The events, as bits in an unsigned 8-bit value:
*    Bit      Description
*     0        Counter overflow.
*     1        Counter underflow.
*     2        Counter reset due to index, if index input is used.
*     3        Invalid A, B inputs state transition.
*
*******************************************************************************/
uint8 RL_QuadDec_GetEvents(void) 
{
    return (RL_QuadDec_STATUS_REG & RL_QuadDec_INIT_INT_MASK);
}


/*******************************************************************************
* Function Name: RL_QuadDec_SetInterruptMask
********************************************************************************
*
* Summary:
*  Enables / disables interrupts due to the events.
*  For the 32-bit counter, the overflow, underflow and reset interrupts cannot
*  be disabled, these bits are ignored.
*
* Parameters:
*  mask: Enable / disable bits in an 8-bit value, where 1 enables the interrupt.
*
* Return:
*  None.
*
*******************************************************************************/
void RL_QuadDec_SetInterruptMask(uint8 mask) 
{
    #if (RL_QuadDec_COUNTER_SIZE == RL_QuadDec_COUNTER_SIZE_32_BIT)
        /* Underflow, Overflow and Reset interrupts for 32-bit Counter are always enable */
        mask |= (RL_QuadDec_COUNTER_OVERFLOW | RL_QuadDec_COUNTER_UNDERFLOW |
                 RL_QuadDec_COUNTER_RESET);
    #endif /* RL_QuadDec_COUNTER_SIZE == RL_QuadDec_COUNTER_SIZE_32_BIT */

    RL_QuadDec_STATUS_MASK = mask;
}


/*******************************************************************************
* Function Name: RL_QuadDec_GetInterruptMask
********************************************************************************
*
* Summary:
*  Reports the current interrupt mask settings.
*
* Parameters:
*  None.
*
* Return:
*  Enable / disable bits in an 8-bit value, where 1 enables the interrupt.
*  For the 32-bit counter, the overflow, underflow and reset enable bits are
*  always set.
*
*******************************************************************************/
uint8 RL_QuadDec_GetInterruptMask(void) 
{
    return (RL_QuadDec_STATUS_MASK & RL_QuadDec_INIT_INT_MASK);
}


/* [] END OF FILE */
