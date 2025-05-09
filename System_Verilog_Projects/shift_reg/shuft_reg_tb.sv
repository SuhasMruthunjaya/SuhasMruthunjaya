`timescale 1ns/ 1ps
`define Half_clock_period 10


module shuft_reg_tb();
	
	logic tb_q, tb_d, tb_reset_n,tb_clk;
	


	shift_reg inst_0(	.d(tb_d),
							.reset_n(tb_reset_n),
							.q(tb_q),
							.clk(tb_clk)
						   );		
							
initial 
begin
tb_clk=0;
forever begin
	# `Half_clock_period tb_clk= ~tb_clk;
	end
end
							
initial
begin
#10
tb_reset_n = 1'b1;

tb_d = 1'b0;

#60

tb_d = 1'b1;

#60

tb_d = 1'b0;

#60

tb_d = 1'b0;

#60

tb_d = 1'b1;

#60

tb_d = 1'b0;

#60

;
end
endmodule
