/*
Group Assignment by -
Name: Suhas Bangalore Mruthunjaya 
Matriculation Number: 1119281 
Name: Umesh Vijaykumar Chandargi 
Matriculation Number: 1119268
*/

`timescale 1ns/1ps

`define HALF_CLOCK_PERIOD   10
`define RESET_PERIOD 	   100
`define DELAY 	    	   	200
`define SIM_DURATION 	  10000

module sha1_Implimentation_tb();

	// ### signals that should get monitored ... 
	logic tb_q_done;
	logic [511:0]tb_data;
	logic [159:0]tb_q_data;

	// ### clock generation process ...
   logic tb_local_clock = 0;
 	initial 
		begin: clock_generation_process
			tb_local_clock = 0;
				forever begin
					#`HALF_CLOCK_PERIOD tb_local_clock = ~tb_local_clock;
				end
		end	

	logic tb_local_reset_n = 0;
	
	initial 
		begin: reset_generation_process
			$display ("Simulation starts ...");
			// reset assertion ... 
			#`RESET_PERIOD tb_local_reset_n = 1'b1;
			#`SIM_DURATION
			$display ("Simulation done ...");
			$stop();
		end
		
	logic [9:0] counter = 0;
	
	always_ff@(posedge tb_local_clock)
		counter = counter + 1;
		
	// if counter is equal to 255, tb_start is set to one ... 
	logic tb_start; assign tb_start = (counter >  128) ? 1'b1 : 1'b0;
	
	//this 512 bits of data is the preprocessing output of "FSOC22/23 is fun!".
	assign tb_data = 512'b01000110010100110100111101000011001100100011001000101111001100100011001100100000011010010111001100100000011001100111010101101110001000011000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000010001000;
	
	sha1_Implimentation dut_0 (.clk(tb_local_clock),
									  .reset_n(tb_local_reset_n),
									  .start(tb_start),
									  .q_done(tb_q_done),
									  .data(tb_data),
									  .q_data(tb_q_data)
									  );
	
endmodule 