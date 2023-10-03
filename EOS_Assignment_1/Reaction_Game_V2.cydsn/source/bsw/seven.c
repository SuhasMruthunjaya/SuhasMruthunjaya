/**
* \file <filename>
* \author <author-name>
* \date <date>
*
* \brief <Symbolic File name>
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
*/

/*****************************************************************************/
/* Include files                                                             */
/*****************************************************************************/

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



/*****************************************************************************/
/* Local function prototypes ('static')                                      */
/*****************************************************************************/


/*****************************************************************************/
/* Function implementation - global ('extern') and local ('static')          */
/*****************************************************************************/

/**
 * <Description>
 * @param <first para>
 * @return <return value>
 */
//type function(type para)

#include "seven.h"
#include "global.h"
#include "Control_Reg_1.h"
#include "time.h"
#include "stdlib.h"
#include "game.h"
char display[sizeof(int)*8+1];


/*
    This function displays 1 or 2 on the seven segment display randomly.
    @param uint32_t variable_number: Static variable defined in the systic 
    counter ISR. This increments every counter tick and we are using this 
    value to get the random value by doing a modulus of 2. 
*/
RC_t Seven_segment_button(uint32_t variable_number)
{       
        /* For UART display: Mallocing and using it for itoa function. */

        randomTime = variable_number%2;
        
        if(randomTime == 0)
        {
        count = 0;
        Control_Reg_1_Write(0xDA);
        UART_LOG_PutString("\rRandomTime = 2");
        SetRelAlarm(alarm_count,1,1);
        
        }
        if(randomTime == 1)
        {
        count = 0;
        Control_Reg_1_Write(0x60);
        UART_LOG_PutString("\rRandomTime = 1");
        SetRelAlarm(alarm_count,1,1);
        
        }
        return RC_SUCCESS;
 }
 
/*
   This function waits for a random time (1, 2 or 3 seconds) before printing
   1 or 2 on the seven segment display.
   @param uint32_t variable_number: Static variable defined in the systic 
   counter ISR. This increments every counter tick and we are using this 
   value to get the random waiting time by doing a modulus of 3.

*/
RC_t Seven_segment_wait_time(uint32_t variable_number)

    {
               
                int var_number = variable_number;
        
                int randomwait = (var_number % 3)+1;  
                variable_number = 0;
                SetRelAlarm(alarm_seven_seg_display_wait,1000*randomwait,0);
    }
