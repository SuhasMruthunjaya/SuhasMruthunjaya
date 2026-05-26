/*
 * by Christian Jakob, h_da, fbeit, Darmstadt, 13 January 2023
 *
 * Lessons learned:
 *
 * Something general at the beginning: Accesses to memory-mapped I/O should not be cached (or the devices will not see the memory
 * access), while accesses to regular memory should be cached.
 *
 * The Nios2 hardware, which is used in this test has a dedicated data cache of 2kB. In general, the Nios II architecture provides the following
 * methods for bypassing the data cache:
 *
 * 		1. I/O load and store instructions - "I/O" variants of loads and stores (ldwio, stwio) bypass the cache while the regular versions
 * 		   (ldw, stw) do not
 * 		2. Bit-31 cache bypass (this option must be activated at hardware compile time! THIS OPTION IS NOT ACTIVATED!
 *
 * Since the 'Bit-31 cache bypass' option is not set in the present Nios2 hardware design (on purpose), we've got to go the way via dedicated
 * compiler flags. As stated above, the Nios2 has specialized memory access instructions that are bypassing the cache: ldwio/stwio, ....
 *
 * By setting the compiler flag "-mno-cache-volatile", the compiler generates the respective I/O accesses. If not, the nios2-elf-gcc compiler
 * generates regular ldw/stw memory accesses.
 *
 * We use the -mno-cache-volatile compiler flag and declare the variables of interest as volatile. In fact MMIOs that are achieved by
 * reading/writing some registers must always be volatile.
 *
 *      -mno-cache-volatile
 *      -mcache-volatile
 *
 *       Volatile memory access bypass the cache using the I/O variants of the load and store instructions. The default is not to bypass the
 *       cache: https://gcc.gnu.org/onlinedocs/gcc/Nios-II-Options.html
 *
 * Another option is always bypass the cache by -mbypass-cache
 *
 */

typedef unsigned int alt_u32;

#define __I  volatile const	// read-only permission
#define __IO volatile 		// read/write permission ...
#define __O  volatile 		// write only permission ;-) doesn't work in C...

// there is no MSB-bit cache bypassing, so no further address modification ...
#define LED_BASE_ADDRESS 0x9000

#define LEDS_ON	 0x00
#define LEDS_OFF 0xFF

// PIO related register
typedef struct {
	__IO alt_u32 DATA_REG;
	__IO alt_u32 DIRECTION_REG;
	__IO alt_u32 INTERRUPTMASK_REG;
	__IO alt_u32 EDGECAPTURE_REG;
	 __O alt_u32 OUTSET_REG;
	 __O alt_u32 OUTCLEAR_REG;
} PIO_TYPE;

#define LEDS (*((PIO_TYPE *) LED_BASE_ADDRESS))

static void delay(alt_u32 iterations) {
	volatile alt_u32 i;
	for(i = iterations; i > 0; i--);
}

int main(void) {
	LEDS.DATA_REG = LEDS_OFF;
	while(1) {
		LEDS.DATA_REG ^= 0xFF;
		delay(500000);
	}
	return 0;
}
