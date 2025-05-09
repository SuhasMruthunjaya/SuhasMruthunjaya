module time_base_gen_tb();

logic in, out, clk;

time_base_gen_tb inst0( .d(in),
								.clk(clk),
								.q(out)
								);

								
								
initial
 
							

begin

in = 1'b1;
#10;

in = 1'b0;
#10;

end

always #10 clk = ~clk;

endmodule