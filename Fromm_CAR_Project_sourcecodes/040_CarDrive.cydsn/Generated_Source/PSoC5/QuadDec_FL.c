/*******************************************************************************
* File Name: QuadDec_FL.c  
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

#include "QuadDec_FL.h"

#if (QuadDec_FL_COUNTER_SIZE == QuadDec_FL_COUNTER_SIZE_32_BIT)
    #include "QuadDec_FL_PVT.h"
#endif /* QuadDec_FL_COUNTER_SIZE == QuadDec_FL_COUNTER_SIZE_32_BIT */

uint8 QuadDec_FL_initVar = 0u;


/*******************************************************************************
* Function Name: QuadDec_FL_Init
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
void QuadDec_FL_Init(void) 
{
    #if (QuadDec_FL_COUNTER_SIZE == QuadDec_FL_COUNTER_SIZE_32_BIT)
        /* Disable Interrupt. */
        CyIntDisable(QuadDec_FL_ISR_NUMBER);
        /* Set the ISR to point to the QuadDec_FL_isr Interrupt. */
        (void) CyIntSetVector(QuadDec_FL_ISR_NUMBER, & QuadDec_FL_ISR);
        /* Set the priority. */
        CyIntSetPriority(QuadDec_FL_ISR_NUMBER, QuadDec_FL_ISR_PRIORITY);
    #endif /* QuadDec_FL_COUNTER_SIZE == QuadDec_FL_COUNTER_SIZE_32_BIT */
}


/*******************************************************************************
* Function Name: QuadDec_FL_Enable
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
void QuadDec_FL_Enable(void) 
{
    uint8 enableInterrupts;

    QuadDec_FL_SetInterruptMask(QuadDec_FL_INIT_INT_MASK);

    /* Clear pending interrupts. */
    (void) QuadDec_FL_GetEvents();
    
    enableInterrupts = CyEnterCriticalSection();

    /* Enable interrupts from Statusi register */
    QuadDec_FL_SR_AUX_CONTROL |= QuadDec_FL_INTERRUPTS_ENABLE;

    CyExitCriticalSection(enableInterrupts);        

    #if (QuadDec_FL_COUNTER_SIZE == QuadDec_FL_COUNTER_SIZE_32_BIT)
        /* Enable Component interrupts */
        CyIntEnable(QuadDec_FL_ISR_NUMBER);
    #endif /* QuadDec_FL_COUNTER_SIZE == QuadDec_FL_COUNTER_SIZE_32_BIT */
}


/*******************************************************************************
* Function Name: QuadDec_FL_Start
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
*  QuadDec_FL_initVar - used to check initial configuration, modified on
*  first function call.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void QuadDec_FL_Start(void) 
{
    #if (QuadDec_FL_COUNTER_SIZE == QuadDec_FL_COUNTER_SIZE_8_BIT)
        QuadDec_FL_Cnt8_Start();
        QuadDec_FL_Cnt8_WriteCounter(QuadDec_FL_COUNTER_INIT_VALUE);
    #else
        /* (QuadDec_FL_COUNTER_SIZE == QuadDec_FL_COUNTER_SIZE_16_BIT) || 
        *  (QuadDec_FL_COUNTER_SIZE == QuadDec_FL_COUNTER_SIZE_32_BIT) 
        */
        QuadDec_FL_Cnt16_Start();
        QuadDec_FL_Cnt16_WriteCounter(QuadDec_FL_COUNTER_INIT_VALUE);
    #endif /* QuadDec_FL_COUNTER_SIZE == QuadDec_FL_COUNTER_SIZE_8_BIT */
    
    #if (QuadDec_FL_COUNTER_SIZE == QuadDec_FL_COUNTER_SIZE_32_BIT)        
       QuadDec_FL_count32SoftPart = 0;
    #endif /* QuadDec_FL_COUNTER_SIZE == QuadDec_FL_COUNTER_SIZE_32_BIT */

    if (QuadDec_FL_initVar == 0u)
    {
        QuadDec_FL_Init();
        QuadDec_FL_initVar = 1u;
    }

    QuadDec_FL_Enable();
}


/*******************************************************************************
* Function Name: QuadDec_FL_Stop
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
void QuadDec_FL_Stop(void) 
{
    uint8 enableInterrupts;

    #if (QuadDec_FL_COUNTER_SIZE == QuadDec_FL_COUNTER_SIZE_8_BIT)
        QuadDec_FL_Cnt8_Stop();
    #else 
        /* (QuadDec_FL_COUNTER_SIZE == QuadDec_FL_COUNTER_SIZE_16_BIT) ||
        *  (QuadDec_FL_COUNTER_SIZE == QuadDec_FL_COUNTER_SIZE_32_BIT)
        */
        QuadDec_FL_Cnt16_Stop();    /* counter disable */
    #endif /* (QuadDec_FL_COUNTER_SIZE == QuadDec_FL_COUNTER_SIZE_8_BIT) */
 
    enableInterrupts = CyEnterCriticalSection();

    /* Disable interrupts interrupts from Statusi register */
    QuadDec_FL_SR_AUX_CONTROL &= (uint8) (~QuadDec_FL_INTERRUPTS_ENABLE);

    CyExitCriticalSection(enableInterrupts);

    #if (QuadDec_FL_COUNTER_SIZE == QuadDec_FL_COUNTER_SIZE_32_BIT)
        CyIntDisable(QuadDec_FL_ISR_NUMBER);    /* interrupt disable */
    #endif /* QuadDec_FL_COUNTER_SIZE == QuadDec_FL_COUNTER_SIZE_32_BIT */
}


/*******************************************************************************
* Function Name: QuadDec_FL_GetCounter
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
*  QuadDec_FL_count32SoftPart - used to get hi 16 bit for current value
*  of the 32-bit counter, when Counter size equal 32-bit.
*
*******************************************************************************/
int32 QuadDec_FL_GetCounter(void) 
{
    int32 count;
    uint16 tmpCnt;

    #if (QuadDec_FL_COUNTER_SIZE == QuadDec_FL_COUNTER_SIZE_32_BIT)
        int16 hwCount;

        CyIntDisable(QuadDec_FL_ISR_NUMBER);

        tmpCnt = QuadDec_FL_Cnt16_ReadCounter();
        hwCount = (int16) ((int32) tmpCnt - (int32) QuadDec_FL_COUNTER_INIT_VALUE);
        count = QuadDec_FL_count32SoftPart + hwCount;

        CyIntEnable(QuadDec_FL_ISR_NUMBER);
    #else 
        /* (QuadDec_FL_COUNTER_SIZE == QuadDec_FL_COUNTER_SIZE_8_BIT) || 
        *  (QuadDec_FL_COUNTER_SIZE == QuadDec_FL_COUNTER_SIZE_16_BIT)
        */
        #if (QuadDec_FL_COUNTER_SIZE == QuadDec_FL_COUNTER_SIZE_8_BIT)
            tmpCnt = QuadDec_FL_Cnt8_ReadCounter();
        #else /* (QuadDec_FL_COUNTER_SIZE == QuadDec_FL_COUNTER_SIZE_16_BIT) */
            tmpCnt = QuadDec_FL_Cnt16_ReadCounter();
        #endif  /* QuadDec_FL_COUNTER_SIZE == QuadDec_FL_COUNTER_SIZE_8_BIT */

        count = (int32) ((int32) tmpCnt -
                (int32) QuadDec_FL_COUNTER_INIT_VALUE);

    #endif /* QuadDec_FL_COUNTER_SIZE == QuadDec_FL_COUNTER_SIZE_32_BIT */ 

    return (count);
}


/*******************************************************************************
* Function Name: QuadDec_FL_SetCounter
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
*  QuadDec_FL_count32SoftPart - modified to set hi 16 bit for current
*  value of the 32-bit counter, when Counter size equal 32-bit.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void QuadDec_FL_SetCounter(int32 value) 
{
    #if ((QuadDec_FL_COUNTER_SIZE == QuadDec_FL_COUNTER_SIZE_8_BIT) || \
         (QuadDec_FL_COUNTER_SIZE == QuadDec_FL_COUNTER_SIZE_16_BIT))
        uint16 count;
        
        if (value >= 0)
        {
            count = (uint16) value + QuadDec_FL_COUNTER_INIT_VALUE;
        }
        else
        {
            count = QuadDec_FL_COUNTER_INIT_VALUE - (uint16)(-value);
        }
        #if (QuadDec_FL_COUNTER_SIZE == QuadDec_FL_COUNTER_SIZE_8_BIT)
            QuadDec_FL_Cnt8_WriteCounter(count);
        #else /* (QuadDec_FL_COUNTER_SIZE == QuadDec_FL_COUNTER_SIZE_16_BIT) */
            QuadDec_FL_Cnt16_WriteCounter(count);
        #endif  /* QuadDec_FL_COUNTER_SIZE == QuadDec_FL_COUNTER_SIZE_8_BIT */
    #else /* (QuadDec_FL_COUNTER_SIZE == QuadDec_FL_COUNTER_SIZE_32_BIT) */
        CyIntDisable(QuadDec_FL_ISR_NUMBER);

        QuadDec_FL_Cnt16_WriteCounter(QuadDec_FL_COUNTER_INIT_VALUE);
        QuadDec_FL_count32SoftPart = value;

        CyIntEnable(QuadDec_FL_ISR_NUMBER);
    #endif  /* (QuadDec_FL_COUNTER_SIZE == QuadDec_FL_COUNTER_SIZE_8_BIT) ||
             * (QuadDec_FL_COUNTER_SIZE == QuadDec_FL_COUNTER_SIZE_16_BIT)
             */
}


/*******************************************************************************
* Function Name: QuadDec_FL_GetEvents
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
uint8 QuadDec_FL_GetEvents(void) 
{
    return (QuadDec_FL_STATUS_REG & QuadDec_FL_INIT_INT_MASK);
}


/*******************************************************************************
* Function Name: QuadDec_FL_SetInterruptMask
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
void QuadDec_FL_SetInterruptMask(uint8 mask) 
{
    #if (QuadDec_FL_COUNTER_SIZE == QuadDec_FL_COUNTER_SIZE_32_BIT)
        /* Underflow, Overflow and Reset interrupts for 32-bit Counter are always enable */
        mask |= (QuadDec_FL_COUNTER_OVERFLOW | QuadDec_FL_COUNTER_UNDERFLOW |
                 QuadDec_FL_COUNTER_RESET);
    #endif /* QuadDec_FL_COUNTER_SIZE == QuadDec_FL_COUNTER_SIZE_32_BIT */

    QuadDec_FL_STATUS_MASK = mask;
}


/*******************************************************************************
* Function Name: QuadDec_FL_GetInterruptMask
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
uint8 QuadDec_FL_GetInterruptMask(void) 
{
    return (QuadDec_FL_STATUS_MASK & QuadDec_FL_INIT_INT_MASK);
}


/* [] END OF FILE */
