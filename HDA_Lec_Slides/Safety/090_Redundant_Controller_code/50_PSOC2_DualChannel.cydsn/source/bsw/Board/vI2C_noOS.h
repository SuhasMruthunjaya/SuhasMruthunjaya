/**
 * \file 	vI2C_noOS.h
 * \author 	Thomas Barth	- Hochschule Darmstadt thomas.barth@h-da.de
 * \date 	25.06.2017
 * \version	0.2
 *
 * \brief virtualI2C queue interface without OS
 *
 *  Changelog:\n
 *  - 0.2   25.06.2017 Barth
 *            - Removed I2C speed option
 *  - 0.1   21.11.2016 Barth
 *            - Initial documentation
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

#ifndef VI2C_NO_OS_H_
#define VI2C_NO_OS_H_

#include "global.h"
    
/**
 * \brief vI2C flags
 */
typedef enum{
    vI2C_FLAG_N         =0,                     /**< \brief No flags. */
    vI2C_FLAG_FREE_M    =BIT(0),                /**< \brief free data pointer afer operation. Can only be used along with #vI2C_FLAG_WRITE*/
    vI2C_FLAG_READ      =BIT(1),                /**< \brief message is a read request. */
    vI2C_FLAG_WRITE     =BIT(2),                /**< \brief message is a write request. */
}vI2C_flags_t;
    

/**
 * \brief I2C state machine states
 *
 * The I2C module can either write or receive frames. A state machine is needed to check if the corresponding action succeeded.
 * \todo Maybe this can be used on a global scale in global.h
 */
typedef enum{
    vI2C_state_idle,                            /**< \brief HW is waiting for the next job. */
    vI2C_state_writing,                         /**< \brief HW is writing a frame. */
    vI2C_state_receiving                        /**< \brief HW is reading a frame. */
}vI2C_state_t;

/**
 * \brief I2C message structure
 */
typedef struct vI2C_msg_t vI2C_msg_t;
/**
 * \brief I2C message structure
 */
struct vI2C_msg_t{
    uint8_t                 slaveAddress;       /**< \brief I2C receiver address */
    uint8_t*                p_data;             /**< \brief pointer to message */
    uint32_t                cnt;                /**< \brief message length in bytes*/
    uint32_t                transfered;         /**< \brief number of bytes that are already transfered */
    vI2C_flags_t            flags;              /**< \brief message flags*/
    transmission_state_t    state;              /**< \brief transmission state */
    void (*p_callback)(vI2C_msg_t);             /**< \brief callback function in case of complete or error*/
    void*                   p_usr_data;         /**< \brief pointer to user data */   
};

/**
 * \brief Init the I2C Hardware and initialize the ringbuffer/queue
 *
 * \return  #RC_SUCCESS
 */
RC_t vI2C_init();

/**
 * \brief Send I2C write or read request to I2C Slave
 *
 * \param   slaveAddress      I2C Slave address
 * \param   p_data            Write: pointer to data that shall be written to the slave. Read: Data container for data received by the slave.
 * \param   cnt               Number of bytes that shall be written/read.
 * \param   flags             flags for the transfer, see #vI2C_flags_t.
 * \param   p_state_handle    Optional transfer state handle, see #transmission_state_t. Can be used to check the state of transfer
 * \param   p_callback        Optional callback function that is called if the transfer suceeded or failed. Transfer details are passed as #vI2C_msg_t.
 * \param   p_usr_data        Optional pointer to user-data that is also passed to the callback function.
 * \return  #RC_SUCCESS if the request was passed to the queue. 
            #RC_ERROR_BUFFER_FULL if the queue is full.
            #RC_ERROR_BAD_PARAM if there is a problem with the parameters.
            #RC_ERROR_INVALID_STATE if the vI2C task has not been started.
 * \note    this function only adds the request to the queue. Callbacks or handlers need to be used to ensure the operation succeeded!
 */
RC_t vI2C_send(uint8_t slaveAddress, uint8_t* p_data, uint8_t cnt, vI2C_flags_t flags, void (*p_callback)(vI2C_msg_t), void* p_usr_data);
    
#endif //VI2C_NO_OS_H_
/* [] END OF FILE */