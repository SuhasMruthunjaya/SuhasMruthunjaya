/**
* \file boardtest.c
* \author Fromm
* \date 18.2.20
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
#include "boardtest.h"

#include "led.h"
#include "poti.h"
#include "engine.h"

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
/* Local function prototypes ('static')                                      */
/*****************************************************************************/

void BT_toggleLed();
void BT_driveEngine();
void BT_triggerSafe1();

/*****************************************************************************/
/* Local variable definitions ('static')                                     */
/*****************************************************************************/

static const BT_testcase_t BT__tests[] = {
    { BT_toggleLed, 100 },
    { BT_driveEngine, 100 },
    { BT_triggerSafe1, 50 },
    
};

static const uint16_t BT__testSize = sizeof(BT__tests) / sizeof (BT_testcase_t);



/*****************************************************************************/
/* Function implementation - global ('extern') and local ('static')          */
/*****************************************************************************/

/**
 * Run all testcases as defined in the table (boardtest.c)
 * @param uint16_t ticktime - IN ticktime of the task in ms
 * @return RC_SUCCESS or error code
 */
RC_t BT_run(uint16_t ticktime)
{
    static uint32_t BT___time = 0;
    
    for (uint16_t i = 0; i < BT__testSize; i++)
    {
        //Call the runnable if tick time is due
        if (BT___time % BT__tests[i].t == 0) BT__tests[i].run();
    }
    
    BT___time += ticktime;
    
    return RC_SUCCESS;
}


RC_t BT_init()
{
    
    return RC_SUCCESS;
    
}
/////////////////////////////////////////////////////////////////////////////


void BT_toggleLed()
{
    static LED_id_t led = LED_1;
    
    LED_Toggle(led);
    
    //go around
    if (led == LED_ALL) led = LED_1; else led++;
    
}

void BT_driveEngine()
{
    sint16_t speed = 0;
    sint16_t controlspeed = 0;
    
    RC_t res =  POTI_ReadPosition(POTI_1, &speed);
    
    //Poti is -100..100, RPM is -200...200
    speed *=2;
    
    //controlspeed reference can be orgnored here
    res = ENG_SetEngineOpenLoop(speed, &controlspeed);
}
    
void BT_triggerSafe1()
{
    static uint8_t toggle = 0;
    
    if (toggle == 0) toggle = 1; else toggle = 0;
    
    Pin_Safe_1_Write(toggle);
}
    
    