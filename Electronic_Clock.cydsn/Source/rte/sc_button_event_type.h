
/*
 * Filename: sc_button_event_type.h
 *
 * Author: Autogenerated by H-DA RTE Generator, (c) Prof. Fromm
 *
 * Description: Signal class for SO_Button_Event object (event leftbutton for short press and rightbutton for short / long press)
 */

#ifndef _H_DEFINE_SC_BUTTON_EVENT_TYPE
#define _H_DEFINE_SC_BUTTON_EVENT_TYPE

#include "project.h"
#include "global.h"
#include "rte_types.h"

/* USER CODE START SC_BUTTON_EVENT_INCLUDES */
    
#include "statemachine_cfg.h"
    

/* USER CODE END SC_BUTTON_EVENT_INCLUDES */



/**********************************************************************
 *       Type Definition for SC_BUTTON_EVENT signal    
 **********************************************************************/

/* USER CODE START SC_BUTTON_EVENT_USERDEFINITIONS */

typedef enum
    {
        Idle_state,
        Right_Button,
        Left_Button
    }
    Button_State;
    
 static Button_State Button__state = Idle_state;

/* USER CODE END SC_BUTTON_EVENT_USERDEFINITIONS */

typedef 
/* USER CODE START SC_BUTTON_EVENT_SIGNALDATADEFINITION */
struct
{
	Event_t ev;
} 
/* USER CODE END SC_BUTTON_EVENT_SIGNALDATADEFINITION */
SC_BUTTON_EVENT_data_t;

/* USER CODE START InitSC_BUTTON_EVENT */
//#error "Provide a sensible init value"
#define SC_BUTTON_EVENT_INIT_DATA ((SC_BUTTON_EVENT_data_t){EV_NONE})
/* USER CODE END InitSC_BUTTON_EVENT */


/**
 * Default IN driver API
 * \param SC_BUTTON_EVENT_data_t *const data : [OUT] scaled data read from the driver
 * \return RC_SUCCESS is all was ok, error code otherwise
 */
RC_t SC_BUTTON_EVENT_driverIn(SC_BUTTON_EVENT_data_t *const data);




/* USER CODE START SC_BUTTON_EVENT_USERFUNCTIONS */

/* USER CODE END SC_BUTTON_EVENT_USERFUNCTIONS */


#endif