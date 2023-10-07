/*
 * Event_Ringbuffer.h
 *
 *  Created on: 15.09.2022
 *      Author: Fromm
 */

#ifndef EVENT_RINGBUFFER_H_
#define EVENT_RINGBUFFER_H_

#include "project.h"
#include "global.h"
typedef uint8_t RB_content_t;

//Ring Buffer object attributes
typedef struct {
	RB_content_t* m_pBuffer; 
	uint16_t m_size;
	uint16_t m_readIdx;
	uint16_t m_writeIdx;
	uint16_t m_fillLevel;
} RB_t;


/**
* Initialises the ringbuffer and sets up the memory for the metadata
* \param RB_t *const me : [IN/OUT] Ring Buffer Object
* \param uint32_t const size : [IN] Size of the Ring Buffer
* \return RC_t: RC_SUCCESS in case of no error else error code
*/
RC_t RB_init(RB_t *const me, uint32_t size);

/**
* Frees up the memory created during initialisation
* \param RB_t *const me : [IN/OUT] Ring Buffer Object
* \return RC_t: RC_SUCCESS in case of no error else error code
*/
RC_t RB_deinit(RB_t *const me);

/**
* Write the data into the Ring buffer
* \param RB_t *const me : [IN/OUT] Ring Buffer Object
* \param void const* const pData : [IN] Data to be written in the RingBuffer
* \return RC_t: RC_SUCCESS in case of no error else error code
*/ 
RC_t RB_put(RB_t *const me, RB_content_t data);

/**
* Read the data present in the Ring buffer
* \param RB_t *const me : [IN/OUT] Ring Buffer Object
* \param void const* const pData : [OUT] Data read from the RingBuffer
* \return RC_t: RC_SUCCESS in case of no error else error code
*/ 
RC_t RB_get(RB_t *const me, RB_content_t *const data);

/**
* Function resets metadata of the RingBuffer to zero
* \param RB_t *const me : [IN/OUT] Ring Buffer Object
* \return RC_t: RC_SUCCESS in case of no error else error code
*/
RC_t RB_clear(RB_t *const me);

/**
* Checks if protocols are available in the RingBuffer. This is required when there are multiple write
* operation happening and the events are lost before reading them
* \param RB_t *const me : [IN/OUT] Ring Buffer Object 
* \return boolean_t: TRUE in case of protocols available or return FALSE
*/
boolean_t RB_prots_available(RB_t *const me);


#endif /* RINGBUFFER_H_ */
