module third_assignment_c (input logic d,reset_n,clk,
						  output logic q);

logic[5:0] s_reg;

always_ff@(posedge clk)
if(reset_n==0)
	s_reg <= 0;
else 
	s_reg <= {s_reg[4:0],d};

assign q=(s_reg== 6'b000111)?1:0;

endmodule 