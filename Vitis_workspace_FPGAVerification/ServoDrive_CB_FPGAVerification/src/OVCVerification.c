/*
 * OVCVerification.c
 *
 *  Created on: 08.10.2025
 *      Author: SESA807379 (Suhas Bangalore Mruthunjaya)
 */

#include "OVCVerification.h"
#include <regex.h>
#include <stdbool.h>

u8 ovc_temp_recv_buffer[BUFFER_SIZE] = {};

void ovc_axi_phase_write(u32 phase_val)
{
	Xil_Out32(AXI_PRACTISE_IP_BASE_ADDR + DAC_PHASE_AXIS_REG_OFFSET, phase_val);
	usleep(1000); // Small delay for AXI write
}

void ovc_axi_staticData_write(int value)
{
    Xil_Out32(AXI_PRACTISE_IP_BASE_ADDR + STATIC_DATA_REG_OFFSET, value);
    //xil_printf("static data written : 0x%x", static_data[index]);
    usleep(1000); // Small delay for AXI write
}

void ovc_axi_startOp_write()
{
    Xil_Out32(AXI_PRACTISE_IP_BASE_ADDR + START_OP_REG_OFFSET, 0x01);
    usleep(1000); // Small delay for AXI write
}

bool is_valid_16bit_hex(const char *str)
{
    if (!str || strlen(str) != 6)
        return false;
    if (str[0] != '0' || str[1] != 'x')
        return false;

    for (int i = 2; i < 6; i++) {
        char c = str[i];
        if (!((c >= '0' && c <= '9') ||
              (c >= 'a' && c <= 'f') ||
              (c >= 'A' && c <= 'F')))
            return false;
    }
    return true;
}


void ovc_static_verification()
{
	 uint16_t hexValue = 0;
     xil_printf("Please send the 16 bit hexadecimal CurrentValue (0x0-f/0x0-F) to receive the OVC status and event values");

	 TotalReceivedCountUART0 = 0; // Reset count
	 while(TotalReceivedCountUART0 == 0){
		 // Do other tasks or simply yield/sleep briefly
		 usleep(100);
	 }

	 if (TotalReceivedCountUART0 > 0)
	 {
		 strncpy((char *)ovc_temp_recv_buffer, (char *)RecvBufferUART0, BUFFER_SIZE);
		 ovc_temp_recv_buffer[BUFFER_SIZE - 1] = '\0';
	 }

	 xil_printf("Received value is : %s\n", ovc_temp_recv_buffer);

	 if(is_valid_16bit_hex((char*) ovc_temp_recv_buffer))
	 {
		 xil_printf("Valid Current (hexa)Value\n");
		 hexValue = (uint16_t)strtoul((char*)ovc_temp_recv_buffer, NULL, 16);

	 }else{
		 xil_printf("Not valid Current (hexa)Value. Please redo the Verification\n");
	 }

//	 xil_printf("hexValue is %d", hexValue);

	 ovc_axi_staticData_write(hexValue);

	 ovc_axi_startOp_write();

	 send_via_UART1();

	 while (ringbuffer_inst.m_fillLevel != 2){};

	 xil_printf("Received from UART1: ");

	 while (ringbuffer_inst.m_fillLevel > 0)
	 {

		 RB_content_t data = 0;
	 	 RB_get(&ringbuffer_inst, &data);
	 	 xil_printf("%c", data);

	 }

	 xil_printf("\r\n");

	 RB_clear(&ringbuffer_inst);

}
