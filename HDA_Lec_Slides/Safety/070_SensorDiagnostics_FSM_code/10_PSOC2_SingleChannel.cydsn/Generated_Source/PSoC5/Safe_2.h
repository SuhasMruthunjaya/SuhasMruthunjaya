/*******************************************************************************
* File Name: Safe_2.h  
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

#if !defined(CY_PINS_Safe_2_H) /* Pins Safe_2_H */
#define CY_PINS_Safe_2_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "Safe_2_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 Safe_2__PORT == 15 && ((Safe_2__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    Safe_2_Write(uint8 value);
void    Safe_2_SetDriveMode(uint8 mode);
uint8   Safe_2_ReadDataReg(void);
uint8   Safe_2_Read(void);
void    Safe_2_SetInterruptMode(uint16 position, uint16 mode);
uint8   Safe_2_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the Safe_2_SetDriveMode() function.
     *  @{
     */
        #define Safe_2_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define Safe_2_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define Safe_2_DM_RES_UP          PIN_DM_RES_UP
        #define Safe_2_DM_RES_DWN         PIN_DM_RES_DWN
        #define Safe_2_DM_OD_LO           PIN_DM_OD_LO
        #define Safe_2_DM_OD_HI           PIN_DM_OD_HI
        #define Safe_2_DM_STRONG          PIN_DM_STRONG
        #define Safe_2_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define Safe_2_MASK               Safe_2__MASK
#define Safe_2_SHIFT              Safe_2__SHIFT
#define Safe_2_WIDTH              1u

/* Interrupt constants */
#if defined(Safe_2__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in Safe_2_SetInterruptMode() function.
     *  @{
     */
        #define Safe_2_INTR_NONE      (uint16)(0x0000u)
        #define Safe_2_INTR_RISING    (uint16)(0x0001u)
        #define Safe_2_INTR_FALLING   (uint16)(0x0002u)
        #define Safe_2_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define Safe_2_INTR_MASK      (0x01u) 
#endif /* (Safe_2__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Safe_2_PS                     (* (reg8 *) Safe_2__PS)
/* Data Register */
#define Safe_2_DR                     (* (reg8 *) Safe_2__DR)
/* Port Number */
#define Safe_2_PRT_NUM                (* (reg8 *) Safe_2__PRT) 
/* Connect to Analog Globals */                                                  
#define Safe_2_AG                     (* (reg8 *) Safe_2__AG)                       
/* Analog MUX bux enable */
#define Safe_2_AMUX                   (* (reg8 *) Safe_2__AMUX) 
/* Bidirectional Enable */                                                        
#define Safe_2_BIE                    (* (reg8 *) Safe_2__BIE)
/* Bit-mask for Aliased Register Access */
#define Safe_2_BIT_MASK               (* (reg8 *) Safe_2__BIT_MASK)
/* Bypass Enable */
#define Safe_2_BYP                    (* (reg8 *) Safe_2__BYP)
/* Port wide control signals */                                                   
#define Safe_2_CTL                    (* (reg8 *) Safe_2__CTL)
/* Drive Modes */
#define Safe_2_DM0                    (* (reg8 *) Safe_2__DM0) 
#define Safe_2_DM1                    (* (reg8 *) Safe_2__DM1)
#define Safe_2_DM2                    (* (reg8 *) Safe_2__DM2) 
/* Input Buffer Disable Override */
#define Safe_2_INP_DIS                (* (reg8 *) Safe_2__INP_DIS)
/* LCD Common or Segment Drive */
#define Safe_2_LCD_COM_SEG            (* (reg8 *) Safe_2__LCD_COM_SEG)
/* Enable Segment LCD */
#define Safe_2_LCD_EN                 (* (reg8 *) Safe_2__LCD_EN)
/* Slew Rate Control */
#define Safe_2_SLW                    (* (reg8 *) Safe_2__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define Safe_2_PRTDSI__CAPS_SEL       (* (reg8 *) Safe_2__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define Safe_2_PRTDSI__DBL_SYNC_IN    (* (reg8 *) Safe_2__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define Safe_2_PRTDSI__OE_SEL0        (* (reg8 *) Safe_2__PRTDSI__OE_SEL0) 
#define Safe_2_PRTDSI__OE_SEL1        (* (reg8 *) Safe_2__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define Safe_2_PRTDSI__OUT_SEL0       (* (reg8 *) Safe_2__PRTDSI__OUT_SEL0) 
#define Safe_2_PRTDSI__OUT_SEL1       (* (reg8 *) Safe_2__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define Safe_2_PRTDSI__SYNC_OUT       (* (reg8 *) Safe_2__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(Safe_2__SIO_CFG)
    #define Safe_2_SIO_HYST_EN        (* (reg8 *) Safe_2__SIO_HYST_EN)
    #define Safe_2_SIO_REG_HIFREQ     (* (reg8 *) Safe_2__SIO_REG_HIFREQ)
    #define Safe_2_SIO_CFG            (* (reg8 *) Safe_2__SIO_CFG)
    #define Safe_2_SIO_DIFF           (* (reg8 *) Safe_2__SIO_DIFF)
#endif /* (Safe_2__SIO_CFG) */

/* Interrupt Registers */
#if defined(Safe_2__INTSTAT)
    #define Safe_2_INTSTAT            (* (reg8 *) Safe_2__INTSTAT)
    #define Safe_2_SNAP               (* (reg8 *) Safe_2__SNAP)
    
	#define Safe_2_0_INTTYPE_REG 		(* (reg8 *) Safe_2__0__INTTYPE)
#endif /* (Safe_2__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_Safe_2_H */


/* [] END OF FILE */
