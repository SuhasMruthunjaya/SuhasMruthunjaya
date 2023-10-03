/*******************************************************************************
* File Name: SYSCLOCK.h
* Version 2.20
*
*  Description:
*   Provides the function and constant definitions for the clock component.
*
*  Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_CLOCK_SYSCLOCK_H)
#define CY_CLOCK_SYSCLOCK_H

#include <cytypes.h>
#include <cyfitter.h>


/***************************************
* Conditional Compilation Parameters
***************************************/

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component cy_clock_v2_20 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5LP) */


/***************************************
*        Function Prototypes
***************************************/

void SYSCLOCK_Start(void) ;
void SYSCLOCK_Stop(void) ;

#if(CY_PSOC3 || CY_PSOC5LP)
void SYSCLOCK_StopBlock(void) ;
#endif /* (CY_PSOC3 || CY_PSOC5LP) */

void SYSCLOCK_StandbyPower(uint8 state) ;
void SYSCLOCK_SetDividerRegister(uint16 clkDivider, uint8 restart) 
                                ;
uint16 SYSCLOCK_GetDividerRegister(void) ;
void SYSCLOCK_SetModeRegister(uint8 modeBitMask) ;
void SYSCLOCK_ClearModeRegister(uint8 modeBitMask) ;
uint8 SYSCLOCK_GetModeRegister(void) ;
void SYSCLOCK_SetSourceRegister(uint8 clkSource) ;
uint8 SYSCLOCK_GetSourceRegister(void) ;
#if defined(SYSCLOCK__CFG3)
void SYSCLOCK_SetPhaseRegister(uint8 clkPhase) ;
uint8 SYSCLOCK_GetPhaseRegister(void) ;
#endif /* defined(SYSCLOCK__CFG3) */

#define SYSCLOCK_Enable()                       SYSCLOCK_Start()
#define SYSCLOCK_Disable()                      SYSCLOCK_Stop()
#define SYSCLOCK_SetDivider(clkDivider)         SYSCLOCK_SetDividerRegister(clkDivider, 1u)
#define SYSCLOCK_SetDividerValue(clkDivider)    SYSCLOCK_SetDividerRegister((clkDivider) - 1u, 1u)
#define SYSCLOCK_SetMode(clkMode)               SYSCLOCK_SetModeRegister(clkMode)
#define SYSCLOCK_SetSource(clkSource)           SYSCLOCK_SetSourceRegister(clkSource)
#if defined(SYSCLOCK__CFG3)
#define SYSCLOCK_SetPhase(clkPhase)             SYSCLOCK_SetPhaseRegister(clkPhase)
#define SYSCLOCK_SetPhaseValue(clkPhase)        SYSCLOCK_SetPhaseRegister((clkPhase) + 1u)
#endif /* defined(SYSCLOCK__CFG3) */


/***************************************
*             Registers
***************************************/

/* Register to enable or disable the clock */
#define SYSCLOCK_CLKEN              (* (reg8 *) SYSCLOCK__PM_ACT_CFG)
#define SYSCLOCK_CLKEN_PTR          ((reg8 *) SYSCLOCK__PM_ACT_CFG)

/* Register to enable or disable the clock */
#define SYSCLOCK_CLKSTBY            (* (reg8 *) SYSCLOCK__PM_STBY_CFG)
#define SYSCLOCK_CLKSTBY_PTR        ((reg8 *) SYSCLOCK__PM_STBY_CFG)

/* Clock LSB divider configuration register. */
#define SYSCLOCK_DIV_LSB            (* (reg8 *) SYSCLOCK__CFG0)
#define SYSCLOCK_DIV_LSB_PTR        ((reg8 *) SYSCLOCK__CFG0)
#define SYSCLOCK_DIV_PTR            ((reg16 *) SYSCLOCK__CFG0)

/* Clock MSB divider configuration register. */
#define SYSCLOCK_DIV_MSB            (* (reg8 *) SYSCLOCK__CFG1)
#define SYSCLOCK_DIV_MSB_PTR        ((reg8 *) SYSCLOCK__CFG1)

/* Mode and source configuration register */
#define SYSCLOCK_MOD_SRC            (* (reg8 *) SYSCLOCK__CFG2)
#define SYSCLOCK_MOD_SRC_PTR        ((reg8 *) SYSCLOCK__CFG2)

#if defined(SYSCLOCK__CFG3)
/* Analog clock phase configuration register */
#define SYSCLOCK_PHASE              (* (reg8 *) SYSCLOCK__CFG3)
#define SYSCLOCK_PHASE_PTR          ((reg8 *) SYSCLOCK__CFG3)
#endif /* defined(SYSCLOCK__CFG3) */


/**************************************
*       Register Constants
**************************************/

/* Power manager register masks */
#define SYSCLOCK_CLKEN_MASK         SYSCLOCK__PM_ACT_MSK
#define SYSCLOCK_CLKSTBY_MASK       SYSCLOCK__PM_STBY_MSK

/* CFG2 field masks */
#define SYSCLOCK_SRC_SEL_MSK        SYSCLOCK__CFG2_SRC_SEL_MASK
#define SYSCLOCK_MODE_MASK          (~(SYSCLOCK_SRC_SEL_MSK))

#if defined(SYSCLOCK__CFG3)
/* CFG3 phase mask */
#define SYSCLOCK_PHASE_MASK         SYSCLOCK__CFG3_PHASE_DLY_MASK
#endif /* defined(SYSCLOCK__CFG3) */

#endif /* CY_CLOCK_SYSCLOCK_H */


/* [] END OF FILE */
