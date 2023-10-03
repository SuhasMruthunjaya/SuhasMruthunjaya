/*******************************************************************************
* File Name: Vlt_div.h  
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

#if !defined(CY_PINS_Vlt_div_H) /* Pins Vlt_div_H */
#define CY_PINS_Vlt_div_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "Vlt_div_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 Vlt_div__PORT == 15 && ((Vlt_div__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    Vlt_div_Write(uint8 value);
void    Vlt_div_SetDriveMode(uint8 mode);
uint8   Vlt_div_ReadDataReg(void);
uint8   Vlt_div_Read(void);
void    Vlt_div_SetInterruptMode(uint16 position, uint16 mode);
uint8   Vlt_div_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the Vlt_div_SetDriveMode() function.
     *  @{
     */
        #define Vlt_div_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define Vlt_div_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define Vlt_div_DM_RES_UP          PIN_DM_RES_UP
        #define Vlt_div_DM_RES_DWN         PIN_DM_RES_DWN
        #define Vlt_div_DM_OD_LO           PIN_DM_OD_LO
        #define Vlt_div_DM_OD_HI           PIN_DM_OD_HI
        #define Vlt_div_DM_STRONG          PIN_DM_STRONG
        #define Vlt_div_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define Vlt_div_MASK               Vlt_div__MASK
#define Vlt_div_SHIFT              Vlt_div__SHIFT
#define Vlt_div_WIDTH              1u

/* Interrupt constants */
#if defined(Vlt_div__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in Vlt_div_SetInterruptMode() function.
     *  @{
     */
        #define Vlt_div_INTR_NONE      (uint16)(0x0000u)
        #define Vlt_div_INTR_RISING    (uint16)(0x0001u)
        #define Vlt_div_INTR_FALLING   (uint16)(0x0002u)
        #define Vlt_div_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define Vlt_div_INTR_MASK      (0x01u) 
#endif /* (Vlt_div__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Vlt_div_PS                     (* (reg8 *) Vlt_div__PS)
/* Data Register */
#define Vlt_div_DR                     (* (reg8 *) Vlt_div__DR)
/* Port Number */
#define Vlt_div_PRT_NUM                (* (reg8 *) Vlt_div__PRT) 
/* Connect to Analog Globals */                                                  
#define Vlt_div_AG                     (* (reg8 *) Vlt_div__AG)                       
/* Analog MUX bux enable */
#define Vlt_div_AMUX                   (* (reg8 *) Vlt_div__AMUX) 
/* Bidirectional Enable */                                                        
#define Vlt_div_BIE                    (* (reg8 *) Vlt_div__BIE)
/* Bit-mask for Aliased Register Access */
#define Vlt_div_BIT_MASK               (* (reg8 *) Vlt_div__BIT_MASK)
/* Bypass Enable */
#define Vlt_div_BYP                    (* (reg8 *) Vlt_div__BYP)
/* Port wide control signals */                                                   
#define Vlt_div_CTL                    (* (reg8 *) Vlt_div__CTL)
/* Drive Modes */
#define Vlt_div_DM0                    (* (reg8 *) Vlt_div__DM0) 
#define Vlt_div_DM1                    (* (reg8 *) Vlt_div__DM1)
#define Vlt_div_DM2                    (* (reg8 *) Vlt_div__DM2) 
/* Input Buffer Disable Override */
#define Vlt_div_INP_DIS                (* (reg8 *) Vlt_div__INP_DIS)
/* LCD Common or Segment Drive */
#define Vlt_div_LCD_COM_SEG            (* (reg8 *) Vlt_div__LCD_COM_SEG)
/* Enable Segment LCD */
#define Vlt_div_LCD_EN                 (* (reg8 *) Vlt_div__LCD_EN)
/* Slew Rate Control */
#define Vlt_div_SLW                    (* (reg8 *) Vlt_div__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define Vlt_div_PRTDSI__CAPS_SEL       (* (reg8 *) Vlt_div__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define Vlt_div_PRTDSI__DBL_SYNC_IN    (* (reg8 *) Vlt_div__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define Vlt_div_PRTDSI__OE_SEL0        (* (reg8 *) Vlt_div__PRTDSI__OE_SEL0) 
#define Vlt_div_PRTDSI__OE_SEL1        (* (reg8 *) Vlt_div__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define Vlt_div_PRTDSI__OUT_SEL0       (* (reg8 *) Vlt_div__PRTDSI__OUT_SEL0) 
#define Vlt_div_PRTDSI__OUT_SEL1       (* (reg8 *) Vlt_div__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define Vlt_div_PRTDSI__SYNC_OUT       (* (reg8 *) Vlt_div__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(Vlt_div__SIO_CFG)
    #define Vlt_div_SIO_HYST_EN        (* (reg8 *) Vlt_div__SIO_HYST_EN)
    #define Vlt_div_SIO_REG_HIFREQ     (* (reg8 *) Vlt_div__SIO_REG_HIFREQ)
    #define Vlt_div_SIO_CFG            (* (reg8 *) Vlt_div__SIO_CFG)
    #define Vlt_div_SIO_DIFF           (* (reg8 *) Vlt_div__SIO_DIFF)
#endif /* (Vlt_div__SIO_CFG) */

/* Interrupt Registers */
#if defined(Vlt_div__INTSTAT)
    #define Vlt_div_INTSTAT            (* (reg8 *) Vlt_div__INTSTAT)
    #define Vlt_div_SNAP               (* (reg8 *) Vlt_div__SNAP)
    
	#define Vlt_div_0_INTTYPE_REG 		(* (reg8 *) Vlt_div__0__INTTYPE)
#endif /* (Vlt_div__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_Vlt_div_H */


/* [] END OF FILE */
