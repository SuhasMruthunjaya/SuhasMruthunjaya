/*
 * Filename: swc_engine.c
 *
 * Author: Autogenerated by H-DA RTE Generator, (c) Prof. Fromm
 *
 * description: Complex Devide driver type runnable for the engine
 * name: swc_engine
 * shortname: engine
 *
 */

#include "project.h"
#include "global.h"
#include "rte.h"
#include "rte_types.h"
#include "swc_engine.h"



/* USER CODE START SWC_ENGINE_INCLUDE */

#include "logging.h"
#include "math.h"
#include "engine_cfg.h"

/* USER CODE END SWC_ENGINE_INCLUDE */


#include "sp_common.h"

/* USER CODE START SWC_ENGINE_USERDEFINITIONS */

/**
 * Engine data:
 * ============
 * Wheel Diameter:		65mm
 * Gear Ratio:			34:1
 * Encoder:				10 PPR
 *
 * Max RPM measured (7V normal):
 * 				engine:	    3900 RPM
 * 				axis:       200 RPM  (in reality a bit less....)
 * 				speed:	    0,7 m/s = (rpm/60 * Pi * wheel_dia_mm/1000)
 *              speed2rpm : speed * 1000 * 60 / pi / wheel_dia_mm = 294 * speed
 *
 * Max rotational speed:
 * 				360deg turn = 2s (based on 10 rotations measured)
 * 				180deg / s
 *              KPhi = ENG_MAX_RPM (200) / 180
 *
 */

#define ENGINE_KY    294    
#define ENGINGE_KPHI 1.1

/* USER CODE END SWC_ENGINE_USERDEFINITIONS */



/*
 * component: swc_engine
 * cycletime: 100
 * description: Engine controller runnable
 * events: 
 * name: ENGINE_setspeed_run
 * shortname: setspeed
 * signalIN: so_targetspeed|so_currentspeed
 * signalOUT: so_controlspeed
 * task: tsk_io
 */
void ENGINE_setspeed_run(RTE_event ev){
	
	/* USER CODE START ENGINE_setspeed_run */
    
    SC_CARSPEED_data_t targetspeed = SC_CARSPEED_INIT_DATA;
    SC_ENGINESPEED_data_t currentspeed = SC_ENGINESPEED_INIT_DATA;
    SC_ENGINESPEED_data_t controlspeed = SC_ENGINESPEED_INIT_DATA;
    SC_CARERRORSTATE_data_t errordata = SC_CARERRORSTATE_INIT_DATA;
    
    //Read in targetspeed and currentspeed
    targetspeed = RTE_SC_CARSPEED_get(&SO_TARGETSPEED_signal);
    
    //Update the decoder values for the control logic
    //Note: Ticktime is hardcoded to 100 in driver
    RTE_SC_ENGINESPEED_pullPort(&SO_CURRENTSPEED_signal);
    
    //Read in error data to check for max allowed speed
    errordata = RTE_SC_CARERRORSTATE_get(&SO_CARERRORSTATE_signal);
   
    //Calculate the enginespeed in RPM
    //Impact of longitude value vy
    controlspeed.m_rpm_fl = ENGINE_KY * targetspeed.m_vy;
    controlspeed.m_rpm_fr = ENGINE_KY * targetspeed.m_vy;
    controlspeed.m_rpm_rl = ENGINE_KY * targetspeed.m_vy;
    controlspeed.m_rpm_rr = ENGINE_KY * targetspeed.m_vy;
    

    //Impact of the rotation
    controlspeed.m_rpm_fl += ENGINGE_KPHI * targetspeed.m_vphi;
    controlspeed.m_rpm_fr -= ENGINGE_KPHI * targetspeed.m_vphi;
    controlspeed.m_rpm_rl += ENGINGE_KPHI * targetspeed.m_vphi;
    controlspeed.m_rpm_rr -= ENGINGE_KPHI * targetspeed.m_vphi;
   
    //Get the max speed value, all others will be scaled accordingly
    sint16_t maxspeed = controlspeed.m_rpm_fl;
    if (abs(controlspeed.m_rpm_fr) > maxspeed) maxspeed = controlspeed.m_rpm_fr;
    if (abs(controlspeed.m_rpm_rl) > maxspeed) maxspeed = controlspeed.m_rpm_rl;
    if (abs(controlspeed.m_rpm_rr) > maxspeed) maxspeed = controlspeed.m_rpm_rr;

    // Calculate the resulting scale value   
    float scale = 1;
    if ( maxspeed > ENG_MAXRPM) scale = (float)ENG_MAXRPM / maxspeed;
    scale = scale * errordata.m_maxSpeed / 100; 
    
    //Scaling of the speed to allowed maxspeed
    controlspeed.m_rpm_fl *= scale;
    controlspeed.m_rpm_fr *= scale;
    controlspeed.m_rpm_rl *= scale;
    controlspeed.m_rpm_rr *= scale;
    
    //LOG_I("Speed","SCALE %d RR %d RL %d FR %d FL %d", (int)(scale*100), controlspeed.m_rpm_rr, controlspeed.m_rpm_rl, controlspeed.m_rpm_fr, controlspeed.m_rpm_fl);
    
    
    //Now let's send the calculated control speed to the RTE
    RTE_SC_ENGINESPEED_set(&SO_CONTROLSPEED_signal, controlspeed);
    
    //And push it to the driver
    RTE_SC_ENGINESPEED_pushPort(&SO_CONTROLSPEED_signal);

    /* USER CODE END ENGINE_setspeed_run */
}

/* USER CODE START SWC_ENGINE_FUNCTIONS */

/* USER CODE END SWC_ENGINE_FUNCTIONS */
