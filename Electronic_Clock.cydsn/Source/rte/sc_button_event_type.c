/*
 * Filename: sc_button_event_type.c
 *
 * Author: Autogenerated by H-DA RTE Generator, (c) Prof. Fromm
 *
 * description: Signal class for SO_Button_Event object (event leftbutton for short press and rightbutton for short / long press)
 * name: sc_Button_Event
 * shortname: Button_Event
 *
 */

#include "project.h"
#include "global.h"
#include "rte.h"
#include "rte_types.h"
#include "sc_button_event_type.h"
#include "stdlib.h"



/* USER CODE START SC_BUTTON_EVENT_INCLUDE */

/* USER CODE END SC_BUTTON_EVENT_INCLUDE */




/* USER CODE START SC_BUTTON_EVENT_USERDEFINITIONS */

/* USER CODE END SC_BUTTON_EVENT_USERDEFINITIONS */


/*****************************************************************************************
 *************** Port Wrapper Implementation for SC_BUTTON_EVENT signal  ****************
 *****************************************************************************************/
 
 

/**
 * Default IN driver API
 */
inline RC_t SC_BUTTON_EVENT_driverIn(SC_BUTTON_EVENT_data_t *const data)
{
	/* USER CODE START driverInSC_BUTTON_EVENT */
//#error "Add your code here"

	//Read data from the MCAL driver

  /*  
    if(Button_left_Read() == 1)
    data->ev = EV_KEYLEFT;
    else if(Button_right_Read() == 1)
    data->ev = EV_KEYRIGHT;
    else
    data->ev = EV_NONE;
 */  
    static uint16_t timer_count;
    static int16_t count;
    
    data->ev = EV_NONE;
    switch(Button__state)
    {
        case Idle_state:
        {
            if(Button_left_Read() == 1)
            {
                
               // UART_LOG_PutString("Left button is pressed ( InDriver)");
                data->ev = EV_KEYLEFT;
                Button__state = Left_Button;
            }
            else if(Button_right_Read() == 1)
            {
                data->ev = EV_KEYRIGHT;
                Button__state = Right_Button;
            }
            break;
        }
        case Left_Button:
        {
            if(Button_left_Read() == 0)
            {
                data->ev = EV_NONE;
                Button__state = Idle_state;
            }
            else if(Button_left_Read() == 1)
            {
                data->ev = EV_NONE;
            }
            break;
        }
        case Right_Button:
        {
            count++;
            if((count < 6) && (Button_right_Read() == 0))
            {
                data->ev = EV_NONE;
                Button__state = Idle_state;
                count = 0;
            }
             else if((count < 6) && (Button_right_Read() == 1))
            {
                data->ev = EV_NONE;
            }
            else if((count > 6) && (Button_right_Read() == 1))
            {
                data->ev = EV_KEYRIGHTLONGPRESS;
                //Button__state = Idle_state;
                count++;
            }
            else if((count > 6) && (Button_right_Read() == 0))
            {
                data->ev = EV_NONE;
                Button__state = Idle_state;
                count=0;
            }
        }
        
    }
    
    timer_count++;
    
    if((timer_count % 5) == 0)
    {
        data->ev = EV_250MS;
    }
    if((timer_count % 1200)==0)
    {
        data->ev = EV_1MIN;
        timer_count = 0;
    }
    
    
	//Scale it to the application type

	return RC_SUCCESS;
	/* USER CODE END driverInSC_BUTTON_EVENT */
}



