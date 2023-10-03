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
     User_led_Write(1);
//    uint8_t data_lsb;
//    uint8_t data_msb;
//    uint16 value = 0xABCD; 
//    uint16 data_16;
//    data_lsb= (value&0xFF);
//    data_msb= ((value&0xFF00)>>8);
//    data_16= (uint16_t)data_msb;
//    data_16= ((uint16_t)data_lsb)|(data_16<<8) ;
//    
//       char display[sizeof(int)*8+1];
//        itoa(data_lsb,display,10);
//       UART_LOG_PutString(display);
//       itoa(data_msb,display,10);
//       UART_LOG_PutString(display);
//       UART_LOG_PutString("\r");*/
//       UART_LOG_PutChar(data_msb);
//       UART_LOG_PutChar(data_lsb);
//       itoa(value,display,10);
//       UART_LOG_PutString(display);
//       UART_LOG_PutString("\r");
//       UART_LOG_PutString("\r");
    
    
    SEQUENCING_t state = IDLE;
   
    //Infinite for loop - Superloop architecture 
    for(;;)
    {
        State_Machine(&state);
    }
    
    
}





/* [] END OF FILE */
