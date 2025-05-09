module test_setup(
	input logic clk, input logic reset_n,
	output logic signed [15:0] q_0, q_1
	);
	
	localparam SYSTEM_FREQUENCY   = 50000000;
	localparam SAMPLING_FREQUENCY = 48000;
	localparam CLOCK_TICKS        = SYSTEM_FREQUENCY/SAMPLING_FREQUENCY;
		
	// ### time base generation - 48kHz sampling frequency ...	
	logic enable;
	
	localparam BIT_WIDTH = $clog2(CLOCK_TICKS);	 
		
	logic [BIT_WIDTH : 0] time_base_counter = 0;
	
	always_ff@(posedge clk)
		if(reset_n == 1'b0)
			time_base_counter <= 0;
		else
			time_base_counter <= (time_base_counter + 1'b1) % CLOCK_TICKS;
			
	assign enable = (time_base_counter == (CLOCK_TICKS - 1'b1)) ? 1'b1 : 1'b0; 
		
	// input register ... 
	logic signed [15:0] xn = 0;
	always_ff@(posedge clk)
		if(reset_n == 1'b0)
			xn <= 16'sb0111101011100001;
		else if(enable)
			xn <= 0;
		
	// input summation node ...
	logic signed [15:0] sum;
		
	logic signed [15:0] reg_0 = 0;
	always_ff@(posedge clk)
		if(reset_n == 1'b0)
			reg_0 <= 0;
		else if(enable)
			reg_0 <= sum <<< 1;
			
	// multiplication by the sine factor ... 
	localparam sine_factor = 16'sb0001000010110101;
	
	logic signed [31:0] mult_0; assign mult_0 = reg_0*sine_factor;
	assign q_0     = $signed(mult_0[30:15] ); 

	// multiplication by the cos factor 		
	localparam cos_factor = 16'sb0111111011101000;
	
	logic signed [31:0] mult_1; assign mult_1 = reg_0 * cos_factor; 
			
	logic signed [15:0] reg_1 = 0;
	always_ff@(posedge clk)
		if(reset_n == 1'b0)
			reg_1 <= 0;
		else if(enable)
			reg_1 <= reg_0;
		
	// multiplication by the 0.5 factor 	
	localparam scale_factor = 16'sb0100000000000000;

	logic signed [31:0] mult_2; 
	assign mult_2 = reg_1 * scale_factor;
	
	assign sum = xn + $signed(mult_1[30:15]) - $signed(mult_2[30:15]);
	
	assign q_1 = (sum <<< 1) - $signed(mult_1[30:15]);
	
endmodule 