
/*
 * Filename: swc_monitor.h
 *
 * Author: Autogenerated by H-DA RTE Generator, (c) Prof. Fromm
 *
 * Description: Error monitor checking the system health
 */

#ifndef _H_DEFINE_SWC_MONITOR
#define _H_DEFINE_SWC_MONITOR

#include "project.h"
#include "global.h"
#include "rte_types.h"

/* USER CODE START SWC_MONITOR_INCLUDES */

/* USER CODE END SWC_MONITOR_INCLUDES */



/* USER CODE START SWC_MONITOR_USERDEFINITIONS */

/* USER CODE END SWC_MONITOR_USERDEFINITIONS */


/*
 * component: swc_monitor
 * cycletime: 10
 * description: Cyclic runnable checking the system health
 * events: 
 * name: MONITOR_health_run
 * shortname: health
 * signalIN: so_joystick|so_targetspeed|so_currentspeed|so_controlspeed|so_protocolRx|so_protocolTx|so_carState|so_eventIn|so_eventOut|so_carErrorState|so_ultrasonic
 * signalOUT: so_carErrorState
 * task: tsk_io
 */
void MONITOR_health_run(RTE_event ev);

/*
 * component: swc_monitor
 * cycletime: 0
 * description: Receive Diagnostic Request and processes it, e.g clears DETor transmits DET to client
 * events: ev_diagnosticrequest_onData
 * name: MONITOR_processDiagnosticRequest_run
 * shortname: processDiagnosticRequest
 * signalIN: so_diagnosticRequest
 * signalOUT: 
 * task: tsk_io
 */
void MONITOR_processDiagnosticRequest_run(RTE_event ev);


#endif