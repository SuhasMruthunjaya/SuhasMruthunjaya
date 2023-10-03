/*******************************************************************************
* File Name: SYSCOUNTER.c  
* Version 3.0
*
*  Description:
*     The Counter component consists of a 8, 16, 24 or 32-bit counter with
*     a selectable period between 2 and 2^Width - 1.  
*
*   Note:
*     None
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "SYSCOUNTER.h"

uint8 SYSCOUNTER_initVar = 0u;


/*******************************************************************************
* Function Name: SYSCOUNTER_Init
********************************************************************************
* Summary:
*     Initialize to the schematic state
* 
* Parameters:  
*  void  
*
* Return: 
*  void
*
*******************************************************************************/
void SYSCOUNTER_Init(void) 
{
        #if (!SYSCOUNTER_UsingFixedFunction && !SYSCOUNTER_ControlRegRemoved)
            uint8 ctrl;
        #endif /* (!SYSCOUNTER_UsingFixedFunction && !SYSCOUNTER_ControlRegRemoved) */
        
        #if(!SYSCOUNTER_UsingFixedFunction) 
            /* Interrupt State Backup for Critical Region*/
            uint8 SYSCOUNTER_interruptState;
        #endif /* (!SYSCOUNTER_UsingFixedFunction) */
        
        #if (SYSCOUNTER_UsingFixedFunction)
            /* Clear all bits but the enable bit (if it's already set for Timer operation */
            SYSCOUNTER_CONTROL &= SYSCOUNTER_CTRL_ENABLE;
            
            /* Clear the mode bits for continuous run mode */
            #if (CY_PSOC5A)
                SYSCOUNTER_CONTROL2 &= ((uint8)(~SYSCOUNTER_CTRL_MODE_MASK));
            #endif /* (CY_PSOC5A) */
            #if (CY_PSOC3 || CY_PSOC5LP)
                SYSCOUNTER_CONTROL3 &= ((uint8)(~SYSCOUNTER_CTRL_MODE_MASK));                
            #endif /* (CY_PSOC3 || CY_PSOC5LP) */
            /* Check if One Shot mode is enabled i.e. RunMode !=0*/
            #if (SYSCOUNTER_RunModeUsed != 0x0u)
                /* Set 3rd bit of Control register to enable one shot mode */
                SYSCOUNTER_CONTROL |= SYSCOUNTER_ONESHOT;
            #endif /* (SYSCOUNTER_RunModeUsed != 0x0u) */
            
            /* Set the IRQ to use the status register interrupts */
            SYSCOUNTER_CONTROL2 |= SYSCOUNTER_CTRL2_IRQ_SEL;
            
            /* Clear and Set SYNCTC and SYNCCMP bits of RT1 register */
            SYSCOUNTER_RT1 &= ((uint8)(~SYSCOUNTER_RT1_MASK));
            SYSCOUNTER_RT1 |= SYSCOUNTER_SYNC;     
                    
            /*Enable DSI Sync all all inputs of the Timer*/
            SYSCOUNTER_RT1 &= ((uint8)(~SYSCOUNTER_SYNCDSI_MASK));
            SYSCOUNTER_RT1 |= SYSCOUNTER_SYNCDSI_EN;

        #else
            #if(!SYSCOUNTER_ControlRegRemoved)
            /* Set the default compare mode defined in the parameter */
            ctrl = SYSCOUNTER_CONTROL & ((uint8)(~SYSCOUNTER_CTRL_CMPMODE_MASK));
            SYSCOUNTER_CONTROL = ctrl | SYSCOUNTER_DEFAULT_COMPARE_MODE;
            
            /* Set the default capture mode defined in the parameter */
            ctrl = SYSCOUNTER_CONTROL & ((uint8)(~SYSCOUNTER_CTRL_CAPMODE_MASK));
            
            #if( 0 != SYSCOUNTER_CAPTURE_MODE_CONF)
                SYSCOUNTER_CONTROL = ctrl | SYSCOUNTER_DEFAULT_CAPTURE_MODE;
            #else
                SYSCOUNTER_CONTROL = ctrl;
            #endif /* 0 != SYSCOUNTER_CAPTURE_MODE */ 
            
            #endif /* (!SYSCOUNTER_ControlRegRemoved) */
        #endif /* (SYSCOUNTER_UsingFixedFunction) */
        
        /* Clear all data in the FIFO's */
        #if (!SYSCOUNTER_UsingFixedFunction)
            SYSCOUNTER_ClearFIFO();
        #endif /* (!SYSCOUNTER_UsingFixedFunction) */
        
        /* Set Initial values from Configuration */
        SYSCOUNTER_WritePeriod(SYSCOUNTER_INIT_PERIOD_VALUE);
        #if (!(SYSCOUNTER_UsingFixedFunction && (CY_PSOC5A)))
            SYSCOUNTER_WriteCounter(SYSCOUNTER_INIT_COUNTER_VALUE);
        #endif /* (!(SYSCOUNTER_UsingFixedFunction && (CY_PSOC5A))) */
        SYSCOUNTER_SetInterruptMode(SYSCOUNTER_INIT_INTERRUPTS_MASK);
        
        #if (!SYSCOUNTER_UsingFixedFunction)
            /* Read the status register to clear the unwanted interrupts */
            (void)SYSCOUNTER_ReadStatusRegister();
            /* Set the compare value (only available to non-fixed function implementation */
            SYSCOUNTER_WriteCompare(SYSCOUNTER_INIT_COMPARE_VALUE);
            /* Use the interrupt output of the status register for IRQ output */
            
            /* CyEnterCriticalRegion and CyExitCriticalRegion are used to mark following region critical*/
            /* Enter Critical Region*/
            SYSCOUNTER_interruptState = CyEnterCriticalSection();
            
            SYSCOUNTER_STATUS_AUX_CTRL |= SYSCOUNTER_STATUS_ACTL_INT_EN_MASK;
            
            /* Exit Critical Region*/
            CyExitCriticalSection(SYSCOUNTER_interruptState);
            
        #endif /* (!SYSCOUNTER_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: SYSCOUNTER_Enable
********************************************************************************
* Summary:
*     Enable the Counter
* 
* Parameters:  
*  void  
*
* Return: 
*  void
*
* Side Effects: 
*   If the Enable mode is set to Hardware only then this function has no effect 
*   on the operation of the counter.
*
*******************************************************************************/
void SYSCOUNTER_Enable(void) 
{
    /* Globally Enable the Fixed Function Block chosen */
    #if (SYSCOUNTER_UsingFixedFunction)
        SYSCOUNTER_GLOBAL_ENABLE |= SYSCOUNTER_BLOCK_EN_MASK;
        SYSCOUNTER_GLOBAL_STBY_ENABLE |= SYSCOUNTER_BLOCK_STBY_EN_MASK;
    #endif /* (SYSCOUNTER_UsingFixedFunction) */  
        
    /* Enable the counter from the control register  */
    /* If Fixed Function then make sure Mode is set correctly */
    /* else make sure reset is clear */
    #if(!SYSCOUNTER_ControlRegRemoved || SYSCOUNTER_UsingFixedFunction)
        SYSCOUNTER_CONTROL |= SYSCOUNTER_CTRL_ENABLE;                
    #endif /* (!SYSCOUNTER_ControlRegRemoved || SYSCOUNTER_UsingFixedFunction) */
    
}


/*******************************************************************************
* Function Name: SYSCOUNTER_Start
********************************************************************************
* Summary:
*  Enables the counter for operation 
*
* Parameters:  
*  void  
*
* Return: 
*  void
*
* Global variables:
*  SYSCOUNTER_initVar: Is modified when this function is called for the  
*   first time. Is used to ensure that initialization happens only once.
*
*******************************************************************************/
void SYSCOUNTER_Start(void) 
{
    if(SYSCOUNTER_initVar == 0u)
    {
        SYSCOUNTER_Init();
        
        SYSCOUNTER_initVar = 1u; /* Clear this bit for Initialization */        
    }
    
    /* Enable the Counter */
    SYSCOUNTER_Enable();        
}


/*******************************************************************************
* Function Name: SYSCOUNTER_Stop
********************************************************************************
* Summary:
* Halts the counter, but does not change any modes or disable interrupts.
*
* Parameters:  
*  void  
*
* Return: 
*  void
*
* Side Effects: If the Enable mode is set to Hardware only then this function
*               has no effect on the operation of the counter.
*
*******************************************************************************/
void SYSCOUNTER_Stop(void) 
{
    /* Disable Counter */
    #if(!SYSCOUNTER_ControlRegRemoved || SYSCOUNTER_UsingFixedFunction)
        SYSCOUNTER_CONTROL &= ((uint8)(~SYSCOUNTER_CTRL_ENABLE));        
    #endif /* (!SYSCOUNTER_ControlRegRemoved || SYSCOUNTER_UsingFixedFunction) */
    
    /* Globally disable the Fixed Function Block chosen */
    #if (SYSCOUNTER_UsingFixedFunction)
        SYSCOUNTER_GLOBAL_ENABLE &= ((uint8)(~SYSCOUNTER_BLOCK_EN_MASK));
        SYSCOUNTER_GLOBAL_STBY_ENABLE &= ((uint8)(~SYSCOUNTER_BLOCK_STBY_EN_MASK));
    #endif /* (SYSCOUNTER_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: SYSCOUNTER_SetInterruptMode
********************************************************************************
* Summary:
* Configures which interrupt sources are enabled to generate the final interrupt
*
* Parameters:  
*  InterruptsMask: This parameter is an or'd collection of the status bits
*                   which will be allowed to generate the counters interrupt.   
*
* Return: 
*  void
*
*******************************************************************************/
void SYSCOUNTER_SetInterruptMode(uint8 interruptsMask) 
{
    SYSCOUNTER_STATUS_MASK = interruptsMask;
}


/*******************************************************************************
* Function Name: SYSCOUNTER_ReadStatusRegister
********************************************************************************
* Summary:
*   Reads the status register and returns it's state. This function should use
*       defined types for the bit-field information as the bits in this
*       register may be permuteable.
*
* Parameters:  
*  void
*
* Return: 
*  (uint8) The contents of the status register
*
* Side Effects:
*   Status register bits may be clear on read. 
*
*******************************************************************************/
uint8   SYSCOUNTER_ReadStatusRegister(void) 
{
    return SYSCOUNTER_STATUS;
}


#if(!SYSCOUNTER_ControlRegRemoved)
/*******************************************************************************
* Function Name: SYSCOUNTER_ReadControlRegister
********************************************************************************
* Summary:
*   Reads the control register and returns it's state. This function should use
*       defined types for the bit-field information as the bits in this
*       register may be permuteable.
*
* Parameters:  
*  void
*
* Return: 
*  (uint8) The contents of the control register
*
*******************************************************************************/
uint8   SYSCOUNTER_ReadControlRegister(void) 
{
    return SYSCOUNTER_CONTROL;
}


/*******************************************************************************
* Function Name: SYSCOUNTER_WriteControlRegister
********************************************************************************
* Summary:
*   Sets the bit-field of the control register.  This function should use
*       defined types for the bit-field information as the bits in this
*       register may be permuteable.
*
* Parameters:  
*  void
*
* Return: 
*  (uint8) The contents of the control register
*
*******************************************************************************/
void    SYSCOUNTER_WriteControlRegister(uint8 control) 
{
    SYSCOUNTER_CONTROL = control;
}

#endif  /* (!SYSCOUNTER_ControlRegRemoved) */


#if (!(SYSCOUNTER_UsingFixedFunction && (CY_PSOC5A)))
/*******************************************************************************
* Function Name: SYSCOUNTER_WriteCounter
********************************************************************************
* Summary:
*   This funtion is used to set the counter to a specific value
*
* Parameters:  
*  counter:  New counter value. 
*
* Return: 
*  void 
*
*******************************************************************************/
void SYSCOUNTER_WriteCounter(uint16 counter) \
                                   
{
    #if(SYSCOUNTER_UsingFixedFunction)
        /* assert if block is already enabled */
        CYASSERT (0u == (SYSCOUNTER_GLOBAL_ENABLE & SYSCOUNTER_BLOCK_EN_MASK));
        /* If block is disabled, enable it and then write the counter */
        SYSCOUNTER_GLOBAL_ENABLE |= SYSCOUNTER_BLOCK_EN_MASK;
        CY_SET_REG16(SYSCOUNTER_COUNTER_LSB_PTR, (uint16)counter);
        SYSCOUNTER_GLOBAL_ENABLE &= ((uint8)(~SYSCOUNTER_BLOCK_EN_MASK));
    #else
        CY_SET_REG16(SYSCOUNTER_COUNTER_LSB_PTR, counter);
    #endif /* (SYSCOUNTER_UsingFixedFunction) */
}
#endif /* (!(SYSCOUNTER_UsingFixedFunction && (CY_PSOC5A))) */


/*******************************************************************************
* Function Name: SYSCOUNTER_ReadCounter
********************************************************************************
* Summary:
* Returns the current value of the counter.  It doesn't matter
* if the counter is enabled or running.
*
* Parameters:  
*  void:  
*
* Return: 
*  (uint16) The present value of the counter.
*
*******************************************************************************/
uint16 SYSCOUNTER_ReadCounter(void) 
{
    /* Force capture by reading Accumulator */
    /* Must first do a software capture to be able to read the counter */
    /* It is up to the user code to make sure there isn't already captured data in the FIFO */
    #if(SYSCOUNTER_UsingFixedFunction)
		(void)CY_GET_REG16(SYSCOUNTER_COUNTER_LSB_PTR);
	#else
		(void)CY_GET_REG8(SYSCOUNTER_COUNTER_LSB_PTR_8BIT);
	#endif/* (SYSCOUNTER_UsingFixedFunction) */
    
    /* Read the data from the FIFO (or capture register for Fixed Function)*/
    #if(SYSCOUNTER_UsingFixedFunction)
        return ((uint16)CY_GET_REG16(SYSCOUNTER_STATICCOUNT_LSB_PTR));
    #else
        return (CY_GET_REG16(SYSCOUNTER_STATICCOUNT_LSB_PTR));
    #endif /* (SYSCOUNTER_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: SYSCOUNTER_ReadCapture
********************************************************************************
* Summary:
*   This function returns the last value captured.
*
* Parameters:  
*  void
*
* Return: 
*  (uint16) Present Capture value.
*
*******************************************************************************/
uint16 SYSCOUNTER_ReadCapture(void) 
{
    #if(SYSCOUNTER_UsingFixedFunction)
        return ((uint16)CY_GET_REG16(SYSCOUNTER_STATICCOUNT_LSB_PTR));
    #else
        return (CY_GET_REG16(SYSCOUNTER_STATICCOUNT_LSB_PTR));
    #endif /* (SYSCOUNTER_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: SYSCOUNTER_WritePeriod
********************************************************************************
* Summary:
* Changes the period of the counter.  The new period 
* will be loaded the next time terminal count is detected.
*
* Parameters:  
*  period: (uint16) A value of 0 will result in
*         the counter remaining at zero.  
*
* Return: 
*  void
*
*******************************************************************************/
void SYSCOUNTER_WritePeriod(uint16 period) 
{
    #if(SYSCOUNTER_UsingFixedFunction)
        CY_SET_REG16(SYSCOUNTER_PERIOD_LSB_PTR,(uint16)period);
    #else
        CY_SET_REG16(SYSCOUNTER_PERIOD_LSB_PTR, period);
    #endif /* (SYSCOUNTER_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: SYSCOUNTER_ReadPeriod
********************************************************************************
* Summary:
* Reads the current period value without affecting counter operation.
*
* Parameters:  
*  void:  
*
* Return: 
*  (uint16) Present period value.
*
*******************************************************************************/
uint16 SYSCOUNTER_ReadPeriod(void) 
{
    #if(SYSCOUNTER_UsingFixedFunction)
        return ((uint16)CY_GET_REG16(SYSCOUNTER_PERIOD_LSB_PTR));
    #else
        return (CY_GET_REG16(SYSCOUNTER_PERIOD_LSB_PTR));
    #endif /* (SYSCOUNTER_UsingFixedFunction) */
}


#if (!SYSCOUNTER_UsingFixedFunction)
/*******************************************************************************
* Function Name: SYSCOUNTER_WriteCompare
********************************************************************************
* Summary:
* Changes the compare value.  The compare output will 
* reflect the new value on the next UDB clock.  The compare output will be 
* driven high when the present counter value compares true based on the 
* configured compare mode setting. 
*
* Parameters:  
*  Compare:  New compare value. 
*
* Return: 
*  void
*
*******************************************************************************/
void SYSCOUNTER_WriteCompare(uint16 compare) \
                                   
{
    #if(SYSCOUNTER_UsingFixedFunction)
        CY_SET_REG16(SYSCOUNTER_COMPARE_LSB_PTR, (uint16)compare);
    #else
        CY_SET_REG16(SYSCOUNTER_COMPARE_LSB_PTR, compare);
    #endif /* (SYSCOUNTER_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: SYSCOUNTER_ReadCompare
********************************************************************************
* Summary:
* Returns the compare value.
*
* Parameters:  
*  void:
*
* Return: 
*  (uint16) Present compare value.
*
*******************************************************************************/
uint16 SYSCOUNTER_ReadCompare(void) 
{
    return (CY_GET_REG16(SYSCOUNTER_COMPARE_LSB_PTR));
}


#if (SYSCOUNTER_COMPARE_MODE_SOFTWARE)
/*******************************************************************************
* Function Name: SYSCOUNTER_SetCompareMode
********************************************************************************
* Summary:
*  Sets the software controlled Compare Mode.
*
* Parameters:
*  compareMode:  Compare Mode Enumerated Type.
*
* Return:
*  void
*
*******************************************************************************/
void SYSCOUNTER_SetCompareMode(uint8 compareMode) 
{
    /* Clear the compare mode bits in the control register */
    SYSCOUNTER_CONTROL &= ((uint8)(~SYSCOUNTER_CTRL_CMPMODE_MASK));
    
    /* Write the new setting */
    SYSCOUNTER_CONTROL |= compareMode;
}
#endif  /* (SYSCOUNTER_COMPARE_MODE_SOFTWARE) */


#if (SYSCOUNTER_CAPTURE_MODE_SOFTWARE)
/*******************************************************************************
* Function Name: SYSCOUNTER_SetCaptureMode
********************************************************************************
* Summary:
*  Sets the software controlled Capture Mode.
*
* Parameters:
*  captureMode:  Capture Mode Enumerated Type.
*
* Return:
*  void
*
*******************************************************************************/
void SYSCOUNTER_SetCaptureMode(uint8 captureMode) 
{
    /* Clear the capture mode bits in the control register */
    SYSCOUNTER_CONTROL &= ((uint8)(~SYSCOUNTER_CTRL_CAPMODE_MASK));
    
    /* Write the new setting */
    SYSCOUNTER_CONTROL |= ((uint8)((uint8)captureMode << SYSCOUNTER_CTRL_CAPMODE0_SHIFT));
}
#endif  /* (SYSCOUNTER_CAPTURE_MODE_SOFTWARE) */


/*******************************************************************************
* Function Name: SYSCOUNTER_ClearFIFO
********************************************************************************
* Summary:
*   This function clears all capture data from the capture FIFO
*
* Parameters:  
*  void:
*
* Return: 
*  None
*
*******************************************************************************/
void SYSCOUNTER_ClearFIFO(void) 
{

    while(0u != (SYSCOUNTER_ReadStatusRegister() & SYSCOUNTER_STATUS_FIFONEMP))
    {
        (void)SYSCOUNTER_ReadCapture();
    }

}
#endif  /* (!SYSCOUNTER_UsingFixedFunction) */


/* [] END OF FILE */

