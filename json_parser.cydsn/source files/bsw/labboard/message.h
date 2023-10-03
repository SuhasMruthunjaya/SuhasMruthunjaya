/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/

/* [] END OF FILE */
/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/

/* [] END OF FILE */
#ifndef MESSAGE_H_
#define MESSAGE_H_

#include "global.h"
#include "project.h"
#include "drawer.h"


//typedef uint8_t RB_content_t;

    
typedef struct
{
     uint16_t m_size;
     void* m_pBuffer;
    
    
} message_t;


typedef struct {
	EventMaskType m_ev;
    TaskType m_task;
    message_t* msgbox_buffer;
    uint16_t size;
	uint16_t m_readIdx;
	uint16_t m_writeIdx;
	uint16_t m_fillLevel;
} MSG_messagebox_t;

/**
* Initialises the ringbuffer and sets up the memory for the metadata
* \param MSG_messagebox_t *const me : [IN/OUT] Message Box Object
* \param uint16_t const size : [IN] Size of the ringbuffer
* \param EventMaskType const ev : [IN] Event which will be
fired in case of a new message
* \param TaskType const task : [IN] Receiver task of the
event
* \return RC_t: RC_SUCCESS in case of no error else error code
*/
RC_t MSG_init(MSG_messagebox_t *const me, uint16_t const size, EventMaskType const ev, TaskType const task);

/**
* Send a message by creating a temporary transfer buffer,
* copying the data into this buffer and firing an event
* to the receiver task
* \param MSG_messagebox_t *const me : [IN/OUT] Message Box Object
* \param void const* const pData : [IN] Data to be transmitted
* \param uint16_t const size : [IN] Size of the transmitted
data
* \return RC_t: RC_SUCCESS in case of no error else error code
*/
RC_t MSG_sendMessage(MSG_messagebox_t *const me, void const* const
pData, uint16_t const size);
/**
* Returns the size of the next message in the buffer.
* Required for providing storage on the receiver side
* \param MSG_messagebox_t *const me : [IN/OUT] Message Box Object
* \param uint16_t *const size : [OUT] Size of the next message, 0 in case of no message
* \return RC_t: RC_SUCCESS in case of no error else error code
*/
RC_t MSG_getSizeOfNextMessage(MSG_messagebox_t *const me, uint16_t
*const size);
/**
* Wait for the next message (using OS services)
* \param MSG_messagebox_t *const me : [IN/OUT] Message Box Object
* \return RC_t: RC_SUCCESS in case of no error else error code
*/
RC_t MSG_waitNextMessage(MSG_messagebox_t *const me);
/**
* Reads the message from the transfer buffer and
* releases the allocated memory
* \param MSG_messagebox_t *const me : [IN/OUT] Message Box Object
* \param void *const pData : [OUT] Pointer to the memory
for storing the received message
* \return RC_t: RC_SUCCESS in case of no error else error code
*/
RC_t MSG_receiveMessage(MSG_messagebox_t *const me, void* pData,
uint16_t const size);

/**
* Checks whether MSG object is still present in the Message Box.
* \param MSG_messagebox_t *const me : [IN/OUT] Message Box Object
* \return boolean_t: false in case of no data present else true
*/

boolean_t if_data_present(MSG_messagebox_t *const me);

/**
* Prints the recieved message object content
* \param Drawer_t* const me: [IN] Drawer object
* \return RC_t: RC_SUCCESS in case of no error else error code
*/

RC_t printdbg_msg(Drawer_t* const me);


#endif /* MESSAGE_H_ */
