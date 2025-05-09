module Syn_resetable_reg(
input logic reset_n, sload, clk,
input logic [7:0]d,
output logic [7:0]q);

always_ff@(posedge clk)


if(reset_n==0)
q <= 0;

else if(sload == 1)
q <= d;

else 
q <= q;


endmodule
