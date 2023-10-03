/**
 * \file 	det.c
 * \author 	Peter Fromm	- Hochschule Darmstadt 
 * \date 	26.11.2016
 * \version 0.1
 *
 * \brief  Logging mechanism
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
/*=======================[ Includes ]===============================================================*/
#include <project.h>
#include "det_cfg.h"


/*=======================[ constant data ]===============================================================*/

/**\brief Array of strings, containing human readable representations of event sources */
const char * const DET_source_strings[] = {
		DET_CFG(DET_CFG_ENUM_STR)
};

/**\brief Configuration storage */
const DET_event_table_entry_t DET_event_table[] = {
		DET_CFG(DET_CFG_ENTRY)
};
/*=======================[ variable data ]===============================================================*/

#define DET_BUFFERSIZE 100

/** Sample buffer, may also be defined in application */
DET_event_log_entry_t DET_default[DET_BUFFERSIZE] = {};

DET_t DET = {
    DET_BUFFERSIZE,
    0,
    (DET_event_log_entry_t*)&DET_default
};

/*=======================[ Function implementation ]=====================================================*/

/**
 * Returns the time in ms for the event timestamp 
 **/
uint32_t DET_getTimeInMs()
{
    TickType currentTime = 0;
    GetCounterValue(cnt_systick, &currentTime);
    
    return (uint32_t) currentTime;
}


/**
 * Locks access to the data
 **/
void DET_lock()
{
    GetResource(res_det);
}

/**
 * Unlocks access to the data
 **/
void DET_unlock()
{
    ReleaseResource(res_det);
}

/**
 * Deactivate all actors
 **/
void DET_deactivateActors()
{
    //Deactivate AND gate for engines
    ENGINE_OnOff_Write(0);
}



/* [] END OF FILE */
