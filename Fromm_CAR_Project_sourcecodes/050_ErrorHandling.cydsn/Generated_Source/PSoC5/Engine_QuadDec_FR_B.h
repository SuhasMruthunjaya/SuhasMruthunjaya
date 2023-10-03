/*******************************************************************************
* File Name: Engine_QuadDec_FR_B.h  
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

#if !defined(CY_PINS_Engine_QuadDec_FR_B_H) /* Pins Engine_QuadDec_FR_B_H */
#define CY_PINS_Engine_QuadDec_FR_B_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "Engine_QuadDec_FR_B_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 Engine_QuadDec_FR_B__PORT == 15 && ((Engine_QuadDec_FR_B__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    Engine_QuadDec_FR_B_Write(uint8 value);
void    Engine_QuadDec_FR_B_SetDriveMode(uint8 mode);
uint8   Engine_QuadDec_FR_B_ReadDataReg(void);
uint8   Engine_QuadDec_FR_B_Read(void);
void    Engine_QuadDec_FR_B_SetInterruptMode(uint16 position, uint16 mode);
uint8   Engine_QuadDec_FR_B_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the Engine_QuadDec_FR_B_SetDriveMode() function.
     *  @{
     */
        #define Engine_QuadDec_FR_B_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define Engine_QuadDec_FR_B_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define Engine_QuadDec_FR_B_DM_RES_UP          PIN_DM_RES_UP
        #define Engine_QuadDec_FR_B_DM_RES_DWN         PIN_DM_RES_DWN
        #define Engine_QuadDec_FR_B_DM_OD_LO           PIN_DM_OD_LO
        #define Engine_QuadDec_FR_B_DM_OD_HI           PIN_DM_OD_HI
        #define Engine_QuadDec_FR_B_DM_STRONG          PIN_DM_STRONG
        #define Engine_QuadDec_FR_B_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define Engine_QuadDec_FR_B_MASK               Engine_QuadDec_FR_B__MASK
#define Engine_QuadDec_FR_B_SHIFT              Engine_QuadDec_FR_B__SHIFT
#define Engine_QuadDec_FR_B_WIDTH              1u

/* Interrupt constants */
#if defined(Engine_QuadDec_FR_B__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in Engine_QuadDec_FR_B_SetInterruptMode() function.
     *  @{
     */
        #define Engine_QuadDec_FR_B_INTR_NONE      (uint16)(0x0000u)
        #define Engine_QuadDec_FR_B_INTR_RISING    (uint16)(0x0001u)
        #define Engine_QuadDec_FR_B_INTR_FALLING   (uint16)(0x0002u)
        #define Engine_QuadDec_FR_B_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define Engine_QuadDec_FR_B_INTR_MASK      (0x01u) 
#endif /* (Engine_QuadDec_FR_B__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Engine_QuadDec_FR_B_PS                     (* (reg8 *) Engine_QuadDec_FR_B__PS)
/* Data Register */
#define Engine_QuadDec_FR_B_DR                     (* (reg8 *) Engine_QuadDec_FR_B__DR)
/* Port Number */
#define Engine_QuadDec_FR_B_PRT_NUM                (* (reg8 *) Engine_QuadDec_FR_B__PRT) 
/* Connect to Analog Globals */                                                  
#define Engine_QuadDec_FR_B_AG                     (* (reg8 *) Engine_QuadDec_FR_B__AG)                       
/* Analog MUX bux enable */
#define Engine_QuadDec_FR_B_AMUX                   (* (reg8 *) Engine_QuadDec_FR_B__AMUX) 
/* Bidirectional Enable */                                                        
#define Engine_QuadDec_FR_B_BIE                    (* (reg8 *) Engine_QuadDec_FR_B__BIE)
/* Bit-mask for Aliased Register Access */
#define Engine_QuadDec_FR_B_BIT_MASK               (* (reg8 *) Engine_QuadDec_FR_B__BIT_MASK)
/* Bypass Enable */
#define Engine_QuadDec_FR_B_BYP                    (* (reg8 *) Engine_QuadDec_FR_B__BYP)
/* Port wide control signals */                                                   
#define Engine_QuadDec_FR_B_CTL                    (* (reg8 *) Engine_QuadDec_FR_B__CTL)
/* Drive Modes */
#define Engine_QuadDec_FR_B_DM0                    (* (reg8 *) Engine_QuadDec_FR_B__DM0) 
#define Engine_QuadDec_FR_B_DM1                    (* (reg8 *) Engine_QuadDec_FR_B__DM1)
#define Engine_QuadDec_FR_B_DM2                    (* (reg8 *) Engine_QuadDec_FR_B__DM2) 
/* Input Buffer Disable Override */
#define Engine_QuadDec_FR_B_INP_DIS                (* (reg8 *) Engine_QuadDec_FR_B__INP_DIS)
/* LCD Common or Segment Drive */
#define Engine_QuadDec_FR_B_LCD_COM_SEG            (* (reg8 *) Engine_QuadDec_FR_B__LCD_COM_SEG)
/* Enable Segment LCD */
#define Engine_QuadDec_FR_B_LCD_EN                 (* (reg8 *) Engine_QuadDec_FR_B__LCD_EN)
/* Slew Rate Control */
#define Engine_QuadDec_FR_B_SLW                    (* (reg8 *) Engine_QuadDec_FR_B__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define Engine_QuadDec_FR_B_PRTDSI__CAPS_SEL       (* (reg8 *) Engine_QuadDec_FR_B__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define Engine_QuadDec_FR_B_PRTDSI__DBL_SYNC_IN    (* (reg8 *) Engine_QuadDec_FR_B__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define Engine_QuadDec_FR_B_PRTDSI__OE_SEL0        (* (reg8 *) Engine_QuadDec_FR_B__PRTDSI__OE_SEL0) 
#define Engine_QuadDec_FR_B_PRTDSI__OE_SEL1        (* (reg8 *) Engine_QuadDec_FR_B__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define Engine_QuadDec_FR_B_PRTDSI__OUT_SEL0       (* (reg8 *) Engine_QuadDec_FR_B__PRTDSI__OUT_SEL0) 
#define Engine_QuadDec_FR_B_PRTDSI__OUT_SEL1       (* (reg8 *) Engine_QuadDec_FR_B__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define Engine_QuadDec_FR_B_PRTDSI__SYNC_OUT       (* (reg8 *) Engine_QuadDec_FR_B__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(Engine_QuadDec_FR_B__SIO_CFG)
    #define Engine_QuadDec_FR_B_SIO_HYST_EN        (* (reg8 *) Engine_QuadDec_FR_B__SIO_HYST_EN)
    #define Engine_QuadDec_FR_B_SIO_REG_HIFREQ     (* (reg8 *) Engine_QuadDec_FR_B__SIO_REG_HIFREQ)
    #define Engine_QuadDec_FR_B_SIO_CFG            (* (reg8 *) Engine_QuadDec_FR_B__SIO_CFG)
    #define Engine_QuadDec_FR_B_SIO_DIFF           (* (reg8 *) Engine_QuadDec_FR_B__SIO_DIFF)
#endif /* (Engine_QuadDec_FR_B__SIO_CFG) */

/* Interrupt Registers */
#if defined(Engine_QuadDec_FR_B__INTSTAT)
    #define Engine_QuadDec_FR_B_INTSTAT            (* (reg8 *) Engine_QuadDec_FR_B__INTSTAT)
    #define Engine_QuadDec_FR_B_SNAP               (* (reg8 *) Engine_QuadDec_FR_B__SNAP)
    
	#define Engine_QuadDec_FR_B_0_INTTYPE_REG 		(* (reg8 *) Engine_QuadDec_FR_B__0__INTTYPE)
#endif /* (Engine_QuadDec_FR_B__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_Engine_QuadDec_FR_B_H */


/* [] END OF FILE */
