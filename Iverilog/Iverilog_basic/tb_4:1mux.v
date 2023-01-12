module tb;
reg t_a,t_b,t_c,t_d,s0,s1;
wire o;



mux41 m(.a(t_a),.b(t_b),.c(t_c),.d(t_d),.s0(s0),.s1(s1),.o(o));

initial begin
$dumpfile("dump_41mux.vcd");
$dumpvars(0,tb);
end
initial begin
$monitor(t_a," " ,t_b," ",t_c," ",t_d,"   ",s1," ",s0,"   ",o);
t_a=2'b00;
t_b=2'b01;
t_c=2'b10;
t_d=2'b11;
s0=1'b0;
s1=1'b0;
#10
s0=1'b1;
s1=1'b0;
#10
s0=1'b0;
s1=1'b1;
#10
s0=1'b1;
s1=1'b1;

end
endmodule


