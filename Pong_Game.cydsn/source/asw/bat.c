/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/

/**
* \file BAT.c
* \author Suhas Bangalore Mruthunjaya
* \date 03/05/2023
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

#include "bat.h"
#include "screen.h"

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
 * Initialises the BAT position on the screen
 * @param *me : Pointer pointing to the bat object
 * @param *pos : Pointer pointing to the position object (X,Y)
 * @return RC_t : returns RC_Success if the initialisation is successfull
 */
RC_t BAT_init(BAT_t *me, uint16_t pos)
{
    me->current_bat_pos = pos;
    me->previous_bat_pos = pos;
    
    return RC_SUCCESS;
    
}

/**
 * Updates the position and draws the bat on the screen using the new updates X,Y Position
 * @param *me : Pointer pointing to the bat object
 * @return RC_t : returns RC_Success if the bat position is successfully updated on the screen
 */

RC_t BAT_update_pos(BAT_t *me, JOYSTICK_t joystick_pos)
{
    
    if((joystick_pos.joystick_direction == UP) && (me->current_bat_pos > BAT_MINPOS))
    {
       
       me->previous_bat_pos = me->current_bat_pos + BAT_HEIGHT;
       me->current_bat_pos --;
        

    }
    else if((joystick_pos.joystick_direction == DOWN) && (me->current_bat_pos < BAT_MAXPOS))
    {
        
        me->previous_bat_pos = me->current_bat_pos;
        me->current_bat_pos ++;
       
    }
 
    
    return RC_SUCCESS;
}

/** Get the bat current position
 *  @param BAT_t *me - pointer to the BAT object
 *  @param uint16_t pos - pos of type uint16_t
 *  @return returns RC_Success if the current position is updated to the pos
*/
uint16_t BAT_GetCurrentPosition(BAT_t *me)
{
   uint16_t pos;
   pos = me->current_bat_pos ;
   return pos;
    
}


/** Get the bat previous position
 *  @param BAT_t *me - pointer to the BAT object
 *  @param uint16_t pos - pos of type uint16_t
 *  @return returns RC_Success if the previous position is updated to the pos
*/
    
uint16_t BAT_GetPreviousPosition(BAT_t *me)
{
    uint16_t pos;
    pos = me->previous_bat_pos;
    return pos;
    
}



