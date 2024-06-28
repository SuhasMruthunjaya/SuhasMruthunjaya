/**
 * \file <filename>
 * \author <author-name>
 * \date <date>
 *
 * \brief File containing attributes and functions of Game Class
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



#ifndef GAME_H
#define GAME_H
#include "global.h"
#include "stdlib.h"
#include "pong.h"
#include "ball.h"
#include "bat.h"
#include "position.h"
#include "game_cfg.h"
/*****************************************************************************/
/* Global pre-processor symbols/macros and type declarations                 */
/*****************************************************************************/


//####################### Enumerations
/**
 * \brief Enumerations. Use brief, otherwise the index won't have a brief explanation.
 *
 * Detailed explaination of the enumeration.
 */



//!####################### Structures
/*!
 * \brief Game type created to have elements of the Game logic.
 *	life and score are inside the individual game elements
 *
 */
struct sGame {
	GAME_event_t ev;

};
typedef struct sGame GAME_t;



/*****************************************************************************/
/* API functions                                                             */
/*****************************************************************************/
/*!
 * Process the events obtained inside the Game state machine
 * @param STATE_event_t ev - IN Events to be processed inside the state machine
 * @return GAME_event_t - Event name is returned
 */
RC_t GAME_process_event(STATE_event_t ev);

/*!
 * Initialisation of the Game state machine
 * @param none
 * @return GAME_event_t - Event name is returned
 */
RC_t GAME_InitState();

/*!
 * Get the event names from the Game object
 * @param none
 * @return GAME_event_t - Event name is returned
 */
GAME_event_t GAME_get_event();

/*!
 * Set the events which are needed for the Game state machine
 * @param GAME_event_t ev - IN Event to be set
 * @return RC_SUCCESS when all okay
 */
RC_t GAME_set_event(GAME_event_t ev);

#endif /* FILE_H */
