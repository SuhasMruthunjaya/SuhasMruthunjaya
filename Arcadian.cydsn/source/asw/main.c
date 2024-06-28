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
#include "game.h"


ISR(systick_handler)
{
	CounterTick(cnt_systick);
}

int main()
{
	int counter;

	//Set systick period to 1 ms. Enable the INT and start it.
	EE_systick_set_period(MILLISECONDS_TO_TICKS(1, BCLK__BUS_CLK__HZ));
	EE_systick_enable_int();
	CyGlobalIntEnable; /* Enable global interrupts. */

	/* Place your initialization/startup code here (e.g. MyInst_Start()) */

	// Start Operating System

	for(;;)
		StartOS(OSDEFAULTAPPMODE);
}

void unhandledException()
{
	//Ooops, something terrible happened....check the call stack to see how we got here...
	__asm("bkpt");
}

/*!
 * Callback function needed for Tick event. Alarm is triggered as per the game speed
 * This speed is set in the game_cfg.h. Therefore this function is called every tick
 * and GAME_EV_TICK is obtained
 * @param none
 * @return void
 */
void cb_tick()
{
	GAME_set_event(GAME_EV_TICK);
}

/*!
 * Category 2 ISR (OS ISR) defined for the Buttons used for this project.
 * Set the events according to each button press
 * Button 1 -> Start button event
 * Button 2 -> Up button event
 * Button 3 -> Stop button event
 * Button 4 -> Down button event
 */
ISR2(isr_Button)
{
	if (BUTTON_1_Read()==1)
	{
		GAME_set_event(GAME_EV_BUTTON_START);

	}
	if (BUTTON_2_Read()==1)
	{
		GAME_set_event(GAME_EV_BUTTON_UP);

	}
	if (BUTTON_3_Read()==1)
	{
		GAME_set_event(GAME_EV_BUTTON_STOP);

	}
	if (BUTTON_4_Read()==1)
	{
		GAME_set_event(GAME_EV_BUTTON_DOWN);

	}
}


/*********************************************************************
 ***********
 * Task Definitions
 **********************************************************************
 **********/

/*!
 * Init Task used to Initialize all drivers used in the project
 * It is also used to activate the game and background task
 * followed by the tick alarm
 */
TASK(tsk_init)
{

	//Init MCAL Drivers

	UART_LOG_Start();
	JOYSTICK_ADC_Init();
	CAN_Start();

	TFT_init();


	//Reconfigure ISRs with OS parameters.
	//This line MUST be called after the hardware driver
	//initialization!
	EE_system_init();
	// Must be started after interrupt reconfiguration
	EE_systick_start();

	ActivateTask(tsk_game);
	ActivateTask(tsk_background);
	SetRelAlarm(alarm_tick,GAMESPEED,GAMESPEED);
	TerminateTask();
}

/*!
 * Game Task created to process the Arcadian game logic. It initializes the
 * Game state machine along with Menu. This task works cyclically using the tick event
 * obtained from the call back function. Based on the buttons events obtained
 * from the ISR2, Pong or soccer game logic is called and its respective state machine.
 */
TASK(tsk_game)
{

	EventMaskType ev = 0;
	GAME_event_t gameEv = GAME_EV_NONE;

	GAME_InitState();

	while(1)
	{
		WaitEvent(ev_newGameEvent);
		GetEvent(tsk_game,&ev);
		ClearEvent(ev);


		if (ev & ev_newGameEvent)
		{
			gameEv = GAME_get_event();
			GAME_process_event(gameEv);

		}
	}

	TerminateTask();
}



/*!
 * Background task is kept empty.
 */
TASK(tsk_background)
{
	while(1)
	{
		__asm("nop");
	}
}


/* [] END OF FILE */


/* [] END OF FILE */
