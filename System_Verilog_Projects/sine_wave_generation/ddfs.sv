module ddfs (
   input logic clk, input logic reset_n, 
   output logic [7:0] q, lut_address, q_temp
);

logic enable;
time_base_gen #(.L(521)) inst_0 (.clk(clk), .reset_n(reset_n), .q(enable));
//logic [7:0] lut_address;

phase_acc inst_1 (.clk(clk), .reset_n(reset_n), .enable(enable), .q(lut_address),.q_temp(q_temp));

sine_wave_lut inst_2 (.address(lut_address), .q(q));

endmodule
