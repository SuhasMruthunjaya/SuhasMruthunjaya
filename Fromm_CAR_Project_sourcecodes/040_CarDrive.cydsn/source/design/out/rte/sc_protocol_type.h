
/*
 * Filename: sc_protocol_type.h
 *
 * Author: Autogenerated by H-DA RTE Generator, (c) Prof. Fromm
 *
 * Description: XBee protocol from remote
 */

#ifndef _H_DEFINE_SC_PROTOCOL_TYPE
#define _H_DEFINE_SC_PROTOCOL_TYPE

#include "project.h"
#include "global.h"
#include "rte_types.h"

/* USER CODE START SC_PROTOCOL_INCLUDES */
#include "ringbuffer.h"
/* USER CODE END SC_PROTOCOL_INCLUDES */



/**********************************************************************
 *       Type Definition for SC_PROTOCOL signal    
 **********************************************************************/

/* USER CODE START SC_PROTOCOL_USERDEFINITIONS */

typedef enum{
	PROT_MID__NONE			=  0,       /**<\brief undefined protocol */
	PROT_MID__CONNECT 		= 'C',      /**<\brief connection related protocol */
	PROT_MID__JOYSTICK 		= 'J',      /**<\brief joystick data protocol */

}PROTOCOL_mid_t;

/* Feature Identifiers */
typedef enum{
    PROT_FID_Activate   = 'A',       /**<\brief Activate Feature (remote) */
    PROT_FID_Brake      = 'B',       /**<\brief brake pressed (remote) */
    PROT_FID_Connect    = 'C',       /**<\brief request connection (remote), confirm connection (car) */
    PROT_FID_Feature    = 'F',       /**<\brief request list of features (remote), provide features (car) */
    PROT_FID_Disconnect = 'D',       /**<\brief request disconnect (remote), confirm disconnect (car) */
    PROT_FID_Joystick   = 'J',       /**<\brief joystick data package (remote) */
	PROT_FID_Present	= 'P',       /**<\brief request car identifier (remote), confirm present (car) */
    PROT_FID_Reset      = 'R',       /**<\brief request state machine reset without answer (remote) */
    PROT_FID_Stop       = 'S',       /**<\brief request emergency stop (remote) */
}PROTOCOL_fid_t;

typedef enum
{
    PROT_sender_broadcast = '*',     /**<\brief broadcast id */
    PROT_sender_car   =  'C',        /**<\brief car id */
    PROT_sender_remote = 'R',        /**<\brief remote id */
    
} PROTOCOL_sender_t;

    
    
/* Protocol specific globals */
#define PROTOCOL_SIZERXBUF          100     /*!< Size of the UART reception ringbuffer */
#define PROTOCOL_PAYLOAD_SIZE 		50		/*!< Payload max 50 byte (Feature List) */


#define PROTOCOL_EOP1_VALUE 		0x0D    /*!< EOP Character 1 - must be public as it is required in ISR*/
#define PROTOCOL_EOP2_VALUE 		0x0E    /*!< EOP Character 1 - must be public as it is required in ISR*/
   
/* USER CODE END SC_PROTOCOL_USERDEFINITIONS */

typedef 
/* USER CODE START SC_PROTOCOL_SIGNALDATADEFINITION */
struct
{
    PROTOCOL_mid_t  m_mid;                             /**< \brief Protocol ID, first byte in protocol */
    PROTOCOL_fid_t  m_fid;                             /**<\ brief feature identifier */
    uint8_t         m_length;                          /**<\ length of the valid payload */
    uint8_t         m_payload[PROTOCOL_PAYLOAD_SIZE];  /**<\ payload */
} 
/* USER CODE END SC_PROTOCOL_SIGNALDATADEFINITION */
SC_PROTOCOL_data_t;

/* USER CODE START InitSC_PROTOCOL */
#define SC_PROTOCOL_INIT_DATA ((SC_PROTOCOL_data_t){0})
/* USER CODE END InitSC_PROTOCOL */


/**
 * Default IN driver API
 * \param SC_PROTOCOL_data_t *const data : [OUT] scaled data read from the driver
 * \return RC_SUCCESS is all was ok, error code otherwise
 */
RC_t SC_PROTOCOL_driverIn(SC_PROTOCOL_data_t *const data);



/**
 * Default OUT driver API
 * \param const SC_PROTOCOL_data_t  *const data : [IN] signal data for the driver, will be scaled in this function
 * \return RC_SUCCESS is all was ok, error code otherwise
 */
RC_t SC_PROTOCOL_driverOut(const SC_PROTOCOL_data_t  *const data);


/* USER CODE START SC_PROTOCOL_USERFUNCTIONS */

/**
 * Physical buffer (array) for the ringbuffer
 */
extern uint8_t PROTOCOL_uartBuffer[PROTOCOL_SIZERXBUF];

/**
 * Global ringbuffer object, required in the ISR and driver
 */
extern ringbuffer_hdl_t PROTOCOL_rx_buffer;

/**
 * As the sender and receiver possibly do not start at the same time and we might suffer from boot-bytes, 
 * all bytes are ignored until we find the first true byte in the sequence
 * this concept is also used for resynchronisation
 * \param uint8_t data  : IN Byte currently received
 * \ return: TRUE if system is in sync, false otherwise
 */
boolean_t PROTOCOL_SyncProtocol(uint8_t data);

/**
 * In case a transmission error occurs, the system shall wait for the next valid protocol
 * For this, we set the corresponding flag to FALSE again
 */
void PROTOCOL_UnsyncProtocol();

/* USER CODE END SC_PROTOCOL_USERFUNCTIONS */


#endif