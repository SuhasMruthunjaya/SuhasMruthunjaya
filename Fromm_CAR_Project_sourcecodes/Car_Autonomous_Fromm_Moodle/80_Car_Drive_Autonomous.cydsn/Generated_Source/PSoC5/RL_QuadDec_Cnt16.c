/*******************************************************************************
* File Name: RL_QuadDec_Cnt16.c  
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

#include "RL_QuadDec_Cnt16.h"

uint8 RL_QuadDec_Cnt16_initVar = 0u;


/*******************************************************************************
* Function Name: RL_QuadDec_Cnt16_Init
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
void RL_QuadDec_Cnt16_Init(void) 
{
        #if (!RL_QuadDec_Cnt16_UsingFixedFunction && !RL_QuadDec_Cnt16_ControlRegRemoved)
            uint8 ctrl;
        #endif /* (!RL_QuadDec_Cnt16_UsingFixedFunction && !RL_QuadDec_Cnt16_ControlRegRemoved) */
        
        #if(!RL_QuadDec_Cnt16_UsingFixedFunction) 
            /* Interrupt State Backup for Critical Region*/
            uint8 RL_QuadDec_Cnt16_interruptState;
        #endif /* (!RL_QuadDec_Cnt16_UsingFixedFunction) */
        
        #if (RL_QuadDec_Cnt16_UsingFixedFunction)
            /* Clear all bits but the enable bit (if it's already set for Timer operation */
            RL_QuadDec_Cnt16_CONTROL &= RL_QuadDec_Cnt16_CTRL_ENABLE;
            
            /* Clear the mode bits for continuous run mode */
            #if (CY_PSOC5A)
                RL_QuadDec_Cnt16_CONTROL2 &= ((uint8)(~RL_QuadDec_Cnt16_CTRL_MODE_MASK));
            #endif /* (CY_PSOC5A) */
            #if (CY_PSOC3 || CY_PSOC5LP)
                RL_QuadDec_Cnt16_CONTROL3 &= ((uint8)(~RL_QuadDec_Cnt16_CTRL_MODE_MASK));                
            #endif /* (CY_PSOC3 || CY_PSOC5LP) */
            /* Check if One Shot mode is enabled i.e. RunMode !=0*/
            #if (RL_QuadDec_Cnt16_RunModeUsed != 0x0u)
                /* Set 3rd bit of Control register to enable one shot mode */
                RL_QuadDec_Cnt16_CONTROL |= RL_QuadDec_Cnt16_ONESHOT;
            #endif /* (RL_QuadDec_Cnt16_RunModeUsed != 0x0u) */
            
            /* Set the IRQ to use the status register interrupts */
            RL_QuadDec_Cnt16_CONTROL2 |= RL_QuadDec_Cnt16_CTRL2_IRQ_SEL;
            
            /* Clear and Set SYNCTC and SYNCCMP bits of RT1 register */
            RL_QuadDec_Cnt16_RT1 &= ((uint8)(~RL_QuadDec_Cnt16_RT1_MASK));
            RL_QuadDec_Cnt16_RT1 |= RL_QuadDec_Cnt16_SYNC;     
                    
            /*Enable DSI Sync all all inputs of the Timer*/
            RL_QuadDec_Cnt16_RT1 &= ((uint8)(~RL_QuadDec_Cnt16_SYNCDSI_MASK));
            RL_QuadDec_Cnt16_RT1 |= RL_QuadDec_Cnt16_SYNCDSI_EN;

        #else
            #if(!RL_QuadDec_Cnt16_ControlRegRemoved)
            /* Set the default compare mode defined in the parameter */
            ctrl = RL_QuadDec_Cnt16_CONTROL & ((uint8)(~RL_QuadDec_Cnt16_CTRL_CMPMODE_MASK));
            RL_QuadDec_Cnt16_CONTROL = ctrl | RL_QuadDec_Cnt16_DEFAULT_COMPARE_MODE;
            
            /* Set the default capture mode defined in the parameter */
            ctrl = RL_QuadDec_Cnt16_CONTROL & ((uint8)(~RL_QuadDec_Cnt16_CTRL_CAPMODE_MASK));
            
            #if( 0 != RL_QuadDec_Cnt16_CAPTURE_MODE_CONF)
                RL_QuadDec_Cnt16_CONTROL = ctrl | RL_QuadDec_Cnt16_DEFAULT_CAPTURE_MODE;
            #else
                RL_QuadDec_Cnt16_CONTROL = ctrl;
            #endif /* 0 != RL_QuadDec_Cnt16_CAPTURE_MODE */ 
            
            #endif /* (!RL_QuadDec_Cnt16_ControlRegRemoved) */
        #endif /* (RL_QuadDec_Cnt16_UsingFixedFunction) */
        
        /* Clear all data in the FIFO's */
        #if (!RL_QuadDec_Cnt16_UsingFixedFunction)
            RL_QuadDec_Cnt16_ClearFIFO();
        #endif /* (!RL_QuadDec_Cnt16_UsingFixedFunction) */
        
        /* Set Initial values from Configuration */
        RL_QuadDec_Cnt16_WritePeriod(RL_QuadDec_Cnt16_INIT_PERIOD_VALUE);
        #if (!(RL_QuadDec_Cnt16_UsingFixedFunction && (CY_PSOC5A)))
            RL_QuadDec_Cnt16_WriteCounter(RL_QuadDec_Cnt16_INIT_COUNTER_VALUE);
        #endif /* (!(RL_QuadDec_Cnt16_UsingFixedFunction && (CY_PSOC5A))) */
        RL_QuadDec_Cnt16_SetInterruptMode(RL_QuadDec_Cnt16_INIT_INTERRUPTS_MASK);
        
        #if (!RL_QuadDec_Cnt16_UsingFixedFunction)
            /* Read the status register to clear the unwanted interrupts */
            (void)RL_QuadDec_Cnt16_ReadStatusRegister();
            /* Set the compare value (only available to non-fixed function implementation */
            RL_QuadDec_Cnt16_WriteCompare(RL_QuadDec_Cnt16_INIT_COMPARE_VALUE);
            /* Use the interrupt output of the status register for IRQ output */
            
            /* CyEnterCriticalRegion and CyExitCriticalRegion are used to mark following region critical*/
            /* Enter Critical Region*/
            RL_QuadDec_Cnt16_interruptState = CyEnterCriticalSection();
            
            RL_QuadDec_Cnt16_STATUS_AUX_CTRL |= RL_QuadDec_Cnt16_STATUS_ACTL_INT_EN_MASK;
            
            /* Exit Critical Region*/
            CyExitCriticalSection(RL_QuadDec_Cnt16_interruptState);
            
        #endif /* (!RL_QuadDec_Cnt16_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: RL_QuadDec_Cnt16_Enable
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
void RL_QuadDec_Cnt16_Enable(void) 
{
    /* Globally Enable the Fixed Function Block chosen */
    #if (RL_QuadDec_Cnt16_UsingFixedFunction)
        RL_QuadDec_Cnt16_GLOBAL_ENABLE |= RL_QuadDec_Cnt16_BLOCK_EN_MASK;
        RL_QuadDec_Cnt16_GLOBAL_STBY_ENABLE |= RL_QuadDec_Cnt16_BLOCK_STBY_EN_MASK;
    #endif /* (RL_QuadDec_Cnt16_UsingFixedFunction) */  
        
    /* Enable the counter from the control register  */
    /* If Fixed Function then make sure Mode is set correctly */
    /* else make sure reset is clear */
    #if(!RL_QuadDec_Cnt16_ControlRegRemoved || RL_QuadDec_Cnt16_UsingFixedFunction)
        RL_QuadDec_Cnt16_CONTROL |= RL_QuadDec_Cnt16_CTRL_ENABLE;                
    #endif /* (!RL_QuadDec_Cnt16_ControlRegRemoved || RL_QuadDec_Cnt16_UsingFixedFunction) */
    
}


/*******************************************************************************
* Function Name: RL_QuadDec_Cnt16_Start
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
*  RL_QuadDec_Cnt16_initVar: Is modified when this function is called for the  
*   first time. Is used to ensure that initialization happens only once.
*
*******************************************************************************/
void RL_QuadDec_Cnt16_Start(void) 
{
    if(RL_QuadDec_Cnt16_initVar == 0u)
    {
        RL_QuadDec_Cnt16_Init();
        
        RL_QuadDec_Cnt16_initVar = 1u; /* Clear this bit for Initialization */        
    }
    
    /* Enable the Counter */
    RL_QuadDec_Cnt16_Enable();        
}


/*******************************************************************************
* Function Name: RL_QuadDec_Cnt16_Stop
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
void RL_QuadDec_Cnt16_Stop(void) 
{
    /* Disable Counter */
    #if(!RL_QuadDec_Cnt16_ControlRegRemoved || RL_QuadDec_Cnt16_UsingFixedFunction)
        RL_QuadDec_Cnt16_CONTROL &= ((uint8)(~RL_QuadDec_Cnt16_CTRL_ENABLE));        
    #endif /* (!RL_QuadDec_Cnt16_ControlRegRemoved || RL_QuadDec_Cnt16_UsingFixedFunction) */
    
    /* Globally disable the Fixed Function Block chosen */
    #if (RL_QuadDec_Cnt16_UsingFixedFunction)
        RL_QuadDec_Cnt16_GLOBAL_ENABLE &= ((uint8)(~RL_QuadDec_Cnt16_BLOCK_EN_MASK));
        RL_QuadDec_Cnt16_GLOBAL_STBY_ENABLE &= ((uint8)(~RL_QuadDec_Cnt16_BLOCK_STBY_EN_MASK));
    #endif /* (RL_QuadDec_Cnt16_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: RL_QuadDec_Cnt16_SetInterruptMode
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
void RL_QuadDec_Cnt16_SetInterruptMode(uint8 interruptsMask) 
{
    RL_QuadDec_Cnt16_STATUS_MASK = interruptsMask;
}


/*******************************************************************************
* Function Name: RL_QuadDec_Cnt16_ReadStatusRegister
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
uint8   RL_QuadDec_Cnt16_ReadStatusRegister(void) 
{
    return RL_QuadDec_Cnt16_STATUS;
}


#if(!RL_QuadDec_Cnt16_ControlRegRemoved)
/*******************************************************************************
* Function Name: RL_QuadDec_Cnt16_ReadControlRegister
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
uint8   RL_QuadDec_Cnt16_ReadControlRegister(void) 
{
    return RL_QuadDec_Cnt16_CONTROL;
}


/*******************************************************************************
* Function Name: RL_QuadDec_Cnt16_WriteControlRegister
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
void    RL_QuadDec_Cnt16_WriteControlRegister(uint8 control) 
{
    RL_QuadDec_Cnt16_CONTROL = control;
}

#endif  /* (!RL_QuadDec_Cnt16_ControlRegRemoved) */


#if (!(RL_QuadDec_Cnt16_UsingFixedFunction && (CY_PSOC5A)))
/*******************************************************************************
* Function Name: RL_QuadDec_Cnt16_WriteCounter
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
void RL_QuadDec_Cnt16_WriteCounter(uint16 counter) \
                                   
{
    #if(RL_QuadDec_Cnt16_UsingFixedFunction)
        /* assert if block is already enabled */
        CYASSERT (0u == (RL_QuadDec_Cnt16_GLOBAL_ENABLE & RL_QuadDec_Cnt16_BLOCK_EN_MASK));
        /* If block is disabled, enable it and then write the counter */
        RL_QuadDec_Cnt16_GLOBAL_ENABLE |= RL_QuadDec_Cnt16_BLOCK_EN_MASK;
        CY_SET_REG16(RL_QuadDec_Cnt16_COUNTER_LSB_PTR, (uint16)counter);
        RL_QuadDec_Cnt16_GLOBAL_ENABLE &= ((uint8)(~RL_QuadDec_Cnt16_BLOCK_EN_MASK));
    #else
        CY_SET_REG16(RL_QuadDec_Cnt16_COUNTER_LSB_PTR, counter);
    #endif /* (RL_QuadDec_Cnt16_UsingFixedFunction) */
}
#endif /* (!(RL_QuadDec_Cnt16_UsingFixedFunction && (CY_PSOC5A))) */


/*******************************************************************************
* Function Name: RL_QuadDec_Cnt16_ReadCounter
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
uint16 RL_QuadDec_Cnt16_ReadCounter(void) 
{
    /* Force capture by reading Accumulator */
    /* Must first do a software capture to be able to read the counter */
    /* It is up to the user code to make sure there isn't already captured data in the FIFO */
    #if(RL_QuadDec_Cnt16_UsingFixedFunction)
		(void)CY_GET_REG16(RL_QuadDec_Cnt16_COUNTER_LSB_PTR);
	#else
		(void)CY_GET_REG8(RL_QuadDec_Cnt16_COUNTER_LSB_PTR_8BIT);
	#endif/* (RL_QuadDec_Cnt16_UsingFixedFunction) */
    
    /* Read the data from the FIFO (or capture register for Fixed Function)*/
    #if(RL_QuadDec_Cnt16_UsingFixedFunction)
        return ((uint16)CY_GET_REG16(RL_QuadDec_Cnt16_STATICCOUNT_LSB_PTR));
    #else
        return (CY_GET_REG16(RL_QuadDec_Cnt16_STATICCOUNT_LSB_PTR));
    #endif /* (RL_QuadDec_Cnt16_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: RL_QuadDec_Cnt16_ReadCapture
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
uint16 RL_QuadDec_Cnt16_ReadCapture(void) 
{
    #if(RL_QuadDec_Cnt16_UsingFixedFunction)
        return ((uint16)CY_GET_REG16(RL_QuadDec_Cnt16_STATICCOUNT_LSB_PTR));
    #else
        return (CY_GET_REG16(RL_QuadDec_Cnt16_STATICCOUNT_LSB_PTR));
    #endif /* (RL_QuadDec_Cnt16_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: RL_QuadDec_Cnt16_WritePeriod
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
void RL_QuadDec_Cnt16_WritePeriod(uint16 period) 
{
    #if(RL_QuadDec_Cnt16_UsingFixedFunction)
        CY_SET_REG16(RL_QuadDec_Cnt16_PERIOD_LSB_PTR,(uint16)period);
    #else
        CY_SET_REG16(RL_QuadDec_Cnt16_PERIOD_LSB_PTR, period);
    #endif /* (RL_QuadDec_Cnt16_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: RL_QuadDec_Cnt16_ReadPeriod
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
uint16 RL_QuadDec_Cnt16_ReadPeriod(void) 
{
    #if(RL_QuadDec_Cnt16_UsingFixedFunction)
        return ((uint16)CY_GET_REG16(RL_QuadDec_Cnt16_PERIOD_LSB_PTR));
    #else
        return (CY_GET_REG16(RL_QuadDec_Cnt16_PERIOD_LSB_PTR));
    #endif /* (RL_QuadDec_Cnt16_UsingFixedFunction) */
}


#if (!RL_QuadDec_Cnt16_UsingFixedFunction)
/*******************************************************************************
* Function Name: RL_QuadDec_Cnt16_WriteCompare
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
void RL_QuadDec_Cnt16_WriteCompare(uint16 compare) \
                                   
{
    #if(RL_QuadDec_Cnt16_UsingFixedFunction)
        CY_SET_REG16(RL_QuadDec_Cnt16_COMPARE_LSB_PTR, (uint16)compare);
    #else
        CY_SET_REG16(RL_QuadDec_Cnt16_COMPARE_LSB_PTR, compare);
    #endif /* (RL_QuadDec_Cnt16_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: RL_QuadDec_Cnt16_ReadCompare
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
uint16 RL_QuadDec_Cnt16_ReadCompare(void) 
{
    return (CY_GET_REG16(RL_QuadDec_Cnt16_COMPARE_LSB_PTR));
}


#if (RL_QuadDec_Cnt16_COMPARE_MODE_SOFTWARE)
/*******************************************************************************
* Function Name: RL_QuadDec_Cnt16_SetCompareMode
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
void RL_QuadDec_Cnt16_SetCompareMode(uint8 compareMode) 
{
    /* Clear the compare mode bits in the control register */
    RL_QuadDec_Cnt16_CONTROL &= ((uint8)(~RL_QuadDec_Cnt16_CTRL_CMPMODE_MASK));
    
    /* Write the new setting */
    RL_QuadDec_Cnt16_CONTROL |= compareMode;
}
#endif  /* (RL_QuadDec_Cnt16_COMPARE_MODE_SOFTWARE) */


#if (RL_QuadDec_Cnt16_CAPTURE_MODE_SOFTWARE)
/*******************************************************************************
* Function Name: RL_QuadDec_Cnt16_SetCaptureMode
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
void RL_QuadDec_Cnt16_SetCaptureMode(uint8 captureMode) 
{
    /* Clear the capture mode bits in the control register */
    RL_QuadDec_Cnt16_CONTROL &= ((uint8)(~RL_QuadDec_Cnt16_CTRL_CAPMODE_MASK));
    
    /* Write the new setting */
    RL_QuadDec_Cnt16_CONTROL |= ((uint8)((uint8)captureMode << RL_QuadDec_Cnt16_CTRL_CAPMODE0_SHIFT));
}
#endif  /* (RL_QuadDec_Cnt16_CAPTURE_MODE_SOFTWARE) */


/*******************************************************************************
* Function Name: RL_QuadDec_Cnt16_ClearFIFO
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
void RL_QuadDec_Cnt16_ClearFIFO(void) 
{

    while(0u != (RL_QuadDec_Cnt16_ReadStatusRegister() & RL_QuadDec_Cnt16_STATUS_FIFONEMP))
    {
        (void)RL_QuadDec_Cnt16_ReadCapture();
    }

}
#endif  /* (!RL_QuadDec_Cnt16_UsingFixedFunction) */


/* [] END OF FILE */

