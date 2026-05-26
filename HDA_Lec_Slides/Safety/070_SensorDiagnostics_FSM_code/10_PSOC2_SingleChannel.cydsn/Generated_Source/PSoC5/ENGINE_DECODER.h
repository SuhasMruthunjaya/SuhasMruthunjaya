/*******************************************************************************
* File Name: ENGINE_DECODER.h  
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

#if !defined(CY_QUADRATURE_DECODER_ENGINE_DECODER_H)
#define CY_QUADRATURE_DECODER_ENGINE_DECODER_H

#include "cyfitter.h"
#include "CyLib.h"
#include "cytypes.h"

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component QuadDec_v3_0 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5LP) */

#define ENGINE_DECODER_COUNTER_SIZE               (32u)
#define ENGINE_DECODER_COUNTER_SIZE_8_BIT         (8u)
#define ENGINE_DECODER_COUNTER_SIZE_16_BIT        (16u)
#define ENGINE_DECODER_COUNTER_SIZE_32_BIT        (32u)

#if (ENGINE_DECODER_COUNTER_SIZE == ENGINE_DECODER_COUNTER_SIZE_8_BIT)
    #include "ENGINE_DECODER_Cnt8.h"
#else 
    /* (ENGINE_DECODER_COUNTER_SIZE == ENGINE_DECODER_COUNTER_SIZE_16_BIT) || 
    *  (ENGINE_DECODER_COUNTER_SIZE == ENGINE_DECODER_COUNTER_SIZE_32_BIT) 
    */
    #include "ENGINE_DECODER_Cnt16.h"
#endif /* ENGINE_DECODER_COUNTER_SIZE == ENGINE_DECODER_COUNTER_SIZE_8_BIT */

extern uint8 ENGINE_DECODER_initVar;


/***************************************
*   Conditional Compilation Parameters
***************************************/

#define ENGINE_DECODER_COUNTER_RESOLUTION         (1u)


/***************************************
*       Data Struct Definition
***************************************/

/* Sleep Mode API Support */
typedef struct
{
    uint8 enableState;
} ENGINE_DECODER_BACKUP_STRUCT;


/***************************************
*        Function Prototypes
***************************************/

void  ENGINE_DECODER_Init(void) ;
void  ENGINE_DECODER_Start(void) ;
void  ENGINE_DECODER_Stop(void) ;
void  ENGINE_DECODER_Enable(void) ;
uint8 ENGINE_DECODER_GetEvents(void) ;
void  ENGINE_DECODER_SetInterruptMask(uint8 mask) ;
uint8 ENGINE_DECODER_GetInterruptMask(void) ;
int32 ENGINE_DECODER_GetCounter(void) ;
void  ENGINE_DECODER_SetCounter(int32 value)
;
void  ENGINE_DECODER_Sleep(void) ;
void  ENGINE_DECODER_Wakeup(void) ;
void  ENGINE_DECODER_SaveConfig(void) ;
void  ENGINE_DECODER_RestoreConfig(void) ;

#if (ENGINE_DECODER_COUNTER_SIZE == ENGINE_DECODER_COUNTER_SIZE_32_BIT)
    CY_ISR_PROTO(ENGINE_DECODER_ISR);
#endif /* ENGINE_DECODER_COUNTER_SIZE == ENGINE_DECODER_COUNTER_SIZE_32_BIT */


/***************************************
*           API Constants
***************************************/

#if (ENGINE_DECODER_COUNTER_SIZE == ENGINE_DECODER_COUNTER_SIZE_32_BIT)
    #define ENGINE_DECODER_ISR_NUMBER             ((uint8) ENGINE_DECODER_isr__INTC_NUMBER)
    #define ENGINE_DECODER_ISR_PRIORITY           ((uint8) ENGINE_DECODER_isr__INTC_PRIOR_NUM)
#endif /* ENGINE_DECODER_COUNTER_SIZE == ENGINE_DECODER_COUNTER_SIZE_32_BIT */


/***************************************
*    Enumerated Types and Parameters
***************************************/

#define ENGINE_DECODER_GLITCH_FILTERING           (1u)
#define ENGINE_DECODER_INDEX_INPUT                (0u)


/***************************************
*    Initial Parameter Constants
***************************************/

#if (ENGINE_DECODER_COUNTER_SIZE == ENGINE_DECODER_COUNTER_SIZE_8_BIT)
    #define ENGINE_DECODER_COUNTER_INIT_VALUE    (0x80u)
#else 
    /* (ENGINE_DECODER_COUNTER_SIZE == ENGINE_DECODER_COUNTER_SIZE_16_BIT) ||
    *  (ENGINE_DECODER_COUNTER_SIZE == ENGINE_DECODER_COUNTER_SIZE_32_BIT)
    */
    #define ENGINE_DECODER_COUNTER_INIT_VALUE    (0x8000u)
    #define ENGINE_DECODER_COUNTER_MAX_VALUE     (0x7FFFu)
#endif /* ENGINE_DECODER_COUNTER_SIZE == ENGINE_DECODER_COUNTER_SIZE_8_BIT */


/***************************************
*             Registers
***************************************/

#define ENGINE_DECODER_STATUS_REG                 (* (reg8 *) ENGINE_DECODER_bQuadDec_Stsreg__STATUS_REG)
#define ENGINE_DECODER_STATUS_PTR                 (  (reg8 *) ENGINE_DECODER_bQuadDec_Stsreg__STATUS_REG)
#define ENGINE_DECODER_STATUS_MASK                (* (reg8 *) ENGINE_DECODER_bQuadDec_Stsreg__MASK_REG)
#define ENGINE_DECODER_STATUS_MASK_PTR            (  (reg8 *) ENGINE_DECODER_bQuadDec_Stsreg__MASK_REG)
#define ENGINE_DECODER_SR_AUX_CONTROL             (* (reg8 *) ENGINE_DECODER_bQuadDec_Stsreg__STATUS_AUX_CTL_REG)
#define ENGINE_DECODER_SR_AUX_CONTROL_PTR         (  (reg8 *) ENGINE_DECODER_bQuadDec_Stsreg__STATUS_AUX_CTL_REG)


/***************************************
*        Register Constants
***************************************/

#define ENGINE_DECODER_COUNTER_OVERFLOW_SHIFT     (0x00u)
#define ENGINE_DECODER_COUNTER_UNDERFLOW_SHIFT    (0x01u)
#define ENGINE_DECODER_COUNTER_RESET_SHIFT        (0x02u)
#define ENGINE_DECODER_INVALID_IN_SHIFT           (0x03u)
#define ENGINE_DECODER_COUNTER_OVERFLOW           ((uint8) (0x01u << ENGINE_DECODER_COUNTER_OVERFLOW_SHIFT))
#define ENGINE_DECODER_COUNTER_UNDERFLOW          ((uint8) (0x01u << ENGINE_DECODER_COUNTER_UNDERFLOW_SHIFT))
#define ENGINE_DECODER_COUNTER_RESET              ((uint8) (0x01u << ENGINE_DECODER_COUNTER_RESET_SHIFT))
#define ENGINE_DECODER_INVALID_IN                 ((uint8) (0x01u << ENGINE_DECODER_INVALID_IN_SHIFT))

#define ENGINE_DECODER_INTERRUPTS_ENABLE_SHIFT    (0x04u)
#define ENGINE_DECODER_INTERRUPTS_ENABLE          ((uint8)(0x01u << ENGINE_DECODER_INTERRUPTS_ENABLE_SHIFT))
#define ENGINE_DECODER_INIT_INT_MASK              (0x0Fu)


/******************************************************************************************
* Following code are OBSOLETE and must not be used starting from Quadrature Decoder 2.20
******************************************************************************************/
#define ENGINE_DECODER_DISABLE                    (0x00u)


#endif /* CY_QUADRATURE_DECODER_ENGINE_DECODER_H */


/* [] END OF FILE */
