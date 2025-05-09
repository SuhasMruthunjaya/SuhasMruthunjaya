`timescale 1ns/1ps
`define HALF_CLOCK_PERIOD 10
`define RESET_PERIOD 100
`define SIM_DURATION 5000000

module ddfs_tb();

   logic [7:0] tb_q,tb_q_phase;
	logic [7:0] tb_q_temp;

   logic tb_clk = 0;
   initial begin
      tb_clk = 0;
      forever begin
         #`HALF_CLOCK_PERIOD tb_clk = ~tb_clk;
      end
   end

   logic tb_reset_n = 0;
   initial begin
      $display("Simulation starts ...");
      #`RESET_PERIOD
      tb_reset_n = 1;
      #`SIM_DURATION
      $stop();
   end

   ddfs inst_dut (
      .clk(tb_clk),
      .reset_n(tb_reset_n),
      .q(tb_q),
		.lut_address(tb_q_phase),
		.q_temp(tb_q_temp)
   );

endmodule
