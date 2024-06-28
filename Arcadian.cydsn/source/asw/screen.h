
//* ========================================
// *
// * Copyright YOUR COMPANY, THE YEAR
// * All Rights Reserved
// * UNPUBLISHED, LICENSED SOFTWARE.
// *
// * CONFIDENTIAL AND PROPRIETARY INFORMATION
// * WHICH IS THE PROPERTY OF your company.
// *
// * ========================================
// */

/**
 * \file <filename>
 * \author <author-name>
 * \date <date>
 *
 * \brief File containing attributes and functions of Screen Class
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

#ifndef SCREEN_H
#define SCREEN_H

/*****************************************************************************/
/* Global pre-processor symbols/macros and type declarations                 */
/*****************************************************************************/

#include "global.h"
#include "position.h"
#include "bat.h"
#include "ball.h"
#include "tft.h"    
    
//####################### Defines/Macros
/** 
 * \brief Dimensions of the TFT display
 */

  #define SCREEN_HEIGHT 128
  #define SCREEN_WIDTH 160
  
    

//####################### Enumerations
/**
* \brief Enumerations. Use brief, otherwise the index won't have a brief explanation.
*
* Detailed explaination of the enumeration.
*/


//####################### Structures
/*!
 * \brief Screen type created to have models to be drawn the TFT display.
 *	Bat and Ball are the models to be displayed in the TFT display
 *  It is created as a pointer (association relation). Each game will created objects
 *  screen will get the pointer to those objects
 */
typedef struct
    {
        BAT_t* m_pBat;
        BALL_t* m_pBall;
    } SCREEN_t;

/*!
 * \brief NetCoordinates_t type created to have net to be drawn the TFT display
 *	especially for soccer ´game.
 *  X coordinate will stay the same, y will have start and end cordinate
 */
typedef struct
    {
        uint8_t m_x;
        uint8_t m_y1;
        uint8_t m_y2;       
        
    }NetCoordinates_t;
    
extern NetCoordinates_t Net_CordinateRangeTable[];
/*****************************************************************************/
/* Extern global variables                                                   */
/*****************************************************************************/

/**
 * <description>
 */

   

/*****************************************************************************/
/* API functions                                                             */
/*****************************************************************************/

/**
 * <Description>
 * @param <Format: copy of the parameter type and name - description>
 * @return <return description>
 */



/*****************************************************************************/
/* Extern global variables                                                   */
/*****************************************************************************/

/**
 * <description>
 */


/*****************************************************************************/
/* API functions                                                             */
/*****************************************************************************/


/*!
 * Initialisation of the screen
 * @param SCREEN_t *const me - constant pointer (address cannot be changed in the function) pointing to the SCREEN Object
 * @param BAT_t *const pBat  - constant pointer (address cannot be changed in the function) pointing to the BAT Object
 * @param BALL_t *const pBall  - constant pointer (address cannot be changed in the function) pointing to the BALL Object
 * @return returns RC_SUCCESS if the initialisation is successful
 */
RC_t SCREEN_init(SCREEN_t *const me, BAT_t *const pBat, BALL_t *const pBALL);

/*!
 * Initialisation Ball object pointer in the screen type (Association)
 * @param SCREEN_t *const me - constant pointer (address cannot be changed in the function) pointing to the SCREEN Object
 * @param BALL_t *const pBall  - constant pointer (address cannot be changed in the function) pointing to the BALL Object
 * @return returns RC_SUCCESS if the initialisation is successful
 */
RC_t SCREEN_BALLInit(SCREEN_t *const me,BALL_t *const pBALL);

/*!
 * Update new position of the Screen elements
 * @param SCREEN_t *const me - constant pointer (address cannot be changed in the function) pointing to the SCREEN Object
 * @return returns RC_SUCCESS if the update is successful
 */
RC_t SCREEN_update(SCREEN_t *me);

/*!
 * Draws Walls on all sides which is needed for the Pong game
 * @param none
 * @return returns RC_SUCCESS if the process is successful
 */
RC_t SCREEN_drawPongWall();

/*!
 * Draws Walls on three sides which is needed for the Soccer game
 * @param none
 * @return returns RC_SUCCESS if the process is successful
 */
RC_t SCREEN_drawSoccerWall();

/*!
 * Draws Net on one side of the screen which is needed for the Soccer game
 * @param none
 * @return returns RC_SUCCESS if the process is successful
 */
RC_t SCREEN_drawSoccerNet();

/**
 * Function to check if the ball is hitting the Net. Small part is re-drawn so as to
 * have the net unchanged when the ball passes through it.
 * @param SCREEN_t *const me - constant pointer
 * (address cannot be changed in the function) pointing to the SCREEN Object
 * @return void
 */
void SCREEN_SoccerCheckBallHitNet(SCREEN_t *const me);

/**
 * Function to show Welcome message for Pong game
 * @param none
 * @return void
 */
void SCREEN_PongShowWelcomeMessage();

/**
 * Function to show Game Score for Pong game
 * @param uint16_t score - IN Score data to be printed on TFT
 * @return void
 */
void SCREEN_PongShowGameScore(uint16_t score);

/**
 * Function to show message for loosing one life in Pong game
 * @param none
 * @return void
 */
void SCREEN_PongShowLoosingLife();

/**
 * Function to show message for loosing one life in Soccer game
 * @param none
 * @return void
 */
void SCREEN_SoccerShowLostRound();

/**
 * Function to show Game round won message in Soccer game
 * @param none
 * @return void
 */
void SCREEN_SoccerWonRoundMessage();

/**
 * Function to show Game lost message in Soccer game
 * @param none
 * @return void
 */
void SCREEN_SoccerShowGameLostMessage();

/**
 * Function to show Game won message in Soccer game
 * @param none
 * @return void
 */
void SCREEN_SoccerShowGameWonMessage();


/**
 * Function to show Timeout message in Soccer game
 * @param none
 * @return void
 */
void SCREEN_SoccerShowTimeoutMessage();

/**
 * Function to show Welcome message in Soccer game
 * @param none
 * @return void
 */
void SCREEN_SoccerShowWelcomeMessage();


#endif /* FILE_H */
