 
/*
 * Filename: sc_carstate_type.h
 *
 * Author: Autogenerated by H-DA RTE Generator, (c) Prof. Fromm
 *
 * Description: Connection state and algorithm of the car
 */

#ifndef _H_DEFINE_SC_CARSTATE_TYPE
#define _H_DEFINE_SC_CARSTATE_TYPE

#include "project.h"
#include "global.h"
#include "rte_types.h"

/* USER CODE START SC_CARSTATE_INCLUDES */

/* USER CODE END SC_CARSTATE_INCLUDES */



/**********************************************************************
 *       Type Definition for SC_CARSTATE signal    
 **********************************************************************/

/* USER CODE START SC_CARSTATE_USERDEFINITIONS */

        
/* USER CODE END SC_CARSTATE_USERDEFINITIONS */

typedef 
/* USER CODE START SC_CARSTATE_SIGNALDATADEFINITION */
struct
{
	sint8_t			m_algoIndex;	/**< \brief Current algo of the car, -1 = invalid */
} 
/* USER CODE END SC_CARSTATE_SIGNALDATADEFINITION */
SC_CARSTATE_data_t;

/* USER CODE START InitSC_CARSTATE */
#define SC_CARSTATE_INIT_DATA ((SC_CARSTATE_data_t){})
/* USER CODE END InitSC_CARSTATE */





/* USER CODE START SC_CARSTATE_USERFUNCTIONS */

/* USER CODE END SC_CARSTATE_USERFUNCTIONS */


#endif