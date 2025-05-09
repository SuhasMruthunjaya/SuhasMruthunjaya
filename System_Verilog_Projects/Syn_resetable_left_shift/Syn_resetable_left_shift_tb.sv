module Syn_resetable_left_shift_tb();
 logic d, clk, reset_n, q;
 
Syn_resetable_left_shift inst (.d(d),
										 .clk(clk),
										 .reset_n(reset_n),
										 .q(q)
										);
										

										
initial

begin 

reset_n = 1; d = 4'b1010; clk = 0; 
#50;

/*reset_n = 1; d = 1;
#50;

reset_n = 1; d = 0;  
#50;

reset_n = 1; d = 0;  
#50;

reset_n = 1; d = 1;  
#50;
*/
end

always #25 clk = ~clk;

endmodule 