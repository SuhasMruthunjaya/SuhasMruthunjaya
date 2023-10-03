package state_machine_definitions;

	enum logic [1:0] {__RESET = 2'b00, __IDLE = 2'b01, __PROC = 2'b10, __DONE = 2'b11} state;
	// ...  

endpackage 


module sha1_Implimentation(
	input logic clk,
	input logic reset_n,
	input logic start,
	input logic [511:0] data,
 	output logic [159:0] q_data,
	output logic q_done
	

);

	import state_machine_definitions::*;
	
	
	localparam LOOP_ITERATIONS = 81;
	localparam ITERATIONS      = LOOP_ITERATIONS - 1;
	localparam BITWIDTH        = $clog2(ITERATIONS);
	
	
	

	/* ### start pulse detection ##############################################
	
	CPU asserts a start pulse ...
	
										  ___________________________________________________
	start_signal:		__________|                                                   |_______________________________________
	
										 ^
										 |
										 
								 ACTUAL START
						
	
	We are using the start_signal to derive a 50MHz related start pulse ..., which is only high for 20ns ... 
	
							             _
							____________| |________________________________________________________________________________________
	
	
	We use this start pulse to trigger our sha-1 processing stage ...
	
	*/
	
	// with the following structure, we are detecting the rising edge of our start signal ... 
	
	logic [3:0] sync_reg = 0;
	
	// shifting data (start signal) from the right-hand side. shifting everything to the left ... newest data is placed at the LSB side ...
	always_ff@(posedge clk)
		begin : start_detection
			if(reset_n == 1'b0)
				sync_reg <= 4'b0000;
			else
				sync_reg <= {sync_reg[2:0],start};
		
		end : start_detection

	// comparator that continuously evaluates the content of our sync_reg ...
	logic sync_start; assign sync_start = (sync_reg == 4'b0011) ? 1'b1 : 1'b0; 

	
	logic [31:0] W_data [0:79];
	logic [31:0] W_mask = 32'b11111111111111111111111111111111;
	logic [6:0] i_row = 15;	
	logic [7:0] data_register = 1;
	logic [31:0] temp;
	

	always_ff@(posedge clk)
	begin
	W_data[0] <= (data>>480) & W_mask;
	if(i_row > 0)
		begin
			W_data[i_row] <= (data>>32*(15-i_row)) & W_mask;
			i_row <= i_row - 1;
			data_register <=  data_register + 1;
		end
	if((data_register>=16) && (data_register<80))
		begin
		//	temp = (W_data[data_register-3]^W_data[data_register-8]^W_data[data_register-14]^W_data[data_register-16]);
			W_data[data_register] <= (((W_data[data_register-3]^W_data[data_register-8]^W_data[data_register-14]^W_data[data_register-16]) << 1)|((W_data[data_register-3]^W_data[data_register-8]^W_data[data_register-14]^W_data[data_register-16]) >> (32 - 1))); 
			data_register <= data_register+1;
		end
	 end
	
	// ### 'state-machine' ... #######################################################################################################
	
	logic [31:0]a = 32'h67452301;
	logic [31:0]b = 32'hEFCDAB89;
	logic [31:0]c = 32'h98BADCFE;
	logic [31:0]d = 32'h10325476;
	logic [31:0]e = 32'hC3D2E1F0;
	
	//hash values
	logic [31:0]h0 = 32'h67452301;
	logic [31:0]h1 = 32'hEFCDAB89;
	logic [31:0]h2 = 32'h98BADCFE;
	logic [31:0]h3 = 32'h10325476;
	logic [31:0]h4 = 32'hC3D2E1F0;


	 logic [31:0]q0;
	 logic [31:0]q1; 
	 logic [31:0]q2; 
	 logic [31:0]q3; 
	 logic [31:0]q4;
	

		
	logic [BITWIDTH-1:0] state_counter = 'd0;

	
	always_ff@(posedge clk)
		begin : state_machine
			if(reset_n == 1'b0)
				begin
				
					state_counter <= 0;
					state 		  <= __RESET;
				end
			else
				begin
					case(state)
						__RESET:	
							begin
								
								state_counter <= 0;
								state 		  <= __IDLE;
							end	
						__IDLE: 
							begin
								state_counter <= 0;
								
								if(sync_start)
									state <= __PROC;
									
							end
						__PROC: 
							begin
								/*
									do something meaningful ... , the control signal is just used for illustration purposes ...
								*/
							
								if(state_counter < 20)
									
									begin	
										
										e <= d;
										d <= c;
										c <= (((b<<30) | (b >> (32-30))));
										b <= a;
										a <=  ((a<<5) | (a >> (32-5))) + ((b&c)|((~b)&d)) + e + W_data[state_counter] + 32'h5A827999;
										
									end
									
								else if(state_counter >= 20 && state_counter < 40)
									begin	
										
										e <= d;
										d <= c;
										c <= (((b<<30) | (b >> (32-30))));
										b <= a;
										a <= ((a<<5) | (a >> (32-5))) + (b^c^d) + e + W_data[state_counter] + 32'h6ED9EBA1;
									
									end
									
								else if(state_counter >= 40 && state_counter < 60)
									begin
										
										e <= d;
										d <= c;
										c <= (((b<<30) | (b >> (32-30))));
										b <= a;
										a <= ((a<<5) | (a >> (32-5))) + ((b&c)|(b&d)|(c&d)) + e + W_data[state_counter] + 32'h8F1BBCDC;;
										
									end
								else if(state_counter >= 60 && state_counter <= 80)
									begin
										
										e <= d;
										d <= c;
										c <= (((b<<30) | (b >> (32-30))));
										b <= a;
										a <= ((a<<5) | (a >> (32-5))) + (b^c^d) + e + W_data[state_counter] + 32'hCA62C1D6;;
										
									end

							
								if(state_counter == ITERATIONS)
									begin
										state_counter <= 0;
										q0 <= a + h0;
										q1 <= b + h1;
										q2 <= c + h2;
										q3 <= d + h3;
										q4 <= e + h4;
										state         <= __DONE;
									end
								else
									begin
										state_counter <= state_counter + 1;
										state         <= __PROC;
									end
							end
						__DONE:
							begin
								
								state_counter <= 0;
								state			  <= __IDLE;
							end
						default:
							begin
								
								state_counter <= 0;
								state 		  <= __RESET;
							end
					endcase
				end
			end : state_machine
				
			
			always_ff@(posedge clk)
			begin
				if(state == __DONE)
				begin
				q_done <= 1'b1;
				q_data[159:128] <= q0;
				q_data[127:96] <= q1;
				q_data[95:64] <= q2;
				q_data[63:32] <= q3;
				q_data[31:0] <= q4;
				end
				else
				q_done <= 1'b0;
			end
		

endmodule 