/*******************************************************************************
* File Name: FL_QDA.h  
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

#if !defined(CY_PINS_FL_QDA_H) /* Pins FL_QDA_H */
#define CY_PINS_FL_QDA_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "FL_QDA_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 FL_QDA__PORT == 15 && ((FL_QDA__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    FL_QDA_Write(uint8 value);
void    FL_QDA_SetDriveMode(uint8 mode);
uint8   FL_QDA_ReadDataReg(void);
uint8   FL_QDA_Read(void);
void    FL_QDA_SetInterruptMode(uint16 position, uint16 mode);
uint8   FL_QDA_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the FL_QDA_SetDriveMode() function.
     *  @{
     */
        #define FL_QDA_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define FL_QDA_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define FL_QDA_DM_RES_UP          PIN_DM_RES_UP
        #define FL_QDA_DM_RES_DWN         PIN_DM_RES_DWN
        #define FL_QDA_DM_OD_LO           PIN_DM_OD_LO
        #define FL_QDA_DM_OD_HI           PIN_DM_OD_HI
        #define FL_QDA_DM_STRONG          PIN_DM_STRONG
        #define FL_QDA_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define FL_QDA_MASK               FL_QDA__MASK
#define FL_QDA_SHIFT              FL_QDA__SHIFT
#define FL_QDA_WIDTH              1u

/* Interrupt constants */
#if defined(FL_QDA__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in FL_QDA_SetInterruptMode() function.
     *  @{
     */
        #define FL_QDA_INTR_NONE      (uint16)(0x0000u)
        #define FL_QDA_INTR_RISING    (uint16)(0x0001u)
        #define FL_QDA_INTR_FALLING   (uint16)(0x0002u)
        #define FL_QDA_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define FL_QDA_INTR_MASK      (0x01u) 
#endif /* (FL_QDA__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define FL_QDA_PS                     (* (reg8 *) FL_QDA__PS)
/* Data Register */
#define FL_QDA_DR                     (* (reg8 *) FL_QDA__DR)
/* Port Number */
#define FL_QDA_PRT_NUM                (* (reg8 *) FL_QDA__PRT) 
/* Connect to Analog Globals */                                                  
#define FL_QDA_AG                     (* (reg8 *) FL_QDA__AG)                       
/* Analog MUX bux enable */
#define FL_QDA_AMUX                   (* (reg8 *) FL_QDA__AMUX) 
/* Bidirectional Enable */                                                        
#define FL_QDA_BIE                    (* (reg8 *) FL_QDA__BIE)
/* Bit-mask for Aliased Register Access */
#define FL_QDA_BIT_MASK               (* (reg8 *) FL_QDA__BIT_MASK)
/* Bypass Enable */
#define FL_QDA_BYP                    (* (reg8 *) FL_QDA__BYP)
/* Port wide control signals */                                                   
#define FL_QDA_CTL                    (* (reg8 *) FL_QDA__CTL)
/* Drive Modes */
#define FL_QDA_DM0                    (* (reg8 *) FL_QDA__DM0) 
#define FL_QDA_DM1                    (* (reg8 *) FL_QDA__DM1)
#define FL_QDA_DM2                    (* (reg8 *) FL_QDA__DM2) 
/* Input Buffer Disable Override */
#define FL_QDA_INP_DIS                (* (reg8 *) FL_QDA__INP_DIS)
/* LCD Common or Segment Drive */
#define FL_QDA_LCD_COM_SEG            (* (reg8 *) FL_QDA__LCD_COM_SEG)
/* Enable Segment LCD */
#define FL_QDA_LCD_EN                 (* (reg8 *) FL_QDA__LCD_EN)
/* Slew Rate Control */
#define FL_QDA_SLW                    (* (reg8 *) FL_QDA__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define FL_QDA_PRTDSI__CAPS_SEL       (* (reg8 *) FL_QDA__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define FL_QDA_PRTDSI__DBL_SYNC_IN    (* (reg8 *) FL_QDA__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define FL_QDA_PRTDSI__OE_SEL0        (* (reg8 *) FL_QDA__PRTDSI__OE_SEL0) 
#define FL_QDA_PRTDSI__OE_SEL1        (* (reg8 *) FL_QDA__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define FL_QDA_PRTDSI__OUT_SEL0       (* (reg8 *) FL_QDA__PRTDSI__OUT_SEL0) 
#define FL_QDA_PRTDSI__OUT_SEL1       (* (reg8 *) FL_QDA__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define FL_QDA_PRTDSI__SYNC_OUT       (* (reg8 *) FL_QDA__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(FL_QDA__SIO_CFG)
    #define FL_QDA_SIO_HYST_EN        (* (reg8 *) FL_QDA__SIO_HYST_EN)
    #define FL_QDA_SIO_REG_HIFREQ     (* (reg8 *) FL_QDA__SIO_REG_HIFREQ)
    #define FL_QDA_SIO_CFG            (* (reg8 *) FL_QDA__SIO_CFG)
    #define FL_QDA_SIO_DIFF           (* (reg8 *) FL_QDA__SIO_DIFF)
#endif /* (FL_QDA__SIO_CFG) */

/* Interrupt Registers */
#if defined(FL_QDA__INTSTAT)
    #define FL_QDA_INTSTAT            (* (reg8 *) FL_QDA__INTSTAT)
    #define FL_QDA_SNAP               (* (reg8 *) FL_QDA__SNAP)
    
	#define FL_QDA_0_INTTYPE_REG 		(* (reg8 *) FL_QDA__0__INTTYPE)
#endif /* (FL_QDA__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_FL_QDA_H */


/* [] END OF FILE */
