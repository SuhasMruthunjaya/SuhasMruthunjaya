/*
 * Filename: sc_ultrasonicarray_type.c
 *
 * Author: Autogenerated by H-DA RTE Generator, (c) Prof. Fromm
 *
 * description: Set of 4 ultrasonic sensors
 * name: sc_ultrasonicArray
 * shortname: ultrasonicArray
 *
 */

#include "project.h"
#include "global.h"
#include "rte.h"
#include "rte_types.h"
#include "sc_ultrasonicarray_type.h"



/* USER CODE START SC_ULTRASONICARRAY_INCLUDE */

#include "ultrasonic.h"
#include "ultrasonic_cfg.h"

/* USER CODE END SC_ULTRASONICARRAY_INCLUDE */




/* USER CODE START SC_ULTRASONICARRAY_USERDEFINITIONS */

/* USER CODE END SC_ULTRASONICARRAY_USERDEFINITIONS */


/*****************************************************************************************
 *************** Port Wrapper Implementation for SC_ULTRASONICARRAY signal  ****************
 *****************************************************************************************/
 
 

/**
 * Default IN driver API
 */
inline RC_t SC_ULTRASONICARRAY_driverIn(SC_ULTRASONICARRAY_data_t *const data)
{
	/* USER CODE START driverInSC_ULTRASONICARRAY */
    
    //Set trigger to next position. We do this in the pullport, as this is called cyclically.
    //On the reception side, we might miss an echo.
    
    data->m_index++;
    data->m_index %= 4;

	//Read data from the MCAL driver
    
    
    //Will fire the current trigger and reset the distance
    switch (data->m_index)
    {
        case 0 : US_Fire(&US_front); break;
        case 1 : US_Fire(&US_rear); break;
        case 2 : US_Fire(&US_left); break;
        case 3 : US_Fire(&US_right); break;
        default: break;
    }
    

	//Scale it to the application type

	return RC_SUCCESS;
	/* USER CODE END driverInSC_ULTRASONICARRAY */
}


