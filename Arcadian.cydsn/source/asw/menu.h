/**
* \file menu.h
* \author Umesh V Chandargi
* \date 14.09.2023
*
* \brief File containing Menu viewing funtions for Arcadian games
*
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


 
#ifndef MENU_H
#define MENU_H

#include "global.h"
#include "game_cfg.h"

    
/*****************************************************************************/
/* Global pre-processor symbols/macros and type declarations                 */
/*****************************************************************************/






//!####################### Structures
/**
* \Brief Structure type for MENU functions on the TFT display
* Menu must know the game enum
* it has an index for the selectedgame.
* Menu must know total number of games.
* It also has a pointer to the Game Config table, to know the names of each game* .
*/
struct sMenu {
    GAME_Enum_t m_game;
    uint8_t     m_selectedGame;
    uint8_t     m_numberGames;
    GAME_CfgTable_t *p_CfgTable;
};
typedef struct sMenu MENU_t;


/*****************************************************************************/
/* Extern global variables                                                   */
/*****************************************************************************/



/*****************************************************************************/
/* API functions                                                             */
/*****************************************************************************/

/*!
 * Initialisation of the Menu object
 * @param none
 * @return none
 */
void MENU_init();

/*!
 * Returns the index of the selected game
 * @param none
 * @return uint8_t- returns the index value
 */
uint8_t MENU_GetIndex();

/*!
 * Move the index to the Previous game in the Menu list
 * @param none
 * @return none
 */
void MENU_prevgame();

/*!
 * Move the index to the Next game in the Menu list
 * @param none
 * @return none
 */
void MENU_nextgame();

/*!
 * Print the Menu list on the TFT display
 * @param none
 * @return none
 */
void MENU_ShowMenu();

#endif /* FILE_H */
