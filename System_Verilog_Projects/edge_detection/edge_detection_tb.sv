module edge_detection_tb ();
logic out_flag, temp, clk;
edge_detection inst(.out_flag(out_flag),
						  .temp(temp),
						  .clk(clk)
						 );
						  
initial
begin 

temp = 0; clk = 0;
#50;

temp = 1; 
#50;

temp = 0;
#50;

end 

always #10 clk=~clk;
endmodule 
