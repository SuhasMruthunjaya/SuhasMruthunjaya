/*`timescale 1ns/1ps

`define HALF_CLOCK_PERIOD   10
`define RESET_PERIOD 	   100
`define DELAY 	    	   	200
`define SIM_DURATION 	  5000

module time_base_generation_tb();
logic tb_clk;
logic tb_reset_n;
logic tb_q;
logic tb_enable;
//logic tb_temp;

initial 
begin 

#100 tb_reset_n = 1;

end 


initial 
begin : Clk_generaton_process

tb_clk=0;

forever #`HALF_CLOCK_PERIOD tb_clk = ~ tb_clk; 

end


time_base_generation #(.cycles(1025)) inst0 (.clk(tb_clk),
									 .reset_n(tb_reset_n),
									 .q(tb_q),
									 .enable(tb_enable)
									);

endmodule 

*/

`timescale 1ns/1ps
`define half_clock_period 10
`define reset_period 200
`define sim_duration 50000

module time_base_generation_tb();

logic tb_clk = 0;
logic tb_reset_n = 0;
logic enable;
logic [7:0]tb_q;

initial begin: clk_generation_process
	forever
		#`half_clock_period tb_clk = ~ tb_clk;
end

initial begin: reset_generation_process

	$display("simulation starts..");
	
	#`reset_period tb_reset_n = 1'b1;
	
//	#`sim_duration
//	$stop();

end

time_base_generation #(.cycles(521)) inst0 (.clk(tb_clk),
									 .reset_n(tb_reset_n),
									 .q(tb_q),
									 .enable(enable));


endmodule

