/**
 * \file menu.c
 * \author Umesh V Chandargi
 * \date 14.09.2023
 *
 * \brief File containing Menu viewing funtions for Arcadian games
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
#include "menu.h"
#include "tft.h"

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

/*!
 * Creation of Menu Object
 * Arcadian game has only one menu. So therefore a singleton object is created.
 * It is made static to hide the data members
 */
static MENU_t MENU_game;




/*****************************************************************************/
/* Local function prototypes ('static')                                      */
/*****************************************************************************/


/*****************************************************************************/
/* Function implementation - global ('extern') and local ('static')          */
/*****************************************************************************/
/*!
 * Initialisation of the Menu object
 * @param none
 * @return none
 */
void MENU_init()
{
	MENU_game.m_game= GAME_PONG;
	MENU_game.m_numberGames=DISPLAY_NUMBEROFGAMES;
	MENU_game.m_selectedGame = GAME_PONG;
	MENU_game.p_CfgTable= &GAME_table;

}

/*!
 * Returns the index of the selected game
 * @param none
 * @return uint8_t- returns the index value
 */
uint8_t MENU_GetIndex()
{
	return MENU_game.m_selectedGame;
}

/*!
 * Move the index to the Previous game in the Menu list
 * @param none
 * @return none
 */
void MENU_prevgame()
{
	MENU_game.m_selectedGame =  (MENU_game.m_selectedGame + MENU_game.m_numberGames -1) % MENU_game.m_numberGames;
	MENU_ShowMenu();


}

/*!
 * Move the index to the Next game in the Menu list
 * @param none
 * @return none
 */
void MENU_nextgame()
{
	MENU_game.m_selectedGame =  (MENU_game.m_selectedGame + 1) % MENU_game.m_numberGames;
	MENU_ShowMenu();
	//MENU_activategame();

}

/*!
 * Print the Menu list on the TFT display
 * @param none
 * @return none
 */
void MENU_ShowMenu()
{
	GAME_CfgTable_t* table= MENU_game.p_CfgTable;
	TFT_clearScreen();
	TFT_setTextSize(2);
	TFT_setTextColor(WHITE);
	for (uint8_t i = 0; i < MENU_game.m_numberGames; i++)
	{
		TFT_setCursor(20,(i+2)*20);
		TFT_print((char*)(*table)[i].m_gameName); //!(*table)[i].m_gameName - provides game name
	}

	//!Show the cursor
	if (MENU_game.m_numberGames > 0)
	{
		TFT_fillTriangle(2, (MENU_game.m_selectedGame+3)*20-2, 16, (MENU_game.m_selectedGame+2)*20 + 5 - 2, 2, (MENU_game.m_selectedGame+2)*20 - 2, YELLOW);
	}
	else
	{
		TFT_setCursor(20,20);
		TFT_setTextColor(RED);
		TFT_print("No Features yet");
	}

}

