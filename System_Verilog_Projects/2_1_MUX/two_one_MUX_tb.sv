module two_one_MUX_tb();
logic d0, d1, q, select;

two_one_MUX inst1( .d0(d0),
					.d1(d1),
					.q(q),
					.select(select)
				 );
								  
initial
begin

d0=0; d1=0; select=0;
#10;

d0=0; d1=1; select=0;
#10;

d0=1; d1=0; select=1;
#10;

d0=1; d1=1; select=1;
#10;

end
endmodule 