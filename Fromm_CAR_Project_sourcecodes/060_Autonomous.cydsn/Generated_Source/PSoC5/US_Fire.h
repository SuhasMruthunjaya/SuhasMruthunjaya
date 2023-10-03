/*******************************************************************************
* File Name: US_Fire.h  
* Version 1.80
*
* Description:
*  This file containts Control Register function prototypes and register defines
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_CONTROL_REG_US_Fire_H) /* CY_CONTROL_REG_US_Fire_H */
#define CY_CONTROL_REG_US_Fire_H

#include "cyfitter.h"

#if ((CYDEV_CHIP_FAMILY_USED == CYDEV_CHIP_FAMILY_PSOC3) || \
     (CYDEV_CHIP_FAMILY_USED == CYDEV_CHIP_FAMILY_PSOC4) || \
     (CYDEV_CHIP_FAMILY_USED == CYDEV_CHIP_FAMILY_PSOC5))
    #include "cytypes.h"
#else
    #include "syslib/cy_syslib.h"
#endif

    
/***************************************
*     Data Struct Definitions
***************************************/

/* Sleep Mode API Support */
typedef struct
{
    uint8 controlState;

} US_Fire_BACKUP_STRUCT;


/***************************************
*         Function Prototypes 
***************************************/

void    US_Fire_Write(uint8 control) ;
uint8   US_Fire_Read(void) ;

void US_Fire_SaveConfig(void) ;
void US_Fire_RestoreConfig(void) ;
void US_Fire_Sleep(void) ; 
void US_Fire_Wakeup(void) ;


/***************************************
*            Registers        
***************************************/

/* Control Register */
#define US_Fire_Control        (* (reg8 *) US_Fire_Sync_ctrl_reg__CONTROL_REG )
#define US_Fire_Control_PTR    (  (reg8 *) US_Fire_Sync_ctrl_reg__CONTROL_REG )

#endif /* End CY_CONTROL_REG_US_Fire_H */


/* [] END OF FILE */
