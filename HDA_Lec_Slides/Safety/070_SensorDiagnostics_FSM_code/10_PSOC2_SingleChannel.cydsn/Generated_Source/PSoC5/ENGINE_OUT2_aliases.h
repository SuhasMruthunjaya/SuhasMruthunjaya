/*******************************************************************************
* File Name: ENGINE_OUT2.h  
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

#if !defined(CY_PINS_ENGINE_OUT2_ALIASES_H) /* Pins ENGINE_OUT2_ALIASES_H */
#define CY_PINS_ENGINE_OUT2_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"


/***************************************
*              Constants        
***************************************/
#define ENGINE_OUT2_0			(ENGINE_OUT2__0__PC)
#define ENGINE_OUT2_0_INTR	((uint16)((uint16)0x0001u << ENGINE_OUT2__0__SHIFT))

#define ENGINE_OUT2_INTR_ALL	 ((uint16)(ENGINE_OUT2_0_INTR))

#endif /* End Pins ENGINE_OUT2_ALIASES_H */


/* [] END OF FILE */
