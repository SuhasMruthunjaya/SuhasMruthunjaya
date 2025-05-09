 // SystemVerilog Example ‘1’- Testbench for lp_filter.sv
 // written by Dr. C. Jakob, fbeit, h_da, April 2022, christian.jakob@h-da.de

 `timescale 1ns/1ps
 `define FULL_CLOCK_PERIOD 2000000
 `define HALF_CLOCK_PERIOD 10
 `define RESET_PERIOD 4000
 `define SIM_DURATION 20000

 module Recursive_IIRFilter_Digital_Resonator_tb();

 // ### clock generation process ...
 logic tb_local_clock = 0;
 logic tb_enable;
 initial
 begin: clock_generation_process
 tb_local_clock = 0;
 forever begin
 #`HALF_CLOCK_PERIOD tb_local_clock = ~tb_local_clock;
 end
 end

 logic tb_local_reset_n = 1'b0;
 logic [15:0] tb_test_sig = 16'b0000000000000000;
 logic [15:0] tb_q;
 logic [15:0] test_signal_rom [2**10-1:0];

 integer i;
 integer j;

 initial
 begin: reset_generation_process
 $display ("Simulation starts ...");
 reset_filter;
 $readmemh("output.txt", test_signal_rom);
 //for(j = 0; j < 2000; j = j+1) begin
 for (i = 0; i < 1024; i = i+1) begin
 #`FULL_CLOCK_PERIOD tb_test_sig = (test_signal_rom[i]);
 end
 //i = 0;
 //end
 //#`SIM_DURATION
 $display ("Simulation done ...");
 //$stop();
 end

 Recursive_IIRFilter_Digital_Resonator inst1 (.clk(tb_local_clock),
 .reset_n(tb_local_reset_n),
 .d(tb_test_sig),
 .q(tb_q),
 .enable(tb_enable));

 task reset_filter; begin
 tb_local_reset_n = 1'b0;
 #`RESET_PERIOD
 tb_local_reset_n = 1'b1;
 end
 endtask
 endmodule 