/*
 * Event_Ringbuffer.c
 *
 *  Created on: 15.09.2022
 *      Author: Fromm
 */

#include <stdlib.h>
#include "Event_Ringbuffer.h"

/**
* Initialises the ringbuffer and sets up the memory for the metadata
* \param RB_t *const me : [IN/OUT] Ring Buffer Object
* \param uint32_t const size : [IN] Size of the Ring Buffer
* \return RC_t: RC_SUCCESS in case of no error else error code
*/
RC_t RB_init(RB_t *const me, uint32_t size)
{
	me->m_size = size;
	me->m_pBuffer = (RB_content_t*)malloc(100 * sizeof(uint8_t));

	return RB_clear(me);


}

/**
* Frees up the memory created during initialisation
* \param RB_t *const me : [IN/OUT] Ring Buffer Object
* \return RC_t: RC_SUCCESS in case of no error else error code
*/
RC_t RB_deinit(RB_t *const me)
{
	free(me->m_pBuffer);

	return RC_SUCCESS;
}

/**
* Write the data into the Ring buffer
* \param RB_t *const me : [IN/OUT] Ring Buffer Object
* \param void const* const pData : [IN] Data to be written in the RingBuffer
* \return RC_t: RC_SUCCESS in case of no error else error code
*/
RC_t RB_put(RB_t *const me, RB_content_t data)
{
	if (me->m_fillLevel < me->m_size)
	{
        //GetResource(res_globalRingBuffer);
		me->m_pBuffer[me->m_writeIdx] = data;

		me->m_writeIdx++;
		me->m_writeIdx %= me->m_size;

		me->m_fillLevel++;
        //ReleaseResource(res_globalRingBuffer);
		return RC_SUCCESS;

	}
	else
	{
		return RC_ERROR_BUFFER_FULL;
	}

	return RC_SUCCESS;
}

/**
* Read the data present in the Ring buffer
* \param RB_t *const me : [IN/OUT] Ring Buffer Object
* \param void const* const pData : [OUT] Data read from the RingBuffer
* \return RC_t: RC_SUCCESS in case of no error else error code
*/ 
RC_t RB_get(RB_t *const me, RB_content_t *const data)
{
	if (me->m_fillLevel > 0)
	{
        //GetResource(res_globalRingBuffer);
		*data = me->m_pBuffer[me->m_readIdx];

		me->m_readIdx++;
		me->m_readIdx %= me->m_size;

		me->m_fillLevel--;
        //ReleaseResource(res_globalRingBuffer);
		return RC_SUCCESS;
	}
	else
	{
		return RC_ERROR_BUFFER_EMTPY;
	}
}

/**
* Function resets metadata of the RingBuffer to zero
* \param RB_t *const me : [IN/OUT] Ring Buffer Object
* \return RC_t: RC_SUCCESS in case of no error else error code
*/
RC_t RB_clear(RB_t *const me)
{
	me->m_fillLevel = 0;
	me->m_readIdx = 0;
	me->m_writeIdx = 0;

	return RC_SUCCESS;
}

/**
* Checks if protocols are available in the RingBuffer. This is required when there are multiple write
* operation happening and the events are lost before reading them
* \param RB_t *const me : [IN/OUT] Ring Buffer Object 
* \return boolean_t: TRUE in case of protocols available or return FALSE
*/
boolean_t RB_prots_available(RB_t *const me)
{
    if(me->m_fillLevel>0)
    return TRUE;
    
    else
    return FALSE;
    
}
