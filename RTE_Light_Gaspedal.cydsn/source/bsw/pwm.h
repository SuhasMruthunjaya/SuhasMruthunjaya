#ifndef PWM_H
#define PWM_H

#include "global.h"   
#include "derivate.h"


/**
 * Initializes the PWM
 * @return RC_SUCCESS if initialization is successful
 */
    RC_t PWM_INIT();
    
/**
 * Writes to the PWM HAL Driver
 * @param duty_cycle: Duty cycle to be sent to the driver
 * @return RC_SUCCESS
 */    
    RC_t PWM_WRITE(uint8_t duty_cycle);
    
    
#endif /* CYAPICALLBACKS_H */   
/* [] */
