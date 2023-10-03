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
#include "sequencing.h"



int main()
{
    //Init MCAL Drivers
    UART_LOG_Start();
    WaveDAC8_1_Start();
    //UART_LOG_PutString("hello");
    SEQUENCING_t state = IDLE;
    uint16_t ADC_array[SAMPLES];
    int32 fft_array[SAMPLES*2]; 
    
    
    //Infinite for loop - Superloop architecture 
    for(;;)
    {
        State_Machine(&state, ADC_array, fft_array);
        
    }
    
    
}





/* [] END OF FILE */
