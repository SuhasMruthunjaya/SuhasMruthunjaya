/*******************************************************************************
* File Name: FL_QuadDec.h  
* Version 3.0
*
* Description:
*  This file provides constants and parameter values for the Quadrature
*  Decoder component.
*
* Note:
*  None.
*
********************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_QUADRATURE_DECODER_FL_QuadDec_H)
#define CY_QUADRATURE_DECODER_FL_QuadDec_H

#include "cyfitter.h"
#include "CyLib.h"
#include "cytypes.h"

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component QuadDec_v3_0 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5LP) */

#define FL_QuadDec_COUNTER_SIZE               (32u)
#define FL_QuadDec_COUNTER_SIZE_8_BIT         (8u)
#define FL_QuadDec_COUNTER_SIZE_16_BIT        (16u)
#define FL_QuadDec_COUNTER_SIZE_32_BIT        (32u)

#if (FL_QuadDec_COUNTER_SIZE == FL_QuadDec_COUNTER_SIZE_8_BIT)
    #include "FL_QuadDec_Cnt8.h"
#else 
    /* (FL_QuadDec_COUNTER_SIZE == FL_QuadDec_COUNTER_SIZE_16_BIT) || 
    *  (FL_QuadDec_COUNTER_SIZE == FL_QuadDec_COUNTER_SIZE_32_BIT) 
    */
    #include "FL_QuadDec_Cnt16.h"
#endif /* FL_QuadDec_COUNTER_SIZE == FL_QuadDec_COUNTER_SIZE_8_BIT */

extern uint8 FL_QuadDec_initVar;


/***************************************
*   Conditional Compilation Parameters
***************************************/

#define FL_QuadDec_COUNTER_RESOLUTION         (1u)


/***************************************
*       Data Struct Definition
***************************************/

/* Sleep Mode API Support */
typedef struct
{
    uint8 enableState;
} FL_QuadDec_BACKUP_STRUCT;


/***************************************
*        Function Prototypes
***************************************/

void  FL_QuadDec_Init(void) ;
void  FL_QuadDec_Start(void) ;
void  FL_QuadDec_Stop(void) ;
void  FL_QuadDec_Enable(void) ;
uint8 FL_QuadDec_GetEvents(void) ;
void  FL_QuadDec_SetInterruptMask(uint8 mask) ;
uint8 FL_QuadDec_GetInterruptMask(void) ;
int32 FL_QuadDec_GetCounter(void) ;
void  FL_QuadDec_SetCounter(int32 value)
;
void  FL_QuadDec_Sleep(void) ;
void  FL_QuadDec_Wakeup(void) ;
void  FL_QuadDec_SaveConfig(void) ;
void  FL_QuadDec_RestoreConfig(void) ;

#if (FL_QuadDec_COUNTER_SIZE == FL_QuadDec_COUNTER_SIZE_32_BIT)
    CY_ISR_PROTO(FL_QuadDec_ISR);
#endif /* FL_QuadDec_COUNTER_SIZE == FL_QuadDec_COUNTER_SIZE_32_BIT */


/***************************************
*           API Constants
***************************************/

#if (FL_QuadDec_COUNTER_SIZE == FL_QuadDec_COUNTER_SIZE_32_BIT)
    #define FL_QuadDec_ISR_NUMBER             ((uint8) FL_QuadDec_isr__INTC_NUMBER)
    #define FL_QuadDec_ISR_PRIORITY           ((uint8) FL_QuadDec_isr__INTC_PRIOR_NUM)
#endif /* FL_QuadDec_COUNTER_SIZE == FL_QuadDec_COUNTER_SIZE_32_BIT */


/***************************************
*    Enumerated Types and Parameters
***************************************/

#define FL_QuadDec_GLITCH_FILTERING           (0u)
#define FL_QuadDec_INDEX_INPUT                (0u)


/***************************************
*    Initial Parameter Constants
***************************************/

#if (FL_QuadDec_COUNTER_SIZE == FL_QuadDec_COUNTER_SIZE_8_BIT)
    #define FL_QuadDec_COUNTER_INIT_VALUE    (0x80u)
#else 
    /* (FL_QuadDec_COUNTER_SIZE == FL_QuadDec_COUNTER_SIZE_16_BIT) ||
    *  (FL_QuadDec_COUNTER_SIZE == FL_QuadDec_COUNTER_SIZE_32_BIT)
    */
    #define FL_QuadDec_COUNTER_INIT_VALUE    (0x8000u)
    #define FL_QuadDec_COUNTER_MAX_VALUE     (0x7FFFu)
#endif /* FL_QuadDec_COUNTER_SIZE == FL_QuadDec_COUNTER_SIZE_8_BIT */


/***************************************
*             Registers
***************************************/

#define FL_QuadDec_STATUS_REG                 (* (reg8 *) FL_QuadDec_bQuadDec_Stsreg__STATUS_REG)
#define FL_QuadDec_STATUS_PTR                 (  (reg8 *) FL_QuadDec_bQuadDec_Stsreg__STATUS_REG)
#define FL_QuadDec_STATUS_MASK                (* (reg8 *) FL_QuadDec_bQuadDec_Stsreg__MASK_REG)
#define FL_QuadDec_STATUS_MASK_PTR            (  (reg8 *) FL_QuadDec_bQuadDec_Stsreg__MASK_REG)
#define FL_QuadDec_SR_AUX_CONTROL             (* (reg8 *) FL_QuadDec_bQuadDec_Stsreg__STATUS_AUX_CTL_REG)
#define FL_QuadDec_SR_AUX_CONTROL_PTR         (  (reg8 *) FL_QuadDec_bQuadDec_Stsreg__STATUS_AUX_CTL_REG)


/***************************************
*        Register Constants
***************************************/

#define FL_QuadDec_COUNTER_OVERFLOW_SHIFT     (0x00u)
#define FL_QuadDec_COUNTER_UNDERFLOW_SHIFT    (0x01u)
#define FL_QuadDec_COUNTER_RESET_SHIFT        (0x02u)
#define FL_QuadDec_INVALID_IN_SHIFT           (0x03u)
#define FL_QuadDec_COUNTER_OVERFLOW           ((uint8) (0x01u << FL_QuadDec_COUNTER_OVERFLOW_SHIFT))
#define FL_QuadDec_COUNTER_UNDERFLOW          ((uint8) (0x01u << FL_QuadDec_COUNTER_UNDERFLOW_SHIFT))
#define FL_QuadDec_COUNTER_RESET              ((uint8) (0x01u << FL_QuadDec_COUNTER_RESET_SHIFT))
#define FL_QuadDec_INVALID_IN                 ((uint8) (0x01u << FL_QuadDec_INVALID_IN_SHIFT))

#define FL_QuadDec_INTERRUPTS_ENABLE_SHIFT    (0x04u)
#define FL_QuadDec_INTERRUPTS_ENABLE          ((uint8)(0x01u << FL_QuadDec_INTERRUPTS_ENABLE_SHIFT))
#define FL_QuadDec_INIT_INT_MASK              (0x0Fu)


/******************************************************************************************
* Following code are OBSOLETE and must not be used starting from Quadrature Decoder 2.20
******************************************************************************************/
#define FL_QuadDec_DISABLE                    (0x00u)


#endif /* CY_QUADRATURE_DECODER_FL_QuadDec_H */


/* [] END OF FILE */
