//Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
//Copyright 2022-2023 Advanced Micro Devices, Inc. All Rights Reserved.
//--------------------------------------------------------------------------------
//Tool Version: Vivado v.2023.1 (lin64) Build 3865809 Sun May  7 15:04:56 MDT 2023
//Date        : Thu Feb 20 13:35:44 2025
//Host        : LIABDIT18041 running 64-bit Ubuntu 18.04.6 LTS
//Command     : generate_target ovc_protect_wrapper.bd
//Design      : ovc_protect_wrapper
//Purpose     : IP block netlist
//--------------------------------------------------------------------------------
`timescale 1 ps / 1 ps

module ovc_protect_wrapper
   (aclk,
    aresetn,
    current_raw_adc,
    ovc_clk,
    ovc_event,
    ovc_release,
    ovc_reset_n,
    ovc_status,
    trigger_ovc);
  input aclk;
  input aresetn;
  input [35:0]current_raw_adc;
  input ovc_clk;
  output ovc_event;
  input ovc_release;
  input ovc_reset_n;
  output [5:0]ovc_status;
  input trigger_ovc;

  wire aclk;
  wire aresetn;
  wire [35:0]current_raw_adc;
  wire ovc_clk;
  wire ovc_event;
  wire ovc_release;
  wire ovc_reset_n;
  wire [5:0]ovc_status;
  wire trigger_ovc;

  ovc_protect ovc_protect_i
       (.aclk(aclk),
        .aresetn(aresetn),
        .current_raw_adc(current_raw_adc),
        .ovc_clk(ovc_clk),
        .ovc_event(ovc_event),
        .ovc_release(ovc_release),
        .ovc_reset_n(ovc_reset_n),
        .ovc_status(ovc_status),
        .trigger_ovc(trigger_ovc));
endmodule
