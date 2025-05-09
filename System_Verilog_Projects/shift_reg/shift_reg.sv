module shift_reg(
 input logic d, clk, reset_n,
 output logic q
 );
 logic [5:0] s_reg = 0;


 always_ff@(posedge clk)
 begin
 if(reset_n == 0)
 q <= 0;
 else
// begin
 //s_reg <= {d,s_reg[5:1]};
	s_reg <= {s_reg[4:0],d};
	q <= (s_reg == 6'b000111) ? 1'b1 : 1'b0;
//	if(s_reg == 6'b000111)
//	q <= 1'b1;
//	else 
//	q <= 1'b0;
//	end
	end
	


endmodule