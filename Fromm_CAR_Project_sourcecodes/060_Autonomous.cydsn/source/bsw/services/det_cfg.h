/**
 * \file 	det.h
 * \author 	Peter Fromm	- Hochschule Darmstadt 
 * \date 	27.05.2020
 * \version	1.0
 *
 * \brief Logging and debugging mechanism
 *
 *
 *  Changelog:\n
 *
 * \copyright Copyright ©2018
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

#ifndef DET_CFG_H
#define DET_CFG_H

/*=======================[ Includes ]==============================================================*/

#include "global.h"

    
/*=======================[ Symbols ]===============================================================*/

/** \brief makro to create the enumeration values */
#define DET_CFG_ENUM(name, action) 			DET_##name,

/** \brief Stringification of enumeration values */
#define DET_CFG_ENUM_STR(name,action) 		#name,

/** \brief Extraction of event action from the config */
#define DET_CFG_ACTION(name,action)			action,

/** \brief Makro to define an config entry */
#define DET_CFG_ENTRY(name,action)			{DET_##name, action},

/*=======================[ Types ]=================================================================*/

/**
 * \brief DET event escalation options
 */
typedef enum{   
    NONE,           /**< \brief No additional action */
	BREAKPOINT,     /**< \brief Set a breakpoint */
    RESET,   		/**< \brief Reset the chip */
	STOP     		/**< \brief Stop the car */
}CEH_reaction_t;    

/*=======================[ Event configuration ]=================================================================*/

//===================	Event Name							ACTION			==========================//
#define DET_CFG(DEF)\
		DEF(			EMPTY,								NONE            )	/* NOP, do not remove */		\
		DEF(			HASBOOTED,							NONE            )	/* Bootup message */			\
		DEF(			FSM_EVENT,						    NONE            )	/* State machine event */				\
		DEF(			FSM_STATE,						    NONE            )	/* State CHange */				\
	

/**
 * \brief event source enumeration
 */
typedef enum{
	DET_CFG(DET_CFG_ENUM)
	CEH_SOURCE_MAX									/**< \brief Number of events configured in the CEH */
} DET_event_t;

/**
 * \brief event configuration entry type
 */
typedef struct{
	DET_event_t	    event;							/**< \brief Source of the error event */
	CEH_reaction_t	reaction;						/**< \brief reaction for this event */
}DET_event_table_entry_t;



/**
 * \brief event storage entry type
 */
typedef struct{
	DET_event_t	    event;		/**< \brief Source of the error event */
	uint32_t        data;       /**< \brief Additional Payload */
    uint32_t        timestamp;  /**< \brief Timestamp in ms */
}DET_event_log_entry_t;

/*=======================[ Storage / Object configuration ]=================================================================*/

typedef struct
{
    uint16_t size;                      /*!< Size of the buffer */
    uint16_t nextFree;                /*!< Next Free Entry of the buffer */
    DET_event_log_entry_t* buffer;      /*!< Pointer to the buffer */
} DET_t;

/*=======================[ API ]=================================================================*/

/**\brief Array of strings, containing human readable representations of event sources */
extern const char * const DET_source_strings[];

/**\brief Configuration storage */
extern const DET_event_table_entry_t DET_event_table[];

/**\brief Defaulkt DET object */
extern DET_t DET;

/**
 * Returns the time in ms for the event timestamp 
 **/
uint32_t DET_getTimeInMs();

/**
 * Deactivate all actors
 **/
void DET_deactivateActors();

/**
 * Locks access to the data
 **/
void DET_lock();

/**
 * Unlocks access to the data
 **/
void DET_unlock();


#endif /* DET_H */

/* [] END OF FILE */