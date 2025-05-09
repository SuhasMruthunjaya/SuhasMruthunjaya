module relational_operators(
input logic [3:0] d0, d1,
output logic q
);

assign q = (d0 >= d1) && (d1 != 0);

endmodule