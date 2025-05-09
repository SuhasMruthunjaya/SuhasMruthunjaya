module Syn_resetable_left_shift(
 input logic [3:0]d, 
 input logic clk, reset_n,
 output logic q
 );
 logic [3:0] s_reg = 0;

 always_ff@(posedge clk)
 if(reset_n == 0)
 s_reg <= 0;
 else
 s_reg <= {s_reg[2:0],d};

 assign q = s_reg[3];

 endmodule
