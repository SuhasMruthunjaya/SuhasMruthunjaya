/**
* \file <filename>
* \author <author-name>
* \date <date>
*
* \brief  File containing attributes and functions of Joystick Class
*
* \copyright Copyright ©2016
* Department of electrical engineering and information technology, Hochschule Darmstadt - University of applied sciences (h_da). All Rights Reserved.
* Permission to use, copy, modify, and distribute this software and its documentation for educational, and research purposes in the context of non-commercial
* (unless permitted by h_da) and official h_da projects, is hereby granted for enrolled students of h_da, provided that the above copyright notice,
* this paragraph and the following paragraph appear in all copies, modifications, and distributions.
* Contact Prof.Dr.-Ing. Peter Fromm, peter.fromm@h-da.de, Birkenweg 8 64295 Darmstadt - GERMANY for commercial requests.
*
* \warning This software is a PROTOTYPE version and is not designed or intended for use in production, especially not for safety-critical applications!
* The user represents and warrants that it will NOT use or redistribute the Software for such purposes.
* This prototype is for research purposes only. This software is provided "AS IS," without a warranty of any kind.
**/

#ifndef JOYSTICK_H
#define JOYSTICK_H

    
#include "global.h"
#include "position.h"
#include "joystick_adc.h"

/*****************************************************************************/
/* Global pre-processor symbols/macros and type declarations                 */
/*****************************************************************************/

//####################### Defines/Macros
/** 
 * \brief a brief description of what the define is representing
*
* If needed, a more detailed description can be given below */

//####################### Enumerations
/**
* \ Enum correlating the directions of Joystick
*/

 typedef enum{
    UP,          /**< Selection of BAT moving upwards */   
    DOWN,        /**< Selection of BAT moving downwards */   
    CENTER       /**< Selection of BAT at the center */   
    
}direction_t;   
        

//####################### Structures
/**
* \ Structure containing X,Y ( of type Cordinate_t) cordinates of the joystick 
*/
typedef struct
    {
        sint8_t Cordinate_x;
        sint8_t Cordinate_y;
        direction_t joystick_direction;
    
    }JOYSTICK_t;


/*****************************************************************************/
/* Extern global variables                                                   */
/*****************************************************************************/

/**
 * <description>
 */


/*****************************************************************************/
/* API functions                                                             */
/*****************************************************************************/

/**
 * Read the Joystick position from the driver and set the Cordinates and direction of the Joystick object
 * @param JOYSTICK_t* me - IN Address of the joystick object created
 * @return RC_SUCCESS if all ok
 */
RC_t JOYSTICK_update(JOYSTICK_t *me);

/**
 * Get the Joystick direction 
 * @param JOYSTICK_t const * const me - IN Address of the joystick object created
 * @return direction_t return the enum value 
 */
direction_t JOYSTICK_GetDirection(JOYSTICK_t const * const me);  

/**
 * Get the Joystick Y Cordinate 
 * @param JOYSTICK_t const * const me - IN Address of the joystick object created
 * @return sint8_t return the Y Cordinate 
 */
sint8_t JOYSTICK_GetYCordinate(JOYSTICK_t const * const me); 
    
#endif /* FILE_H */
