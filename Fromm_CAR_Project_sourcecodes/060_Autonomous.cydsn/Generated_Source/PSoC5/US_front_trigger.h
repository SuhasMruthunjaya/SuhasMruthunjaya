/*******************************************************************************
* File Name: US_front_trigger.h  
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

#if !defined(CY_PINS_US_front_trigger_H) /* Pins US_front_trigger_H */
#define CY_PINS_US_front_trigger_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "US_front_trigger_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 US_front_trigger__PORT == 15 && ((US_front_trigger__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    US_front_trigger_Write(uint8 value);
void    US_front_trigger_SetDriveMode(uint8 mode);
uint8   US_front_trigger_ReadDataReg(void);
uint8   US_front_trigger_Read(void);
void    US_front_trigger_SetInterruptMode(uint16 position, uint16 mode);
uint8   US_front_trigger_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the US_front_trigger_SetDriveMode() function.
     *  @{
     */
        #define US_front_trigger_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define US_front_trigger_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define US_front_trigger_DM_RES_UP          PIN_DM_RES_UP
        #define US_front_trigger_DM_RES_DWN         PIN_DM_RES_DWN
        #define US_front_trigger_DM_OD_LO           PIN_DM_OD_LO
        #define US_front_trigger_DM_OD_HI           PIN_DM_OD_HI
        #define US_front_trigger_DM_STRONG          PIN_DM_STRONG
        #define US_front_trigger_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define US_front_trigger_MASK               US_front_trigger__MASK
#define US_front_trigger_SHIFT              US_front_trigger__SHIFT
#define US_front_trigger_WIDTH              1u

/* Interrupt constants */
#if defined(US_front_trigger__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in US_front_trigger_SetInterruptMode() function.
     *  @{
     */
        #define US_front_trigger_INTR_NONE      (uint16)(0x0000u)
        #define US_front_trigger_INTR_RISING    (uint16)(0x0001u)
        #define US_front_trigger_INTR_FALLING   (uint16)(0x0002u)
        #define US_front_trigger_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define US_front_trigger_INTR_MASK      (0x01u) 
#endif /* (US_front_trigger__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define US_front_trigger_PS                     (* (reg8 *) US_front_trigger__PS)
/* Data Register */
#define US_front_trigger_DR                     (* (reg8 *) US_front_trigger__DR)
/* Port Number */
#define US_front_trigger_PRT_NUM                (* (reg8 *) US_front_trigger__PRT) 
/* Connect to Analog Globals */                                                  
#define US_front_trigger_AG                     (* (reg8 *) US_front_trigger__AG)                       
/* Analog MUX bux enable */
#define US_front_trigger_AMUX                   (* (reg8 *) US_front_trigger__AMUX) 
/* Bidirectional Enable */                                                        
#define US_front_trigger_BIE                    (* (reg8 *) US_front_trigger__BIE)
/* Bit-mask for Aliased Register Access */
#define US_front_trigger_BIT_MASK               (* (reg8 *) US_front_trigger__BIT_MASK)
/* Bypass Enable */
#define US_front_trigger_BYP                    (* (reg8 *) US_front_trigger__BYP)
/* Port wide control signals */                                                   
#define US_front_trigger_CTL                    (* (reg8 *) US_front_trigger__CTL)
/* Drive Modes */
#define US_front_trigger_DM0                    (* (reg8 *) US_front_trigger__DM0) 
#define US_front_trigger_DM1                    (* (reg8 *) US_front_trigger__DM1)
#define US_front_trigger_DM2                    (* (reg8 *) US_front_trigger__DM2) 
/* Input Buffer Disable Override */
#define US_front_trigger_INP_DIS                (* (reg8 *) US_front_trigger__INP_DIS)
/* LCD Common or Segment Drive */
#define US_front_trigger_LCD_COM_SEG            (* (reg8 *) US_front_trigger__LCD_COM_SEG)
/* Enable Segment LCD */
#define US_front_trigger_LCD_EN                 (* (reg8 *) US_front_trigger__LCD_EN)
/* Slew Rate Control */
#define US_front_trigger_SLW                    (* (reg8 *) US_front_trigger__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define US_front_trigger_PRTDSI__CAPS_SEL       (* (reg8 *) US_front_trigger__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define US_front_trigger_PRTDSI__DBL_SYNC_IN    (* (reg8 *) US_front_trigger__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define US_front_trigger_PRTDSI__OE_SEL0        (* (reg8 *) US_front_trigger__PRTDSI__OE_SEL0) 
#define US_front_trigger_PRTDSI__OE_SEL1        (* (reg8 *) US_front_trigger__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define US_front_trigger_PRTDSI__OUT_SEL0       (* (reg8 *) US_front_trigger__PRTDSI__OUT_SEL0) 
#define US_front_trigger_PRTDSI__OUT_SEL1       (* (reg8 *) US_front_trigger__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define US_front_trigger_PRTDSI__SYNC_OUT       (* (reg8 *) US_front_trigger__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(US_front_trigger__SIO_CFG)
    #define US_front_trigger_SIO_HYST_EN        (* (reg8 *) US_front_trigger__SIO_HYST_EN)
    #define US_front_trigger_SIO_REG_HIFREQ     (* (reg8 *) US_front_trigger__SIO_REG_HIFREQ)
    #define US_front_trigger_SIO_CFG            (* (reg8 *) US_front_trigger__SIO_CFG)
    #define US_front_trigger_SIO_DIFF           (* (reg8 *) US_front_trigger__SIO_DIFF)
#endif /* (US_front_trigger__SIO_CFG) */

/* Interrupt Registers */
#if defined(US_front_trigger__INTSTAT)
    #define US_front_trigger_INTSTAT            (* (reg8 *) US_front_trigger__INTSTAT)
    #define US_front_trigger_SNAP               (* (reg8 *) US_front_trigger__SNAP)
    
	#define US_front_trigger_0_INTTYPE_REG 		(* (reg8 *) US_front_trigger__0__INTTYPE)
#endif /* (US_front_trigger__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_US_front_trigger_H */


/* [] END OF FILE */
