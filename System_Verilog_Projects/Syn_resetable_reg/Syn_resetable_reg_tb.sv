module Syn_resetable_reg_tb();
logic reset_n, sload, clk,d,q;

Syn_resetable_reg inst(.reset_n(reset_n),
							  .sload(sload),
							  .clk(clk),
							  .d(d),
							  .q(q)
							 );
							 

initial

begin

reset_n = 0; sload = 1; d=1;
#10;

reset_n = 1; sload = 0; d=1;
#10;

reset_n = 1; sload = 1; d=1;
#10;

end

always #10 clk = ~clk; 

endmodule 

 