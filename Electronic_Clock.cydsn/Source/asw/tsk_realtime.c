/*
 * Filename: tsk_realtime.c
 *
 * Author: Autogenerated by H-DA RTE Generator, (c) Prof. Fromm
 *
 * description: This task will contain all real time operations, e.g: CLOCK_input and CLOCK_control runnables
 * events: ev_1ms|ev_Button_OnData
 * mode: Cyclic and Event
 * name: tsk_realtime
 * shortname: realtime
 * signalpoolsRO: sp_common
 * signalpoolsRW: sp_common
 * tickEvent: ev_Button_OnData
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

#include "swc_input.h"
#include "swc_control.h"



/* USER CODE START TSK_REALTIME_USERDEFINITIONS */

/* USER CODE END TSK_REALTIME_USERDEFINITIONS */

/*******************************************************************************
 * Runnable Tables from Activation Engine
 *******************************************************************************/

/* Cyclic Table */

const RTE_cyclicTable_t RTE_cyclicActivationTable_tsk_realtime[] = {
	{ INPUT_Clock_Input_run, 50 },	//Runnable for  Button input events for left short and right short/long press
};
const uint16_t RTE_cyclicActivation_tsk_realtime_size = sizeof (RTE_cyclicActivationTable_tsk_realtime) / sizeof(RTE_cyclicTable_t); 

/* Event Table */
const RTE_eventTable_t RTE_eventActivationTable_tsk_realtime[] = {
    { CONTROL_Clock_Control_run, ev_Button_OnData },  //Runnable for Control runnable containing state machine
}; 
const uint16_t RTE_eventActivation_tsk_realtime_size = sizeof (RTE_eventActivationTable_tsk_realtime) / sizeof(RTE_eventTable_t);

/*******************************************************************************
 * Task Body
 *******************************************************************************/


/*
 * description: This task will contain all real time operations, e.g: CLOCK_input and CLOCK_control runnables
 * events: ev_1ms|ev_Button_OnData
 * mode: Cyclic and Event
 * name: tsk_realtime
 * shortname: realtime
 * signalpoolsRO: sp_common
 * signalpoolsRW: sp_common
 * tickEvent: ev_Button_OnData
 * timertickperiod: 1
 */
TASK(tsk_realtime)
{
	/* ticktime of the task */
	uint32_t ticktime = 0;
	
    EventMaskType ev = 0;
	
	/* USER CODE START TSK_REALTIME_INIT */

	/* USER CODE END TSK_REALTIME_INIT */
    
    while(1)
    {
        //Wait, read and clear the event
        WaitEvent(ev_1ms|ev_Button_OnData);
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
