/**
* \file ultrasonic_type.h
* \author P. Fromm
* \date 11.06.21
*
* \brief Type definition for the ultrasonic sensor
*
* detailed description what the file does
*/


 
#ifndef ULTRASONIC_TYPE_H
#define ULTRASONIC_TYPE_H

/*****************************************************************************/
/* Global pre-processor symbols/macros and type declarations                 */
/*****************************************************************************/

#include "global.h"
    
    
typedef enum {US_IDLE, US_FIRING, US_VALID} US_state_t;
    
typedef struct {
    US_state_t  m_state;        /*!< validity state */
    uint16_t    m_distance;     /*!< distance in cm */
} US_distance_t;

    
//Function Pointer for trigger pin function (setter)
typedef void(*US_trigger)(uint8_t val);

typedef struct{
    US_trigger      m_trigger_func; /*!< Pointer to the trigger function */
    US_distance_t*  m_distance;     /*!< Pointer where the resulting distance will be stored */
} US_t;
    
    

// Wrapper to allow representing the file in Together as class
#ifdef TOGETHER

class ULTRASONIC_CFG
{
public:
#endif /* Together */


#ifdef TOGETHER

};
#endif /* Together */

#endif /* ULTRASONIC_CFG_H */
