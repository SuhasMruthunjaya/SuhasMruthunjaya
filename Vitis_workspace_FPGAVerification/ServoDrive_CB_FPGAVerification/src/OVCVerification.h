/*
 * OVCVerification.h
 *
 *  Created on: 08.10.2025
 *      Author: SESA807379 (Suhas Bangalore Mruthunjaya)
 */

#ifndef SRC_OVCVERIFICATION_H_
#define SRC_OVCVERIFICATION_H_

#include "axi_reg.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "logFile.h"
#include "platform.h"
#include "xil_printf.h"
#include "xuartps.h"
#include "xil_io.h"
#include "dsp/transform_functions.h"
#include "sleep.h"
#include "uart_comm.h"



void ovc_axi_phase_write(u32 phase_val);

void ovc_axi_staticData_write(int index);

void ovc_axi_startOp_write();

void ovc_static_verification();


#endif /* SRC_OVCVERIFICATION_H_ */
