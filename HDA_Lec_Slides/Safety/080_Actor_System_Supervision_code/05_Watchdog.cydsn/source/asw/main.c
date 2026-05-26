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
#include "watchdog.h"
#include "watchdog_cfg.h"
#include "gpio.h"

/** -------------------------------- ISR Prototypes --------------------------------------------- **/
CY_ISR_PROTO(isr_watchdogtrigger);
CY_ISR_PROTO(isr_watchdogreset);

/** -------------------------------- Global System Variables --------------------------------------------- **/
volatile uint32_t SYS_upTime = 0;



int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */

    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    
    isr_WD_trigger_StartEx(isr_watchdogtrigger);
    isr_WD_reset_StartEx(isr_watchdogreset);
    
    WATCHDOG_Init();
    
    for(;;)
    {
        /* Place your application code here. */

        //To make the time base visible on the scope
        RC_t res = RC_ERROR;
        
       
        if (RC_SUCCESS != WATCHDOG_ProcessTrigger(ev_tick))
        {
            res = GPIO_setPowerOff(0);
        }

        CyDelay(WATCHDOG_TICKTIME);

        STATE_tick();
        SYS_upTime += WATCHDOG_TICKTIME;


        
    }
}

/**
 * Alive tick for the watchdog via GPIO
 */
CY_ISR(isr_watchdogtrigger)
{
    WDT_ClearInterrupt();
    
    if (RC_SUCCESS != WATCHDOG_Trigger_isr())
    {
        GPIO_setPowerOff(0);
    }
}

/**
 * Process the GP0 reset interrupt
 * If the delay since the last reset is long enough, a reset event will be fired
 */
CY_ISR(isr_watchdogreset)
{
    GP0_ClearInterrupt();
    
    if (SYS_upTime > WATCHDOG_getMinResetTime())
    {
        SYS_upTime = 0;
        WATCHDOG_ProcessTrigger(ev_restart); 
    }
}

/* [] END OF FILE */
