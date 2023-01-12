module tb;
reg t_a,t_b,t_c,t_d,t_e,t_f,t_g,t_h,s0,s1,s2;
wire o;
mux81 m(.a(t_a),.b(t_b),.c(t_c),.d(t_d),.e(t_e),.f(t_f),.g(t_g),.h(t_h),.s0(s0),.s1(s1),.s2(s2),.o(o));

initial begin
$dumpfile("dump_81mux.vcd");
$dumpvars(0,tb);
end
initial begin
$monitor(t_a," " ,t_b," ",t_c," ",t_d," ",t_e," " ,t_f," ",t_g," ",t_h,"   ",s2," ",s1," ",s0,"   ",o);
t_a=3'b000;
t_b=3'b001;
t_c=3'b010;
t_d=3'b011;
t_e=3'b100;
t_f=3'b101;
t_g=3'b110;
t_h=3'b111;
s0=1'b0;
s1=1'b0;
s2=1'b0;
#10
s0=1'b1;
s1=1'b0;
s2=1'b0;
#10
s0=1'b0;
s1=1'b1;
s2=1'b0;
#10
s0=1'b1;
s1=1'b1;
s2=1'b0;
#10
s0=1'b0;
s1=1'b0;
s2=1'b1;
#10
s0=1'b1;
s1=1'b0;
s2=1'b1;
#10
s0=1'b0;
s1=1'b1;
s2=1'b1;
#10
s0=1'b1;
s1=1'b1;
s2=1'b1;

end
endmodule

