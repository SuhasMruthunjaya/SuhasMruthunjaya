module full_adder(
input logic A,B,Cin,
output logic Sum,Cout);

logic q1,q2,q3;

always_comb
begin
q1 = (A^B);
Sum = (q1^Cin);
q2 = (q1&Cin);
q3 = (A&B);
Cout = (q2|q3);
end
endmodule 