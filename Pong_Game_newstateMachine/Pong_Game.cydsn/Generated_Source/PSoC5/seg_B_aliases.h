/*******************************************************************************
* File Name: seg_B.h  
* Version 2.20
*
* Description:
*  This file contains the Alias definitions for Per-Pin APIs in cypins.h. 
*  Information on using these APIs can be found in the System Reference Guide.
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_seg_B_ALIASES_H) /* Pins seg_B_ALIASES_H */
#define CY_PINS_seg_B_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"


/***************************************
*              Constants        
***************************************/
#define seg_B_0			(seg_B__0__PC)
#define seg_B_0_INTR	((uint16)((uint16)0x0001u << seg_B__0__SHIFT))

#define seg_B_INTR_ALL	 ((uint16)(seg_B_0_INTR))

#endif /* End Pins seg_B_ALIASES_H */


/* [] END OF FILE */
