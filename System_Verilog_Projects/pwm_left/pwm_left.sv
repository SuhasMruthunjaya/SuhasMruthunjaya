module pwm_left(
input logic [8:0] duty_cycle,
input logic clk, reset_n, enable,
output logic q
);

// PWM Counter
logic [7:0] reg_0 = 0;

always_ff@(posedge clk)
begin : pwm_counter
if(reset_n == 1'b0)
reg_0 <= 8'b00000000;
else if(enable)
reg_0 <= reg_0 + 1'b1;
end : pwm_counter

// PWM Comparator
assign q = duty_cycle[8] ? 1'b1 : (reg_0 >= duty_cycle) ? 1'b0 : 1'b1;

endmodule