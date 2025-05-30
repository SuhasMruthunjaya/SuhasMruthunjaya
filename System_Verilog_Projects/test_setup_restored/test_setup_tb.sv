`timescale 1ns/1ps

`define HALF_CLOCK_PERIOD     10
`define RESET_PERIOD 	      20
`define SIM_DURATION 	50000000

module test_setup_tb();
	
	logic signed [15:0] tb_q_0, tb_q_1;
	
	// ### clock generation process ..
	
	logic tb_local_clock = 0;
	initial 
		begin: clock_generation_process
			tb_local_clock = 0;
			forever	
				begin
					#`HALF_CLOCK_PERIOD tb_local_clock = ~tb_local_clock;
				end
		end	
		
	// ### (active low) reset generation process ...
	logic tb_local_reset = 1'b0;
	
	initial 
		begin: reset_generation_process
			$display ("Simulation starts ...");
			#`RESET_PERIOD tb_local_reset = 1'b1;	
			#`SIM_DURATION
			$stop();
		end

	test_setup inst_0(.clk(tb_local_clock),
						   .reset_n(tb_local_reset),
							.q_0(tb_q_0),
							.q_1(tb_q_1)
						   );		
endmodule
