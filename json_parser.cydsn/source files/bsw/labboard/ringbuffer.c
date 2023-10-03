/*
 * Ringbuffer.c
 *
 *  Created on: 15.09.2022
 *      Author: Fromm
 */

#include <stdlib.h>
#include "ringbuffer.h"

//Todo:error checking at many places


/**
* Initialises the ringbuffer and sets up the memory for the metadata
* \param RB_t *const me : [IN/OUT] Ringbuffer object
* \param uint16_t const size : [IN] Size of the ringbuffer
* \return RC_t: RC_SUCCESS in case of no error else error code
*/
RC_t RB_init(RB_t *const me, uint32_t size)
{   
  
	me->m_size = size;
	me->m_pBuffer = (RB_content_t*)malloc(size * sizeof(RB_content_t));

	return RB_clear(me);
    

}

/**
* Free the ringbuffer
* \param RB_t *const me : [IN/OUT] Ringbuffer object
* \return RC_t: RC_SUCCESS in case of no error else error code
*/
RC_t RB_deinit(RB_t *const me)
{
    
	free(me->m_pBuffer);

	return RC_SUCCESS;
    
}

/**
* Puts the data into the ringbuffer character by character
* \param RB_t *const me : [IN/OUT] Ringbuffer object
* \param RB_content_t data : [IN] Data that needs to be written into the buffer
* \return RC_t: RC_SUCCESS in case of no error else error code
*/

RC_t RB_put(RB_t *const me, RB_content_t data)
{   
    
    if (me->m_fillLevel < me->m_size)
	{   
        GetResource(res_ringbuffer);
		me->m_pBuffer[me->m_writeIdx] = data;

		me->m_writeIdx++;
		me->m_writeIdx %= me->m_size;

		me->m_fillLevel++;
        
        ReleaseResource(res_ringbuffer);
		return RC_SUCCESS;

	}
	else
	{
		return RC_ERROR_BUFFER_FULL;
	}
    

}


/**
*  Gets the data from the ringbuffer.
* \param RB_t *const me : [IN/OUT] Ringbuffer object
* \param RB_content_t data : [OUT] Data that is recieved from the buffer 
* \return RC_t: RC_SUCCESS in case of no error else error code
*/

RC_t RB_get(RB_t *const me, RB_content_t *const data)
{
    
    
	if (me->m_fillLevel > 0)
	{
        
        GetResource(res_ringbuffer);
        
		*data = me->m_pBuffer[me->m_readIdx];

		me->m_readIdx++;
		me->m_readIdx %= me->m_size;

		me->m_fillLevel--;
        
        ReleaseResource(res_ringbuffer);

		return RC_SUCCESS;
	}
	else
	{
		return RC_ERROR_BUFFER_EMTPY;
	}
   
}

/**
*  Clears the Ringbuffer
* \param RB_t *const me : [IN/OUT] Ringbuffer object
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
* Finds out if data is still present in the ringbuffer
* \param RB_t *const me : [IN/OUT] Ringbuffer object
* \return boolean_t: false in case of no data present else true
*/
boolean_t if_RB_data_present(RB_t *const me)
{
    if((me->m_fillLevel) > 0)
    return TRUE;
    else 
    return FALSE;
}