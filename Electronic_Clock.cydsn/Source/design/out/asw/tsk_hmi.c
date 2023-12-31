/*
 * Filename: tsk_hmi.c
 *
 * Author: Autogenerated by H-DA RTE Generator, (c) Prof. Fromm
 *
 * description: Task for displaying the clock data on TFT display. It is a long runnable, hence it is kept as a seperate task
 * events: 
 * mode: Cyclic
 * name: tsk_HMI
 * shortname: HMI
 * signalpoolsRO: sp_common
 * signalpoolsRW: sp_common
 * tickEvent: 0
 * timertickperiod: 1
 *
 */

#include "project.h"
#include "global.h"
#include "rte.h"
#include "rte_types.h"
#include "tsk_hmi.h"



/* USER CODE START TSK_HMI_INCLUDE */

/* USER CODE END TSK_HMI_INCLUDE */

#include "swc_display.h"



/* USER CODE START TSK_HMI_USERDEFINITIONS */

/* USER CODE END TSK_HMI_USERDEFINITIONS */

/*******************************************************************************
 * Runnable Tables from Activation Engine
 *******************************************************************************/

/* Cyclic Table */

const RTE_cyclicTable_t RTE_cyclicActivationTable_tsk_hmi[] = {
	{ DISPLAY_Clock_Display_run, 250 },	//Runnable for HMI runnable 
};
const uint16_t RTE_cyclicActivation_tsk_hmi_size = sizeof (RTE_cyclicActivationTable_tsk_hmi) / sizeof(RTE_cyclicTable_t); 


/*******************************************************************************
 * Task Body
 *******************************************************************************/


/*
 * description: Task for displaying the clock data on TFT display. It is a long runnable, hence it is kept as a seperate task
 * events: 
 * mode: Cyclic
 * name: tsk_HMI
 * shortname: HMI
 * signalpoolsRO: sp_common
 * signalpoolsRW: sp_common
 * tickEvent: 0
 * timertickperiod: 1
 */
TASK(tsk_hmi)
{
	/* ticktime of the task */
	static uint32_t ticktime = 0;

	/* USER CODE START TSK_HMI_TASKBOBY_PRE */

	/* USER CODE END TSK_HMI_TASKBODY_PRE */
    
    //Process all cyclic runnables which are due
    RTE_ProcessCyclicTable(RTE_cyclicActivationTable_tsk_hmi, RTE_cyclicActivation_tsk_hmi_size, ticktime);
	
	/* USER CODE START TSK_HMI_TASKBODY_POST */

	/* USER CODE END TSK_HMI_TASKBODY_POST */

	ticktime += 1;
	if (ticktime > 0xFFFFFF00) ticktime = 0;
	
	TerminateTask();
    
}


/*******************************************************************************
 * Interrupt Service Routines
 *******************************************************************************/

/* USER CODE START TSK_HMI_ISR */

/* USER CODE END TSK_HMI_ISR */

