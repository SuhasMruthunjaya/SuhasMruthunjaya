
/*
 * Filename: tsk_io.h
 *
 * Author: Autogenerated by H-DA RTE Generator, (c) Prof. Fromm
 *
 * Description: This task will contain all IO operations, e.g. remote, engine,...
 */

#ifndef _H_DEFINE_TSK_IO
#define _H_DEFINE_TSK_IO

#include "project.h"
#include "global.h"
#include "rte_types.h"

/* USER CODE START TSK_IO_INCLUDES */

/* USER CODE END TSK_IO_INCLUDES */



/*
 * description: This task will contain all IO operations, e.g. remote, engine,...
 * events: ev_diagnosticrequest_onData|ev_eventout_onData|ev_protocolrx_onError|ev_tick_1ms|ev_xbee_rx
 * mode: Cyclic and Event
 * name: tsk_io
 * shortname: io
 * signalpoolsRO: sp_common
 * signalpoolsRW: sp_common
 * tickEvent: ev_tick_1ms
 * timertickperiod: 1
 */
DeclareTask(tsk_io);


#endif