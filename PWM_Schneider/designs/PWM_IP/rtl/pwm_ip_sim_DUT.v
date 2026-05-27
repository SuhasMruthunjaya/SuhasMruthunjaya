//Copyright 1986-2021 Xilinx, Inc. All Rights Reserved.
//--------------------------------------------------------------------------------
//Tool Version: Vivado v.2021.2 (win64) Build 3367213 Tue Oct 19 02:48:09 MDT 2021
//Date        : Fri Feb 24 09:56:50 2023
//Host        : WTDELVSE201964L running 64-bit major release  (build 9200)
//Command     : generate_target pwm_ip_sim_wrapper.bd
//Design      : pwm_ip_sim_wrapper
//Purpose     : IP block netlist
//--------------------------------------------------------------------------------
`timescale 1 ps / 1 ps

module pwm_ip_sim_DUT
   (PWM_Trig_0,
    PWM_U_0,
    PWM_V_0,
    PWM_W_0,
    aclk,
    areset);
  output PWM_Trig_0;
  output [1:0]PWM_U_0;
  output [1:0]PWM_V_0;
  output [1:0]PWM_W_0;
  input aclk;
  input areset;

  wire PWM_Trig_0;
  wire [1:0]PWM_U_0;
  wire [1:0]PWM_V_0;
  wire [1:0]PWM_W_0;
  wire aclk;
  wire areset;

  pwm_ip_sim pwm_ip_sim_i
       (.PWM_Trig_0(PWM_Trig_0),
        .PWM_U_0(PWM_U_0),
        .PWM_V_0(PWM_V_0),
        .PWM_W_0(PWM_W_0),
        .aclk(aclk),
        .areset(areset));
endmodule
