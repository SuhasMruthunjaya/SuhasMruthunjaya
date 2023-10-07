/**
* \file game_cfg.h
* \author P. Fromm
* \date 23.6.20
*
* \brief generic statemachine implementation, based on 2 Layer lookup table
*
* detailed description what the file does
*
* \note <notes>
* \todo <todos>
* \warning <warnings, e.g. dependencies, order of execution etc.>
*
*  Changelog:\n
*  - 1.0; 23.06.2020; P. Fromm
*            - Initial version
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

/*****************************************************************************/
/* Global pre-processor symbols/macros and type declarations                 */
/*****************************************************************************/
#include "global.h"

    
#define DISPLAY_FEATURESTRINGLENGTH 10
#define DISPLAY_NUMBERFEATURE 2
    
typedef char displayString_t[DISPLAY_FEATURESTRINGLENGTH];    
typedef  RC_t (*Game_func_t)();

typedef struct{
    displayString_t m_gameName;
    Game_func_t Init;
    Game_func_t Game_cyclic;
    Game_func_t DeInit;
        
}GAME_cfg_t;

typedef GAME_cfg_t  GAME_CfgTable_t[];


 enum eGame{
  GAME_PONG,  /**< Pong gamw */
  GAME_SOCCER, /**< Soccer game */
} ;
typedef enum eGame GAME_Enum_t;

 enum eGameState{
  GAME_IS_SELECTING, /**< Some documentation second. */
  GAME_IS_SELECTEDGAME, /**< Some documentation second. */ 
} ;
typedef enum eGameState GAME_State_t;


 enum eGameEvent{
  GAME_EV_NONE,  /**< Some documentation first. */    
  GAME_EV_TICK,  /**< Some documentation first. */
  GAME_EV_BUTTON_START, /**< Some documentation second. */
  GAME_EV_BUTTON_STOP, /**< Some documentation second. */
  GAME_EV_BUTTON_UP, /**< Some documentation second. */    
  GAME_EV_BUTTON_DOWN, /**< Some documentation second. */     
} ;
typedef enum eGameEvent GAME_event_t;

#define GameStateMachine_INIT_DATA    GAME_IS_SELECTING


/** ----------------------------- Event and State definitions --------------------------------------- **/    

// We will use the event definition from the event signal.
// Strictly spoken, the state machine events are only a subset, 
// but we want to avoid multiple similar definitions.
typedef uint8_t STATE_event_t;
    
// Same argument for the states
typedef uint8_t STATE_state_t;

//Initial state of the state machine
#define STATE_INITIALSTATE GameStateMachine_INIT_DATA 


/*****************************************************************************/
/* API functions                                                             */
/*****************************************************************************/

/**
 * <Description>
 * @param <Format: copy of the parameter type and name - description>
 * @return <return description>
 */
RC_t Cfg_init(GAME_cfg_t *me);

/**
 * <Description>
 * @param <Format: copy of the parameter type and name - description>
 * @return <return description>
 */
RC_t Cfg_GameInfo(GAME_cfg_t *me);

/**
 * <Description>
 * @param <Format: copy of the parameter type and name - description>
 * @return <return description>
 */
RC_t Cfg_GameCyclic(GAME_cfg_t *me);



#endif /* GAME_CFG_H */
