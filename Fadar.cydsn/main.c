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
#include "project.h"

typedef struct
{
    int RED;
    int Green;
    int Blue;
    int time;
    
}RG__Glow_t;






const RG__Glow_t RG_glowtable_1[] = {
//Red Green Blue TimeInMS
{255, 0, 0, 500},
{0, 255, 0, 500},
{0, 0, 255, 500},
{0, 0, 0, 100},
{255, 255, 255, 100},
{0, 0, 0, 100},
{255, 255, 255, 100},
{0, 0, 0, 100},
{255, 255, 255, 100}
};



void  rgb (RG__Glow_t value)
{
    Pin_RGB_RED_Write(value.RED);
    Pin_RGB_Green_Write(value.Green);
    Pin_RGB_Blue_Write(value.Blue);
    CyDelay(value.time);
}


int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */

    /* Place your initialization/startup code here (e.g. MyInst_Start()) */

    for(int i=0;i<9;i++)
    {
        
        rgb(RG_glowtable_1[i]);
    }
        
        
        
        
        
        
        
        
        
        
        /* Place your application code here. */
/*       PWM_ledGreen_Enable();
        PWM_ledYellow_Enable();
        PWM_ledRed_Enable();
       
        for(int i=0; i<256; i++)
        
        {
            PWM_ledRed_WriteCompare(i);
            Pin_RGB_Green_Write(i);
            CyDelay(10);
        }
        
        for(int i=256; i>0; i--)
        
        {
            PWM_ledRed_WriteCompare(i);
            CyDelay(10);

        }
        
        for(int i=0; i<256; i++)
        
        {
            PWM_ledGreen_WriteCompare(i);
            CyDelay(10);
        }
        
        for(int i=256; i>0; i--)
        
        {
            PWM_ledGreen_WriteCompare(i);
            CyDelay(10);
        }
        
*/ 
        
    }      
        
        
    
}

/* [] END OF FILE */
