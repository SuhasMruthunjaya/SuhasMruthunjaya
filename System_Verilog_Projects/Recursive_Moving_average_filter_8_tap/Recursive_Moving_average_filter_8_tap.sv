module Recursive_Moving_average_filter_8_tap(
input logic clk, input logic reset_n,
input logic signed [15:0] d,
output logic signed [15:0] q
 );

 logic signed [15:0] del [8:0];
 logic [15:0] y_n;

 integer i;

 always_ff@(posedge clk)
 if(reset_n == 1'b0)
 for (i = 0; i <= 8; i = i+1) begin : clear_fir
 del[i] <= 0;
 end
 else
 for (i = 0; i <= 8; i = i+1) begin : shift_fir
 if(i == 0)
 del[i] <= d;
 else
 del[i] <= del[i-1];
 end

 logic signed [18:0] difference;
 assign difference = del[0] - del[8];
 
 always_ff@(posedge clk)
 if(reset_n == 1'b0)
 y_n <= 0;
 else 
 y_n <= q;
 
 assign q = y_n + $signed( difference[18:3] );

 endmodule