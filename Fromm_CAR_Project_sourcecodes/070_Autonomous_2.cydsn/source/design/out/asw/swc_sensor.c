/*
 * Filename: swc_sensor.c
 *
 * Author: Autogenerated by H-DA RTE Generator, (c) Prof. Fromm
 *
 * description: Software component containing sensor runnables, e.g. ultrasonic
 * name: swc_sensor
 * shortname: sensor
 *
 */

#include "project.h"
#include "global.h"
#include "rte.h"
#include "rte_types.h"
#include "swc_sensor.h"



/* USER CODE START SWC_SENSOR_INCLUDE */

#include "logging.h"
#include "ultrasonic_type.h"

/* USER CODE END SWC_SENSOR_INCLUDE */


#include "sp_common.h"

/* USER CODE START SWC_SENSOR_USERDEFINITIONS */

void SENSOR__print(char const * const name, US_distance_t const * const  distance)
{
    LOG_I(name, "S = %d, D = %d[cm]", distance->m_state, distance->m_distance)
}

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
void SENSOR_update_run(RTE_event ev){
	
	/* USER CODE START SENSOR_update_run */

    //We fire the sensor, the rest happens in the ISR context
    RTE_SC_ULTRASONICARRAY_pullPort(&SO_ULTRASONIC_signal);
    
    //Some diagnostics
    SC_ULTRASONICARRAY_data_t us = RTE_SC_ULTRASONICARRAY_get(&SO_ULTRASONIC_signal);
    SENSOR__print("front",&us.m_distance_front);
    SENSOR__print("rigth",&us.m_distance_right);
    SENSOR__print("rear",&us.m_distance_rear);
    SENSOR__print("left",&us.m_distance_left);
    
    /* USER CODE END SENSOR_update_run */
}

/* USER CODE START SWC_SENSOR_FUNCTIONS */

/* USER CODE END SWC_SENSOR_FUNCTIONS */
