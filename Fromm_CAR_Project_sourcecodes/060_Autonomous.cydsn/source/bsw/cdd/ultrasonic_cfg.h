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
#include "ultrasonic_type.h"
    

typedef enum {US_NONE, US_FRONT, US_REAR, US_RIGHT, US_LEFT, US_MAX} US_id_t;

    

// Wrapper to allow representing the file in Together as class
#ifdef TOGETHER

class ULTRASONIC_CFG
{
public:
#endif /* Together */

/*****************************************************************************/
/* Extern global variables                                                   */
/*****************************************************************************/

extern US_t US_front;
extern US_t US_rear;
extern US_t US_left;
extern US_t US_right;



#ifdef TOGETHER

};
#endif /* Together */

#endif /* ULTRASONIC_CFG_H */
