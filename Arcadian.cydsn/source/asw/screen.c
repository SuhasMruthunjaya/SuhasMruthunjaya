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
#include "project.h"
#include "global.h"
#include "stdlib.h"
#include "tft.h"
#include "joystick.h"
#include "screen.h"

#include "logging.h"

/*****************************************************************************/
/* Local pre-processor symbols/macros ('#define')                            */
/*****************************************************************************/

/*****************************************************************************/
/* Global variable definitions (declared in header file with 'extern')       */
/*****************************************************************************/

/*****************************************************************************/
/* Local type definitions ('typedef')                                        */
/*****************************************************************************/
/*!
 * \brief Net_CordinateRangeTable created to have multiple dotted line
 * which forms as a net to be drawn the TFT display for soccer ´game.
 *  X coordinate will stay the same, y will have start and end cordinate
 */
NetCoordinates_t Net_CordinateRangeTable[] = {
		/* m_x                 m_y1    m_y2 */
		{ SCREEN_HEIGHT-1,    16,     24},
		{ SCREEN_HEIGHT-1,    32,     40},
		{ SCREEN_HEIGHT-1,    48,     56},
		{ SCREEN_HEIGHT-1,    64,     72},
		{ SCREEN_HEIGHT-1,    80,     88},
		{ SCREEN_HEIGHT-1,    96,     104},
		{ SCREEN_HEIGHT-1,    112,     120},
		{ SCREEN_HEIGHT-1,    128,     136},
		{ SCREEN_HEIGHT-1,    144,     152},

};
uint8_t Net_CordinateRangeTable_size = sizeof(Net_CordinateRangeTable)/sizeof(NetCoordinates_t);
/*****************************************************************************/
/* Local variable definitions ('static')                                     */
/*****************************************************************************/



/*****************************************************************************/
/* Local function prototypes ('static')                                      */
/*****************************************************************************/
/**
 * Updates the position and draws the bat on the screen
 * @param *me : Pointer pointing to the bat object
 * @return void
 */
static void SCREEN__updateBat(BAT_t *const me); 

/**
 * Updates the position and draws the ball on the screen
 * @param *me : Pointer pointing to the ball object
 * @return void
 */
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
	uint8_t BatSpeed;


	bat_current_pos = BAT_GetCurrentPosition(me);
	bat_previous_pos = BAT_GetPreviousPosition(me);
	BatSpeed= BAT_GetBatSpeed(me);

	TFT_fillRect(0,bat_previous_pos,BAT_WIDTH,BatSpeed,BLACK);
	TFT_fillRect(0,bat_current_pos,BAT_WIDTH,BAT_HEIGHT,RED);



}

/**
 * Updates the position and draws the ball on the screen
 * @param *me : Pointer pointing to the ball object
 * @return void
 */
static void SCREEN__updateBall(BALL_t *const me)
{
	Cordinate_t ball_current_pos;
	Cordinate_t ball_previous_pos;


	ball_current_pos = BALL_getcurrentballpos(me);
	ball_previous_pos = BALL_getpreviousballpos(me);

	TFT_fillRect(ball_previous_pos.X,ball_previous_pos.Y,BALL_WIDTH,BALL_HEIGHT,BLACK);
	TFT_fillRect(ball_current_pos.X,ball_current_pos.Y,BALL_WIDTH,BALL_HEIGHT,RED);
}


/*!
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

/*!
 * Initialisation Ball object pointer in the screen type (Association)
 * @param SCREEN_t *const me - constant pointer (address cannot be changed in the function) pointing to the SCREEN Object
 * @param BALL_t *const pBall  - constant pointer (address cannot be changed in the function) pointing to the BALL Object
 * @return returns RC_SUCCESS if the initialisation is successful
 */
RC_t SCREEN_BALLInit(SCREEN_t *const me,BALL_t *const pBALL)
{

	me->m_pBall = pBALL;
	return RC_SUCCESS;
}

/*!
 * Update new position of the Screen elements
 * @param SCREEN_t *const me - constant pointer (address cannot be changed in the function) pointing to the SCREEN Object
 * @return returns RC_SUCCESS if the update is successful
 */
RC_t SCREEN_update(SCREEN_t *const me)
{
	SCREEN__updateBat(me->m_pBat);
	SCREEN__updateBall(me->m_pBall);

	return RC_SUCCESS;
}

/*!
 * Draws Walls on all sides which is needed for the Pong game
 * @param none
 * @return returns RC_SUCCESS if the process is successful
 */
RC_t SCREEN_drawPongWall()
{
	TFT_fillRect(0, 0, SCREEN_HEIGHT, WALL_WIDTH, RED); // screen left


	TFT_fillRect(SCREEN_HEIGHT-WALL_WIDTH, 0, WALL_WIDTH, SCREEN_WIDTH, RED); //screen up


	TFT_fillRect(0, SCREEN_WIDTH- WALL_WIDTH, SCREEN_HEIGHT, WALL_WIDTH, RED); // screen right
}

/*!
 * Draws Net on one side of the screen which is needed for the Soccer game
 * @param none
 * @return returns RC_SUCCESS if the process is successful
 */
RC_t SCREEN_drawSoccerNet()
{
	int val=18; //16 lines and 16 spaces
	uint8_t x=SCREEN_HEIGHT-1;
	for(int i=0; i<val/2;i++)
	{
		int temp = 2*i+2;
		TFT_writeLine(x, temp*(SCREEN_WIDTH/val), x, (temp+1)* (SCREEN_WIDTH/val), RED);
		TFT_writeLine(x, (temp+1)* (SCREEN_WIDTH/val), x, (temp+2)* (SCREEN_WIDTH/val), BLACK);
	}

}

/**
 * Function to check if the ball is hitting the Net. Small part is re-drawn so as to
 * have the net unchanged when the ball passes through it.
 * @param SCREEN_t *const me - constant pointer
 * (address cannot be changed in the function) pointing to the SCREEN Object
 * @return void
 */
void SCREEN_SoccerCheckBallHitNet(SCREEN_t *const me)
{
	Cordinate_t prev_pos= BALL_getpreviousballpos(me->m_pBall);
	uint16_t BallPosY_1 = prev_pos.Y;
	uint16_t BallPosY_2 = prev_pos.Y + BALL_WIDTH;
	uint16_t BallPosX= prev_pos.X;
	for(int i=0; i<Net_CordinateRangeTable_size; i++)
	{
		if(((BallPosY_1 >= Net_CordinateRangeTable[i].m_y1) || BallPosY_2>= Net_CordinateRangeTable[i].m_y1)
				&&
				(( BallPosY_1 <= Net_CordinateRangeTable[i].m_y2) || ( BallPosY_2 <= Net_CordinateRangeTable[i].m_y2)))
		{
			for(int j1=0;j1<BALL_WIDTH;j1++)
			{
				if(BallPosX == Net_CordinateRangeTable[i].m_x)
				{
					//!redraw the net
					TFT_writeLine( Net_CordinateRangeTable[i].m_x, Net_CordinateRangeTable[i].m_y1,
							Net_CordinateRangeTable[i].m_x, Net_CordinateRangeTable[i].m_y2, RED);
				}
				else
				{
					BallPosX++;
				}

			}
		}
	}
}

/*!
 * Draws Walls on three sides which is needed for the Soccer game
 * @param none
 * @return returns RC_SUCCESS if the process is successful
 */
RC_t SCREEN_drawSoccerWall()
{
	TFT_fillRect(0, 0, SCREEN_HEIGHT, WALL_WIDTH, RED); // screen left

	//TFT_fillRect(SCREEN_HEIGHT-WALL_WIDTH, 0, WALL_WIDTH, SCREEN_WIDTH, RED); //screen up

	SCREEN_drawSoccerNet();
	TFT_fillRect(0, SCREEN_WIDTH- WALL_WIDTH, SCREEN_HEIGHT, WALL_WIDTH, RED); // screen right


}
/**
 * Function to show Welcome message for Pong game
 * @param none
 * @return void
 */
void SCREEN_PongShowWelcomeMessage()
{
	TFT_clearScreen();
	TFT_setTextColor(YELLOW);
	TFT_setTextSize(1);
	TFT_setCursor(5,10);
	TFT_print("Welcome to PONG Game");
	TFT_writeLine(0, 30, 128, 30, YELLOW);
	TFT_setCursor(40,50);
	TFT_print("Press B.1");
	TFT_setCursor(0,70);
	TFT_print("for starting the game");
	TFT_writeLine(0,90,128,90,YELLOW);
	TFT_setCursor(10,110);
	TFT_print("The number of life");
	TFT_setCursor(10,130);
	TFT_print("will be displayed");
	TFT_setCursor(40,150);
	TFT_print("on 7seg ");


}

/**
 * Function to show Game Score for Pong game
 * @param uint16_t score - IN Score data to be printed on TFT
 * @return void
 */
void SCREEN_PongShowGameScore(uint16_t score)
{
	char buffer[255];
	itoa(score,buffer,10);
	TFT_clearScreen();
	TFT_setTextColor(RED);
	TFT_setTextSize(2);
	TFT_setCursor(10,25);
	TFT_print("Game Over");
	TFT_setTextSize(1);
	TFT_setTextColor(GREEN);
	TFT_setCursor(10,60);
	TFT_print("Total Score is ");
	TFT_print(buffer);
	TFT_setTextColor(YELLOW);
	TFT_setCursor(20,80);
	TFT_print("For restarting");
	TFT_setCursor(20,100);
	TFT_print("Press B.1");
	TFT_setCursor(20,120);
	TFT_print("To Exit the Game");
	TFT_setCursor(20,140);
	TFT_print("Press B.3");
}

/**
 * Function to show message for loosing one life in Pong game
 * @param none
 * @return void
 */
void SCREEN_PongShowLoosingLife()
{
	TFT_clearScreen();
	TFT_setTextColor(YELLOW);
	TFT_setTextSize(1);
	TFT_setCursor(20,35);
	TFT_print("You lost 1 life");
	TFT_setCursor(20,60);
	TFT_print("To Continue");
	TFT_setCursor(20,80);
	TFT_print("Press B.1");
	TFT_setCursor(20,100);
	TFT_print("To Exit the Game");
	TFT_setCursor(20,120);
	TFT_print("Press B.3");
}

/**
 * Function to show Welcome message in Soccer game
 * @param none
 * @return void
 */
void SCREEN_SoccerShowWelcomeMessage()
{
	TFT_clearScreen();
	TFT_setTextColor(YELLOW);
	TFT_setTextSize(1);
	TFT_setCursor(5,10);
	TFT_print("Welcome to SOCCER Game");
	TFT_writeLine(0, 30, 128, 30, YELLOW);
	TFT_setCursor(40,50);
	TFT_print("Press B.1");
	TFT_setCursor(0,70);
	TFT_print("for starting the game");
	TFT_writeLine(0,90,128,90,YELLOW);
	TFT_setCursor(10,110);
	TFT_print("The number of life");
	TFT_setCursor(10,130);
	TFT_print("will be displayed");
	TFT_setCursor(40,150);
	TFT_print("on 7seg ");
}





/**
 * Function to show message for loosing one life in Soccer game
 * @param none
 * @return void
 */
void SCREEN_SoccerShowLostRound()
{
	TFT_clearScreen();
	TFT_setTextColor(RED);
	TFT_setTextSize(1);
	TFT_setCursor(20,35);
	TFT_print("Round Lost :(");
	TFT_setCursor(20,60);
	TFT_print("You lost 1 life");
    TFT_setTextColor(YELLOW);
	TFT_setCursor(20,80);
	TFT_print("To Continue");
	TFT_setCursor(20,100);
	TFT_print("Press B.1");
	TFT_setCursor(20,120);
	TFT_print("To Exit the Game");
	TFT_setCursor(20,140);
	TFT_print("Press B.3");
}

/**
 * Function to show Game round won message in Soccer game
 * @param none
 * @return void
 */
void SCREEN_SoccerWonRoundMessage()
{
	TFT_clearScreen();
	TFT_setTextColor(GREEN);
	TFT_setTextSize(1);
	TFT_setCursor(20,35);
	TFT_print("Round Won!! :)");
    TFT_setTextColor(YELLOW);
	TFT_setCursor(20,60);
	TFT_print("To Continue");
	TFT_setCursor(20,80);
	TFT_print("Press B.1");
	TFT_setCursor(20,100);
	TFT_print("To Exit the Game");
	TFT_setCursor(20,120);
	TFT_print("Press B.3");
}

/**
 * Function to show Game lost message in Soccer game
 * @param none
 * @return void
 */
void SCREEN_SoccerShowGameLostMessage()
{
	TFT_clearScreen();
	TFT_setTextColor(RED);
	TFT_setTextSize(2);
	TFT_setCursor(10,25);
	TFT_print("Game Over");
	TFT_setTextSize(1);
	TFT_setCursor(20,50);
	TFT_print("You have lost");
    TFT_setCursor(20,60);
	TFT_print("the game :(");
	TFT_setTextColor(YELLOW);
	TFT_setCursor(20,80);
	TFT_print("For restarting");
	TFT_setCursor(20,100);
	TFT_print("Press B.1");
	TFT_setCursor(20,120);
	TFT_print("To Exit the Game");
	TFT_setCursor(20,140);
	TFT_print("Press B.3");
}

/**
 * Function to show Game won message in Soccer game
 * @param none
 * @return void
 */
void SCREEN_SoccerShowGameWonMessage()
{
	TFT_clearScreen();
	TFT_setTextColor(RED);
	TFT_setTextSize(2);
	TFT_setCursor(10,25);
	TFT_print("Game Over");
	TFT_setTextSize(1);
	TFT_setTextColor(GREEN);
	TFT_setCursor(20,50);
	TFT_print("You have won");
    TFT_setCursor(20,60);
	TFT_print("the game! :)");
	TFT_setTextColor(YELLOW);
	TFT_setCursor(20,80);
	TFT_print("For restarting");
	TFT_setCursor(20,100);
	TFT_print("Press B.1");
	TFT_setCursor(20,120);
	TFT_print("To Exit the Game");
	TFT_setCursor(20,140);
	TFT_print("Press B.3");

}


/**
 * Function to show Timeout message in Soccer game
 * @param none
 * @return void
 */
void SCREEN_SoccerShowTimeoutMessage()
{
	TFT_clearScreen();
	TFT_setTextColor(RED);
	TFT_setTextSize(2);
	TFT_setCursor(1,25);
	TFT_print("CONNECTION");
	TFT_setCursor(10,45);
	TFT_print("TIMEOUT:(");
	TFT_setTextSize(1);
	TFT_setCursor(10,70);
	TFT_print("Press STOP Button");
	TFT_setCursor(20,90);
	TFT_print("and Try Again");

}
