module six_one_MUX_tb();
logic d0, d1, d2, d3, d4, d5, q, select;

six_one_MUX inst1( .d0(d0),
					.d1(d1),
					.d2(d2),
					.d3(d3),
					.d4(d4),
					.d5(d5),
					.q(q),
					.select(select)
				 );
								  
initial
begin

d0=0; d1=0; d2=0; d3=0; d4=0; d5=1; select=00;
#10;

d0=0; d1=1; d2=0; d3=0; d4=0; d5=1; select=01;
#10;

d0=0; d1=0; d2=0; d3=0; d4=0; d5=1; select=10;
#10;

d0=0; d1=0; d2=0; d3=1; d4=0; d5=1; select=11;
#10;

end
endmodule 