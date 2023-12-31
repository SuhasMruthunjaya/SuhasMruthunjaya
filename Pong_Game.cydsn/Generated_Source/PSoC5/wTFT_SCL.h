/*******************************************************************************
* File Name: wTFT_SCL.h  
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

#if !defined(CY_PINS_wTFT_SCL_H) /* Pins wTFT_SCL_H */
#define CY_PINS_wTFT_SCL_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "wTFT_SCL_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 wTFT_SCL__PORT == 15 && ((wTFT_SCL__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    wTFT_SCL_Write(uint8 value);
void    wTFT_SCL_SetDriveMode(uint8 mode);
uint8   wTFT_SCL_ReadDataReg(void);
uint8   wTFT_SCL_Read(void);
void    wTFT_SCL_SetInterruptMode(uint16 position, uint16 mode);
uint8   wTFT_SCL_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the wTFT_SCL_SetDriveMode() function.
     *  @{
     */
        #define wTFT_SCL_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define wTFT_SCL_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define wTFT_SCL_DM_RES_UP          PIN_DM_RES_UP
        #define wTFT_SCL_DM_RES_DWN         PIN_DM_RES_DWN
        #define wTFT_SCL_DM_OD_LO           PIN_DM_OD_LO
        #define wTFT_SCL_DM_OD_HI           PIN_DM_OD_HI
        #define wTFT_SCL_DM_STRONG          PIN_DM_STRONG
        #define wTFT_SCL_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define wTFT_SCL_MASK               wTFT_SCL__MASK
#define wTFT_SCL_SHIFT              wTFT_SCL__SHIFT
#define wTFT_SCL_WIDTH              1u

/* Interrupt constants */
#if defined(wTFT_SCL__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in wTFT_SCL_SetInterruptMode() function.
     *  @{
     */
        #define wTFT_SCL_INTR_NONE      (uint16)(0x0000u)
        #define wTFT_SCL_INTR_RISING    (uint16)(0x0001u)
        #define wTFT_SCL_INTR_FALLING   (uint16)(0x0002u)
        #define wTFT_SCL_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define wTFT_SCL_INTR_MASK      (0x01u) 
#endif /* (wTFT_SCL__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define wTFT_SCL_PS                     (* (reg8 *) wTFT_SCL__PS)
/* Data Register */
#define wTFT_SCL_DR                     (* (reg8 *) wTFT_SCL__DR)
/* Port Number */
#define wTFT_SCL_PRT_NUM                (* (reg8 *) wTFT_SCL__PRT) 
/* Connect to Analog Globals */                                                  
#define wTFT_SCL_AG                     (* (reg8 *) wTFT_SCL__AG)                       
/* Analog MUX bux enable */
#define wTFT_SCL_AMUX                   (* (reg8 *) wTFT_SCL__AMUX) 
/* Bidirectional Enable */                                                        
#define wTFT_SCL_BIE                    (* (reg8 *) wTFT_SCL__BIE)
/* Bit-mask for Aliased Register Access */
#define wTFT_SCL_BIT_MASK               (* (reg8 *) wTFT_SCL__BIT_MASK)
/* Bypass Enable */
#define wTFT_SCL_BYP                    (* (reg8 *) wTFT_SCL__BYP)
/* Port wide control signals */                                                   
#define wTFT_SCL_CTL                    (* (reg8 *) wTFT_SCL__CTL)
/* Drive Modes */
#define wTFT_SCL_DM0                    (* (reg8 *) wTFT_SCL__DM0) 
#define wTFT_SCL_DM1                    (* (reg8 *) wTFT_SCL__DM1)
#define wTFT_SCL_DM2                    (* (reg8 *) wTFT_SCL__DM2) 
/* Input Buffer Disable Override */
#define wTFT_SCL_INP_DIS                (* (reg8 *) wTFT_SCL__INP_DIS)
/* LCD Common or Segment Drive */
#define wTFT_SCL_LCD_COM_SEG            (* (reg8 *) wTFT_SCL__LCD_COM_SEG)
/* Enable Segment LCD */
#define wTFT_SCL_LCD_EN                 (* (reg8 *) wTFT_SCL__LCD_EN)
/* Slew Rate Control */
#define wTFT_SCL_SLW                    (* (reg8 *) wTFT_SCL__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define wTFT_SCL_PRTDSI__CAPS_SEL       (* (reg8 *) wTFT_SCL__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define wTFT_SCL_PRTDSI__DBL_SYNC_IN    (* (reg8 *) wTFT_SCL__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define wTFT_SCL_PRTDSI__OE_SEL0        (* (reg8 *) wTFT_SCL__PRTDSI__OE_SEL0) 
#define wTFT_SCL_PRTDSI__OE_SEL1        (* (reg8 *) wTFT_SCL__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define wTFT_SCL_PRTDSI__OUT_SEL0       (* (reg8 *) wTFT_SCL__PRTDSI__OUT_SEL0) 
#define wTFT_SCL_PRTDSI__OUT_SEL1       (* (reg8 *) wTFT_SCL__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define wTFT_SCL_PRTDSI__SYNC_OUT       (* (reg8 *) wTFT_SCL__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(wTFT_SCL__SIO_CFG)
    #define wTFT_SCL_SIO_HYST_EN        (* (reg8 *) wTFT_SCL__SIO_HYST_EN)
    #define wTFT_SCL_SIO_REG_HIFREQ     (* (reg8 *) wTFT_SCL__SIO_REG_HIFREQ)
    #define wTFT_SCL_SIO_CFG            (* (reg8 *) wTFT_SCL__SIO_CFG)
    #define wTFT_SCL_SIO_DIFF           (* (reg8 *) wTFT_SCL__SIO_DIFF)
#endif /* (wTFT_SCL__SIO_CFG) */

/* Interrupt Registers */
#if defined(wTFT_SCL__INTSTAT)
    #define wTFT_SCL_INTSTAT            (* (reg8 *) wTFT_SCL__INTSTAT)
    #define wTFT_SCL_SNAP               (* (reg8 *) wTFT_SCL__SNAP)
    
	#define wTFT_SCL_0_INTTYPE_REG 		(* (reg8 *) wTFT_SCL__0__INTTYPE)
#endif /* (wTFT_SCL__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_wTFT_SCL_H */


/* [] END OF FILE */
