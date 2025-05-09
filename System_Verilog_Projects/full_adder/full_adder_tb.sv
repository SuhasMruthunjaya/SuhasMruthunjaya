module full_adder_tb();
logic A,B,Cin,Sum,Cout;

full_adder inst1(.A(A),
						  .B(B),
						  .Cin(Cin),
						  .Sum(Sum),
						  .Cout(Cout)
						  );
						  

initial 

begin

A=0; B=0; Cin=0;
#10;

A=0; B=0; Cin=1;
#10;

end
endmodule 