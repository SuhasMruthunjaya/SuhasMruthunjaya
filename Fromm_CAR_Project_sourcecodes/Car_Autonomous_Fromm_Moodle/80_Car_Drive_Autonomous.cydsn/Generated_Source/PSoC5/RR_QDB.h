/*******************************************************************************
* File Name: RR_QDB.h  
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

#if !defined(CY_PINS_RR_QDB_H) /* Pins RR_QDB_H */
#define CY_PINS_RR_QDB_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "RR_QDB_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 RR_QDB__PORT == 15 && ((RR_QDB__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    RR_QDB_Write(uint8 value);
void    RR_QDB_SetDriveMode(uint8 mode);
uint8   RR_QDB_ReadDataReg(void);
uint8   RR_QDB_Read(void);
void    RR_QDB_SetInterruptMode(uint16 position, uint16 mode);
uint8   RR_QDB_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the RR_QDB_SetDriveMode() function.
     *  @{
     */
        #define RR_QDB_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define RR_QDB_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define RR_QDB_DM_RES_UP          PIN_DM_RES_UP
        #define RR_QDB_DM_RES_DWN         PIN_DM_RES_DWN
        #define RR_QDB_DM_OD_LO           PIN_DM_OD_LO
        #define RR_QDB_DM_OD_HI           PIN_DM_OD_HI
        #define RR_QDB_DM_STRONG          PIN_DM_STRONG
        #define RR_QDB_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define RR_QDB_MASK               RR_QDB__MASK
#define RR_QDB_SHIFT              RR_QDB__SHIFT
#define RR_QDB_WIDTH              1u

/* Interrupt constants */
#if defined(RR_QDB__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in RR_QDB_SetInterruptMode() function.
     *  @{
     */
        #define RR_QDB_INTR_NONE      (uint16)(0x0000u)
        #define RR_QDB_INTR_RISING    (uint16)(0x0001u)
        #define RR_QDB_INTR_FALLING   (uint16)(0x0002u)
        #define RR_QDB_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define RR_QDB_INTR_MASK      (0x01u) 
#endif /* (RR_QDB__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define RR_QDB_PS                     (* (reg8 *) RR_QDB__PS)
/* Data Register */
#define RR_QDB_DR                     (* (reg8 *) RR_QDB__DR)
/* Port Number */
#define RR_QDB_PRT_NUM                (* (reg8 *) RR_QDB__PRT) 
/* Connect to Analog Globals */                                                  
#define RR_QDB_AG                     (* (reg8 *) RR_QDB__AG)                       
/* Analog MUX bux enable */
#define RR_QDB_AMUX                   (* (reg8 *) RR_QDB__AMUX) 
/* Bidirectional Enable */                                                        
#define RR_QDB_BIE                    (* (reg8 *) RR_QDB__BIE)
/* Bit-mask for Aliased Register Access */
#define RR_QDB_BIT_MASK               (* (reg8 *) RR_QDB__BIT_MASK)
/* Bypass Enable */
#define RR_QDB_BYP                    (* (reg8 *) RR_QDB__BYP)
/* Port wide control signals */                                                   
#define RR_QDB_CTL                    (* (reg8 *) RR_QDB__CTL)
/* Drive Modes */
#define RR_QDB_DM0                    (* (reg8 *) RR_QDB__DM0) 
#define RR_QDB_DM1                    (* (reg8 *) RR_QDB__DM1)
#define RR_QDB_DM2                    (* (reg8 *) RR_QDB__DM2) 
/* Input Buffer Disable Override */
#define RR_QDB_INP_DIS                (* (reg8 *) RR_QDB__INP_DIS)
/* LCD Common or Segment Drive */
#define RR_QDB_LCD_COM_SEG            (* (reg8 *) RR_QDB__LCD_COM_SEG)
/* Enable Segment LCD */
#define RR_QDB_LCD_EN                 (* (reg8 *) RR_QDB__LCD_EN)
/* Slew Rate Control */
#define RR_QDB_SLW                    (* (reg8 *) RR_QDB__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define RR_QDB_PRTDSI__CAPS_SEL       (* (reg8 *) RR_QDB__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define RR_QDB_PRTDSI__DBL_SYNC_IN    (* (reg8 *) RR_QDB__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define RR_QDB_PRTDSI__OE_SEL0        (* (reg8 *) RR_QDB__PRTDSI__OE_SEL0) 
#define RR_QDB_PRTDSI__OE_SEL1        (* (reg8 *) RR_QDB__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define RR_QDB_PRTDSI__OUT_SEL0       (* (reg8 *) RR_QDB__PRTDSI__OUT_SEL0) 
#define RR_QDB_PRTDSI__OUT_SEL1       (* (reg8 *) RR_QDB__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define RR_QDB_PRTDSI__SYNC_OUT       (* (reg8 *) RR_QDB__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(RR_QDB__SIO_CFG)
    #define RR_QDB_SIO_HYST_EN        (* (reg8 *) RR_QDB__SIO_HYST_EN)
    #define RR_QDB_SIO_REG_HIFREQ     (* (reg8 *) RR_QDB__SIO_REG_HIFREQ)
    #define RR_QDB_SIO_CFG            (* (reg8 *) RR_QDB__SIO_CFG)
    #define RR_QDB_SIO_DIFF           (* (reg8 *) RR_QDB__SIO_DIFF)
#endif /* (RR_QDB__SIO_CFG) */

/* Interrupt Registers */
#if defined(RR_QDB__INTSTAT)
    #define RR_QDB_INTSTAT            (* (reg8 *) RR_QDB__INTSTAT)
    #define RR_QDB_SNAP               (* (reg8 *) RR_QDB__SNAP)
    
	#define RR_QDB_0_INTTYPE_REG 		(* (reg8 *) RR_QDB__0__INTTYPE)
#endif /* (RR_QDB__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_RR_QDB_H */


/* [] END OF FILE */
