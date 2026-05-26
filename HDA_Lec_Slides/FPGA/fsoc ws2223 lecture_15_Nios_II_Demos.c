
/*
 * h_da, fbeit, imse, fsoc
 * C.Jakob, Darmstadt, 12.12.2022, christian.jakob@h-da.de
 *
 * Intel Nios II (fast version)
 */

#include "system.h"						// bsp(project) directory
#include "alt_types.h"					// bsp(project) directory - hal - inc - alt_types.h
#include <sys/alt_irq.h>				// bsp(project) directory - hal - inc - sys - alt_irq.h

#define ZERO 0x00

#define PUSH_BUTTONS (*((PIO_TYPE *) GPIO_PUSH_BUTTON_BASE_ADDRESS))
#define LEDS		 (*((PIO_TYPE *) GPIO_LED_BASE_ADDRESS))

/*
 *	volatile global variable used in the following IRQ demos
 */

volatile alt_u8 irq_exchange;

/*
 * C-based delay function, not to be intended to be precise ...
 *
 * @param - number of iterations
 * @return - no return value
 */

static void delay_v1(alt_u32 iterations) {
	volatile alt_u32 i;
	for(i = iterations; i > 0; i--);
}

/*
 * 'inline-assembly' based delay function, not to be intended to be precise ...
 *
 *  Plain C can get optimized differently at different times. We use assembler code to bypass compiler optimization, which
 *  might change the timing of the actual C code ... The compiler takes care of registers used when returning to standard C code.
 *
 *  WARNING: Please note that the type of instruction memory highly impacts the loop time (int./ext.SRAM, DRAM, ...) . Cache memory can
 *  lower this, but it often still affects the first loop until the instructions are in the cache. If you need to be exact, put this code
 *  it in tightly coupled memory.
 *
 *	@param - number of iterations
 *	@return - no return value
 */

void delay_v2(volatile alt_u32 count) {
	// we get 'count' from the stack ...
	asm volatile ("		ldw     r2,0(sp)	\n\t"		// ~ 1 (CPU Cycle) - see the document 'Nios II Core Implementation Details'
				  "loop:					\n\t"
				  "		subi    r2,r2,1		\n\t"		// ~ 1 -
				  "		bne     r2,r0,loop	\n\t"		// ~ 2 - Branch (correctly predicted, taken)
				 );
}

/*
 * 'assembly' based delay function, not to be intended to be precise ...
 *
 *  Plain C can get optimized differently at different times. We use assembler code to bypass compiler optimization, which
 *  might change the timing of the actual C code ... The compiler takes care of registers used when returning to standard C code.
 *
 *  WARNING: Please note that the type of instruction memory highly impacts the loop time (int./ext.SRAM, DRAM, ...) . Cache memory can
 *  lower this, but it often still affects the first loop until the instructions are in the cache. If you need to be exact, put this code
 *  it in closely coupled memory.
 *
 *	@param - number of iterations
 *	@return - no return value
 */

extern void delay_v3(alt_u32);

/*
 * task_1: LED Toggeling - C based delay routine
 */

void task_1(void) {
	LEDS.DATA_REG = LEDS_OFF;
	while(1) {
		delay_v1(1000000);
		// read-modify-write register access
		LEDS.DATA_REG ^= 0xFF;
	}
}

/*
 * task_2: LED Toggeling - 'inline assembly' based delay routine
 */

void task_2(void) {
	LEDS.DATA_REG = LEDS_OFF;
	while(1){
		delay_v2(16666666);
		LEDS.DATA_REG ^= 0xFF;
	}
}

/*
 * task_3: LED Toggeling - 'assembly' based delay routine
 */

void task_3(void) {
	LEDS.DATA_REG = LEDS_OFF;
	while(1){
		delay_v3(16666666);
		LEDS.DATA_REG ^= 0xFF;
	}
}

/*
 * task_4: Moving LED (left-shift version)
 */

void task_4(void) {
	alt_u8 leds   = LSB;
	LEDS.DATA_REG = LEDS_OFF;
	while(1) {
		if(leds == MSB) {
			leds = LSB;
		} else {
			leds <<= 1;
		}
		LEDS.DATA_REG = leds;
		delay_v1(500000);
	}
}

/*
 * task_5: Moving LED (right-shift version)
 */

void task_5(void) {
	alt_u8 leds   = MSB;
	LEDS.DATA_REG = LEDS_OFF;
	while(1) {
		if(leds == LSB) {
			leds = MSB;
		} else {
			leds >>= 1;
		}
		LEDS.DATA_REG = leds;
		delay_v1(500000);
	}
}

/*
 * task_6: Ping-Pong LED
 */

void task_6(void) {
	alt_u8 leds      = LSB;
	alt_u8 direction = LEFT;
	LEDS.DATA_REG    = LEDS_OFF;
	while(1) {
		LEDS.DATA_REG = leds;
		delay_v2(500000);
		if((direction == LEFT)  && (leds == MSB))
			direction = RIGHT;
		if((direction == RIGHT) && (leds == LSB))
			direction = LEFT;

		if(direction == LEFT)
			leds <<= 1;
		else
			leds >>= 1;
	}
}

/*
 * task_7: Just playing arround ...
 */

alt_u32 delay_times[] = {1000000,2000000,300000,400000,500000,600000,700000,800000};

void task_7(void) {
	LEDS.DATA_REG    = LEDS_OFF;
	while(1) {
		for(alt_u8 i = 0; i < 8;i++) {
			LEDS.DATA_REG ^= 0xFF;
			delay_v3(delay_times[i]);
		}
	}
}
/*
 * task_8: turn on the LED when the pushbutton-0  is pressed ...
 */

void task_8(void) {
	LEDS.DATA_REG = LEDS_OFF;
	while(1) {
		LEDS.DATA_REG = (PUSH_BUTTONS.DATA_REG & (1 << PUSH_BUTTON_0)) ? 0 : 1;
	}
}

/*
 * task_9: polling based method to toggle the state of all eight LEDs when pushbutton-0 is pressed
 */

void task_9(void) {
	LEDS.DATA_REG = LEDS_OFF;
	while(1) {
		// wait until the button is pressed ...
		while((PUSH_BUTTONS.DATA_REG & (1 << PUSH_BUTTON_0)) == 1);
		LEDS.DATA_REG ^= 0xFF;
		// wait until the button is released ...
		while((PUSH_BUTTONS.DATA_REG & (1 << PUSH_BUTTON_0)) == 0);
	}
}

/*
 * task_10: Using the PIO 'Edge Capture Register' - Toggle the state of all eight LEDs when pushbutton-0 is pressed
 */

void task_10(void) {
	LEDS.DATA_REG = LEDS_OFF;
	PUSH_BUTTONS.EDGECAPTURE_REG = 0;
	while(1) {
		//Bit-0 in the edgecapture register is set to 1 whenever a negative edge is detected ...
		if(PUSH_BUTTONS.EDGECAPTURE_REG & (1 << PUSH_BUTTON_0)) {
			LEDS.DATA_REG ^= 0xFF;
			// reset (or clearing) bit-0 in the edgecapture register by writing a '1' to that particular bit position
			PUSH_BUTTONS.EDGECAPTURE_REG |= (1 << PUSH_BUTTON_0);
		}
	}
}


/*
 * task_11: pretty much the same as the previous example ...
 */

void task_11(void) {
	alt_u32 tmp_reg;
	LEDS.DATA_REG = LEDS_OFF;
	PUSH_BUTTONS.EDGECAPTURE_REG = 0;
	while(1) {
		while(PUSH_BUTTONS.EDGECAPTURE_REG == 0);
		tmp_reg = PUSH_BUTTONS.EDGECAPTURE_REG;
		PUSH_BUTTONS.EDGECAPTURE_REG |= tmp_reg;
		LEDS.DATA_REG ^= 0xFF;
	}
}


/*
 * task_12: Toggle the state of LED-0 or LED-1 in case that the associated pushbutton (0/1) is pressed
 */

void task_12(void) {
	alt_u8 previousPbState, newPbStates, buttonPushed;
	LEDS.DATA_REG    = LEDS_OFF;
	previousPbState  = ~PUSH_BUTTONS.DATA_REG;
	while(1) {
		newPbStates     = ~PUSH_BUTTONS.DATA_REG;
		buttonPushed    = ~previousPbState & newPbStates;
		LEDS.DATA_REG   = LEDS.DATA_REG ^ buttonPushed;
		previousPbState = newPbStates;
	}
}


/*
 * task_13: toggle the state of all leds when one of the two buttons is pressed
 */

void task_13(void) {
	alt_u32 tmp_reg;
	LEDS.DATA_REG = LEDS_OFF;
	PUSH_BUTTONS.EDGECAPTURE_REG = 0;
	while(1) {
		if((PUSH_BUTTONS.EDGECAPTURE_REG & (1 << PUSH_BUTTON_0)) || (PUSH_BUTTONS.EDGECAPTURE_REG & (1 << PUSH_BUTTON_1))  ) {
			// reset the respective bit in the edgecapture register by writing a '1' to that particular bit position
			tmp_reg = PUSH_BUTTONS.EDGECAPTURE_REG;
			PUSH_BUTTONS.EDGECAPTURE_REG |= tmp_reg;
			LEDS.DATA_REG ^= 0xFF;
		}
	}
}

/*
 * task_14: irq-version of demo-1, LED access within main()
 */

static void push_button_irq_task_14(void *context, alt_u32 id);

static void push_button_irq_task_14(void *context, alt_u32 id) __attribute__ ((section (".exceptions")));

void task_14(void) {
	LEDS.DATA_REG = LEDS_OFF;
	PUSH_BUTTONS.INTERRUPTMASK_REG = (1 << PUSH_BUTTON_0);
	PUSH_BUTTONS.EDGECAPTURE_REG   = 0;
	// registering the interrupt service routine ...
	alt_ic_isr_register(PUSH_BUTTON_IRQ_INTERRUPT_CONTROLLER_ID,
						PUSH_BUTTON_IRQ,
						(void *)push_button_irq_task_14,
						ZERO,
						ZERO
						);

	while(1) {
		if(irq_exchange) {
			LEDS.DATA_REG ^= 0xFF;
			irq_exchange   = 0x00;
		}
	}
}


/*
 * task_15:  same as the previous example, however right now using both pushbuttons ...
 */

static void push_button_irq_task_15(void *context, alt_u32 id) __attribute__ ((section (".exceptions")));

void task_15(void) {
	LEDS.DATA_REG = LEDS_OFF;
	PUSH_BUTTONS.INTERRUPTMASK_REG = ((1 << PUSH_BUTTON_0) | (1 << PUSH_BUTTON_1));
	PUSH_BUTTONS.EDGECAPTURE_REG   = 0;
	// registering the interrupt service routine ...
	alt_ic_isr_register(PUSH_BUTTON_IRQ_INTERRUPT_CONTROLLER_ID,
						PUSH_BUTTON_IRQ,
						(void *)push_button_irq_task_15,
						ZERO,
						ZERO
						);
	while(1) {
		if(irq_exchange) {
			LEDS.DATA_REG ^= 0xFF;
			irq_exchange   = 0x00;
		}
	}
}

/*
 *	task_16: Johnson Counter Version-1: all bits are shifted to the left, with the INVERTED MSB looping back to the LSB position ...
 *	This version doesn't work, check the assembly code generated and explain the reason why ...
 */

void task_16(void) {
	alt_u8 leds = 1;
	alt_u8 tmp  = 0;
	LEDS.DATA_REG = LEDS_OFF;
	while(1) {
		tmp = (~(leds & 0x80)) >> 7;
		leds <<= 1;
		leds |= tmp;
		LEDS.DATA_REG = leds;
		delay_v3(500000);
	}
}

/*
 *	task_17: Johnson Counter Version-2: all bits are shifted to the left, with the INVERTED MSB looping back to the LSB position ...
 *	This version works ... Why?
 */

void task_17(void) {
	alt_u8 leds = 1;
	alt_u8 tmp  = 0;
	LEDS.DATA_REG = LEDS_OFF;
	while(1) {
		tmp = (~(leds & 0x80));
		tmp = tmp >> 7;
		leds <<= 1;
		leds |= tmp;
		LEDS.DATA_REG = leds;
		delay_v3(500000);
	}
}

/*
 *	task_18: Johnson Counter Version-3: all bits are shifted to the left, with the INVERTED MSB looping back to the LSB position ...
 *	This version works ... Why?
 */

void task_18(void) {
	alt_u8 leds = 1;
	alt_u8 tmp  = 0;
	LEDS.DATA_REG = LEDS_OFF;
	while(1) {
		tmp = ((alt_u8)(~(leds & 0x80))) >> 7;
		leds <<= 1;
		leds |= tmp;
		LEDS.DATA_REG = ~leds;
		delay_v3(500000);
	}
}

/*
 *	task_19: Johnson Counter Version-4: all bits are shifted to the left, with the INVERTED MSB looping back to the LSB position ...
 *	This version works ... Why?
 */

void task_19(void) {
	alt_u8 leds = 1;
	alt_u8 lsb  = 0;
	LEDS.DATA_REG = LEDS_OFF;
	while(1) {
		lsb = ((leds ^ 0x80) & 0x80) >> 7;
		leds <<= 1;
		leds |= lsb;
		LEDS.DATA_REG = ~leds;
		delay_v3(500000);
	}
}

/*
 *	task_20: You can use the outset and outclear registers to set and clear individual bits
 *  of the output port. For example, to set bit 6 of the output port, write 0x40 ... These register
 *	must be created at design time! Key take-away: There is no read-modify-write cycle necessary, we are 
 *  just writing to the respective registers
 */

void task_20(void) {
	alt_u8 switch_leds = 1;
	LEDS.DATA_REG      = LEDS_OFF;
	while(1) {
		if(switch_leds){
			LEDS.OUTCLEAR_REG = 0x0F; //0x0000 1111 - clearing these 4 lower bits
			LEDS.OUTSET_REG   = 0xF0; //0x1111 0000 - setting these 4 higher bits
			switch_leds = 0;
		} else {
			LEDS.OUTCLEAR_REG = 0xF0;
			LEDS.OUTSET_REG   = 0x0F;
			switch_leds = 1;
		}
		delay_v3(5000000);
	}
}

/*
 * task_21: how to exchange data between the ISR and the actual main routine ... When an ISR is dispateched, 
 * a pointer to a global variable is submitted to the ISR. We declare a void pointer. this pointer is initialized 
 * with the address of the global
 * variable. Inside the ISR, we've got to cast this pointer ...
 */

volatile alt_u32 edge_capture = 0;

static void push_button_irq_task_21(void *context, alt_u32 id) __attribute__ ((section (".exceptions")));

void task_21(void) {

	LEDS.DATA_REG = LEDS_OFF;

	alt_u32 edge_capture_tmp = 0;

	void * edge_capture_ptr = (void *) & edge_capture;

	// registering the interrupt service routine ...
	alt_ic_isr_register(PUSH_BUTTON_IRQ_INTERRUPT_CONTROLLER_ID,
						PUSH_BUTTON_IRQ,
						(void *)push_button_irq_task_21,
						edge_capture_ptr,
						ZERO
						);

	PUSH_BUTTONS.INTERRUPTMASK_REG = ((1 << PUSH_BUTTON_0) | (1 << PUSH_BUTTON_1));
	PUSH_BUTTONS.EDGECAPTURE_REG   = 0;

	while(1) {
		if(edge_capture != edge_capture_tmp) {
			LEDS.DATA_REG    = edge_capture;
			edge_capture_tmp = edge_capture;
		}
	}
}

int main(void){

	task_8();

	while(1){
	}
	return 0;
}



static void push_button_irq_task_14(void *context, alt_u32 id) {
	PUSH_BUTTONS.EDGECAPTURE_REG |= (1 << PUSH_BUTTON_0);
	irq_exchange = 1;
}

static void push_button_irq_task_15(void *context, alt_u32 id) {
	alt_u32 tmp_reg = PUSH_BUTTONS.EDGECAPTURE_REG;
	PUSH_BUTTONS.EDGECAPTURE_REG |= tmp_reg;
	irq_exchange = 1;
}

static void push_button_irq_task_21(void *context, alt_u32 id) {
	volatile alt_u32 * local_tmp = (volatile alt_u32 *) context;
	// IRQ acknowledged ...
	alt_u32 local_reg = PUSH_BUTTONS.EDGECAPTURE_REG;
	PUSH_BUTTONS.EDGECAPTURE_REG = local_reg;
	// ...
	*local_tmp = local_reg;
}

