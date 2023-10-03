/*******************************************************************************
* File Name: FR_QDB.h  
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

#if !defined(CY_PINS_FR_QDB_H) /* Pins FR_QDB_H */
#define CY_PINS_FR_QDB_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "FR_QDB_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 FR_QDB__PORT == 15 && ((FR_QDB__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    FR_QDB_Write(uint8 value);
void    FR_QDB_SetDriveMode(uint8 mode);
uint8   FR_QDB_ReadDataReg(void);
uint8   FR_QDB_Read(void);
void    FR_QDB_SetInterruptMode(uint16 position, uint16 mode);
uint8   FR_QDB_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the FR_QDB_SetDriveMode() function.
     *  @{
     */
        #define FR_QDB_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define FR_QDB_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define FR_QDB_DM_RES_UP          PIN_DM_RES_UP
        #define FR_QDB_DM_RES_DWN         PIN_DM_RES_DWN
        #define FR_QDB_DM_OD_LO           PIN_DM_OD_LO
        #define FR_QDB_DM_OD_HI           PIN_DM_OD_HI
        #define FR_QDB_DM_STRONG          PIN_DM_STRONG
        #define FR_QDB_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define FR_QDB_MASK               FR_QDB__MASK
#define FR_QDB_SHIFT              FR_QDB__SHIFT
#define FR_QDB_WIDTH              1u

/* Interrupt constants */
#if defined(FR_QDB__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in FR_QDB_SetInterruptMode() function.
     *  @{
     */
        #define FR_QDB_INTR_NONE      (uint16)(0x0000u)
        #define FR_QDB_INTR_RISING    (uint16)(0x0001u)
        #define FR_QDB_INTR_FALLING   (uint16)(0x0002u)
        #define FR_QDB_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define FR_QDB_INTR_MASK      (0x01u) 
#endif /* (FR_QDB__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define FR_QDB_PS                     (* (reg8 *) FR_QDB__PS)
/* Data Register */
#define FR_QDB_DR                     (* (reg8 *) FR_QDB__DR)
/* Port Number */
#define FR_QDB_PRT_NUM                (* (reg8 *) FR_QDB__PRT) 
/* Connect to Analog Globals */                                                  
#define FR_QDB_AG                     (* (reg8 *) FR_QDB__AG)                       
/* Analog MUX bux enable */
#define FR_QDB_AMUX                   (* (reg8 *) FR_QDB__AMUX) 
/* Bidirectional Enable */                                                        
#define FR_QDB_BIE                    (* (reg8 *) FR_QDB__BIE)
/* Bit-mask for Aliased Register Access */
#define FR_QDB_BIT_MASK               (* (reg8 *) FR_QDB__BIT_MASK)
/* Bypass Enable */
#define FR_QDB_BYP                    (* (reg8 *) FR_QDB__BYP)
/* Port wide control signals */                                                   
#define FR_QDB_CTL                    (* (reg8 *) FR_QDB__CTL)
/* Drive Modes */
#define FR_QDB_DM0                    (* (reg8 *) FR_QDB__DM0) 
#define FR_QDB_DM1                    (* (reg8 *) FR_QDB__DM1)
#define FR_QDB_DM2                    (* (reg8 *) FR_QDB__DM2) 
/* Input Buffer Disable Override */
#define FR_QDB_INP_DIS                (* (reg8 *) FR_QDB__INP_DIS)
/* LCD Common or Segment Drive */
#define FR_QDB_LCD_COM_SEG            (* (reg8 *) FR_QDB__LCD_COM_SEG)
/* Enable Segment LCD */
#define FR_QDB_LCD_EN                 (* (reg8 *) FR_QDB__LCD_EN)
/* Slew Rate Control */
#define FR_QDB_SLW                    (* (reg8 *) FR_QDB__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define FR_QDB_PRTDSI__CAPS_SEL       (* (reg8 *) FR_QDB__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define FR_QDB_PRTDSI__DBL_SYNC_IN    (* (reg8 *) FR_QDB__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define FR_QDB_PRTDSI__OE_SEL0        (* (reg8 *) FR_QDB__PRTDSI__OE_SEL0) 
#define FR_QDB_PRTDSI__OE_SEL1        (* (reg8 *) FR_QDB__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define FR_QDB_PRTDSI__OUT_SEL0       (* (reg8 *) FR_QDB__PRTDSI__OUT_SEL0) 
#define FR_QDB_PRTDSI__OUT_SEL1       (* (reg8 *) FR_QDB__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define FR_QDB_PRTDSI__SYNC_OUT       (* (reg8 *) FR_QDB__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(FR_QDB__SIO_CFG)
    #define FR_QDB_SIO_HYST_EN        (* (reg8 *) FR_QDB__SIO_HYST_EN)
    #define FR_QDB_SIO_REG_HIFREQ     (* (reg8 *) FR_QDB__SIO_REG_HIFREQ)
    #define FR_QDB_SIO_CFG            (* (reg8 *) FR_QDB__SIO_CFG)
    #define FR_QDB_SIO_DIFF           (* (reg8 *) FR_QDB__SIO_DIFF)
#endif /* (FR_QDB__SIO_CFG) */

/* Interrupt Registers */
#if defined(FR_QDB__INTSTAT)
    #define FR_QDB_INTSTAT            (* (reg8 *) FR_QDB__INTSTAT)
    #define FR_QDB_SNAP               (* (reg8 *) FR_QDB__SNAP)
    
	#define FR_QDB_0_INTTYPE_REG 		(* (reg8 *) FR_QDB__0__INTTYPE)
#endif /* (FR_QDB__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_FR_QDB_H */


/* [] END OF FILE */
