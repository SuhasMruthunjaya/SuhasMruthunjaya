module parity_check (
input logic [7:0] d, 
output logic q);

integer i;
logic is_odd;

always_comb 
begin
is_odd = 0;
for(i=0;i<=7;i++)
begin
is_odd = is_odd ^ d[i];
end

end

assign q = is_odd;
endmodule


