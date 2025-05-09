module six_one_MUX(
 input logic [3:0] d0, d1, d2, d3, d4, d5,
 input logic [2:0] select, output logic [3:0] q
 );
 
 always_comb
 begin
 if(select == 3’d0)
 begin q = d0; end
 else if(select == 3’d1)
 q = d1;
 else if(select == 3’d2)
 q = d2;
 else if(select == 3’d3)
 q = d3;
 else if(select == 3’d4)
 q = d4;
 else
 q = d5;
 end
 endmodule