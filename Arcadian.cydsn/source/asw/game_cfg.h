/**
* \file game_cfg.h
* \author P. Fromm
* \date 23.6.20
*
* \brief File created to avoid cyclic dependency between Menu and Game, it contains configuration data such as tzpedef structures and enums
* needed for both game and menu
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
**/


 
#ifndef GAME_CFG_H
#define GAME_CFG_H
#include "global.h"
    
/*****************************************************************************/
/* Global pre-processor symbols/macros and type declarations                 */
/*****************************************************************************/

//####################### Defines/Macros
/** 
 * \brief Macros needed for the Game. Gamespeed is defined as tick in ms
 * eg. 10ms means the Game tick is set to 10ms. Game can be slowed down by
 *  increasing this value. 
 *  Nunber of games are set to 2. (Pong and Soccer) More games can be added 
 *  and this number can be increased.
 *  String length of each game name is set to max of 10
 */
    
#define GAMESPEED 10
#define DISPLAY_FEATURESTRINGLENGTH 10
#define DISPLAY_NUMBEROFGAMES 2
    
typedef char displayString_t[DISPLAY_FEATURESTRINGLENGTH];    
typedef  RC_t (*Game_func_t)();


//!####################### Structures
/*!
 * \brief Configuration data mentioned for each Arcadian game
 * It consists for Game name, Init of respective game state machine,
 * Cyclic logic function calls and finally de-init
 *
 */
typedef struct{
    displayString_t m_gameName;
    Game_func_t Init;
    Game_func_t Game_cyclic;
    Game_func_t DeInit;
        
}GAME_cfg_t;

typedef GAME_cfg_t  GAME_CfgTable_t[];


//! Configuration table for all the games played in the Arcadian
extern GAME_CfgTable_t GAME_table;

//!####################### Enumerations
/*!
 * \brief Different Arcadian game names defined as GAME_Enum_t
 *
 */
 enum eGame{
  GAME_PONG,  /**< Pong gamw */
  GAME_SOCCER, /**< Soccer game */
} ;
typedef enum eGame GAME_Enum_t;

/*!
 * \brief State names of the Game State Machine
 *
 */
 enum eGameState{
  GAME_IS_SELECTING, /**< First state- Menu is displayed to select available games */
  GAME_IS_SELECTEDGAME, /**< Second state- Respective Game play is called*/
} ;
typedef enum eGameState GAME_State_t;

/*!
 * \brief Events used in Game State Machine
 *
 */
 enum eGameEvent{
  GAME_EV_NONE,  //!**< No Event */
  GAME_EV_TICK,  //!**< Repeated Tick event eg.10ms tick */
  GAME_EV_BUTTON_START, //!**< Event when BUTTON_1 is pressed */
  GAME_EV_BUTTON_STOP, //!**< Event when BUTTON_3 is pressed */
  GAME_EV_BUTTON_UP, //!**< Event when BUTTON_2 is pressed */
  GAME_EV_BUTTON_DOWN, //!**< Event when BUTTON_4 is pressed */
} ;
typedef enum eGameEvent GAME_event_t;

#define GameStateMachine_INIT_DATA    GAME_IS_SELECTING


/** ----------------------------- Event and State definitions --------------------------------------- **/    

/*!
 * \brief Event type and casted to uint8_t so that State machine process event function
 * can consider all enum types. This is needed for different state machines used in the entire project
 */
typedef uint8_t STATE_event_t;
typedef uint8_t STATE_state_t;


/*****************************************************************************/
/* API functions                                                             */
/*****************************************************************************/




#endif /* GAME_CFG_H */
