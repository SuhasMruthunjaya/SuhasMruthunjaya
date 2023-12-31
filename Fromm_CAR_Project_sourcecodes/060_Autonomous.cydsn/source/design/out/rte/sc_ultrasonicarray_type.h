
/*
 * Filename: sc_ultrasonicarray_type.h
 *
 * Author: Autogenerated by H-DA RTE Generator, (c) Prof. Fromm
 *
 * Description: Set of 4 ultrasonic sensors
 */

#ifndef _H_DEFINE_SC_ULTRASONICARRAY_TYPE
#define _H_DEFINE_SC_ULTRASONICARRAY_TYPE

#include "project.h"
#include "global.h"
#include "rte_types.h"

/* USER CODE START SC_ULTRASONICARRAY_INCLUDES */
#include "ultrasonic_type.h"
/* USER CODE END SC_ULTRASONICARRAY_INCLUDES */



/**********************************************************************
 *       Type Definition for SC_ULTRASONICARRAY signal    
 **********************************************************************/

/* USER CODE START SC_ULTRASONICARRAY_USERDEFINITIONS */

    
    
/* USER CODE END SC_ULTRASONICARRAY_USERDEFINITIONS */

typedef 
/* USER CODE START SC_ULTRASONICARRAY_SIGNALDATADEFINITION */
struct
{
    uint8_t  m_index;                   /*!< index of the sensor currently being fired */
    
	US_distance_t m_distance_front;          /*!< front distance */
	US_distance_t m_distance_rear;           /*!< rear distance */
	US_distance_t m_distance_left;           /*!< left distance */
	US_distance_t m_distance_right;          /*!< right distance */
    
} 
/* USER CODE END SC_ULTRASONICARRAY_SIGNALDATADEFINITION */
SC_ULTRASONICARRAY_data_t;

/* USER CODE START InitSC_ULTRASONICARRAY */
#define SC_ULTRASONICARRAY_INIT_DATA ((SC_ULTRASONICARRAY_data_t){0, {US_IDLE, 0}, {US_IDLE, 0}, {US_IDLE, 0}, {US_IDLE, 0}})
/* USER CODE END InitSC_ULTRASONICARRAY */


/**
 * Default IN driver API
 * \param SC_ULTRASONICARRAY_data_t *const data : [OUT] scaled data read from the driver
 * \return RC_SUCCESS is all was ok, error code otherwise
 */
RC_t SC_ULTRASONICARRAY_driverIn(SC_ULTRASONICARRAY_data_t *const data);




/* USER CODE START SC_ULTRASONICARRAY_USERFUNCTIONS */

/* USER CODE END SC_ULTRASONICARRAY_USERFUNCTIONS */


#endif