/*******************************************************************************
* File Name: ENGINE_DECODER.c  
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

#include "ENGINE_DECODER.h"

#if (ENGINE_DECODER_COUNTER_SIZE == ENGINE_DECODER_COUNTER_SIZE_32_BIT)
    #include "ENGINE_DECODER_PVT.h"
#endif /* ENGINE_DECODER_COUNTER_SIZE == ENGINE_DECODER_COUNTER_SIZE_32_BIT */

uint8 ENGINE_DECODER_initVar = 0u;


/*******************************************************************************
* Function Name: ENGINE_DECODER_Init
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
void ENGINE_DECODER_Init(void) 
{
    #if (ENGINE_DECODER_COUNTER_SIZE == ENGINE_DECODER_COUNTER_SIZE_32_BIT)
        /* Disable Interrupt. */
        CyIntDisable(ENGINE_DECODER_ISR_NUMBER);
        /* Set the ISR to point to the ENGINE_DECODER_isr Interrupt. */
        (void) CyIntSetVector(ENGINE_DECODER_ISR_NUMBER, & ENGINE_DECODER_ISR);
        /* Set the priority. */
        CyIntSetPriority(ENGINE_DECODER_ISR_NUMBER, ENGINE_DECODER_ISR_PRIORITY);
    #endif /* ENGINE_DECODER_COUNTER_SIZE == ENGINE_DECODER_COUNTER_SIZE_32_BIT */
}


/*******************************************************************************
* Function Name: ENGINE_DECODER_Enable
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
void ENGINE_DECODER_Enable(void) 
{
    uint8 enableInterrupts;

    ENGINE_DECODER_SetInterruptMask(ENGINE_DECODER_INIT_INT_MASK);

    /* Clear pending interrupts. */
    (void) ENGINE_DECODER_GetEvents();
    
    enableInterrupts = CyEnterCriticalSection();

    /* Enable interrupts from Statusi register */
    ENGINE_DECODER_SR_AUX_CONTROL |= ENGINE_DECODER_INTERRUPTS_ENABLE;

    CyExitCriticalSection(enableInterrupts);        

    #if (ENGINE_DECODER_COUNTER_SIZE == ENGINE_DECODER_COUNTER_SIZE_32_BIT)
        /* Enable Component interrupts */
        CyIntEnable(ENGINE_DECODER_ISR_NUMBER);
    #endif /* ENGINE_DECODER_COUNTER_SIZE == ENGINE_DECODER_COUNTER_SIZE_32_BIT */
}


/*******************************************************************************
* Function Name: ENGINE_DECODER_Start
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
*  ENGINE_DECODER_initVar - used to check initial configuration, modified on
*  first function call.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void ENGINE_DECODER_Start(void) 
{
    #if (ENGINE_DECODER_COUNTER_SIZE == ENGINE_DECODER_COUNTER_SIZE_8_BIT)
        ENGINE_DECODER_Cnt8_Start();
        ENGINE_DECODER_Cnt8_WriteCounter(ENGINE_DECODER_COUNTER_INIT_VALUE);
    #else
        /* (ENGINE_DECODER_COUNTER_SIZE == ENGINE_DECODER_COUNTER_SIZE_16_BIT) || 
        *  (ENGINE_DECODER_COUNTER_SIZE == ENGINE_DECODER_COUNTER_SIZE_32_BIT) 
        */
        ENGINE_DECODER_Cnt16_Start();
        ENGINE_DECODER_Cnt16_WriteCounter(ENGINE_DECODER_COUNTER_INIT_VALUE);
    #endif /* ENGINE_DECODER_COUNTER_SIZE == ENGINE_DECODER_COUNTER_SIZE_8_BIT */
    
    #if (ENGINE_DECODER_COUNTER_SIZE == ENGINE_DECODER_COUNTER_SIZE_32_BIT)        
       ENGINE_DECODER_count32SoftPart = 0;
    #endif /* ENGINE_DECODER_COUNTER_SIZE == ENGINE_DECODER_COUNTER_SIZE_32_BIT */

    if (ENGINE_DECODER_initVar == 0u)
    {
        ENGINE_DECODER_Init();
        ENGINE_DECODER_initVar = 1u;
    }

    ENGINE_DECODER_Enable();
}


/*******************************************************************************
* Function Name: ENGINE_DECODER_Stop
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
void ENGINE_DECODER_Stop(void) 
{
    uint8 enableInterrupts;

    #if (ENGINE_DECODER_COUNTER_SIZE == ENGINE_DECODER_COUNTER_SIZE_8_BIT)
        ENGINE_DECODER_Cnt8_Stop();
    #else 
        /* (ENGINE_DECODER_COUNTER_SIZE == ENGINE_DECODER_COUNTER_SIZE_16_BIT) ||
        *  (ENGINE_DECODER_COUNTER_SIZE == ENGINE_DECODER_COUNTER_SIZE_32_BIT)
        */
        ENGINE_DECODER_Cnt16_Stop();    /* counter disable */
    #endif /* (ENGINE_DECODER_COUNTER_SIZE == ENGINE_DECODER_COUNTER_SIZE_8_BIT) */
 
    enableInterrupts = CyEnterCriticalSection();

    /* Disable interrupts interrupts from Statusi register */
    ENGINE_DECODER_SR_AUX_CONTROL &= (uint8) (~ENGINE_DECODER_INTERRUPTS_ENABLE);

    CyExitCriticalSection(enableInterrupts);

    #if (ENGINE_DECODER_COUNTER_SIZE == ENGINE_DECODER_COUNTER_SIZE_32_BIT)
        CyIntDisable(ENGINE_DECODER_ISR_NUMBER);    /* interrupt disable */
    #endif /* ENGINE_DECODER_COUNTER_SIZE == ENGINE_DECODER_COUNTER_SIZE_32_BIT */
}


/*******************************************************************************
* Function Name: ENGINE_DECODER_GetCounter
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
*  ENGINE_DECODER_count32SoftPart - used to get hi 16 bit for current value
*  of the 32-bit counter, when Counter size equal 32-bit.
*
*******************************************************************************/
int32 ENGINE_DECODER_GetCounter(void) 
{
    int32 count;
    uint16 tmpCnt;

    #if (ENGINE_DECODER_COUNTER_SIZE == ENGINE_DECODER_COUNTER_SIZE_32_BIT)
        int16 hwCount;

        CyIntDisable(ENGINE_DECODER_ISR_NUMBER);

        tmpCnt = ENGINE_DECODER_Cnt16_ReadCounter();
        hwCount = (int16) ((int32) tmpCnt - (int32) ENGINE_DECODER_COUNTER_INIT_VALUE);
        count = ENGINE_DECODER_count32SoftPart + hwCount;

        CyIntEnable(ENGINE_DECODER_ISR_NUMBER);
    #else 
        /* (ENGINE_DECODER_COUNTER_SIZE == ENGINE_DECODER_COUNTER_SIZE_8_BIT) || 
        *  (ENGINE_DECODER_COUNTER_SIZE == ENGINE_DECODER_COUNTER_SIZE_16_BIT)
        */
        #if (ENGINE_DECODER_COUNTER_SIZE == ENGINE_DECODER_COUNTER_SIZE_8_BIT)
            tmpCnt = ENGINE_DECODER_Cnt8_ReadCounter();
        #else /* (ENGINE_DECODER_COUNTER_SIZE == ENGINE_DECODER_COUNTER_SIZE_16_BIT) */
            tmpCnt = ENGINE_DECODER_Cnt16_ReadCounter();
        #endif  /* ENGINE_DECODER_COUNTER_SIZE == ENGINE_DECODER_COUNTER_SIZE_8_BIT */

        count = (int32) ((int32) tmpCnt -
                (int32) ENGINE_DECODER_COUNTER_INIT_VALUE);

    #endif /* ENGINE_DECODER_COUNTER_SIZE == ENGINE_DECODER_COUNTER_SIZE_32_BIT */ 

    return (count);
}


/*******************************************************************************
* Function Name: ENGINE_DECODER_SetCounter
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
*  ENGINE_DECODER_count32SoftPart - modified to set hi 16 bit for current
*  value of the 32-bit counter, when Counter size equal 32-bit.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void ENGINE_DECODER_SetCounter(int32 value) 
{
    #if ((ENGINE_DECODER_COUNTER_SIZE == ENGINE_DECODER_COUNTER_SIZE_8_BIT) || \
         (ENGINE_DECODER_COUNTER_SIZE == ENGINE_DECODER_COUNTER_SIZE_16_BIT))
        uint16 count;
        
        if (value >= 0)
        {
            count = (uint16) value + ENGINE_DECODER_COUNTER_INIT_VALUE;
        }
        else
        {
            count = ENGINE_DECODER_COUNTER_INIT_VALUE - (uint16)(-value);
        }
        #if (ENGINE_DECODER_COUNTER_SIZE == ENGINE_DECODER_COUNTER_SIZE_8_BIT)
            ENGINE_DECODER_Cnt8_WriteCounter(count);
        #else /* (ENGINE_DECODER_COUNTER_SIZE == ENGINE_DECODER_COUNTER_SIZE_16_BIT) */
            ENGINE_DECODER_Cnt16_WriteCounter(count);
        #endif  /* ENGINE_DECODER_COUNTER_SIZE == ENGINE_DECODER_COUNTER_SIZE_8_BIT */
    #else /* (ENGINE_DECODER_COUNTER_SIZE == ENGINE_DECODER_COUNTER_SIZE_32_BIT) */
        CyIntDisable(ENGINE_DECODER_ISR_NUMBER);

        ENGINE_DECODER_Cnt16_WriteCounter(ENGINE_DECODER_COUNTER_INIT_VALUE);
        ENGINE_DECODER_count32SoftPart = value;

        CyIntEnable(ENGINE_DECODER_ISR_NUMBER);
    #endif  /* (ENGINE_DECODER_COUNTER_SIZE == ENGINE_DECODER_COUNTER_SIZE_8_BIT) ||
             * (ENGINE_DECODER_COUNTER_SIZE == ENGINE_DECODER_COUNTER_SIZE_16_BIT)
             */
}


/*******************************************************************************
* Function Name: ENGINE_DECODER_GetEvents
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
uint8 ENGINE_DECODER_GetEvents(void) 
{
    return (ENGINE_DECODER_STATUS_REG & ENGINE_DECODER_INIT_INT_MASK);
}


/*******************************************************************************
* Function Name: ENGINE_DECODER_SetInterruptMask
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
void ENGINE_DECODER_SetInterruptMask(uint8 mask) 
{
    #if (ENGINE_DECODER_COUNTER_SIZE == ENGINE_DECODER_COUNTER_SIZE_32_BIT)
        /* Underflow, Overflow and Reset interrupts for 32-bit Counter are always enable */
        mask |= (ENGINE_DECODER_COUNTER_OVERFLOW | ENGINE_DECODER_COUNTER_UNDERFLOW |
                 ENGINE_DECODER_COUNTER_RESET);
    #endif /* ENGINE_DECODER_COUNTER_SIZE == ENGINE_DECODER_COUNTER_SIZE_32_BIT */

    ENGINE_DECODER_STATUS_MASK = mask;
}


/*******************************************************************************
* Function Name: ENGINE_DECODER_GetInterruptMask
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
uint8 ENGINE_DECODER_GetInterruptMask(void) 
{
    return (ENGINE_DECODER_STATUS_MASK & ENGINE_DECODER_INIT_INT_MASK);
}


/* [] END OF FILE */
