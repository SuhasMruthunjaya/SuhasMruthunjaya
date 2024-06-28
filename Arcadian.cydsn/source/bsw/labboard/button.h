/**
* \file button.h
* \author P. Fromm
* \date 28.8.17
*
* \brief File containing attributes and functions of lower level button class
*
* \copyright Copyright ©2016
* Department of electrical engineering and information technology, Hochschule Darmstadt - University of applied sciences (h_da). All Rights Reserved.
* Permission to use, copy, modify, and distribute this software and its documentation for educational, and research purposes in the context of non-commercial
* (unless permitted by h_da) and official h_da projects, is hereby granted for enrolled students of h_da, provided that the above copyright notice,
* this paragraph and the following paragraph appear in all copies, modifications, and distributions.
* Contact Prof.Dr.-Ing. Peter Fromm, peter.fromm@h-da.de, Birkenweg 8 64295 Darmstadt - GERMANY for commercial requests.
*
* \warning This software is a PROTOTYPE version and is not designed or intended for use in production, especially not for safety-critical applications!
* The user represents and warrants that it will NOT use or redistribute the Software for such purposes.
* This prototype is for research purposes only. This software is provided "AS IS," without a warranty of any kind.
*/
 
#ifndef BUTTON_H
#define BUTTON_H
    
#include "project.h"    
#include "global.h"

/*****************************************************************************/
/* Global pre-processor symbols/macros and type declarations                 */
/*****************************************************************************/

    
//####################### MACROS


//####################### Enumerations
/**
* \brief Enumeration identifying the display to be set
*
*/
/* USER CODE START SC_BUTTONEVENT_USERDEFINITIONS */
typedef enum{
   IDLE,
   ShortPress   
    
}ButtonPressStates_t;


/*****************************************************************************/
/* Extern global variables                                                   */
/*****************************************************************************/



/*****************************************************************************/
/* API functions                                                             */
/*****************************************************************************/
/**
 * Check Button Short press - polling method  
 * @param ButtonPressStates_t* StateVar - IN Statemachine variable
 * @param uint16* EV_value - OUT Event data
 * @param EVENT_t EV_shortpress - IN Event names
 * @return RC_SUCCESS if all ok
 */
RC_t BUTTON1_CheckShortPress(ButtonPressStates_t* StateVar, 
    uint16 *const EV_value, uint16 EV_shortpress);

/**
 * Statemachine code for Button Short press - polling method  
 * @param ButtonPressStates_t* StateVar - IN Statemachine variable
* @param  uint8_t BUTTONSTATUS - IN Status of the Button
 * @param uint16* EV_value - OUT Event data
 * @param EVENT_t EV_shortpress - IN Event names
 * @return RC_SUCCESS if all ok
 */
RC_t EV_ShortPressStateMachine(ButtonPressStates_t* StateVar, uint8_t BUTTONSTATUS, 
    uint16 *const EV_value, uint16 EV_shortpress);




#endif /* FILE_H */
