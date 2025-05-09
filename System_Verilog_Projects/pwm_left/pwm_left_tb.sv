`timescale 1ns/1ps
`define HALF_CLOCK_PERIOD 10
`define RESET_PERIOD 200
`define SIM_DURATION 500000

module pwm_left_tb();

logic tb_q;
logic [8:0] tb_duty_cycle = 0;

logic tb_local_clock = 0;
initial begin: clock_generation_process
tb_local_clock = 0;
forever begin
#`HALF_CLOCK_PERIOD tb_local_clock = ~tb_local_clock;
end
end

logic [3:0] tb_counter = 0;
always_ff@(posedge tb_local_clock)
tb_counter <= tb_counter + 1'b1;

logic tb_enable; assign tb_enable = &tb_counter;

logic tb_local_reset_n = 1'b0;
initial begin: reset_generation_process
$display ("Simulation starts ...");
tb_local_reset_n = 1'b1;
#40000
tb_duty_cycle = 1;
#40000
tb_duty_cycle = 2;
#40000
tb_duty_cycle = 64;
#40000
tb_duty_cycle = 128;
#40000
tb_duty_cycle = 255;
#40000
tb_duty_cycle = 256;
#`SIM_DURATION
$display ("Simulation done ...");
$stop();
end

pwm_left dut_inst_0 (
.clk(tb_local_clock),
.reset_n(tb_local_reset_n),
.enable(tb_enable),
.duty_cycle(tb_duty_cycle),
.q(tb_q)
);

endmodule
