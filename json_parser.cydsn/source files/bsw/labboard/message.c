#include <message.h>
#include "drawer.h"
#include <stdlib.h>


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
RC_t MSG_init(MSG_messagebox_t *const me, uint16_t const size, EventMaskType const ev, TaskType const task)
{   
    me->size = size;
    me->msgbox_buffer = (message_t*)malloc(me->size * sizeof(message_t));
    me->m_ev = ev;
    me->m_task = task;
    me->m_fillLevel = 0;
    me->m_readIdx = 0;
    me->m_writeIdx = 0;
    
    return RC_SUCCESS;
}
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
pData, uint16_t const size)
{
   if(me->m_fillLevel < me->size)
    {   
        GetResource(res_msgbuffer);
         
        me->msgbox_buffer[me->m_writeIdx].m_pBuffer = (uint8_t*)malloc(size);
        
        void* drawer_object = me->msgbox_buffer[me->m_writeIdx].m_pBuffer;
        me->msgbox_buffer[me->m_writeIdx].m_size = size;
        
        for(int i=0; i< size; i++)
        {
        ((uint8_t*)drawer_object)[i] = ((uint8_t*)pData)[i];
        }
        
        
        me->m_writeIdx++;
        me->m_writeIdx %= me->size;

		me->m_fillLevel++;
        
        ReleaseResource(res_msgbuffer);
        
        SetEvent(me->m_task,me->m_ev);
        
        return RC_SUCCESS; 
        
    }
    else
    return RC_ERROR_BUFFER_FULL;;    
}
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
RC_t MSG_waitNextMessage(MSG_messagebox_t *const me)
{ 
    EventMaskType ev = 0;
    
    WaitEvent(me->m_ev);
    GetEvent(me->m_task,&ev);
    ClearEvent(ev);    
    
    if(ev & me->m_ev)
    {
  //  UART_LOG_PutString("event_came\r");
    return RC_SUCCESS;
    }
    else
    return RC_ERROR_INVALID;
    
}
/**
* Reads the message from the transfer buffer and
* releases the allocated memory
* \param MSG_messagebox_t *const me : [IN/OUT] Message Box Object
* \param void *const pData : [OUT] Pointer to the memory
for storing the received message
* \return RC_t: RC_SUCCESS in case of no error else error code
*/
RC_t MSG_receiveMessage(MSG_messagebox_t *const me, void* pData,
uint16_t const size)
{
    if (me->m_fillLevel > 0)
	{
       
        GetResource(res_msgbuffer);
        for(int i=0; i<size; i++)
        {
            ((uint8_t*)pData)[i] = ((uint8_t*)(me->msgbox_buffer[me->m_readIdx].m_pBuffer))[i];
             
        }
        free(me->msgbox_buffer[me->m_readIdx].m_pBuffer);
        me->m_readIdx++;
		me->m_readIdx %= me->size;

		me->m_fillLevel--;
        
        ReleaseResource(res_msgbuffer);

		return RC_SUCCESS;
	}
	else
	{
		return RC_ERROR_BUFFER_EMTPY;
	}
}

/**
* Checks whether MSG object is still present in the Message Box.
* \param MSG_messagebox_t *const me : [IN/OUT] Message Box Object
* \return boolean_t: false in case of no data present else true
*/

boolean_t if_data_present(MSG_messagebox_t *const me)
{   
    if((me->m_fillLevel) > 0)
    return TRUE;
    else 
    return FALSE;
}

/**
* Prints the recieved message object content
* \param Drawer_t* const me: [IN] Drawer object
* \return RC_t: RC_SUCCESS in case of no error else error code
*/
RC_t printdbg_msg(Drawer_t* const me)
{
            char display[50];
            UART_LOG_PutString("reciever");
            UART_LOG_PutString("\r");
            itoa(me->command,display,10);
            UART_LOG_PutString(display);
            UART_LOG_PutString("\r");
            itoa(me->data.coordinate[0],display,10);
            UART_LOG_PutString(display);
            UART_LOG_PutString("\r");
            itoa(me->data.coordinate[1],display,10);
            UART_LOG_PutString(display);
            UART_LOG_PutString("\r");
            itoa(me->data.coordinate[2],display,10);
            UART_LOG_PutString(display);
            UART_LOG_PutString("\r");
            itoa(me->data.coordinate[3],display,10);
            UART_LOG_PutString(display);
            UART_LOG_PutString("\r");
}