/**
* \file watchdog_cfg.c
* \author P. Fromm
* \date 22.3.20
*
* \brief Watchdog Configuration
*
* \copyright Copyright ©2020
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


#include "watchdog_cfg.h"
#include "watchdog.h"

#include "dip.h"

/*****************************************************************************/
/* Local pre-processor symbols/macros ('#define')                            */
/*****************************************************************************/



/*****************************************************************************/
/* Global variable definitions (declared in header file with 'extern')       */
/*****************************************************************************/

/**
 * Timing for Time Out Watchdog in [ms] depending on the time configuration
 */
static const WATCHDOG_Alive_t WATCHDOG__Alive_timing[] =
    {   {1000, 10000},         /**< /brief Default value 1000ms */
        {500,   5000},         /**< /brief Value 500ms */
        {100,   1000},         /**< /brief Value 100ms */
        {10,     100},         /**< /brief Value 10ms */
    };
static const uint16_t WATCHDOG__Alive_timing_size = sizeof (WATCHDOG__Alive_timing) / sizeof(WATCHDOG_Alive_t);

/**
 * Timing for Window Watchdog in [ms] depending on the time configuration
 */
static const WATCHDOG_Window_t WATCHDOG__Window_timing[] = 
{
    {500, 1000, 5000},        /**< /brief Default value 500ms...1000ms */
    {250, 500,  2000},         /**< /brief Value 250ms...500ms */
    {450, 500,  1000},         /**< /brief Value 450ms...500ms */
    {50,  100,   500}          /**< /brief Value  50ms...100ms */
};
static const uint16_t WATCHDOG__Window_timing_size = sizeof (WATCHDOG__Window_timing) / sizeof(WATCHDOG_Window_t);

/**
 * Timing for Time Out Watchdog in [ms] depending on the time configuration
 */
static const WATCHDOG_QA_t WATCHDOG__QA_timing[] =
    {   {1000, 10000},         /**< /brief Default value 1000ms */
        {500,   5000},         /**< /brief Value 500ms */
        {100,   1000},         /**< /brief Value 100ms */
        {10,     100},         /**< /brief Value 10ms */
    };
static const uint16_t WATCHDOG__QA_timing_size = sizeof (WATCHDOG__QA_timing) / sizeof(WATCHDOG_QA_t);



/*****************************************************************************/
/* Function implementations                                                  */
/*****************************************************************************/


WATCHDOG_time_t WATCHDOG_getStartTime()
{
    uint8_t pos = DIP_readTime();
    DIP_mode_t mode = DIP_readMode();
    
    switch (mode)
    {
        case DIP_mode_off      : return 0;
        case DIP_mode_alive    : return 0;
        case DIP_mode_window   : return WATCHDOG__Window_timing[pos].m_start;
        case DIP_mode_qa       : return 0;
        default                : return 0;
    }
    
}

WATCHDOG_time_t WATCHDOG_getEndTime()
{
    
    uint8_t pos = DIP_readTime();
    DIP_mode_t mode = DIP_readMode();
    
    switch (mode)
    {
        case DIP_mode_off      : return UINT_MAX;
        case DIP_mode_alive    : return WATCHDOG__Alive_timing[pos].m_timeout;
        case DIP_mode_window   : return WATCHDOG__Window_timing[pos].m_end;
        case DIP_mode_qa       : return WATCHDOG__QA_timing[pos].m_timeout;
        default                : return 0;
    }
}

WATCHDOG_time_t WATCHDOG_getMinResetTime()
{
    uint8_t pos = DIP_readTime();
    DIP_mode_t mode = DIP_readMode();
    
    switch (mode)
    {
        case DIP_mode_off      : return UINT_MAX;
        case DIP_mode_alive    : return WATCHDOG__Alive_timing[pos].m_reset;
        case DIP_mode_window   : return WATCHDOG__Window_timing[pos].m_reset;
        case DIP_mode_qa       : return WATCHDOG__QA_timing[pos].m_reset;
        default                : return 0;
    }
}
