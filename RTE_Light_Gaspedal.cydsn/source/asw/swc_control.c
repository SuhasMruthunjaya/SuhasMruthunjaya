/*
 * Filename: swc_control.c
 *
 * Author: Autogenerated by H-DA RTE Generator, (c) Prof. Fromm
 *
 * description: To calculate the engine speed from the incoming joystick commands
 * name: swc_control
 * shortname: control
 *
 */

#include "project.h"
#include "stdlib.h"
#include "global.h"
#include "rte.h"
#include "rte_types.h"
#include "swc_control.h"
#include "watchdog.h"


/* USER CODE START SWC_CONTROL_INCLUDE */

/* USER CODE END SWC_CONTROL_INCLUDE */


#include "sp_common.h"

/* USER CODE START SWC_CONTROL_USERDEFINITIONS */

/* USER CODE END SWC_CONTROL_USERDEFINITIONS */



/*
 * component: swc_control
 * cycletime: 0
 * description: Control representing Runnable
 * events: ev_joystick_onData
 * name: CONTROL_calcControl_run
 * shortname: calcControl
 * signalIN: so_joystick
 * signalOUT: so_engine_speed
 * task: tsk_realtime
 */
void CONTROL_calcControl_run(RTE_event ev)
{
	
	/* USER CODE START CONTROL_calcControl_run */
    
    
    SC_SPEED_data_t engine_speed;
    
    
    
/*    char display[sizeof(int)*8+1];
      itoa(SO_ENGINE_SPEED_signal.age,display,10);
      UART_LOG_PutString("\r");
      UART_LOG_PutString(display);
 */   
    
    if(SO_JOYSTICK_signal.age < 100)
    {
        
    SC_JOYSTICK_data_t joystick_value = RTE_SC_JOYSTICK_get(&SO_JOYSTICK_signal);
    uint8_t joystickX_value = joystick_value.x;
    
        if(joystickX_value > 128)
        {
            engine_speed.value = 0;
            RTE_SC_SPEED_set(&SO_ENGINE_SPEED_signal, engine_speed);
        }
        else
        {
            engine_speed.value = 2*(joystickX_value);
            RTE_SC_SPEED_set(&SO_ENGINE_SPEED_signal, engine_speed);
        }
    }
    else
    {
        engine_speed.value = 0;
        RTE_SC_SPEED_set(&SO_ENGINE_SPEED_signal, engine_speed);
    }
    
     WD_Alive(3);
     
    /* USER CODE END CONTROL_calcControl_run */
}

/* USER CODE START SWC_CONTROL_FUNCTIONS */

/* USER CODE END SWC_CONTROL_FUNCTIONS */

