module two_one_MUX (
input logic [3:0] d0, d1, input logic select,
output logic [3:0] q
);

assign q = (select == 1) ? d1 : d0;

endmodule
