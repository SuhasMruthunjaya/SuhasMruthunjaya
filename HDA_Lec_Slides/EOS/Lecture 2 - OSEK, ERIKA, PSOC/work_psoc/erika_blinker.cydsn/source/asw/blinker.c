/**
* \file <filename>
* \author <author-name>
* \date <date>
*
* \brief <Symbolic File name>
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
#include "blinker.h"

#include "seven.h"
#include "led.h"

/*****************************************************************************/
/* Local pre-processor symbols/macros ('#define')                            */
/*****************************************************************************/

/*****************************************************************************/
/* Global variable definitions (declared in header file with 'extern')       */
/*****************************************************************************/

BLINKER_t BLINKER_left = {BLINKER_LEFT, 0};
BLINKER_t BLINKER_right = {BLINKER_RIGHT, 0};

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
 * Blinker Initialisation
 * @param BLINKER_t *const me   - blinker object
 * @param BLINKER_Id_t led      - left/right blinker
 * @return RC_SUCCESS
 */
RC_t BLINKER_Init(BLINKER_t *const me, BLINKER_Id_t led)
{
    
    me->led = led;
    me->remainingBlinks = 0;
    me->emergency = FALSE;
    
    return RC_SUCCESS;
}
    

/**
 * Set Blinker depending on button press
 * @param BLINKER_t *const me   - blinker object
 * @param uint8_t noBlinks      - number of blinks to go
 * @return RC_SUCCESS
 */
RC_t BLINKER_Set(BLINKER_t *const me, uint8_t noBlinks)
{
    if (me->remainingBlinks < noBlinks)
    {
        me->remainingBlinks = noBlinks;
    }
    
    return RC_SUCCESS;
}


/**
 * Perform a blink and decrement blink counter
 * @param BLINKER_t *const me   - blinker object
 * @return RC_SUCCESS
 */
RC_t BLINKER_Blink(BLINKER_t *const me)
{
    LED_id_t led = LED_ALL;
    SEVEN_id_t seven = SEVEN_0;
    
    switch (me->led)
    {
        case BLINKER_LEFT : 
            led = LED_GREEN;
            seven = SEVEN_1;
            break;
        case BLINKER_RIGHT : 
            led = LED_RED;
            seven = SEVEN_0;
            break;
    }
    
    //normal operation
    if (FALSE == me->emergency)
    {
        if (me->remainingBlinks > 0)
        {
            LED_Toggle(led); 
            SEVEN_Set(seven, me->remainingBlinks);
            
            me->remainingBlinks--;    

        }
        else    
        {
            //Robustness code, to make sure everything is turned off at the end of the sequence
            SEVEN_Clear(seven);
            LED_Set(led, LED_OFF);
        }
    }
    
    
    //Emergency
    if (TRUE == me->emergency)
    {
        LED_Toggle(led); 
        SEVEN_Set(seven, 14); //E
    }
}
    
/**
 * Perform a blink and decrement blink counter
 * @param BLINKER_t *const me   - blinker object
 * @return RC_SUCCESS
 */
RC_t BLINKER_Emergency(BLINKER_t *const left, BLINKER_t *const right)
{
    left->emergency = TRUE;
    right->emergency = TRUE;
}

