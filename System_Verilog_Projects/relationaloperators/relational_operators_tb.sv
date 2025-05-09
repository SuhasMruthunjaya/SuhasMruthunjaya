module relational_operators_tb();
logic d0, d1,q;

relational_operators inst1( .d0(d0),
									 .d1(d1),
									 .q(q)
								  );
								  
initial
begin

d0=0; d1=0; 
#10;

d0=0; d1=1;
#10;

d0=1; d1=0;
#10;

d0=1; d1=1;
#10;

end
endmodule 