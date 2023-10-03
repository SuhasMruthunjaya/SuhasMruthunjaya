/*******************************************************************************
* File Name: FR_QDA.h  
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

#if !defined(CY_PINS_FR_QDA_H) /* Pins FR_QDA_H */
#define CY_PINS_FR_QDA_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "FR_QDA_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 FR_QDA__PORT == 15 && ((FR_QDA__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    FR_QDA_Write(uint8 value);
void    FR_QDA_SetDriveMode(uint8 mode);
uint8   FR_QDA_ReadDataReg(void);
uint8   FR_QDA_Read(void);
void    FR_QDA_SetInterruptMode(uint16 position, uint16 mode);
uint8   FR_QDA_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the FR_QDA_SetDriveMode() function.
     *  @{
     */
        #define FR_QDA_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define FR_QDA_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define FR_QDA_DM_RES_UP          PIN_DM_RES_UP
        #define FR_QDA_DM_RES_DWN         PIN_DM_RES_DWN
        #define FR_QDA_DM_OD_LO           PIN_DM_OD_LO
        #define FR_QDA_DM_OD_HI           PIN_DM_OD_HI
        #define FR_QDA_DM_STRONG          PIN_DM_STRONG
        #define FR_QDA_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define FR_QDA_MASK               FR_QDA__MASK
#define FR_QDA_SHIFT              FR_QDA__SHIFT
#define FR_QDA_WIDTH              1u

/* Interrupt constants */
#if defined(FR_QDA__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in FR_QDA_SetInterruptMode() function.
     *  @{
     */
        #define FR_QDA_INTR_NONE      (uint16)(0x0000u)
        #define FR_QDA_INTR_RISING    (uint16)(0x0001u)
        #define FR_QDA_INTR_FALLING   (uint16)(0x0002u)
        #define FR_QDA_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define FR_QDA_INTR_MASK      (0x01u) 
#endif /* (FR_QDA__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define FR_QDA_PS                     (* (reg8 *) FR_QDA__PS)
/* Data Register */
#define FR_QDA_DR                     (* (reg8 *) FR_QDA__DR)
/* Port Number */
#define FR_QDA_PRT_NUM                (* (reg8 *) FR_QDA__PRT) 
/* Connect to Analog Globals */                                                  
#define FR_QDA_AG                     (* (reg8 *) FR_QDA__AG)                       
/* Analog MUX bux enable */
#define FR_QDA_AMUX                   (* (reg8 *) FR_QDA__AMUX) 
/* Bidirectional Enable */                                                        
#define FR_QDA_BIE                    (* (reg8 *) FR_QDA__BIE)
/* Bit-mask for Aliased Register Access */
#define FR_QDA_BIT_MASK               (* (reg8 *) FR_QDA__BIT_MASK)
/* Bypass Enable */
#define FR_QDA_BYP                    (* (reg8 *) FR_QDA__BYP)
/* Port wide control signals */                                                   
#define FR_QDA_CTL                    (* (reg8 *) FR_QDA__CTL)
/* Drive Modes */
#define FR_QDA_DM0                    (* (reg8 *) FR_QDA__DM0) 
#define FR_QDA_DM1                    (* (reg8 *) FR_QDA__DM1)
#define FR_QDA_DM2                    (* (reg8 *) FR_QDA__DM2) 
/* Input Buffer Disable Override */
#define FR_QDA_INP_DIS                (* (reg8 *) FR_QDA__INP_DIS)
/* LCD Common or Segment Drive */
#define FR_QDA_LCD_COM_SEG            (* (reg8 *) FR_QDA__LCD_COM_SEG)
/* Enable Segment LCD */
#define FR_QDA_LCD_EN                 (* (reg8 *) FR_QDA__LCD_EN)
/* Slew Rate Control */
#define FR_QDA_SLW                    (* (reg8 *) FR_QDA__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define FR_QDA_PRTDSI__CAPS_SEL       (* (reg8 *) FR_QDA__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define FR_QDA_PRTDSI__DBL_SYNC_IN    (* (reg8 *) FR_QDA__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define FR_QDA_PRTDSI__OE_SEL0        (* (reg8 *) FR_QDA__PRTDSI__OE_SEL0) 
#define FR_QDA_PRTDSI__OE_SEL1        (* (reg8 *) FR_QDA__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define FR_QDA_PRTDSI__OUT_SEL0       (* (reg8 *) FR_QDA__PRTDSI__OUT_SEL0) 
#define FR_QDA_PRTDSI__OUT_SEL1       (* (reg8 *) FR_QDA__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define FR_QDA_PRTDSI__SYNC_OUT       (* (reg8 *) FR_QDA__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(FR_QDA__SIO_CFG)
    #define FR_QDA_SIO_HYST_EN        (* (reg8 *) FR_QDA__SIO_HYST_EN)
    #define FR_QDA_SIO_REG_HIFREQ     (* (reg8 *) FR_QDA__SIO_REG_HIFREQ)
    #define FR_QDA_SIO_CFG            (* (reg8 *) FR_QDA__SIO_CFG)
    #define FR_QDA_SIO_DIFF           (* (reg8 *) FR_QDA__SIO_DIFF)
#endif /* (FR_QDA__SIO_CFG) */

/* Interrupt Registers */
#if defined(FR_QDA__INTSTAT)
    #define FR_QDA_INTSTAT            (* (reg8 *) FR_QDA__INTSTAT)
    #define FR_QDA_SNAP               (* (reg8 *) FR_QDA__SNAP)
    
	#define FR_QDA_0_INTTYPE_REG 		(* (reg8 *) FR_QDA__0__INTTYPE)
#endif /* (FR_QDA__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_FR_QDA_H */


/* [] END OF FILE */
