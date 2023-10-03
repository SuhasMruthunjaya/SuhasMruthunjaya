/**
* \file ultrasonic_config.h
* \author P. Fromm
* \date 2.7.20
*
* \brief COnfiguration of the ultrasonic sensor, mainly MCAL function mapping
*
* detailed description what the file does
*/


 
#ifndef ULTRASONIC_CFG_H
#define ULTRASONIC_CFG_H

/*****************************************************************************/
/* Global pre-processor symbols/macros and type declarations                 */
/*****************************************************************************/

#include "global.h"
    
typedef enum {US_NONE, US_FRONT, US_REAR, US_RIGHT, US_LEFT, US_MAX} US_id_t;

//Function Pointer for trigger pin function (setter)
typedef void(*US_trigger)(uint8_t val);

//FUnction Pointer for echo pin function (getter)
typedef uint8_t (*US_echo)();

typedef struct{
    US_trigger m_trigger_func;
    US_echo    m_echo_func;
} US_port_cfg_t;
    

// Wrapper to allow representing the file in Together as class
#ifdef TOGETHER

class ULTRASONIC_CFG
{
public:
#endif /* Together */

/*****************************************************************************/
/* Extern global variables                                                   */
/*****************************************************************************/

extern const US_port_cfg_t US_ports[US_MAX];


#ifdef TOGETHER

};
#endif /* Together */

#endif /* ULTRASONIC_CFG_H */
