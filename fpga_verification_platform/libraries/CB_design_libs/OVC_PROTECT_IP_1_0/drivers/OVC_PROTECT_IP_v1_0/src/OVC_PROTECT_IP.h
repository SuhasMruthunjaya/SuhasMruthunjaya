
#ifndef OVC_PROTECT_IP_H
#define OVC_PROTECT_IP_H


/****************** Include Files ********************/
#include "xil_types.h"
#include "xstatus.h"

#define OVC_PROTECT_IP_S_AXI_LITE_OVC_PROTECT_IP_ID_OFFSET  0x0 // ID for the IP Core:  0x00000002
#define OVC_PROTECT_IP_S_AXI_LITE_IP_VERSION_OFFSET         0x4 // IP Core Version :    0x00000001 has to be automated later
#define OVC_PROTECT_IP_S_AXI_LITE_OVC_LIMITS_OFFSET         0x8 // limits register: [11:0]-low limit (overcurrent) [27:16]-high limit (short circuit)
#define OVC_PROTECT_IP_S_AXI_LITE_OVC_SETTINGS_OFFSET       0xC // settings register: [11:0]-current offset (0x800 default) [27:16]- ovc timer (0x280 default - 10us)


/**************************** Type Definitions *****************************/
/**
 *
 * Write a value to a OVC_PROTECT_IP register. A 32 bit write is performed.
 * If the component is implemented in a smaller width, only the least
 * significant data is written.
 *
 * @param   BaseAddress is the base address of the OVC_PROTECT_IPdevice.
 * @param   RegOffset is the register offset from the base to write to.
 * @param   Data is the data written to the register.
 *
 * @return  None.
 *
 * @note
 * C-style signature:
 * 	void OVC_PROTECT_IP_mWriteReg(u32 BaseAddress, unsigned RegOffset, u32 Data)
 *
 */
#define OVC_PROTECT_IP_mWriteReg(BaseAddress, RegOffset, Data) \
  	Xil_Out32((BaseAddress) + (RegOffset), (u32)(Data))

/**
 *
 * Read a value from a OVC_PROTECT_IP register. A 32 bit read is performed.
 * If the component is implemented in a smaller width, only the least
 * significant data is read from the register. The most significant data
 * will be read as 0.
 *
 * @param   BaseAddress is the base address of the OVC_PROTECT_IP device.
 * @param   RegOffset is the register offset from the base to write to.
 *
 * @return  Data is the data from the register.
 *
 * @note
 * C-style signature:
 * 	u32 OVC_PROTECT_IP_mReadReg(u32 BaseAddress, unsigned RegOffset)
 *
 */
#define OVC_PROTECT_IP_mReadReg(BaseAddress, RegOffset) \
    Xil_In32((BaseAddress) + (RegOffset))

/************************** Function Prototypes ****************************/
/**
 *
 * Run a self-test on the driver/device. Note this may be a destructive test if
 * resets of the device are performed.
 *
 * If the hardware system is not built correctly, this function may never
 * return to the caller.
 *
 * @param   baseaddr_p is the base address of the OVC_PROTECT_IP instance to be worked on.
 *
 * @return
 *
 *    - XST_SUCCESS   if all self-test code passed
 *    - XST_FAILURE   if any self-test code failed
 *
 * @note    Caching must be turned off for this function to work.
 * @note    Self test may fail if data memory and device are not on the same bus.
 *
 */
XStatus OVC_PROTECT_IP_Reg_SelfTest(void * baseaddr_p);

#endif // OVC_PROTECT_IP_H
