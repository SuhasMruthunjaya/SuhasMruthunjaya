
/*
 * Filename: swc_sensor.h
 *
 * Author: Autogenerated by H-DA RTE Generator, (c) Prof. Fromm
 *
 * Description: Software component containing sensor runnables, e.g. ultrasonic
 */

#ifndef _H_DEFINE_SWC_SENSOR
#define _H_DEFINE_SWC_SENSOR

#include "project.h"
#include "global.h"
#include "rte_types.h"

/* USER CODE START SWC_SENSOR_INCLUDES */

/* USER CODE END SWC_SENSOR_INCLUDES */



/* USER CODE START SWC_SENSOR_USERDEFINITIONS */

/* USER CODE END SWC_SENSOR_USERDEFINITIONS */


/*
 * component: swc_sensor
 * cycletime: 25
 * description: Runnable updating the next ultrasonic sensor of the arrays.
 * events: 
 * name: SENSOR_update_run
 * shortname: update
 * signalIN: 
 * signalOUT: so_ultrasonic
 * task: tsk_io
 */
void SENSOR_update_run(RTE_event ev);


#endif