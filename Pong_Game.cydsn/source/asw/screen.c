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

static void SCREEN__updateBat(BAT_t *const me); 
static void SCREEN__updateBall(BALL_t *const me); 

 
/*****************************************************************************/
/* Function implementation - global ('extern') and local ('static')          */
/*****************************************************************************/

/**
 * Updates the position and draws the bat on the screen
 * @param *me : Pointer pointing to the bat object
 * @return void
*/


static void SCREEN__updateBat(BAT_t *const me)
{
     
  //  TFT_clearScreen();
    
    uint16_t bat_current_pos;
    uint16_t bat_previous_pos;
    
    
    bat_current_pos = BAT_GetCurrentPosition(me);
    bat_previous_pos = BAT_GetPreviousPosition(me);
    
    TFT_fillRect(0,bat_previous_pos,BAT_WIDTH,1,BLACK);
    TFT_fillRect(0,bat_current_pos,BAT_WIDTH,BAT_HEIGHT,RED);
    
 
  
}


static void SCREEN__updateBall(BALL_t *const me)
{
    
 //   TFT_clearScreen();
    //  me->current_ball_pos.X <= BALL_WIDTH
 
    
    Cordinate_t ball_current_pos;
    Cordinate_t ball_previous_pos;
    
    
    ball_current_pos = BALL_getcurrentballpos(me);
    ball_previous_pos = BALL_getpreviousballpos(me);
 
/*    
  if (ball_current_pos.X >= (SCREEN_HEIGHT - BALL_WIDTH) up ||  ball_current_pos.X <= BALL_WIDTH )down {
    me->ball_speed.pos.X *= -1;   // Reverse the X direction
  }
  if (ball_current_pos.Y >= (SCREEN_WIDTH - BALL_WIDTH)right || ball_current_pos.Y <= 0) left {
    me->ball_speed.pos.Y *= -1;   // Reverse the Y direction
  }
*/    
    
    TFT_fillRect(ball_previous_pos.X,ball_previous_pos.Y,BALL_WIDTH,BALL_HEIGHT,BLACK);
    TFT_fillRect(ball_current_pos.X,ball_current_pos.Y,BALL_WIDTH,BALL_HEIGHT,RED);
}


/**
 * Initialisation of the screen
 * @param SCREEN_t *const me - constant pointer (address cannot be changed in the function) pointing to the SCREEN Object
 * @param BAT_t *const pBat  - constant pointer (address cannot be changed in the function) pointing to the BAT Object
 * @param BALL_t *const pBall  - constant pointer (address cannot be changed in the function) pointing to the BALL Object
 * @return returns RC_SUCCESS if the initialisation is successful
 */

RC_t SCREEN_init(SCREEN_t *const me, BAT_t *const pBat, BALL_t *const pBall)
{
    
    me->m_pBat = pBat;
    me->m_pBall = pBall;
    return RC_SUCCESS;
}
    
    
/**
 * <Description>
 * @param <Format: copy of the parameter type and name - description>
 * @return <return description>
 */
RC_t SCREEN_update(SCREEN_t *const me)
{
    SCREEN__updateBat(me->m_pBat);
    SCREEN__updateBall(me->m_pBall);
    return RC_SUCCESS;
}

/*
SCREEN_SIDES SCREEN_reachedpos( BALL_t *const me )
{
   if(me->current_ball_pos.X >= (SCREEN_HEIGHT - BALL_WIDTH))
    return SCREEN_left;
   if(me->current_ball_pos.X <= BALL_WIDTH)
    return SCREEN_down;
   if(me->

    
}
*/