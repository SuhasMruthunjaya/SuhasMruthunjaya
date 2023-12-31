/*
 * Filename: tsk_realtime.c
 *
 * Author: Autogenerated by H-DA RTE Generator, (c) Prof. Fromm
 *
 * description: This task will contain all real time operations, e.g: joystick, control, Engine and Brake
 * events: ev_1ms|ev_engine_speed_onData|ev_joystick_onData
 * mode: Cyclic and Event
 * name: tsk_realtime
 * shortname: realtime
 * signalpoolsRO: sp_common
 * signalpoolsRW: sp_common
 * tickEvent: ev_1ms
 * timertickperiod: 1
 *
 */

#include "project.h"
#include "global.h"
#include "rte.h"
#include "rte_types.h"
#include "tsk_realtime.h"



/* USER CODE START TSK_REALTIME_INCLUDE */

/* USER CODE END TSK_REALTIME_INCLUDE */

#include "swc_joystick.h"
#include "swc_control.h"
#include "swc_engine.h"
#include "swc_brake.h"



/* USER CODE START TSK_REALTIME_USERDEFINITIONS */

/* USER CODE END TSK_REALTIME_USERDEFINITIONS */

/*******************************************************************************
 * Runnable Tables from Activation Engine
 *******************************************************************************/

/* Cyclic Table */

const RTE_cyclicTable_t RTE_cyclicActivationTable_tsk_realtime[] = {
	{ JOYSTICK_readJoystick_run, 10 },	//Joystick representing Runnable
	{ ENGINE_setEngine_run, 100 },	//Engine representing Runnable
};
const uint16_t RTE_cyclicActivation_tsk_realtime_size = sizeof (RTE_cyclicActivationTable_tsk_realtime) / sizeof(RTE_cyclicTable_t); 

/* Event Table */
const RTE_eventTable_t RTE_eventActivationTable_tsk_realtime[] = {
    { CONTROL_calcControl_run, ev_joystick_onData },  //Control representing Runnable
    { BRAKE_setBrakeLight_run, ev_engine_speed_onData },  //Breake representing Runnable
}; 
const uint16_t RTE_eventActivation_tsk_realtime_size = sizeof (RTE_eventActivationTable_tsk_realtime) / sizeof(RTE_eventTable_t);

/*******************************************************************************
 * Task Body
 *******************************************************************************/


/*
 * description: This task will contain all real time operations, e.g: joystick, control, Engine and Brake
 * events: ev_1ms|ev_engine_speed_onData|ev_joystick_onData
 * mode: Cyclic and Event
 * name: tsk_realtime
 * shortname: realtime
 * signalpoolsRO: sp_common
 * signalpoolsRW: sp_common
 * tickEvent: ev_1ms
 * timertickperiod: 1
 */
TASK(tsk_realtime)
{
	/* ticktime of the task */
	uint32_t ticktime = 0;
	
    EventMaskType ev = 0;
	
	/* USER CODE START TSK_REALTIME_INIT */
    
    RTE_SC_SPEED_init(&SO_ENGINE_SPEED_signal);
    RTE_SC_PWM_init(&SO_RGB_LED_signal);
    
	/* USER CODE END TSK_REALTIME_INIT */
    
    while(1)
    {
        //Wait, read and clear the event
        WaitEvent(ev_1ms|ev_engine_speed_onData|ev_joystick_onData);
        GetEvent(tsk_realtime,&ev);
        ClearEvent(ev);
    
		/* USER CODE START TSK_REALTIME_TASKBOBY_PRE */

		/* USER CODE END TSK_REALTIME_TASKBODY_PRE */
        
        
        if (ev & ev_1ms){
            //Process Cyclic table on tick
            
            RTE_ProcessCyclicTable(RTE_cyclicActivationTable_tsk_realtime, RTE_cyclicActivation_tsk_realtime_size, ticktime);

			ticktime += 1;
			if (ticktime > 0xFFFFFF00) ticktime = 0;

		};
		
		//Process data driven events
		RTE_ProcessEventTable(RTE_eventActivationTable_tsk_realtime, RTE_eventActivation_tsk_realtime_size, ev);
		
		/* USER CODE START TSK_REALTIME_TASKBODY_POST */

		/* USER CODE END TSK_REALTIME_TASKBODY_POST */
        
    }
	
	//Just in Case
	TerminateTask();
}


/*******************************************************************************
 * Interrupt Service Routines
 *******************************************************************************/

/* USER CODE START TSK_REALTIME_ISR */

/* USER CODE END TSK_REALTIME_ISR */

