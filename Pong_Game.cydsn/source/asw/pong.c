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
#include "project.h"
#include "global.h"
#include "stdlib.h"
#include "tft.h"
#include "joystick.h"
#include "screen.h"
#include "pong.h"


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

 static RC_t PONG__control(BALL_t *const me, BAT_t *const bat);

 
/*****************************************************************************/
/* Function implementation - global ('extern') and local ('static')          */
/*****************************************************************************/


//RC_t PONG_init(PONG_GAME_t* pong,JOYSTICK_t* joystick, BAT_t* bat, BALL_t* ball)
//{
//    pong->joystick = *joystick;
//    pong->bat = *bat;
//    pong->ball = *ball;
//    
//   
//}



/**
 * Updates the position and draws the bat on the screen
 * @param *me : Pointer pointing to the bat object
 * @return void
*/


RC_t PONG_play(PONG_GAME_t* me)
{
    JOYSTICK_update(&me->joystick);  
    BAT_update_pos(&me->bat,me->joystick);
        
    PONG__control(&me->ball, &me->bat); 
        
    BALL_update_pos(&me->ball);
        
    return RC_SUCCESS;
}

PONG_BOUNDARY PONG_BallReachedBoundary( BALL_t *const me, BAT_t *const bat)
{
   if(me->current_ball_pos.X >= (SCREEN_HEIGHT - BALL_WIDTH))
    return PONG_BOUNDARY_up;
   if (me->current_ball_pos.Y >= (SCREEN_WIDTH - BALL_WIDTH))
    return PONG_BOUNDARY_right;
   if (me->current_ball_pos.Y <= 0)
    return PONG_BOUNDARY_left;
   // me->current_ball_pos.X <= BALL_WIDTH) && 
   if((me->current_ball_pos.X <= BALL_WIDTH) && (bat->current_bat_pos <= me->current_ball_pos.Y) && (me->current_ball_pos.Y <= (bat->current_bat_pos + BAT_HEIGHT) ))
    return PONG_BOUNDARY_down;

}


static RC_t PONG__control(BALL_t *const me, BAT_t *const bat)
{
    if(PONG_BallReachedBoundary(me,bat) == PONG_BOUNDARY_right)
    {
        BALL_flipYSpeed(me);
        
    }
    if(PONG_BallReachedBoundary(me,bat) == PONG_BOUNDARY_left)
    {
        BALL_flipYSpeed(me);
        
    }
    if(PONG_BallReachedBoundary(me,bat) == PONG_BOUNDARY_up)
    {
        BALL_flipXSpeed(me);
        
    }
    
    if(PONG_BallReachedBoundary(me,bat) == PONG_BOUNDARY_down)
    {
        BALL_flipXSpeed(me);
        
    }
    
    return RC_SUCCESS; 
}
  