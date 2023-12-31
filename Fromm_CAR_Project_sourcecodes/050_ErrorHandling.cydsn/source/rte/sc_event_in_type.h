
/*
 * Filename: sc_event_in_type.h
 *
 * Author: Autogenerated by H-DA RTE Generator, (c) Prof. Fromm
 *
 * Description: Event from remote to application
 */

#ifndef _H_DEFINE_SC_EVENT_IN_TYPE
#define _H_DEFINE_SC_EVENT_IN_TYPE

#include "project.h"
#include "global.h"
#include "rte_types.h"

/* USER CODE START SC_EVENT_IN_INCLUDES */

#include "sc_protocol_type.h"

/* USER CODE END SC_EVENT_IN_INCLUDES */



/**********************************************************************
 *       Type Definition for SC_EVENT_IN signal    
 **********************************************************************/

/* USER CODE START SC_EVENT_IN_USERDEFINITIONS */

typedef enum
{
	//Error cases
    EV_IN_NoEvent,

    //Connection Related Events
    EV_IN_Reset,
	EV_IN_Present,
    EV_IN_Connect,
    EV_IN_Disconnect,
    EV_IN_RequestFeature,
    EV_IN_ActivateFeature,

    //Driving related Events
    EV_IN_Joystick,
    EV_IN_Stop,

} 
EVENT_in_t;
    
#define EVENT_PAYLOADSIZE PROTOCOL_PAYLOAD_SIZE

/* USER CODE END SC_EVENT_IN_USERDEFINITIONS */

typedef 
/* USER CODE START SC_EVENT_IN_SIGNALDATADEFINITION */
struct
{
    EVENT_in_t m_ev;
    uint8_t m_lengthPayload;
    uint8_t m_payload[EVENT_PAYLOADSIZE];
} 
/* USER CODE END SC_EVENT_IN_SIGNALDATADEFINITION */
SC_EVENT_IN_data_t;

/* USER CODE START InitSC_EVENT_IN */

#define SC_EVENT_IN_INIT_DATA ((SC_EVENT_IN_data_t){})
/* USER CODE END InitSC_EVENT_IN */





/* USER CODE START SC_EVENT_IN_USERFUNCTIONS */

/* USER CODE END SC_EVENT_IN_USERFUNCTIONS */


#endif