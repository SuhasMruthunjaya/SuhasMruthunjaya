/*******************************************************************************
* File Name: Engine_PWM_Front.h
* Version 3.30
*
* Description:
*  Contains the prototypes and constants for the functions available to the
*  PWM user module.
*
* Note:
*
********************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/

#if !defined(CY_PWM_Engine_PWM_Front_H)
#define CY_PWM_Engine_PWM_Front_H

#include "cyfitter.h"
#include "cytypes.h"
#include "CyLib.h" /* For CyEnterCriticalSection() and CyExitCriticalSection() functions */

extern uint8 Engine_PWM_Front_initVar;


/***************************************
* Conditional Compilation Parameters
***************************************/
#define Engine_PWM_Front_Resolution                     (16u)
#define Engine_PWM_Front_UsingFixedFunction             (0u)
#define Engine_PWM_Front_DeadBandMode                   (0u)
#define Engine_PWM_Front_KillModeMinTime                (0u)
#define Engine_PWM_Front_KillMode                       (0u)
#define Engine_PWM_Front_PWMMode                        (1u)
#define Engine_PWM_Front_PWMModeIsCenterAligned         (0u)
#define Engine_PWM_Front_DeadBandUsed                   (0u)
#define Engine_PWM_Front_DeadBand2_4                    (0u)

#if !defined(Engine_PWM_Front_PWMUDB_genblk8_stsreg__REMOVED)
    #define Engine_PWM_Front_UseStatus                  (1u)
#else
    #define Engine_PWM_Front_UseStatus                  (0u)
#endif /* !defined(Engine_PWM_Front_PWMUDB_genblk8_stsreg__REMOVED) */

#if !defined(Engine_PWM_Front_PWMUDB_genblk1_ctrlreg__REMOVED)
    #define Engine_PWM_Front_UseControl                 (1u)
#else
    #define Engine_PWM_Front_UseControl                 (0u)
#endif /* !defined(Engine_PWM_Front_PWMUDB_genblk1_ctrlreg__REMOVED) */

#define Engine_PWM_Front_UseOneCompareMode              (0u)
#define Engine_PWM_Front_MinimumKillTime                (1u)
#define Engine_PWM_Front_EnableMode                     (0u)

#define Engine_PWM_Front_CompareMode1SW                 (0u)
#define Engine_PWM_Front_CompareMode2SW                 (0u)

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component PWM_v3_30 requires cy_boot v3.0 or later
#endif /* (CY_ PSOC5LP) */

/* Use Kill Mode Enumerated Types */
#define Engine_PWM_Front__B_PWM__DISABLED 0
#define Engine_PWM_Front__B_PWM__ASYNCHRONOUS 1
#define Engine_PWM_Front__B_PWM__SINGLECYCLE 2
#define Engine_PWM_Front__B_PWM__LATCHED 3
#define Engine_PWM_Front__B_PWM__MINTIME 4


/* Use Dead Band Mode Enumerated Types */
#define Engine_PWM_Front__B_PWM__DBMDISABLED 0
#define Engine_PWM_Front__B_PWM__DBM_2_4_CLOCKS 1
#define Engine_PWM_Front__B_PWM__DBM_256_CLOCKS 2


/* Used PWM Mode Enumerated Types */
#define Engine_PWM_Front__B_PWM__ONE_OUTPUT 0
#define Engine_PWM_Front__B_PWM__TWO_OUTPUTS 1
#define Engine_PWM_Front__B_PWM__DUAL_EDGE 2
#define Engine_PWM_Front__B_PWM__CENTER_ALIGN 3
#define Engine_PWM_Front__B_PWM__DITHER 5
#define Engine_PWM_Front__B_PWM__HARDWARESELECT 4


/* Used PWM Compare Mode Enumerated Types */
#define Engine_PWM_Front__B_PWM__LESS_THAN 1
#define Engine_PWM_Front__B_PWM__LESS_THAN_OR_EQUAL 2
#define Engine_PWM_Front__B_PWM__GREATER_THAN 3
#define Engine_PWM_Front__B_PWM__GREATER_THAN_OR_EQUAL_TO 4
#define Engine_PWM_Front__B_PWM__EQUAL 0
#define Engine_PWM_Front__B_PWM__FIRMWARE 5



/***************************************
* Data Struct Definition
***************************************/


/**************************************************************************
 * Sleep Wakeup Backup structure for PWM Component
 *************************************************************************/
typedef struct
{

    uint8 PWMEnableState;

    #if(!Engine_PWM_Front_UsingFixedFunction)
        uint16 PWMUdb;               /* PWM Current Counter value  */
        #if(!Engine_PWM_Front_PWMModeIsCenterAligned)
            uint16 PWMPeriod;
        #endif /* (!Engine_PWM_Front_PWMModeIsCenterAligned) */
        #if (Engine_PWM_Front_UseStatus)
            uint8 InterruptMaskValue;   /* PWM Current Interrupt Mask */
        #endif /* (Engine_PWM_Front_UseStatus) */

        /* Backup for Deadband parameters */
        #if(Engine_PWM_Front_DeadBandMode == Engine_PWM_Front__B_PWM__DBM_256_CLOCKS || \
            Engine_PWM_Front_DeadBandMode == Engine_PWM_Front__B_PWM__DBM_2_4_CLOCKS)
            uint8 PWMdeadBandValue; /* Dead Band Counter Current Value */
        #endif /* deadband count is either 2-4 clocks or 256 clocks */

        /* Backup Kill Mode Counter*/
        #if(Engine_PWM_Front_KillModeMinTime)
            uint8 PWMKillCounterPeriod; /* Kill Mode period value */
        #endif /* (Engine_PWM_Front_KillModeMinTime) */

        /* Backup control register */
        #if(Engine_PWM_Front_UseControl)
            uint8 PWMControlRegister; /* PWM Control Register value */
        #endif /* (Engine_PWM_Front_UseControl) */

    #endif /* (!Engine_PWM_Front_UsingFixedFunction) */

}Engine_PWM_Front_backupStruct;


/***************************************
*        Function Prototypes
 **************************************/

void    Engine_PWM_Front_Start(void) ;
void    Engine_PWM_Front_Stop(void) ;

#if (Engine_PWM_Front_UseStatus || Engine_PWM_Front_UsingFixedFunction)
    void  Engine_PWM_Front_SetInterruptMode(uint8 interruptMode) ;
    uint8 Engine_PWM_Front_ReadStatusRegister(void) ;
#endif /* (Engine_PWM_Front_UseStatus || Engine_PWM_Front_UsingFixedFunction) */

#define Engine_PWM_Front_GetInterruptSource() Engine_PWM_Front_ReadStatusRegister()

#if (Engine_PWM_Front_UseControl)
    uint8 Engine_PWM_Front_ReadControlRegister(void) ;
    void  Engine_PWM_Front_WriteControlRegister(uint8 control)
          ;
#endif /* (Engine_PWM_Front_UseControl) */

#if (Engine_PWM_Front_UseOneCompareMode)
   #if (Engine_PWM_Front_CompareMode1SW)
       void    Engine_PWM_Front_SetCompareMode(uint8 comparemode)
               ;
   #endif /* (Engine_PWM_Front_CompareMode1SW) */
#else
    #if (Engine_PWM_Front_CompareMode1SW)
        void    Engine_PWM_Front_SetCompareMode1(uint8 comparemode)
                ;
    #endif /* (Engine_PWM_Front_CompareMode1SW) */
    #if (Engine_PWM_Front_CompareMode2SW)
        void    Engine_PWM_Front_SetCompareMode2(uint8 comparemode)
                ;
    #endif /* (Engine_PWM_Front_CompareMode2SW) */
#endif /* (Engine_PWM_Front_UseOneCompareMode) */

#if (!Engine_PWM_Front_UsingFixedFunction)
    uint16   Engine_PWM_Front_ReadCounter(void) ;
    uint16 Engine_PWM_Front_ReadCapture(void) ;

    #if (Engine_PWM_Front_UseStatus)
            void Engine_PWM_Front_ClearFIFO(void) ;
    #endif /* (Engine_PWM_Front_UseStatus) */

    void    Engine_PWM_Front_WriteCounter(uint16 counter)
            ;
#endif /* (!Engine_PWM_Front_UsingFixedFunction) */

void    Engine_PWM_Front_WritePeriod(uint16 period)
        ;
uint16 Engine_PWM_Front_ReadPeriod(void) ;

#if (Engine_PWM_Front_UseOneCompareMode)
    void    Engine_PWM_Front_WriteCompare(uint16 compare)
            ;
    uint16 Engine_PWM_Front_ReadCompare(void) ;
#else
    void    Engine_PWM_Front_WriteCompare1(uint16 compare)
            ;
    uint16 Engine_PWM_Front_ReadCompare1(void) ;
    void    Engine_PWM_Front_WriteCompare2(uint16 compare)
            ;
    uint16 Engine_PWM_Front_ReadCompare2(void) ;
#endif /* (Engine_PWM_Front_UseOneCompareMode) */


#if (Engine_PWM_Front_DeadBandUsed)
    void    Engine_PWM_Front_WriteDeadTime(uint8 deadtime) ;
    uint8   Engine_PWM_Front_ReadDeadTime(void) ;
#endif /* (Engine_PWM_Front_DeadBandUsed) */

#if ( Engine_PWM_Front_KillModeMinTime)
    void Engine_PWM_Front_WriteKillTime(uint8 killtime) ;
    uint8 Engine_PWM_Front_ReadKillTime(void) ;
#endif /* ( Engine_PWM_Front_KillModeMinTime) */

void Engine_PWM_Front_Init(void) ;
void Engine_PWM_Front_Enable(void) ;
void Engine_PWM_Front_Sleep(void) ;
void Engine_PWM_Front_Wakeup(void) ;
void Engine_PWM_Front_SaveConfig(void) ;
void Engine_PWM_Front_RestoreConfig(void) ;


/***************************************
*         Initialization Values
**************************************/
#define Engine_PWM_Front_INIT_PERIOD_VALUE          (10000u)
#define Engine_PWM_Front_INIT_COMPARE_VALUE1        (0u)
#define Engine_PWM_Front_INIT_COMPARE_VALUE2        (0u)
#define Engine_PWM_Front_INIT_INTERRUPTS_MODE       (uint8)(((uint8)(0u <<   \
                                                    Engine_PWM_Front_STATUS_TC_INT_EN_MASK_SHIFT)) | \
                                                    (uint8)((uint8)(0u <<  \
                                                    Engine_PWM_Front_STATUS_CMP2_INT_EN_MASK_SHIFT)) | \
                                                    (uint8)((uint8)(0u <<  \
                                                    Engine_PWM_Front_STATUS_CMP1_INT_EN_MASK_SHIFT )) | \
                                                    (uint8)((uint8)(0u <<  \
                                                    Engine_PWM_Front_STATUS_KILL_INT_EN_MASK_SHIFT )))
#define Engine_PWM_Front_DEFAULT_COMPARE2_MODE      (uint8)((uint8)1u <<  Engine_PWM_Front_CTRL_CMPMODE2_SHIFT)
#define Engine_PWM_Front_DEFAULT_COMPARE1_MODE      (uint8)((uint8)1u <<  Engine_PWM_Front_CTRL_CMPMODE1_SHIFT)
#define Engine_PWM_Front_INIT_DEAD_TIME             (1u)


/********************************
*         Registers
******************************** */

#if (Engine_PWM_Front_UsingFixedFunction)
   #define Engine_PWM_Front_PERIOD_LSB              (*(reg16 *) Engine_PWM_Front_PWMHW__PER0)
   #define Engine_PWM_Front_PERIOD_LSB_PTR          ( (reg16 *) Engine_PWM_Front_PWMHW__PER0)
   #define Engine_PWM_Front_COMPARE1_LSB            (*(reg16 *) Engine_PWM_Front_PWMHW__CNT_CMP0)
   #define Engine_PWM_Front_COMPARE1_LSB_PTR        ( (reg16 *) Engine_PWM_Front_PWMHW__CNT_CMP0)
   #define Engine_PWM_Front_COMPARE2_LSB            (0x00u)
   #define Engine_PWM_Front_COMPARE2_LSB_PTR        (0x00u)
   #define Engine_PWM_Front_COUNTER_LSB             (*(reg16 *) Engine_PWM_Front_PWMHW__CNT_CMP0)
   #define Engine_PWM_Front_COUNTER_LSB_PTR         ( (reg16 *) Engine_PWM_Front_PWMHW__CNT_CMP0)
   #define Engine_PWM_Front_CAPTURE_LSB             (*(reg16 *) Engine_PWM_Front_PWMHW__CAP0)
   #define Engine_PWM_Front_CAPTURE_LSB_PTR         ( (reg16 *) Engine_PWM_Front_PWMHW__CAP0)
   #define Engine_PWM_Front_RT1                     (*(reg8 *)  Engine_PWM_Front_PWMHW__RT1)
   #define Engine_PWM_Front_RT1_PTR                 ( (reg8 *)  Engine_PWM_Front_PWMHW__RT1)

#else
   #if (Engine_PWM_Front_Resolution == 8u) /* 8bit - PWM */

       #if(Engine_PWM_Front_PWMModeIsCenterAligned)
           #define Engine_PWM_Front_PERIOD_LSB      (*(reg8 *)  Engine_PWM_Front_PWMUDB_sP16_pwmdp_u0__D1_REG)
           #define Engine_PWM_Front_PERIOD_LSB_PTR  ((reg8 *)   Engine_PWM_Front_PWMUDB_sP16_pwmdp_u0__D1_REG)
       #else
           #define Engine_PWM_Front_PERIOD_LSB      (*(reg8 *)  Engine_PWM_Front_PWMUDB_sP16_pwmdp_u0__F0_REG)
           #define Engine_PWM_Front_PERIOD_LSB_PTR  ((reg8 *)   Engine_PWM_Front_PWMUDB_sP16_pwmdp_u0__F0_REG)
       #endif /* (Engine_PWM_Front_PWMModeIsCenterAligned) */

       #define Engine_PWM_Front_COMPARE1_LSB        (*(reg8 *)  Engine_PWM_Front_PWMUDB_sP16_pwmdp_u0__D0_REG)
       #define Engine_PWM_Front_COMPARE1_LSB_PTR    ((reg8 *)   Engine_PWM_Front_PWMUDB_sP16_pwmdp_u0__D0_REG)
       #define Engine_PWM_Front_COMPARE2_LSB        (*(reg8 *)  Engine_PWM_Front_PWMUDB_sP16_pwmdp_u0__D1_REG)
       #define Engine_PWM_Front_COMPARE2_LSB_PTR    ((reg8 *)   Engine_PWM_Front_PWMUDB_sP16_pwmdp_u0__D1_REG)
       #define Engine_PWM_Front_COUNTERCAP_LSB      (*(reg8 *)  Engine_PWM_Front_PWMUDB_sP16_pwmdp_u0__A1_REG)
       #define Engine_PWM_Front_COUNTERCAP_LSB_PTR  ((reg8 *)   Engine_PWM_Front_PWMUDB_sP16_pwmdp_u0__A1_REG)
       #define Engine_PWM_Front_COUNTER_LSB         (*(reg8 *)  Engine_PWM_Front_PWMUDB_sP16_pwmdp_u0__A0_REG)
       #define Engine_PWM_Front_COUNTER_LSB_PTR     ((reg8 *)   Engine_PWM_Front_PWMUDB_sP16_pwmdp_u0__A0_REG)
       #define Engine_PWM_Front_CAPTURE_LSB         (*(reg8 *)  Engine_PWM_Front_PWMUDB_sP16_pwmdp_u0__F1_REG)
       #define Engine_PWM_Front_CAPTURE_LSB_PTR     ((reg8 *)   Engine_PWM_Front_PWMUDB_sP16_pwmdp_u0__F1_REG)

   #else
        #if(CY_PSOC3) /* 8-bit address space */
            #if(Engine_PWM_Front_PWMModeIsCenterAligned)
               #define Engine_PWM_Front_PERIOD_LSB      (*(reg16 *) Engine_PWM_Front_PWMUDB_sP16_pwmdp_u0__D1_REG)
               #define Engine_PWM_Front_PERIOD_LSB_PTR  ((reg16 *)  Engine_PWM_Front_PWMUDB_sP16_pwmdp_u0__D1_REG)
            #else
               #define Engine_PWM_Front_PERIOD_LSB      (*(reg16 *) Engine_PWM_Front_PWMUDB_sP16_pwmdp_u0__F0_REG)
               #define Engine_PWM_Front_PERIOD_LSB_PTR  ((reg16 *)  Engine_PWM_Front_PWMUDB_sP16_pwmdp_u0__F0_REG)
            #endif /* (Engine_PWM_Front_PWMModeIsCenterAligned) */

            #define Engine_PWM_Front_COMPARE1_LSB       (*(reg16 *) Engine_PWM_Front_PWMUDB_sP16_pwmdp_u0__D0_REG)
            #define Engine_PWM_Front_COMPARE1_LSB_PTR   ((reg16 *)  Engine_PWM_Front_PWMUDB_sP16_pwmdp_u0__D0_REG)
            #define Engine_PWM_Front_COMPARE2_LSB       (*(reg16 *) Engine_PWM_Front_PWMUDB_sP16_pwmdp_u0__D1_REG)
            #define Engine_PWM_Front_COMPARE2_LSB_PTR   ((reg16 *)  Engine_PWM_Front_PWMUDB_sP16_pwmdp_u0__D1_REG)
            #define Engine_PWM_Front_COUNTERCAP_LSB     (*(reg16 *) Engine_PWM_Front_PWMUDB_sP16_pwmdp_u0__A1_REG)
            #define Engine_PWM_Front_COUNTERCAP_LSB_PTR ((reg16 *)  Engine_PWM_Front_PWMUDB_sP16_pwmdp_u0__A1_REG)
            #define Engine_PWM_Front_COUNTER_LSB        (*(reg16 *) Engine_PWM_Front_PWMUDB_sP16_pwmdp_u0__A0_REG)
            #define Engine_PWM_Front_COUNTER_LSB_PTR    ((reg16 *)  Engine_PWM_Front_PWMUDB_sP16_pwmdp_u0__A0_REG)
            #define Engine_PWM_Front_CAPTURE_LSB        (*(reg16 *) Engine_PWM_Front_PWMUDB_sP16_pwmdp_u0__F1_REG)
            #define Engine_PWM_Front_CAPTURE_LSB_PTR    ((reg16 *)  Engine_PWM_Front_PWMUDB_sP16_pwmdp_u0__F1_REG)
        #else
            #if(Engine_PWM_Front_PWMModeIsCenterAligned)
               #define Engine_PWM_Front_PERIOD_LSB      (*(reg16 *) Engine_PWM_Front_PWMUDB_sP16_pwmdp_u0__16BIT_D1_REG)
               #define Engine_PWM_Front_PERIOD_LSB_PTR  ((reg16 *)  Engine_PWM_Front_PWMUDB_sP16_pwmdp_u0__16BIT_D1_REG)
            #else
               #define Engine_PWM_Front_PERIOD_LSB      (*(reg16 *) Engine_PWM_Front_PWMUDB_sP16_pwmdp_u0__16BIT_F0_REG)
               #define Engine_PWM_Front_PERIOD_LSB_PTR  ((reg16 *)  Engine_PWM_Front_PWMUDB_sP16_pwmdp_u0__16BIT_F0_REG)
            #endif /* (Engine_PWM_Front_PWMModeIsCenterAligned) */

            #define Engine_PWM_Front_COMPARE1_LSB       (*(reg16 *) Engine_PWM_Front_PWMUDB_sP16_pwmdp_u0__16BIT_D0_REG)
            #define Engine_PWM_Front_COMPARE1_LSB_PTR   ((reg16 *)  Engine_PWM_Front_PWMUDB_sP16_pwmdp_u0__16BIT_D0_REG)
            #define Engine_PWM_Front_COMPARE2_LSB       (*(reg16 *) Engine_PWM_Front_PWMUDB_sP16_pwmdp_u0__16BIT_D1_REG)
            #define Engine_PWM_Front_COMPARE2_LSB_PTR   ((reg16 *)  Engine_PWM_Front_PWMUDB_sP16_pwmdp_u0__16BIT_D1_REG)
            #define Engine_PWM_Front_COUNTERCAP_LSB     (*(reg16 *) Engine_PWM_Front_PWMUDB_sP16_pwmdp_u0__16BIT_A1_REG)
            #define Engine_PWM_Front_COUNTERCAP_LSB_PTR ((reg16 *)  Engine_PWM_Front_PWMUDB_sP16_pwmdp_u0__16BIT_A1_REG)
            #define Engine_PWM_Front_COUNTER_LSB        (*(reg16 *) Engine_PWM_Front_PWMUDB_sP16_pwmdp_u0__16BIT_A0_REG)
            #define Engine_PWM_Front_COUNTER_LSB_PTR    ((reg16 *)  Engine_PWM_Front_PWMUDB_sP16_pwmdp_u0__16BIT_A0_REG)
            #define Engine_PWM_Front_CAPTURE_LSB        (*(reg16 *) Engine_PWM_Front_PWMUDB_sP16_pwmdp_u0__16BIT_F1_REG)
            #define Engine_PWM_Front_CAPTURE_LSB_PTR    ((reg16 *)  Engine_PWM_Front_PWMUDB_sP16_pwmdp_u0__16BIT_F1_REG)
        #endif /* (CY_PSOC3) */

       #define Engine_PWM_Front_AUX_CONTROLDP1          (*(reg8 *)  Engine_PWM_Front_PWMUDB_sP16_pwmdp_u1__DP_AUX_CTL_REG)
       #define Engine_PWM_Front_AUX_CONTROLDP1_PTR      ((reg8 *)   Engine_PWM_Front_PWMUDB_sP16_pwmdp_u1__DP_AUX_CTL_REG)

   #endif /* (Engine_PWM_Front_Resolution == 8) */

   #define Engine_PWM_Front_COUNTERCAP_LSB_PTR_8BIT ( (reg8 *)  Engine_PWM_Front_PWMUDB_sP16_pwmdp_u0__A1_REG)
   #define Engine_PWM_Front_AUX_CONTROLDP0          (*(reg8 *)  Engine_PWM_Front_PWMUDB_sP16_pwmdp_u0__DP_AUX_CTL_REG)
   #define Engine_PWM_Front_AUX_CONTROLDP0_PTR      ((reg8 *)   Engine_PWM_Front_PWMUDB_sP16_pwmdp_u0__DP_AUX_CTL_REG)

#endif /* (Engine_PWM_Front_UsingFixedFunction) */

#if(Engine_PWM_Front_KillModeMinTime )
    #define Engine_PWM_Front_KILLMODEMINTIME        (*(reg8 *)  Engine_PWM_Front_PWMUDB_sKM_killmodecounterdp_u0__D0_REG)
    #define Engine_PWM_Front_KILLMODEMINTIME_PTR    ((reg8 *)   Engine_PWM_Front_PWMUDB_sKM_killmodecounterdp_u0__D0_REG)
    /* Fixed Function Block has no Kill Mode parameters because it is Asynchronous only */
#endif /* (Engine_PWM_Front_KillModeMinTime ) */

#if(Engine_PWM_Front_DeadBandMode == Engine_PWM_Front__B_PWM__DBM_256_CLOCKS)
    #define Engine_PWM_Front_DEADBAND_COUNT         (*(reg8 *)  Engine_PWM_Front_PWMUDB_sDB255_deadbandcounterdp_u0__D0_REG)
    #define Engine_PWM_Front_DEADBAND_COUNT_PTR     ((reg8 *)   Engine_PWM_Front_PWMUDB_sDB255_deadbandcounterdp_u0__D0_REG)
    #define Engine_PWM_Front_DEADBAND_LSB_PTR       ((reg8 *)   Engine_PWM_Front_PWMUDB_sDB255_deadbandcounterdp_u0__A0_REG)
    #define Engine_PWM_Front_DEADBAND_LSB           (*(reg8 *)  Engine_PWM_Front_PWMUDB_sDB255_deadbandcounterdp_u0__A0_REG)
#elif(Engine_PWM_Front_DeadBandMode == Engine_PWM_Front__B_PWM__DBM_2_4_CLOCKS)
    
    /* In Fixed Function Block these bits are in the control blocks control register */
    #if (Engine_PWM_Front_UsingFixedFunction)
        #define Engine_PWM_Front_DEADBAND_COUNT         (*(reg8 *)  Engine_PWM_Front_PWMHW__CFG0)
        #define Engine_PWM_Front_DEADBAND_COUNT_PTR     ((reg8 *)   Engine_PWM_Front_PWMHW__CFG0)
        #define Engine_PWM_Front_DEADBAND_COUNT_MASK    (uint8)((uint8)0x03u << Engine_PWM_Front_DEADBAND_COUNT_SHIFT)

        /* As defined by the Register Map as DEADBAND_PERIOD[1:0] in CFG0 */
        #define Engine_PWM_Front_DEADBAND_COUNT_SHIFT   (0x06u)
    #else
        /* Lower two bits of the added control register define the count 1-3 */
        #define Engine_PWM_Front_DEADBAND_COUNT         (*(reg8 *)  Engine_PWM_Front_PWMUDB_genblk7_dbctrlreg__CONTROL_REG)
        #define Engine_PWM_Front_DEADBAND_COUNT_PTR     ((reg8 *)   Engine_PWM_Front_PWMUDB_genblk7_dbctrlreg__CONTROL_REG)
        #define Engine_PWM_Front_DEADBAND_COUNT_MASK    (uint8)((uint8)0x03u << Engine_PWM_Front_DEADBAND_COUNT_SHIFT)

        /* As defined by the verilog implementation of the Control Register */
        #define Engine_PWM_Front_DEADBAND_COUNT_SHIFT   (0x00u)
    #endif /* (Engine_PWM_Front_UsingFixedFunction) */
#endif /* (Engine_PWM_Front_DeadBandMode == Engine_PWM_Front__B_PWM__DBM_256_CLOCKS) */



#if (Engine_PWM_Front_UsingFixedFunction)
    #define Engine_PWM_Front_STATUS                 (*(reg8 *) Engine_PWM_Front_PWMHW__SR0)
    #define Engine_PWM_Front_STATUS_PTR             ((reg8 *) Engine_PWM_Front_PWMHW__SR0)
    #define Engine_PWM_Front_STATUS_MASK            (*(reg8 *) Engine_PWM_Front_PWMHW__SR0)
    #define Engine_PWM_Front_STATUS_MASK_PTR        ((reg8 *) Engine_PWM_Front_PWMHW__SR0)
    #define Engine_PWM_Front_CONTROL                (*(reg8 *) Engine_PWM_Front_PWMHW__CFG0)
    #define Engine_PWM_Front_CONTROL_PTR            ((reg8 *) Engine_PWM_Front_PWMHW__CFG0)
    #define Engine_PWM_Front_CONTROL2               (*(reg8 *) Engine_PWM_Front_PWMHW__CFG1)
    #define Engine_PWM_Front_CONTROL3               (*(reg8 *) Engine_PWM_Front_PWMHW__CFG2)
    #define Engine_PWM_Front_GLOBAL_ENABLE          (*(reg8 *) Engine_PWM_Front_PWMHW__PM_ACT_CFG)
    #define Engine_PWM_Front_GLOBAL_ENABLE_PTR      ( (reg8 *) Engine_PWM_Front_PWMHW__PM_ACT_CFG)
    #define Engine_PWM_Front_GLOBAL_STBY_ENABLE     (*(reg8 *) Engine_PWM_Front_PWMHW__PM_STBY_CFG)
    #define Engine_PWM_Front_GLOBAL_STBY_ENABLE_PTR ( (reg8 *) Engine_PWM_Front_PWMHW__PM_STBY_CFG)


    /***********************************
    *          Constants
    ***********************************/

    /* Fixed Function Block Chosen */
    #define Engine_PWM_Front_BLOCK_EN_MASK          (Engine_PWM_Front_PWMHW__PM_ACT_MSK)
    #define Engine_PWM_Front_BLOCK_STBY_EN_MASK     (Engine_PWM_Front_PWMHW__PM_STBY_MSK)
    
    /* Control Register definitions */
    #define Engine_PWM_Front_CTRL_ENABLE_SHIFT      (0x00u)

    /* As defined by Register map as MODE_CFG bits in CFG2*/
    #define Engine_PWM_Front_CTRL_CMPMODE1_SHIFT    (0x04u)

    /* As defined by Register map */
    #define Engine_PWM_Front_CTRL_DEAD_TIME_SHIFT   (0x06u)  

    /* Fixed Function Block Only CFG register bit definitions */
    /*  Set to compare mode */
    #define Engine_PWM_Front_CFG0_MODE              (0x02u)   

    /* Enable the block to run */
    #define Engine_PWM_Front_CFG0_ENABLE            (0x01u)   
    
    /* As defined by Register map as DB bit in CFG0 */
    #define Engine_PWM_Front_CFG0_DB                (0x20u)   

    /* Control Register Bit Masks */
    #define Engine_PWM_Front_CTRL_ENABLE            (uint8)((uint8)0x01u << Engine_PWM_Front_CTRL_ENABLE_SHIFT)
    #define Engine_PWM_Front_CTRL_RESET             (uint8)((uint8)0x01u << Engine_PWM_Front_CTRL_RESET_SHIFT)
    #define Engine_PWM_Front_CTRL_CMPMODE2_MASK     (uint8)((uint8)0x07u << Engine_PWM_Front_CTRL_CMPMODE2_SHIFT)
    #define Engine_PWM_Front_CTRL_CMPMODE1_MASK     (uint8)((uint8)0x07u << Engine_PWM_Front_CTRL_CMPMODE1_SHIFT)

    /* Control2 Register Bit Masks */
    /* As defined in Register Map, Part of the TMRX_CFG1 register */
    #define Engine_PWM_Front_CTRL2_IRQ_SEL_SHIFT    (0x00u)
    #define Engine_PWM_Front_CTRL2_IRQ_SEL          (uint8)((uint8)0x01u << Engine_PWM_Front_CTRL2_IRQ_SEL_SHIFT)

    /* Status Register Bit Locations */
    /* As defined by Register map as TC in SR0 */
    #define Engine_PWM_Front_STATUS_TC_SHIFT        (0x07u)   
    
    /* As defined by the Register map as CAP_CMP in SR0 */
    #define Engine_PWM_Front_STATUS_CMP1_SHIFT      (0x06u)   

    /* Status Register Interrupt Enable Bit Locations */
    #define Engine_PWM_Front_STATUS_KILL_INT_EN_MASK_SHIFT          (0x00u)
    #define Engine_PWM_Front_STATUS_TC_INT_EN_MASK_SHIFT            (Engine_PWM_Front_STATUS_TC_SHIFT - 4u)
    #define Engine_PWM_Front_STATUS_CMP2_INT_EN_MASK_SHIFT          (0x00u)
    #define Engine_PWM_Front_STATUS_CMP1_INT_EN_MASK_SHIFT          (Engine_PWM_Front_STATUS_CMP1_SHIFT - 4u)

    /* Status Register Bit Masks */
    #define Engine_PWM_Front_STATUS_TC              (uint8)((uint8)0x01u << Engine_PWM_Front_STATUS_TC_SHIFT)
    #define Engine_PWM_Front_STATUS_CMP1            (uint8)((uint8)0x01u << Engine_PWM_Front_STATUS_CMP1_SHIFT)

    /* Status Register Interrupt Bit Masks */
    #define Engine_PWM_Front_STATUS_TC_INT_EN_MASK              (uint8)((uint8)Engine_PWM_Front_STATUS_TC >> 4u)
    #define Engine_PWM_Front_STATUS_CMP1_INT_EN_MASK            (uint8)((uint8)Engine_PWM_Front_STATUS_CMP1 >> 4u)

    /*RT1 Synch Constants */
    #define Engine_PWM_Front_RT1_SHIFT             (0x04u)

    /* Sync TC and CMP bit masks */
    #define Engine_PWM_Front_RT1_MASK              (uint8)((uint8)0x03u << Engine_PWM_Front_RT1_SHIFT)
    #define Engine_PWM_Front_SYNC                  (uint8)((uint8)0x03u << Engine_PWM_Front_RT1_SHIFT)
    #define Engine_PWM_Front_SYNCDSI_SHIFT         (0x00u)

    /* Sync all DSI inputs */
    #define Engine_PWM_Front_SYNCDSI_MASK          (uint8)((uint8)0x0Fu << Engine_PWM_Front_SYNCDSI_SHIFT)

    /* Sync all DSI inputs */
    #define Engine_PWM_Front_SYNCDSI_EN            (uint8)((uint8)0x0Fu << Engine_PWM_Front_SYNCDSI_SHIFT)


#else
    #define Engine_PWM_Front_STATUS                (*(reg8 *)   Engine_PWM_Front_PWMUDB_genblk8_stsreg__STATUS_REG )
    #define Engine_PWM_Front_STATUS_PTR            ((reg8 *)    Engine_PWM_Front_PWMUDB_genblk8_stsreg__STATUS_REG )
    #define Engine_PWM_Front_STATUS_MASK           (*(reg8 *)   Engine_PWM_Front_PWMUDB_genblk8_stsreg__MASK_REG)
    #define Engine_PWM_Front_STATUS_MASK_PTR       ((reg8 *)    Engine_PWM_Front_PWMUDB_genblk8_stsreg__MASK_REG)
    #define Engine_PWM_Front_STATUS_AUX_CTRL       (*(reg8 *)   Engine_PWM_Front_PWMUDB_genblk8_stsreg__STATUS_AUX_CTL_REG)
    #define Engine_PWM_Front_CONTROL               (*(reg8 *)   Engine_PWM_Front_PWMUDB_genblk1_ctrlreg__CONTROL_REG)
    #define Engine_PWM_Front_CONTROL_PTR           ((reg8 *)    Engine_PWM_Front_PWMUDB_genblk1_ctrlreg__CONTROL_REG)


    /***********************************
    *          Constants
    ***********************************/

    /* Control Register bit definitions */
    #define Engine_PWM_Front_CTRL_ENABLE_SHIFT      (0x07u)
    #define Engine_PWM_Front_CTRL_RESET_SHIFT       (0x06u)
    #define Engine_PWM_Front_CTRL_CMPMODE2_SHIFT    (0x03u)
    #define Engine_PWM_Front_CTRL_CMPMODE1_SHIFT    (0x00u)
    #define Engine_PWM_Front_CTRL_DEAD_TIME_SHIFT   (0x00u)   /* No Shift Needed for UDB block */
    
    /* Control Register Bit Masks */
    #define Engine_PWM_Front_CTRL_ENABLE            (uint8)((uint8)0x01u << Engine_PWM_Front_CTRL_ENABLE_SHIFT)
    #define Engine_PWM_Front_CTRL_RESET             (uint8)((uint8)0x01u << Engine_PWM_Front_CTRL_RESET_SHIFT)
    #define Engine_PWM_Front_CTRL_CMPMODE2_MASK     (uint8)((uint8)0x07u << Engine_PWM_Front_CTRL_CMPMODE2_SHIFT)
    #define Engine_PWM_Front_CTRL_CMPMODE1_MASK     (uint8)((uint8)0x07u << Engine_PWM_Front_CTRL_CMPMODE1_SHIFT)

    /* Status Register Bit Locations */
    #define Engine_PWM_Front_STATUS_KILL_SHIFT          (0x05u)
    #define Engine_PWM_Front_STATUS_FIFONEMPTY_SHIFT    (0x04u)
    #define Engine_PWM_Front_STATUS_FIFOFULL_SHIFT      (0x03u)
    #define Engine_PWM_Front_STATUS_TC_SHIFT            (0x02u)
    #define Engine_PWM_Front_STATUS_CMP2_SHIFT          (0x01u)
    #define Engine_PWM_Front_STATUS_CMP1_SHIFT          (0x00u)

    /* Status Register Interrupt Enable Bit Locations - UDB Status Interrupt Mask match Status Bit Locations*/
    #define Engine_PWM_Front_STATUS_KILL_INT_EN_MASK_SHIFT          (Engine_PWM_Front_STATUS_KILL_SHIFT)
    #define Engine_PWM_Front_STATUS_FIFONEMPTY_INT_EN_MASK_SHIFT    (Engine_PWM_Front_STATUS_FIFONEMPTY_SHIFT)
    #define Engine_PWM_Front_STATUS_FIFOFULL_INT_EN_MASK_SHIFT      (Engine_PWM_Front_STATUS_FIFOFULL_SHIFT)
    #define Engine_PWM_Front_STATUS_TC_INT_EN_MASK_SHIFT            (Engine_PWM_Front_STATUS_TC_SHIFT)
    #define Engine_PWM_Front_STATUS_CMP2_INT_EN_MASK_SHIFT          (Engine_PWM_Front_STATUS_CMP2_SHIFT)
    #define Engine_PWM_Front_STATUS_CMP1_INT_EN_MASK_SHIFT          (Engine_PWM_Front_STATUS_CMP1_SHIFT)

    /* Status Register Bit Masks */
    #define Engine_PWM_Front_STATUS_KILL            (uint8)((uint8)0x00u << Engine_PWM_Front_STATUS_KILL_SHIFT )
    #define Engine_PWM_Front_STATUS_FIFOFULL        (uint8)((uint8)0x01u << Engine_PWM_Front_STATUS_FIFOFULL_SHIFT)
    #define Engine_PWM_Front_STATUS_FIFONEMPTY      (uint8)((uint8)0x01u << Engine_PWM_Front_STATUS_FIFONEMPTY_SHIFT)
    #define Engine_PWM_Front_STATUS_TC              (uint8)((uint8)0x01u << Engine_PWM_Front_STATUS_TC_SHIFT)
    #define Engine_PWM_Front_STATUS_CMP2            (uint8)((uint8)0x01u << Engine_PWM_Front_STATUS_CMP2_SHIFT)
    #define Engine_PWM_Front_STATUS_CMP1            (uint8)((uint8)0x01u << Engine_PWM_Front_STATUS_CMP1_SHIFT)

    /* Status Register Interrupt Bit Masks  - UDB Status Interrupt Mask match Status Bit Locations */
    #define Engine_PWM_Front_STATUS_KILL_INT_EN_MASK            (Engine_PWM_Front_STATUS_KILL)
    #define Engine_PWM_Front_STATUS_FIFOFULL_INT_EN_MASK        (Engine_PWM_Front_STATUS_FIFOFULL)
    #define Engine_PWM_Front_STATUS_FIFONEMPTY_INT_EN_MASK      (Engine_PWM_Front_STATUS_FIFONEMPTY)
    #define Engine_PWM_Front_STATUS_TC_INT_EN_MASK              (Engine_PWM_Front_STATUS_TC)
    #define Engine_PWM_Front_STATUS_CMP2_INT_EN_MASK            (Engine_PWM_Front_STATUS_CMP2)
    #define Engine_PWM_Front_STATUS_CMP1_INT_EN_MASK            (Engine_PWM_Front_STATUS_CMP1)

    /* Datapath Auxillary Control Register bit definitions */
    #define Engine_PWM_Front_AUX_CTRL_FIFO0_CLR         (0x01u)
    #define Engine_PWM_Front_AUX_CTRL_FIFO1_CLR         (0x02u)
    #define Engine_PWM_Front_AUX_CTRL_FIFO0_LVL         (0x04u)
    #define Engine_PWM_Front_AUX_CTRL_FIFO1_LVL         (0x08u)
    #define Engine_PWM_Front_STATUS_ACTL_INT_EN_MASK    (0x10u) /* As defined for the ACTL Register */
#endif /* Engine_PWM_Front_UsingFixedFunction */

#endif  /* CY_PWM_Engine_PWM_Front_H */


/* [] END OF FILE */
