
module Recursive_IIRFilter_Digital_Resonator(
input logic clk, input logic reset_n,
input logic signed [15:0] d,
output logic signed [15:0] q,
output logic enable
);

localparam CLOCK_TICKS = 100000;

	// ### time base generation - 8kHz sampling frequency ...
	
	localparam BIT_WIDTH = $clog2(CLOCK_TICKS);	 
		
	logic [BIT_WIDTH-1 : 0] time_base_counter = 0;
	
	always_ff@(posedge clk)
		if(reset_n == 1'b0)
			time_base_counter <= 0;
		else
			time_base_counter <= (time_base_counter + 1'b1) % CLOCK_TICKS;
			
	assign enable = (time_base_counter == (CLOCK_TICKS - 1'b1)) ? 1'b1 : 1'b0;



 logic signed [15:0] del [2:0];

 integer i;

 always_ff@(posedge clk)
 if(reset_n == 1'b0)
 for (i = 0; i <= 2; i = i+1) begin : clear_fir
 del[i] <= 0;
 end
 else if(enable)
 begin
	for (i = 0; i <= 2; i = i+1) begin : shift_fir
	if(i == 0)
	del[i] <= d;
	else
	del[i] <= del[i-1];
	end
end

 	logic signed [15:0] y_n [2:0];
   //logic signed [15:0]s;
 
 integer m;
 
 logic signed [31:0] t, u, v;
 logic signed [15:0]almost_op;
 logic signed [31:0]trunc_value;
 
 
// 	logic signed [15:0] x_n = 0;
//	logic signed [15:0] x_n1 = 0;
//	logic signed [15:0] x_n2 = 0;
//	logic signed [15:0] y_n;
//	logic signed [15:0] y_n1 = 0;
//	logic signed [15:0] y_n2 = 0;
 
 
 always_ff@(posedge clk)
 if(reset_n == 1'b0)
 for (m = 0; m <= 2; m = m+1) begin : clear_op_fir
 y_n[m] <= 0;
 end
 else if(enable)
 begin
	for (m = 0; m <= 2; m = m+1) begin : shift_op_fir
	if(m == 0) 
	y_n[m] <= q;
	else
	y_n[m] <= y_n[m-1];
	end
 end
 
//  	always_ff@(posedge clk)
//	begin
//		if(reset_n == 1'b0)
//		begin
//			x_n <= 0;
//			x_n1 <= 0;
//			x_n2 <= 0;
//			y_n1 <= 0;
//			y_n2 <= 0;
//		end
//		else 
//			begin
//			x_n <= d;
//			x_n1 <= x_n;
//			x_n2 <= x_n1;
//			y_n1 <= y_n;
//			y_n2 <= y_n1;
//			end
//	end		
			
			
 
// 	always_ff@(posedge clk)
//		if(reset_n == 1'b0)
//			x_n <= 0;
//		else 
//			x_n <= d;
//			
//	always_ff@(posedge clk)
//		if(reset_n == 1'b0)
//			x_n1 <= 0;
//		else 
//			x_n1 <= x_n;
//		
//	always_ff@(posedge clk)
//		if(reset_n == 1'b0)
//			x_n2 <= 0;
//		else 
//			x_n2 <= x_n1;	
//	
//	always_ff@(posedge clk)
//		if(reset_n == 1'b0)
//			y_n1 <= 0;
//		else 
//			y_n1 <= y_n;
//	
//	always_ff@(posedge clk)
//		if(reset_n == 1'b0)
//			y_n2 <= 0;
//		else 
//			y_n2 <= y_n1;
			
			
 logic signed [15:0] difference;
 //assign difference = x_n - x_n2;
 
 assign difference =  del[0] -  del[2];
 
 assign t = 16'sb0000000000010000*difference;
 assign u = 16'sb0111010010111000* y_n[1];
 assign v = 16'sb0011111010111010* y_n[2];
 
 	logic signed [15:0] prod_0_16;
	logic signed [15:0] prod_1_16;
	logic signed [15:0] prod_2_16;
	
	assign prod_0_16 = $signed(t[30:15]);
	assign prod_1_16 = $signed(u[30:15]);
	assign prod_2_16 = $signed(v[30:15]);
	
	
 
 assign almost_op = $signed( t[31:16]  + u[31:16]  - v[31:16] );
 
 //assign almost_op = prod_0_16 + prod_1_16 - prod_2_16;
 
 //assign trunc_value = $signed(almost_op*2);
 
 assign q = almost_op <<< 1;
 
 //assign q = s <<< 1;
 

 endmodule