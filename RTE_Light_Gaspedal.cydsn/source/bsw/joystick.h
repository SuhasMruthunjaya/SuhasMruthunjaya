/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#ifndef JOYSTICK_H
#define JOYSTICK_H

#include "global.h"   
#include "derivate.h"


/**
 * Joystick INIT function
 * @return RC_t: RC_SUCCESS if init is successfull 
*/
    RC_t JOYSTICK_INIT();

/**
 * Reads the Joystick position and gets the X and Y co-ordinates. 
 * @param sint8_t*x, sint8_t* y : X and Y cordinates of type signed int 8 bit
 * @return RC_SUCCESS 
 */    

    RC_t JOYSTICK_ADC_ReadPosition(sint8_t* x, sint8_t* y);
    
    
#endif /* CYAPICALLBACKS_H */   
/* [] */
