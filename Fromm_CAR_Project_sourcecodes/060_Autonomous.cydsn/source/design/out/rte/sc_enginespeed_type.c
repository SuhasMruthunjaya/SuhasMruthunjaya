/*
 * Filename: sc_enginespeed_type.c
 *
 * Author: Autogenerated by H-DA RTE Generator, (c) Prof. Fromm
 *
 * description: The engine speed record in RPM per engine. Used for controlspeed and currentspeed
 * name: sc_engineSpeed
 * shortname: engineSpeed
 *
 */

#include "project.h"
#include "global.h"
#include "rte.h"
#include "rte_types.h"
#include "sc_enginespeed_type.h"



/* USER CODE START SC_ENGINESPEED_INCLUDE */
#include "engine_cfg.h"
#include "engine.h"

/* USER CODE END SC_ENGINESPEED_INCLUDE */




/* USER CODE START SC_ENGINESPEED_USERDEFINITIONS */


/* USER CODE END SC_ENGINESPEED_USERDEFINITIONS */


/*****************************************************************************************
 *************** Port Wrapper Implementation for SC_ENGINESPEED signal  ****************
 *****************************************************************************************/
 
 

/**
 * Default IN driver API
 */
inline RC_t SC_ENGINESPEED_driverIn(SC_ENGINESPEED_data_t *const data)
{
	/* USER CODE START driverInSC_ENGINESPEED */

	//Read data from the MCAL driver
    //NOTE!!!!! Ticktime is hardcoded to 100ms
    ENG_updateDecoder(&ENG_FL, 100);
    ENG_updateDecoder(&ENG_FR, 100);
    ENG_updateDecoder(&ENG_RL, 100);
    ENG_updateDecoder(&ENG_RR, 100);
    
	//Scale it to the application type
    RC_t result = RC_SUCCESS;
    result = ENG_getSpeed(&ENG_FL, &(data->m_rpm_fl));
    result = ENG_getSpeed(&ENG_FR, &(data->m_rpm_fr));
    result = ENG_getSpeed(&ENG_RL, &(data->m_rpm_rl));
    result = ENG_getSpeed(&ENG_RR, &(data->m_rpm_rr));

	return RC_SUCCESS;
	/* USER CODE END driverInSC_ENGINESPEED */
}
/**
 * Default OUT driver API
 */
inline RC_t SC_ENGINESPEED_driverOut(const SC_ENGINESPEED_data_t  *const data)
{
	/* USER CODE START driverOutSC_ENGINESPEED */

	//Scale application data to drive format

	//Write scaled data to driver
    
    ENG_setSpeed(&ENG_FL, data->m_rpm_fl, ENG_MODE_PID);
    ENG_setSpeed(&ENG_FR, data->m_rpm_fr, ENG_MODE_PID);
    ENG_setSpeed(&ENG_RL, data->m_rpm_rl, ENG_MODE_PID);
    ENG_setSpeed(&ENG_RR, data->m_rpm_rr, ENG_MODE_PID);

	return RC_SUCCESS;
	/* USER CODE END driverOutSC_ENGINESPEED */
}



