/*
 * File Name:         CodeGen\ipcore\PWM_ip_v1_0\include\PWM_ip_addr.h
 * Description:       C Header File
 * Created:           2023-01-23 08:19:58
*/

#ifndef PWM_IP_H_
#define PWM_IP_H_

#define  IPCore_Reset_PWM_ip       0x0  //write 0x1 to bit 0 to reset IP core
#define  IPCore_Enable_PWM_ip      0x4  //enabled (by default) when bit 0 is 0x1
#define  IPCore_Timestamp_PWM_ip   0x8  //contains unique IP timestamp (yymmddHHMM): 2301230818: 2301230819
#define  Deadtime_Data_PWM_ip      0x100  //data register for Inport Deadtime
#define  Frequency_Data_PWM_ip     0x104  //data register for Inport Frequency
#define  Enable_Data_PWM_ip        0x108  //data register for Inport Enable
#define  Duty_U_Data_PWM_ip        0x10C  //data register for Inport Duty_U
#define  Duty_V_Data_PWM_ip        0x110  //data register for Inport Duty_V
#define  Duty_W_Data_PWM_ip        0x114  //data register for Inport Duty_W
#define  PWM_Freq_Data_PWM_ip      0x118  //data register for Outport PWM_Freq
#define  PWM_CntDir_Data_PWM_ip    0x11C  //data register for Outport PWM_CntDir

#endif /* PWM_IP_H_ */
