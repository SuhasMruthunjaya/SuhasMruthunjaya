/*******************************************************************************
* File Name: Engine_PWM_FL.h  
* Version 2.20
*
* Description:
*  This file contains Pin function prototypes and register defines
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_Engine_PWM_FL_H) /* Pins Engine_PWM_FL_H */
#define CY_PINS_Engine_PWM_FL_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "Engine_PWM_FL_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 Engine_PWM_FL__PORT == 15 && ((Engine_PWM_FL__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    Engine_PWM_FL_Write(uint8 value);
void    Engine_PWM_FL_SetDriveMode(uint8 mode);
uint8   Engine_PWM_FL_ReadDataReg(void);
uint8   Engine_PWM_FL_Read(void);
void    Engine_PWM_FL_SetInterruptMode(uint16 position, uint16 mode);
uint8   Engine_PWM_FL_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the Engine_PWM_FL_SetDriveMode() function.
     *  @{
     */
        #define Engine_PWM_FL_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define Engine_PWM_FL_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define Engine_PWM_FL_DM_RES_UP          PIN_DM_RES_UP
        #define Engine_PWM_FL_DM_RES_DWN         PIN_DM_RES_DWN
        #define Engine_PWM_FL_DM_OD_LO           PIN_DM_OD_LO
        #define Engine_PWM_FL_DM_OD_HI           PIN_DM_OD_HI
        #define Engine_PWM_FL_DM_STRONG          PIN_DM_STRONG
        #define Engine_PWM_FL_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define Engine_PWM_FL_MASK               Engine_PWM_FL__MASK
#define Engine_PWM_FL_SHIFT              Engine_PWM_FL__SHIFT
#define Engine_PWM_FL_WIDTH              1u

/* Interrupt constants */
#if defined(Engine_PWM_FL__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in Engine_PWM_FL_SetInterruptMode() function.
     *  @{
     */
        #define Engine_PWM_FL_INTR_NONE      (uint16)(0x0000u)
        #define Engine_PWM_FL_INTR_RISING    (uint16)(0x0001u)
        #define Engine_PWM_FL_INTR_FALLING   (uint16)(0x0002u)
        #define Engine_PWM_FL_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define Engine_PWM_FL_INTR_MASK      (0x01u) 
#endif /* (Engine_PWM_FL__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Engine_PWM_FL_PS                     (* (reg8 *) Engine_PWM_FL__PS)
/* Data Register */
#define Engine_PWM_FL_DR                     (* (reg8 *) Engine_PWM_FL__DR)
/* Port Number */
#define Engine_PWM_FL_PRT_NUM                (* (reg8 *) Engine_PWM_FL__PRT) 
/* Connect to Analog Globals */                                                  
#define Engine_PWM_FL_AG                     (* (reg8 *) Engine_PWM_FL__AG)                       
/* Analog MUX bux enable */
#define Engine_PWM_FL_AMUX                   (* (reg8 *) Engine_PWM_FL__AMUX) 
/* Bidirectional Enable */                                                        
#define Engine_PWM_FL_BIE                    (* (reg8 *) Engine_PWM_FL__BIE)
/* Bit-mask for Aliased Register Access */
#define Engine_PWM_FL_BIT_MASK               (* (reg8 *) Engine_PWM_FL__BIT_MASK)
/* Bypass Enable */
#define Engine_PWM_FL_BYP                    (* (reg8 *) Engine_PWM_FL__BYP)
/* Port wide control signals */                                                   
#define Engine_PWM_FL_CTL                    (* (reg8 *) Engine_PWM_FL__CTL)
/* Drive Modes */
#define Engine_PWM_FL_DM0                    (* (reg8 *) Engine_PWM_FL__DM0) 
#define Engine_PWM_FL_DM1                    (* (reg8 *) Engine_PWM_FL__DM1)
#define Engine_PWM_FL_DM2                    (* (reg8 *) Engine_PWM_FL__DM2) 
/* Input Buffer Disable Override */
#define Engine_PWM_FL_INP_DIS                (* (reg8 *) Engine_PWM_FL__INP_DIS)
/* LCD Common or Segment Drive */
#define Engine_PWM_FL_LCD_COM_SEG            (* (reg8 *) Engine_PWM_FL__LCD_COM_SEG)
/* Enable Segment LCD */
#define Engine_PWM_FL_LCD_EN                 (* (reg8 *) Engine_PWM_FL__LCD_EN)
/* Slew Rate Control */
#define Engine_PWM_FL_SLW                    (* (reg8 *) Engine_PWM_FL__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define Engine_PWM_FL_PRTDSI__CAPS_SEL       (* (reg8 *) Engine_PWM_FL__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define Engine_PWM_FL_PRTDSI__DBL_SYNC_IN    (* (reg8 *) Engine_PWM_FL__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define Engine_PWM_FL_PRTDSI__OE_SEL0        (* (reg8 *) Engine_PWM_FL__PRTDSI__OE_SEL0) 
#define Engine_PWM_FL_PRTDSI__OE_SEL1        (* (reg8 *) Engine_PWM_FL__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define Engine_PWM_FL_PRTDSI__OUT_SEL0       (* (reg8 *) Engine_PWM_FL__PRTDSI__OUT_SEL0) 
#define Engine_PWM_FL_PRTDSI__OUT_SEL1       (* (reg8 *) Engine_PWM_FL__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define Engine_PWM_FL_PRTDSI__SYNC_OUT       (* (reg8 *) Engine_PWM_FL__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(Engine_PWM_FL__SIO_CFG)
    #define Engine_PWM_FL_SIO_HYST_EN        (* (reg8 *) Engine_PWM_FL__SIO_HYST_EN)
    #define Engine_PWM_FL_SIO_REG_HIFREQ     (* (reg8 *) Engine_PWM_FL__SIO_REG_HIFREQ)
    #define Engine_PWM_FL_SIO_CFG            (* (reg8 *) Engine_PWM_FL__SIO_CFG)
    #define Engine_PWM_FL_SIO_DIFF           (* (reg8 *) Engine_PWM_FL__SIO_DIFF)
#endif /* (Engine_PWM_FL__SIO_CFG) */

/* Interrupt Registers */
#if defined(Engine_PWM_FL__INTSTAT)
    #define Engine_PWM_FL_INTSTAT            (* (reg8 *) Engine_PWM_FL__INTSTAT)
    #define Engine_PWM_FL_SNAP               (* (reg8 *) Engine_PWM_FL__SNAP)
    
	#define Engine_PWM_FL_0_INTTYPE_REG 		(* (reg8 *) Engine_PWM_FL__0__INTTYPE)
#endif /* (Engine_PWM_FL__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_Engine_PWM_FL_H */


/* [] END OF FILE */
