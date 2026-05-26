/*
 * ringbuffer.h
 *
 *  Created on: 17.07.2025
 *      Author: SESA807379
 */

#ifndef SRC_RINGBUFFER_H_
#define SRC_RINGBUFFER_H_

#include <stdint.h>
#include <stdbool.h>

/**
 * \brief Return types for RTE and non RTE functions, to indicate the result of a operation
 */
typedef enum
{
	RC_SUCCESS              	=  0,                   			/**< \brief Function was successfully completed.                            	*/
	RC_ERROR                	= -1,                	   			/**< \brief Non specific error.                                             	*/
	RC_ERROR_NULL           	= -2,                		   		/**< \brief A pointer was NULL when a non-NULL pointer was expected.        	*/
	RC_ERROR_ZERO           	= -3,                   			/**< \brief A value was zero when no zero can be accepted.                  	*/
	RC_ERROR_MEMORY         	= -4,                   			/**< \brief Out of memory.                                                  	*/
	RC_ERROR_RANGE          	= -5,                   			/**< \brief A value was out of Range.                                       	*/
	RC_ERROR_OVERRUN        	= -6,                   			/**< \brief A value was too big.                                            	*/
	RC_ERROR_UNDERRUN       	= -7,                   			/**< \brief A value was too small                                           	*/
	RC_ERROR_BUFFER_FULL    	= -8,                   			/**< \brief A buffer was full.                                              	*/
	RC_ERROR_BUFFER_EMTPY   	= -9,                   			/**< \brief A buffer was empty.                                             	*/
	RC_ERROR_BUSY           	= -10,                  			/**< \brief A resource was busy.                                            	*/
	RC_ERROR_TIME_OUT       	= -11,                  			/**< \brief Something take too much time.                                   	*/
	RC_ERROR_OPEN           	= -12,                 				/**< \brief A device can't be opened.                                       	*/
	RC_ERROR_CHECKSUM       	= -13,                  			/**< \brief Wrong checksum.                                                 	*/
	RC_ERROR_READ_ONLY      	= -14,                  			/**< \brief Object is read only.                                            	*/
	RC_ERROR_WRITE_ONLY     	= -15,                  			/**< \brief Object is write only.                                           	*/
	RC_ERROR_INVALID        	= -16,                  			/**< \brief Object is invalid.                                              	*/
	RC_ERROR_READ_FAILS     	= -17,                  			/**< \brief Could not read from object.                                     	*/
	RC_ERROR_WRITE_FAILS    	= -18,                  			/**< \brief Could not write to the object.                                  	*/
	RC_ERROR_NOT_MATCH      	= -19,                  			/**< \brief Could not write to the object.								 	    */
	RC_ERROR_BAD_PARAM      	= -20,                 				/**< \brief Parameters passed to the function are invalid or illegal.           */
	RC_ERROR_BAD_DATA       	= -21,                  			/**< \brief Invalid global data which is required by the function.              */
	RC_ERROR_CANCELED       	= -22,                  			/**< \brief operation was canceled.                                             */
	RC_ERROR_INVALID_STATE  	= -23,                  			/**< \brief The operation can not be performed because of a FSM-state           */
    RC_ERROR_UNKNOWN        	= -24,                  			/**< \brief Unknown error.                                                      */
    RC_ERROR_NOT_IMPLEMENTED    = -25,                  			/**< \brief The requested functionality is not implemented.                     */
}RC_t;



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
bool if_RB_data_present(RB_t *const me);


#endif /* SRC_RINGBUFFER_H_ */
