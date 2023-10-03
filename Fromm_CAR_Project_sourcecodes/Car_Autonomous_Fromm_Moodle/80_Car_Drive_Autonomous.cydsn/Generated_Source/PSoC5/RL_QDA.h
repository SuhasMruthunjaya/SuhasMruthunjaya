/*******************************************************************************
* File Name: RL_QDA.h  
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

#if !defined(CY_PINS_RL_QDA_H) /* Pins RL_QDA_H */
#define CY_PINS_RL_QDA_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "RL_QDA_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 RL_QDA__PORT == 15 && ((RL_QDA__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    RL_QDA_Write(uint8 value);
void    RL_QDA_SetDriveMode(uint8 mode);
uint8   RL_QDA_ReadDataReg(void);
uint8   RL_QDA_Read(void);
void    RL_QDA_SetInterruptMode(uint16 position, uint16 mode);
uint8   RL_QDA_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the RL_QDA_SetDriveMode() function.
     *  @{
     */
        #define RL_QDA_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define RL_QDA_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define RL_QDA_DM_RES_UP          PIN_DM_RES_UP
        #define RL_QDA_DM_RES_DWN         PIN_DM_RES_DWN
        #define RL_QDA_DM_OD_LO           PIN_DM_OD_LO
        #define RL_QDA_DM_OD_HI           PIN_DM_OD_HI
        #define RL_QDA_DM_STRONG          PIN_DM_STRONG
        #define RL_QDA_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define RL_QDA_MASK               RL_QDA__MASK
#define RL_QDA_SHIFT              RL_QDA__SHIFT
#define RL_QDA_WIDTH              1u

/* Interrupt constants */
#if defined(RL_QDA__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in RL_QDA_SetInterruptMode() function.
     *  @{
     */
        #define RL_QDA_INTR_NONE      (uint16)(0x0000u)
        #define RL_QDA_INTR_RISING    (uint16)(0x0001u)
        #define RL_QDA_INTR_FALLING   (uint16)(0x0002u)
        #define RL_QDA_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define RL_QDA_INTR_MASK      (0x01u) 
#endif /* (RL_QDA__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define RL_QDA_PS                     (* (reg8 *) RL_QDA__PS)
/* Data Register */
#define RL_QDA_DR                     (* (reg8 *) RL_QDA__DR)
/* Port Number */
#define RL_QDA_PRT_NUM                (* (reg8 *) RL_QDA__PRT) 
/* Connect to Analog Globals */                                                  
#define RL_QDA_AG                     (* (reg8 *) RL_QDA__AG)                       
/* Analog MUX bux enable */
#define RL_QDA_AMUX                   (* (reg8 *) RL_QDA__AMUX) 
/* Bidirectional Enable */                                                        
#define RL_QDA_BIE                    (* (reg8 *) RL_QDA__BIE)
/* Bit-mask for Aliased Register Access */
#define RL_QDA_BIT_MASK               (* (reg8 *) RL_QDA__BIT_MASK)
/* Bypass Enable */
#define RL_QDA_BYP                    (* (reg8 *) RL_QDA__BYP)
/* Port wide control signals */                                                   
#define RL_QDA_CTL                    (* (reg8 *) RL_QDA__CTL)
/* Drive Modes */
#define RL_QDA_DM0                    (* (reg8 *) RL_QDA__DM0) 
#define RL_QDA_DM1                    (* (reg8 *) RL_QDA__DM1)
#define RL_QDA_DM2                    (* (reg8 *) RL_QDA__DM2) 
/* Input Buffer Disable Override */
#define RL_QDA_INP_DIS                (* (reg8 *) RL_QDA__INP_DIS)
/* LCD Common or Segment Drive */
#define RL_QDA_LCD_COM_SEG            (* (reg8 *) RL_QDA__LCD_COM_SEG)
/* Enable Segment LCD */
#define RL_QDA_LCD_EN                 (* (reg8 *) RL_QDA__LCD_EN)
/* Slew Rate Control */
#define RL_QDA_SLW                    (* (reg8 *) RL_QDA__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define RL_QDA_PRTDSI__CAPS_SEL       (* (reg8 *) RL_QDA__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define RL_QDA_PRTDSI__DBL_SYNC_IN    (* (reg8 *) RL_QDA__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define RL_QDA_PRTDSI__OE_SEL0        (* (reg8 *) RL_QDA__PRTDSI__OE_SEL0) 
#define RL_QDA_PRTDSI__OE_SEL1        (* (reg8 *) RL_QDA__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define RL_QDA_PRTDSI__OUT_SEL0       (* (reg8 *) RL_QDA__PRTDSI__OUT_SEL0) 
#define RL_QDA_PRTDSI__OUT_SEL1       (* (reg8 *) RL_QDA__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define RL_QDA_PRTDSI__SYNC_OUT       (* (reg8 *) RL_QDA__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(RL_QDA__SIO_CFG)
    #define RL_QDA_SIO_HYST_EN        (* (reg8 *) RL_QDA__SIO_HYST_EN)
    #define RL_QDA_SIO_REG_HIFREQ     (* (reg8 *) RL_QDA__SIO_REG_HIFREQ)
    #define RL_QDA_SIO_CFG            (* (reg8 *) RL_QDA__SIO_CFG)
    #define RL_QDA_SIO_DIFF           (* (reg8 *) RL_QDA__SIO_DIFF)
#endif /* (RL_QDA__SIO_CFG) */

/* Interrupt Registers */
#if defined(RL_QDA__INTSTAT)
    #define RL_QDA_INTSTAT            (* (reg8 *) RL_QDA__INTSTAT)
    #define RL_QDA_SNAP               (* (reg8 *) RL_QDA__SNAP)
    
	#define RL_QDA_0_INTTYPE_REG 		(* (reg8 *) RL_QDA__0__INTTYPE)
#endif /* (RL_QDA__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_RL_QDA_H */


/* [] END OF FILE */
