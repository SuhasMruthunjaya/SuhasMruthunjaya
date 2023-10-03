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
#include <stdlib.h>
#include "det.h"
#include "logging.h"


/*=======================[ constant data ]===============================================================*/


/*=======================[ variable data ]===============================================================*/

/*=======================[ Function implementation ]=====================================================*/

/**
 * OPTIONAL Init Function, only required if object is not statically defined in configuration
 * \param DET_t *const me       : [IN/OUT] The object to be initialized
 * \param uint16_t size         : [IN] Size of buffer
 * \return RC_SUCCES or error code
 **/
RC_t DET_init(DET_t *const me, uint16_t size)
{
    me->nextFree = 0;
    me->size = size;
    
    me->buffer = (DET_event_log_entry_t*)malloc(me->size * sizeof(DET_event_log_entry_t));
    return RC_SUCCESS;
}
   
/**
 * Report an store an diagnostic event
 * \param DET_t *const me       : [IN/OUT] The object 
 * \param DET_event_t det_event : [IN] Event to be reported
 * \param uint32_t data         : [IN] Optional payload
 * \return RC_SUCCES or error code
 **/
RC_t DET_report(DET_t *const me, DET_event_t det_event, uint32_t data)
{
    
    
    RC_t result = RC_SUCCESS;
    uint32_t currentTime = DET_getTimeInMs();
    
    if (me->nextFree < me->size)
    {
        DET_lock();
        
        me->buffer[me->nextFree].event = det_event;
        me->buffer[me->nextFree].data = data;
        me->buffer[me->nextFree].timestamp = currentTime;
        
        me->nextFree++;
        
        DET_unlock();
    }
    else
    {
        result = RC_ERROR_BUFFER_FULL;
    }
    
    //Check for additional actions required from configuration
    if(BREAKPOINT == DET_event_table[det_event].reaction)
    {
        __asm("bkpt");
    } 
    else if (RESET == DET_event_table[det_event].reaction)
    {
        CySoftwareReset();
    }
    else if (STOP == DET_event_table[det_event].reaction)
    {
        DET_deactivateActors();
    }
      
    return result;
}

/**
 * Dump content of DET Buffer to UART
 * \param DET_t *const me       : [IN] The object 
 * \return RC_SUCCES or error code
 **/
RC_t DET_dump(DET_t *const me)
{
    DET_lock();
    
    LOG_I("DET","Number of entries: %d", me->nextFree);
    
    
    for (uint16_t i = 0; i < me->nextFree; i++)
    {
        uint32_t hh, mm, ss, ms =  0;
        uint32_t t =  me->buffer[i].timestamp;
        
        hh = t / 3600 / 1000;
        t -= hh * 3600 * 1000;
        mm = t / 60 / 1000;
        t -= mm * 60 * 1000;
        ss = t / 1000;
        t -= ss * 1000;
        ms = t;

        
        LOG_I("DET","[%d] %s %d at %02d:%02d:%02d.%d ", i, DET_source_strings[me->buffer[i].event], me->buffer[i].data, hh, mm, ss, ms);
    }
    
    DET_unlock();
    
    return RC_SUCCESS;
}

/**
 * Clear content of DET Buffer
 * \param DET_t *const me       : [IN] The object 
 * \return RC_SUCCES or error code
 **/
RC_t DET_clear(DET_t *const me)
{
    me->nextFree = 0;
    return RC_SUCCESS;
}

/* [] END OF FILE */
