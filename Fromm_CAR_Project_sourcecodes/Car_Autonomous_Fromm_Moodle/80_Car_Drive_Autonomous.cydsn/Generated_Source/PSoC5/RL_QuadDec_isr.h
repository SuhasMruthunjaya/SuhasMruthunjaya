/*******************************************************************************
* File Name: RL_QuadDec_isr.h
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
#if !defined(CY_ISR_RL_QuadDec_isr_H)
#define CY_ISR_RL_QuadDec_isr_H


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void RL_QuadDec_isr_Start(void);
void RL_QuadDec_isr_StartEx(cyisraddress address);
void RL_QuadDec_isr_Stop(void);

CY_ISR_PROTO(RL_QuadDec_isr_Interrupt);

void RL_QuadDec_isr_SetVector(cyisraddress address);
cyisraddress RL_QuadDec_isr_GetVector(void);

void RL_QuadDec_isr_SetPriority(uint8 priority);
uint8 RL_QuadDec_isr_GetPriority(void);

void RL_QuadDec_isr_Enable(void);
uint8 RL_QuadDec_isr_GetState(void);
void RL_QuadDec_isr_Disable(void);

void RL_QuadDec_isr_SetPending(void);
void RL_QuadDec_isr_ClearPending(void);


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the RL_QuadDec_isr ISR. */
#define RL_QuadDec_isr_INTC_VECTOR            ((reg32 *) RL_QuadDec_isr__INTC_VECT)

/* Address of the RL_QuadDec_isr ISR priority. */
#define RL_QuadDec_isr_INTC_PRIOR             ((reg8 *) RL_QuadDec_isr__INTC_PRIOR_REG)

/* Priority of the RL_QuadDec_isr interrupt. */
#define RL_QuadDec_isr_INTC_PRIOR_NUMBER      RL_QuadDec_isr__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable RL_QuadDec_isr interrupt. */
#define RL_QuadDec_isr_INTC_SET_EN            ((reg32 *) RL_QuadDec_isr__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the RL_QuadDec_isr interrupt. */
#define RL_QuadDec_isr_INTC_CLR_EN            ((reg32 *) RL_QuadDec_isr__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the RL_QuadDec_isr interrupt state to pending. */
#define RL_QuadDec_isr_INTC_SET_PD            ((reg32 *) RL_QuadDec_isr__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the RL_QuadDec_isr interrupt. */
#define RL_QuadDec_isr_INTC_CLR_PD            ((reg32 *) RL_QuadDec_isr__INTC_CLR_PD_REG)


#endif /* CY_ISR_RL_QuadDec_isr_H */


/* [] END OF FILE */
