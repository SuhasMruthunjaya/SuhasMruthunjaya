#ifndef RINGBUFFER_H_
#define RINGBUFFER_H_

#include "global.h"
#include "project.h"


typedef uint8_t RB_content_t;

typedef struct {
	RB_content_t* m_pBuffer;
	uint16_t m_size;
	uint16_t m_readIdx;
	uint16_t m_writeIdx;
	uint16_t m_fillLevel;
} RB_t;

/**
* Initialises the ringbuffer and sets up the memory for the metadata
* \param RB_t *const me : [IN/OUT] Ringbuffer object
* \param uint16_t const size : [IN] Size of the ringbuffer
* \return RC_t: RC_SUCCESS in case of no error else error code
*/
RC_t RB_init(RB_t *const me, uint32_t size);

/**
* Free the ringbuffer
* \param RB_t *const me : [IN/OUT] Ringbuffer object
* \return RC_t: RC_SUCCESS in case of no error else error code
*/

RC_t RB_deinit(RB_t *const me);

/**
* Puts the data into the ringbuffer character by character
* \param RB_t *const me : [IN/OUT] Ringbuffer object
* \param RB_content_t data : [IN] Data that needs to be written into the buffer
* \return RC_t: RC_SUCCESS in case of no error else error code
*/

RC_t RB_put(RB_t *const me, RB_content_t data);

/**
*  Gets the data from the ringbuffer.
* \param RB_t *const me : [IN/OUT] Ringbuffer object
* \param RB_content_t data : [OUT] Data that is recieved from the buffer 
* \return RC_t: RC_SUCCESS in case of no error else error code
*/

RC_t RB_get(RB_t *const me, RB_content_t *const data);

/**
*  Clears the Ringbuffer
* \param RB_t *const me : [IN/OUT] Ringbuffer object
* \return RC_t: RC_SUCCESS in case of no error else error code
*/

RC_t RB_clear(RB_t *const me);

/**
* Finds out if data is still present in the ringbuffer
* \param RB_t *const me : [IN/OUT] Ringbuffer object
* \return boolean_t: false in case of no data present else true
*/
boolean_t if_RB_data_present(RB_t *const me);





#endif /* RINGBUFFER_H_ */
