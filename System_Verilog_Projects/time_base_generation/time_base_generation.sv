module time_base_generation #(parameter cycles = 521)(output logic enable,
output logic [7:0]q,
input logic clk,reset_n);

localparam bandwidth = $clog2(cycles);
//$display("bandwidth = %d", bandwidth);

logic [bandwidth-1:0] temp = 0;


always_ff@(posedge clk)
if (reset_n == 0)
	temp <= 0;
else 
	temp <= (temp+1)%cycles;
	
//logic enable; 
assign enable = (temp == cycles-1)?1:0;

always_ff@(posedge clk)
if(reset_n == 0)
	q<=0;
//else if ((enable==1) && q!=255)
//	q<=q + 1;
//else if(q==255)
//	q<=0;
else if(enable ==1)
	q<=q+1;

endmodule 