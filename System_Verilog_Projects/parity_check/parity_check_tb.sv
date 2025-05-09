module parity_check_tb();
logic d,q;

parity_check inst(.d(d),
						.q(q)
						);
						

initial
begin

d=01010111;
#10;

end
endmodule 