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


/*****************************************************************************/
/* Include files                                                             */
/*****************************************************************************/

#include "sequencing.h"



/*****************************************************************************/
/* Local pre-processor symbols/macros ('#define')                            */
/*****************************************************************************/

/*****************************************************************************/
/* Global variable definitions (declared in header file with 'extern')       */
/*****************************************************************************/

/*****************************************************************************/
/* Local type definitions ('typedef')                                        */
/*****************************************************************************/

/*****************************************************************************/
/* Local variable definitions ('static')                                     */
/*****************************************************************************/

//'arr_count' represents the number of arrays sent to Matlab. 
//This is made 'static' to make 'arr_count' private to the State_Machine code
static uint8_t arr_count = 1; 

/*****************************************************************************/
/* Local function prototypes ('static')                                      */
/*****************************************************************************/


/*****************************************************************************/
/* Function implementation - global ('extern') and local ('static')          */
/*****************************************************************************/


/**
 * Read ADC values and store it in an uint16 array of size 1024
 * @param uint16_t *ADC_array - IN/OUT To store the ADC values
 * @return RC_SUCCESS if all ok
 */
RC_t ReadAndStoreADC(uint16_t *ADC_array)
{
    int32 result;
    uint16 result_mV;
    
    for(uint16_t i=0; i<1024;i++)
    {
       ADC_VtgDiv_Start();
       ADC_VtgDiv_StartConvert();
       ADC_VtgDiv_IsEndConversion(ADC_VtgDiv_WAIT_FOR_RESULT);
       result= ADC_VtgDiv_GetResult32();
       result_mV= ADC_VtgDiv_CountsTo_mVolts(result); 
        //ADC_array[i]= 1;
       ADC_array[i]= (result_mV);
       //UART_PutintVal(i);  
       //UART_PutintVal(ADC_array[i]);

    }
    
    
    return RC_SUCCESS;
}
/**
 * Function consists of State Machine logic to send ADC values to Matlab via UART communication
 * @param SEQUENCING_t* state - IN State of the Sequence passed as address
 * @return RC_SUCCESS if all ok
 */

RC_t State_Machine(SEQUENCING_t* state)
{
    static uint8_t send_once;
    //variables declaration
    uint8_t recieved_data=0;
    uint8_t data_lsb;
    uint8_t data_msb;
     uint16_t ADC_array1[1024];
    
    switch(*state)
    {
        case IDLE: 
        {
            LED_Red_Write(1);
            LED_Yellow_Write(0);
            LED_Green_Write(0);
            #ifdef UD
            UART_LOG_PutString("State:IDLE \r");
            #endif
            if(Push_button_Read()== BUTTON_PRESSED)
            {
                #ifdef UD
                UART_LOG_PutString("State:SAMPLING \r");
                #endif
               *state= SAMPLING; 
            }
            
            break;
        }
        case SAMPLING:
        {
            LED_Red_Write(0);
            LED_Yellow_Write(1);
            LED_Green_Write(0);
            //Recieve 's' character from Matlab script
            recieved_data= UART_LOG_GetChar(); 
            
            //if recieved, then move to next state
            if(recieved_data == 's')
            {
                
                #ifdef UD
                UART_LOG_PutString("State:UART_TRANSFER\r");                
                #endif
                
                //Put ADC values into uint16_t array size 1024
            
                ReadAndStoreADC(ADC_array1);
                send_once=1;
                *state= UART_TRANSFER;
                
                //UART_PutintVal(flag); 
                
            }
            
            break;
        }
        case UART_TRANSFER:
        {
            LED_Red_Write(0);
            LED_Yellow_Write(0);
            LED_Green_Write(1);
            if(send_once==1)
            {
            //send adc values to uart
                for(uint16_t i=0; i<1024;i++)
                {
                   data_lsb= (uint8_t)(ADC_array1[i]&0x00FF);
    
                   data_msb= (uint8_t)((ADC_array1[i] >> 8) &0x00FF)  ; 
                    UART_LOG_PutChar(data_lsb);
                    UART_LOG_PutChar(data_msb);
                    //UART_PutintVal(i); 
                }
                send_once=0;
            }
                
            //Recieve 'o' character from Matlab script
            recieved_data= UART_LOG_GetChar(); 
            
            //if arr_count is less than 10, then move to SAMPLING atate and send the next array
            if(recieved_data == 'o' && arr_count < 10)
            {
                
                #ifdef UD
                UART_LOG_PutString("State:SAMPLING \r");
                #endif
                
                
                
                *state= SAMPLING;
                arr_count++;
            }
            
            //if all 10 arrays are sent then move to IDLE state.
            else if(recieved_data == 'o' && arr_count>= 10)
            {
                arr_count=1;
                *state= IDLE;
            }
            break;
        }
    }
    return RC_SUCCESS;    
}


/* [] END OF FILE */
