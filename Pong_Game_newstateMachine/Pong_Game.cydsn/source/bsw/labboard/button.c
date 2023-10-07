/**
* \file button.c
* \author P. Fromm
* \date 28.8.17
*
* \brief Driver for 7 segment displays
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

/*****************************************************************************/
/* Include files                                                             */
/*****************************************************************************/

#include "button.h"




/*****************************************************************************/
/* Local pre-processor symbols/macros ('#define')                            */
/*****************************************************************************/



/*****************************************************************************/
/* Global variable definitions (declared in header file with 'extern')       */
/*****************************************************************************/

/*****************************************************************************/
/* Local type definitions ('typedef')                                        */
/*****************************************************************************/

/*****************************************************************************/
/* Local variable definitions ('static')                                     */
/*****************************************************************************/


/*****************************************************************************/
/* Local function prototypes ('static')                                      */
/*****************************************************************************/


/*****************************************************************************/
/* Function implementation - global ('extern') and local ('static')          */
/*****************************************************************************/
/**
 * Check Button Short press - polling method  
 * @param ButtonPressStates_t* StateVar - IN Statemachine variable
 * @param uint16* EV_value - OUT Event data
 * @param EVENT_t EV_shortpress - IN Event names
 * @return RC_SUCCESS if all ok
 */
RC_t BUTTON1_CheckShortPress(ButtonPressStates_t* StateVar, 
    uint16 *const EV_value, uint16 EV_shortpress)
{
    uint8_t BUTTONSTATUS = BUTTON_1_Read();
    EV_ShortPressStateMachine(StateVar, BUTTONSTATUS , EV_value , EV_shortpress);
      
    return RC_SUCCESS; 
}
/**
 * Statemachine code for Button Short press - polling method  
 * @param ButtonPressStates_t* StateVar - IN Statemachine variable
* @param  uint8_t BUTTONSTATUS - IN Status of the Button
 * @param uint16* EV_value - OUT Event data
 * @param EVENT_t EV_shortpress - IN Event names
 * @return RC_SUCCESS if all ok
 */
RC_t EV_ShortPressStateMachine(ButtonPressStates_t* StateVar, uint8_t BUTTONSTATUS, 
    uint16 *const EV_value, uint16 EV_shortpress)
{
    
    switch(*StateVar)
    {
        case IDLE:
        {
            if(BUTTONSTATUS==1)
            {
                *EV_value= EV_shortpress;  
                *StateVar= ShortPress;
            } 
        }
        break;

        case ShortPress:
        {
            if(BUTTONSTATUS==1)
            {          
                *StateVar= ShortPress;
            }
            
            else if(BUTTONSTATUS==0)
            {
                 *EV_value=  0;
                *StateVar= IDLE;
            }
        }
        break;
    }
    return RC_SUCCESS;  
}


