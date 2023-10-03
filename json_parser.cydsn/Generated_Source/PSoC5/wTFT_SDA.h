/*******************************************************************************
* File Name: wTFT_SDA.h  
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

#if !defined(CY_PINS_wTFT_SDA_H) /* Pins wTFT_SDA_H */
#define CY_PINS_wTFT_SDA_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "wTFT_SDA_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 wTFT_SDA__PORT == 15 && ((wTFT_SDA__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    wTFT_SDA_Write(uint8 value);
void    wTFT_SDA_SetDriveMode(uint8 mode);
uint8   wTFT_SDA_ReadDataReg(void);
uint8   wTFT_SDA_Read(void);
void    wTFT_SDA_SetInterruptMode(uint16 position, uint16 mode);
uint8   wTFT_SDA_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the wTFT_SDA_SetDriveMode() function.
     *  @{
     */
        #define wTFT_SDA_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define wTFT_SDA_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define wTFT_SDA_DM_RES_UP          PIN_DM_RES_UP
        #define wTFT_SDA_DM_RES_DWN         PIN_DM_RES_DWN
        #define wTFT_SDA_DM_OD_LO           PIN_DM_OD_LO
        #define wTFT_SDA_DM_OD_HI           PIN_DM_OD_HI
        #define wTFT_SDA_DM_STRONG          PIN_DM_STRONG
        #define wTFT_SDA_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define wTFT_SDA_MASK               wTFT_SDA__MASK
#define wTFT_SDA_SHIFT              wTFT_SDA__SHIFT
#define wTFT_SDA_WIDTH              1u

/* Interrupt constants */
#if defined(wTFT_SDA__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in wTFT_SDA_SetInterruptMode() function.
     *  @{
     */
        #define wTFT_SDA_INTR_NONE      (uint16)(0x0000u)
        #define wTFT_SDA_INTR_RISING    (uint16)(0x0001u)
        #define wTFT_SDA_INTR_FALLING   (uint16)(0x0002u)
        #define wTFT_SDA_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define wTFT_SDA_INTR_MASK      (0x01u) 
#endif /* (wTFT_SDA__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define wTFT_SDA_PS                     (* (reg8 *) wTFT_SDA__PS)
/* Data Register */
#define wTFT_SDA_DR                     (* (reg8 *) wTFT_SDA__DR)
/* Port Number */
#define wTFT_SDA_PRT_NUM                (* (reg8 *) wTFT_SDA__PRT) 
/* Connect to Analog Globals */                                                  
#define wTFT_SDA_AG                     (* (reg8 *) wTFT_SDA__AG)                       
/* Analog MUX bux enable */
#define wTFT_SDA_AMUX                   (* (reg8 *) wTFT_SDA__AMUX) 
/* Bidirectional Enable */                                                        
#define wTFT_SDA_BIE                    (* (reg8 *) wTFT_SDA__BIE)
/* Bit-mask for Aliased Register Access */
#define wTFT_SDA_BIT_MASK               (* (reg8 *) wTFT_SDA__BIT_MASK)
/* Bypass Enable */
#define wTFT_SDA_BYP                    (* (reg8 *) wTFT_SDA__BYP)
/* Port wide control signals */                                                   
#define wTFT_SDA_CTL                    (* (reg8 *) wTFT_SDA__CTL)
/* Drive Modes */
#define wTFT_SDA_DM0                    (* (reg8 *) wTFT_SDA__DM0) 
#define wTFT_SDA_DM1                    (* (reg8 *) wTFT_SDA__DM1)
#define wTFT_SDA_DM2                    (* (reg8 *) wTFT_SDA__DM2) 
/* Input Buffer Disable Override */
#define wTFT_SDA_INP_DIS                (* (reg8 *) wTFT_SDA__INP_DIS)
/* LCD Common or Segment Drive */
#define wTFT_SDA_LCD_COM_SEG            (* (reg8 *) wTFT_SDA__LCD_COM_SEG)
/* Enable Segment LCD */
#define wTFT_SDA_LCD_EN                 (* (reg8 *) wTFT_SDA__LCD_EN)
/* Slew Rate Control */
#define wTFT_SDA_SLW                    (* (reg8 *) wTFT_SDA__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define wTFT_SDA_PRTDSI__CAPS_SEL       (* (reg8 *) wTFT_SDA__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define wTFT_SDA_PRTDSI__DBL_SYNC_IN    (* (reg8 *) wTFT_SDA__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define wTFT_SDA_PRTDSI__OE_SEL0        (* (reg8 *) wTFT_SDA__PRTDSI__OE_SEL0) 
#define wTFT_SDA_PRTDSI__OE_SEL1        (* (reg8 *) wTFT_SDA__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define wTFT_SDA_PRTDSI__OUT_SEL0       (* (reg8 *) wTFT_SDA__PRTDSI__OUT_SEL0) 
#define wTFT_SDA_PRTDSI__OUT_SEL1       (* (reg8 *) wTFT_SDA__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define wTFT_SDA_PRTDSI__SYNC_OUT       (* (reg8 *) wTFT_SDA__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(wTFT_SDA__SIO_CFG)
    #define wTFT_SDA_SIO_HYST_EN        (* (reg8 *) wTFT_SDA__SIO_HYST_EN)
    #define wTFT_SDA_SIO_REG_HIFREQ     (* (reg8 *) wTFT_SDA__SIO_REG_HIFREQ)
    #define wTFT_SDA_SIO_CFG            (* (reg8 *) wTFT_SDA__SIO_CFG)
    #define wTFT_SDA_SIO_DIFF           (* (reg8 *) wTFT_SDA__SIO_DIFF)
#endif /* (wTFT_SDA__SIO_CFG) */

/* Interrupt Registers */
#if defined(wTFT_SDA__INTSTAT)
    #define wTFT_SDA_INTSTAT            (* (reg8 *) wTFT_SDA__INTSTAT)
    #define wTFT_SDA_SNAP               (* (reg8 *) wTFT_SDA__SNAP)
    
	#define wTFT_SDA_0_INTTYPE_REG 		(* (reg8 *) wTFT_SDA__0__INTTYPE)
#endif /* (wTFT_SDA__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_wTFT_SDA_H */


/* [] END OF FILE */
