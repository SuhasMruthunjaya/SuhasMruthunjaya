

module IIR_Sinewave_Oscillator(
	input  logic clk,
	input  logic reset_n,
	output logic signed [15:0] q
	);
	
	localparam SYSTEM_FREQUENCY   = 50000000;
	localparam SAMPLING_FREQUENCY = 8000;
	localparam CLOCK_TICKS        = SYSTEM_FREQUENCY/SAMPLING_FREQUENCY;

	// ### time base generation - 8kHz sampling frequency ...	
	logic enable;
	
	localparam BIT_WIDTH = $clog2(CLOCK_TICKS);	 
		
	logic [BIT_WIDTH : 0] time_base_counter = 0;
	
	always_ff@(posedge clk)
		if(reset_n == 1'b0)
			time_base_counter <= 0;
		else
			time_base_counter <= (time_base_counter + 1'b1) % CLOCK_TICKS;
			
	assign enable = (time_base_counter == (CLOCK_TICKS - 1'b1)) ? 1'b1 : 1'b0;
	
	localparam a_scq = 16'sb0000010100000101;
	localparam b_scq = 16'sb0111111110011010;
	localparam c_scq = 16'sb0100000000000000;

	logic signed [15:0] x_n  = 0;
	logic signed [15:0] x_n1 = 0;
	logic signed [15:0] y_n;
	logic signed [15:0] y_n1 = 0;
	logic signed [15:0] y_n2 = 0;
	
	
	always_ff@(posedge clk)
		if(reset_n == 1'b0)
			x_n <= 16'sb0011100110011001;
		else if(enable)
			x_n <= 0;
			
	always_ff@(posedge clk)
		if(reset_n == 1'b0)
			x_n1 <= 0;
		else if(enable)
			x_n1 <= x_n;	
	
	always_ff@(posedge clk)
		if(reset_n == 1'b0)
			y_n1 <= 0;
		else if(enable)
			y_n1 <= y_n;
	
	always_ff@(posedge clk)
		if(reset_n == 1'b0)
			y_n2 <= 0;
		else if(enable)
			y_n2 <= y_n1;	
			
	logic signed [31:0] prod_0;
	logic signed [31:0] prod_1;
	logic signed [31:0] prod_2;	
	
	assign prod_0 = x_n1 * a_scq;
	assign prod_1 = y_n1 * b_scq;
	assign prod_2 = y_n2 * c_scq;
	
	logic signed [15:0] prod_0_16;
	logic signed [15:0] prod_1_16;
	logic signed [15:0] prod_2_16;
	
	assign prod_0_16 = $signed(prod_0[30:15]);
	assign prod_1_16 = $signed(prod_1[30:15]);
	assign prod_2_16 = $signed(prod_2[30:15]);
		
	logic signed [15:0] sum;
	
	assign sum = prod_0_16 + prod_1_16 - prod_2_16;
	assign y_n = sum <<< 1;
		
	assign q   = y_n <<< 1;
	
endmodule