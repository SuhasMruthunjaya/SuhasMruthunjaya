`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 24.02.2023 10:02:25
// Design Name: 
// Module Name: pwm_ip_tb
// Project Name: 
// Target Devices: 
// Tool Versions: 
// Description: 
// 
// Dependencies: 
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
//////////////////////////////////////////////////////////////////////////////////
import axi_vip_pkg::*;
import pwm_ip_sim_axi_vip_0_0_pkg::*;
import pwm_ip_sim_axi_pwm_control_0_pkg::*;

xil_axi_resp_t 	resp;
bit[31:0]  addr, data, base_addr = 32'h44A0_0000;

module pwm_ip_tb();

 // Clock signal
  bit                                     clock;
  // Reset signal
  bit                                     reset;
  
  // PWM signals
  bit                                     pwm_trigger;
  bit [1:0]                               PWM_U;
  bit [1:0]                               PWM_V;
  bit [1:0]                               PWM_W; 
    
  // instantiate bd
  pwm_ip_sim_DUT DUT
        (
            .aclk(clock),
            .areset(reset),
            .PWM_Trig_0(pwm_trigger),
            .PWM_U_0(PWM_U),
            .PWM_V_0(PWM_V),
            .PWM_W_0(PWM_W)
        ); 
        
  initial begin
    reset <= 1'b1;
    repeat (5) @(negedge clock);
  end
  
  always #1.66666 clock <= ~clock; 
  
  // declare the agent for the master VIP
  pwm_ip_sim_axi_pwm_control_0_mst_t      master_agent;
  
  parameter SIZE = 2048;
  reg [15:0] rom_memory_0 [SIZE-1:0]; 
  reg [15:0] rom_memory_1 [SIZE-1:0]; 
  reg [15:0] rom_memory_2 [SIZE-1:0]; 
  integer i;
  
  //Main process
  initial begin
    // read sine look up table
    $readmemh("sine_ph0.mem", rom_memory_0);
    $readmemh("sine_ph1.mem", rom_memory_1);
    $readmemh("sine_ph2.mem", rom_memory_2);
    // create a new agent
    master_agent = new("master vip agent", DUT.pwm_ip_sim_i.axi_pwm_control.inst.IF); 
    // start the clock
    master_agent.start_master(); 
        
    // send frequency word for 500kHz
    #200ns
    wait(pwm_trigger == 1'b1)
    addr = 16'h0104;
    data = 32'h028F5C29;
    master_agent.AXI4LITE_WRITE_BURST(base_addr + addr, 0, data, resp);
        
    // send duty cycle to 50%
    #200ns
    addr = 16'h010C;
    data = 32'h00004000;
    master_agent.AXI4LITE_WRITE_BURST(base_addr + addr, 0, data, resp);
    
    // set duty cycle to 50%
    #200ns
    addr = 16'h010C;
    data = 32'h00004000;
    master_agent.AXI4LITE_WRITE_BURST(base_addr + addr, 0, data, resp);
    #200ns
    addr = 16'h0110;
    master_agent.AXI4LITE_WRITE_BURST(base_addr + addr, 0, data, resp);
    #200ns
    addr = 16'h0114;
    master_agent.AXI4LITE_WRITE_BURST(base_addr + addr, 0, data, resp);
    
    // set dead time to 10 clock cycles (50MHz) -> 200ns
    #200ns
    addr = 16'h0100;
    data = 32'h0000000A;
    master_agent.AXI4LITE_WRITE_BURST(base_addr + addr, 0, data, resp);
    
    // release enable for PWM outputs
    #200ns
    addr = 16'h0108;
    data = 32'h00000001;
    master_agent.AXI4LITE_WRITE_BURST(base_addr + addr, 0, data, resp); 
    
    // enable IP
    #200ns
    addr = 16'h0004;
    data = 32'h00000001;
    master_agent.AXI4LITE_WRITE_BURST(base_addr + addr, 0, data, resp);
    
    // rotating voltage vector 
    #200ns
    for (i = 0; i < $size(rom_memory_0); i++) begin
        wait(pwm_trigger == 1'b1)
            master_agent.AXI4LITE_WRITE_BURST(base_addr + 16'h10C, 0, rom_memory_0[i], resp);
            #30ns
            master_agent.AXI4LITE_WRITE_BURST(base_addr + 16'h110, 0, rom_memory_1[i], resp);
            #30ns
            master_agent.AXI4LITE_WRITE_BURST(base_addr + 16'h114, 0, rom_memory_2[i], resp);
    end
  end
endmodule
