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

/* [] END OF FILE */

#include "Pin_ledRed.h"
#include "led.h"

void LED_Init()
{
    Pin_ledRed_Write(0);
}

void LED_Toggle()
{   
    
    Pin_ledRed_Write(1);
    CyDelay(100);
    Pin_ledRed_Write(0);
    
}
