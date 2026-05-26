/*******************************************************************************
* File Name: ENGINE_DECODER_isr.h
* Version 1.70
*
*  Description:
*   Provides the function definitions for the Interrupt Controller.
*
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/
#if !defined(CY_ISR_ENGINE_DECODER_isr_H)
#define CY_ISR_ENGINE_DECODER_isr_H


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void ENGINE_DECODER_isr_Start(void);
void ENGINE_DECODER_isr_StartEx(cyisraddress address);
void ENGINE_DECODER_isr_Stop(void);

CY_ISR_PROTO(ENGINE_DECODER_isr_Interrupt);

void ENGINE_DECODER_isr_SetVector(cyisraddress address);
cyisraddress ENGINE_DECODER_isr_GetVector(void);

void ENGINE_DECODER_isr_SetPriority(uint8 priority);
uint8 ENGINE_DECODER_isr_GetPriority(void);

void ENGINE_DECODER_isr_Enable(void);
uint8 ENGINE_DECODER_isr_GetState(void);
void ENGINE_DECODER_isr_Disable(void);

void ENGINE_DECODER_isr_SetPending(void);
void ENGINE_DECODER_isr_ClearPending(void);


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the ENGINE_DECODER_isr ISR. */
#define ENGINE_DECODER_isr_INTC_VECTOR            ((reg32 *) ENGINE_DECODER_isr__INTC_VECT)

/* Address of the ENGINE_DECODER_isr ISR priority. */
#define ENGINE_DECODER_isr_INTC_PRIOR             ((reg8 *) ENGINE_DECODER_isr__INTC_PRIOR_REG)

/* Priority of the ENGINE_DECODER_isr interrupt. */
#define ENGINE_DECODER_isr_INTC_PRIOR_NUMBER      ENGINE_DECODER_isr__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable ENGINE_DECODER_isr interrupt. */
#define ENGINE_DECODER_isr_INTC_SET_EN            ((reg32 *) ENGINE_DECODER_isr__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the ENGINE_DECODER_isr interrupt. */
#define ENGINE_DECODER_isr_INTC_CLR_EN            ((reg32 *) ENGINE_DECODER_isr__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the ENGINE_DECODER_isr interrupt state to pending. */
#define ENGINE_DECODER_isr_INTC_SET_PD            ((reg32 *) ENGINE_DECODER_isr__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the ENGINE_DECODER_isr interrupt. */
#define ENGINE_DECODER_isr_INTC_CLR_PD            ((reg32 *) ENGINE_DECODER_isr__INTC_CLR_PD_REG)


#endif /* CY_ISR_ENGINE_DECODER_isr_H */


/* [] END OF FILE */
