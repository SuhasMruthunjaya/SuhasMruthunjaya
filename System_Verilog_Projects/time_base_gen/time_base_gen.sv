module time_base_gen(
	input logic d, input logic clk,
	output logic q);

	logic q1, q2;


	always@(posedge clk)
	begin
	q1 <= d;
	q2 <= q1;
	q <= ~q1 & q2;

	end
endmodule