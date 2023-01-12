module tb;
reg t_a,t_b,t_c,t_d;
wire a,b,c,d,e,f,g,h;

decoder38 x(.a(t_a),.b(t_b),.c(t_c),.d(t_d),.e(a),.f(b),.g(c),.h(d),.i(e),.j(f),.k(g),.l(h));
initial begin
$dumpfile("dump_decoder38.vcd");
$dumpvars(0,tb);
end
initial begin
$monitor(t_d,"  ",t_a," ",t_b," ",t_c,"   ",a," ",b," ",c," ",d," ",e," ",f," ",g," ",h);

t_d=1'b1;
t_a=1'b1;
t_b=1'b1;
t_c=1'b1;
#10
t_d=1'b0;
t_a=1'b0;
t_b=1'b0;
t_c=1'b0;
#10
t_d=1'b0;
t_a=1'b0;
t_b=1'b0;
t_c=1'b1;
#10
t_d=1'b0;
t_a=1'b0;
t_b=1'b1;
t_c=1'b0;
#10
t_d=1'b0;
t_a=1'b0;
t_b=1'b1;
t_c=1'b1;
#10
t_d=1'b0;
t_a=1'b1;
t_b=1'b0;
t_c=1'b0;
#10
t_d=1'b0;
t_a=1'b1;
t_b=1'b0;
t_c=1'b1;
#10
t_d=1'b0;
t_a=1'b1;
t_b=1'b1;
t_c=1'b0;
#10
t_d=1'b0;
t_a=1'b1;
t_b=1'b1;
t_c=1'b1;


end
endmodule
