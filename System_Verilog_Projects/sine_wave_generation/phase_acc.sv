module phase_acc (
   input logic clk, reset_n, enable,
   output logic [7:0] q,
	output logic [7:0] q_temp
);

 //  + ((1>>1) |	(1>>2))
 
 //logic [7:0] q_temp;
 
always_ff @(posedge clk)
   if (reset_n == 1'b0)
      q_temp <= 0;
   else if (enable)
		begin
      q_temp <= q_temp + 8'd1;
		end
		
always_ff @(posedge clk)
   if (reset_n == 1'b0)
      q <= 0;
   else if (enable)
		begin
      q <= q_temp + 8'd32;
		end		
				
		
endmodule
