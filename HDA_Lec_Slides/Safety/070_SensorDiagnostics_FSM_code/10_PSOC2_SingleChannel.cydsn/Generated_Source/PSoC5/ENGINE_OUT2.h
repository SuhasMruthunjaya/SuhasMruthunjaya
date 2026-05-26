/*******************************************************************************
* File Name: ENGINE_OUT2.h  
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

#if !defined(CY_PINS_ENGINE_OUT2_H) /* Pins ENGINE_OUT2_H */
#define CY_PINS_ENGINE_OUT2_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "ENGINE_OUT2_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 ENGINE_OUT2__PORT == 15 && ((ENGINE_OUT2__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    ENGINE_OUT2_Write(uint8 value);
void    ENGINE_OUT2_SetDriveMode(uint8 mode);
uint8   ENGINE_OUT2_ReadDataReg(void);
uint8   ENGINE_OUT2_Read(void);
void    ENGINE_OUT2_SetInterruptMode(uint16 position, uint16 mode);
uint8   ENGINE_OUT2_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the ENGINE_OUT2_SetDriveMode() function.
     *  @{
     */
        #define ENGINE_OUT2_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define ENGINE_OUT2_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define ENGINE_OUT2_DM_RES_UP          PIN_DM_RES_UP
        #define ENGINE_OUT2_DM_RES_DWN         PIN_DM_RES_DWN
        #define ENGINE_OUT2_DM_OD_LO           PIN_DM_OD_LO
        #define ENGINE_OUT2_DM_OD_HI           PIN_DM_OD_HI
        #define ENGINE_OUT2_DM_STRONG          PIN_DM_STRONG
        #define ENGINE_OUT2_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define ENGINE_OUT2_MASK               ENGINE_OUT2__MASK
#define ENGINE_OUT2_SHIFT              ENGINE_OUT2__SHIFT
#define ENGINE_OUT2_WIDTH              1u

/* Interrupt constants */
#if defined(ENGINE_OUT2__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in ENGINE_OUT2_SetInterruptMode() function.
     *  @{
     */
        #define ENGINE_OUT2_INTR_NONE      (uint16)(0x0000u)
        #define ENGINE_OUT2_INTR_RISING    (uint16)(0x0001u)
        #define ENGINE_OUT2_INTR_FALLING   (uint16)(0x0002u)
        #define ENGINE_OUT2_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define ENGINE_OUT2_INTR_MASK      (0x01u) 
#endif /* (ENGINE_OUT2__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define ENGINE_OUT2_PS                     (* (reg8 *) ENGINE_OUT2__PS)
/* Data Register */
#define ENGINE_OUT2_DR                     (* (reg8 *) ENGINE_OUT2__DR)
/* Port Number */
#define ENGINE_OUT2_PRT_NUM                (* (reg8 *) ENGINE_OUT2__PRT) 
/* Connect to Analog Globals */                                                  
#define ENGINE_OUT2_AG                     (* (reg8 *) ENGINE_OUT2__AG)                       
/* Analog MUX bux enable */
#define ENGINE_OUT2_AMUX                   (* (reg8 *) ENGINE_OUT2__AMUX) 
/* Bidirectional Enable */                                                        
#define ENGINE_OUT2_BIE                    (* (reg8 *) ENGINE_OUT2__BIE)
/* Bit-mask for Aliased Register Access */
#define ENGINE_OUT2_BIT_MASK               (* (reg8 *) ENGINE_OUT2__BIT_MASK)
/* Bypass Enable */
#define ENGINE_OUT2_BYP                    (* (reg8 *) ENGINE_OUT2__BYP)
/* Port wide control signals */                                                   
#define ENGINE_OUT2_CTL                    (* (reg8 *) ENGINE_OUT2__CTL)
/* Drive Modes */
#define ENGINE_OUT2_DM0                    (* (reg8 *) ENGINE_OUT2__DM0) 
#define ENGINE_OUT2_DM1                    (* (reg8 *) ENGINE_OUT2__DM1)
#define ENGINE_OUT2_DM2                    (* (reg8 *) ENGINE_OUT2__DM2) 
/* Input Buffer Disable Override */
#define ENGINE_OUT2_INP_DIS                (* (reg8 *) ENGINE_OUT2__INP_DIS)
/* LCD Common or Segment Drive */
#define ENGINE_OUT2_LCD_COM_SEG            (* (reg8 *) ENGINE_OUT2__LCD_COM_SEG)
/* Enable Segment LCD */
#define ENGINE_OUT2_LCD_EN                 (* (reg8 *) ENGINE_OUT2__LCD_EN)
/* Slew Rate Control */
#define ENGINE_OUT2_SLW                    (* (reg8 *) ENGINE_OUT2__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define ENGINE_OUT2_PRTDSI__CAPS_SEL       (* (reg8 *) ENGINE_OUT2__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define ENGINE_OUT2_PRTDSI__DBL_SYNC_IN    (* (reg8 *) ENGINE_OUT2__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define ENGINE_OUT2_PRTDSI__OE_SEL0        (* (reg8 *) ENGINE_OUT2__PRTDSI__OE_SEL0) 
#define ENGINE_OUT2_PRTDSI__OE_SEL1        (* (reg8 *) ENGINE_OUT2__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define ENGINE_OUT2_PRTDSI__OUT_SEL0       (* (reg8 *) ENGINE_OUT2__PRTDSI__OUT_SEL0) 
#define ENGINE_OUT2_PRTDSI__OUT_SEL1       (* (reg8 *) ENGINE_OUT2__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define ENGINE_OUT2_PRTDSI__SYNC_OUT       (* (reg8 *) ENGINE_OUT2__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(ENGINE_OUT2__SIO_CFG)
    #define ENGINE_OUT2_SIO_HYST_EN        (* (reg8 *) ENGINE_OUT2__SIO_HYST_EN)
    #define ENGINE_OUT2_SIO_REG_HIFREQ     (* (reg8 *) ENGINE_OUT2__SIO_REG_HIFREQ)
    #define ENGINE_OUT2_SIO_CFG            (* (reg8 *) ENGINE_OUT2__SIO_CFG)
    #define ENGINE_OUT2_SIO_DIFF           (* (reg8 *) ENGINE_OUT2__SIO_DIFF)
#endif /* (ENGINE_OUT2__SIO_CFG) */

/* Interrupt Registers */
#if defined(ENGINE_OUT2__INTSTAT)
    #define ENGINE_OUT2_INTSTAT            (* (reg8 *) ENGINE_OUT2__INTSTAT)
    #define ENGINE_OUT2_SNAP               (* (reg8 *) ENGINE_OUT2__SNAP)
    
	#define ENGINE_OUT2_0_INTTYPE_REG 		(* (reg8 *) ENGINE_OUT2__0__INTTYPE)
#endif /* (ENGINE_OUT2__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_ENGINE_OUT2_H */


/* [] END OF FILE */
