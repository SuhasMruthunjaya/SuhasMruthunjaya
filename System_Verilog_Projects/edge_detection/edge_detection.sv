module edge_detection(
output logic out_flag, 
input logic temp,
input logic clk
);
    
logic temp_d;   
always_ff@(posedge clk)
temp_d <= temp;    
always_ff@(posedge clk)
begin
 if (~temp && temp_d)
   out_flag<= 1'b1;
 else
   out_flag<= 1'b0;
end
endmodule