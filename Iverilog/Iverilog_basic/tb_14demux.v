module tb;
reg t_a,t_b,t_c;
wire a,b,c,d;

decoder24 x(.a(t_a),.b(t_b),.c(t_c),.d(a),.e(b),.f(c),.g(d));
initial begin
$dumpfile("dump_demux.vcd");
$dumpvars(0,tb);
end
initial begin
$monitor(t_c,"  ",t_a," ",t_b,"   ",a," ",b," ",c," ",d);

t_c=1'b1;
t_a=1'b1;
t_b=1'b1;
#10
t_c=1'b1;
t_a=1'b0;
t_b=1'b0;
#10
t_c=1'b1;
t_a=1'b0;
t_b=1'b1;
#10
t_c=1'b1;
t_a=1'b1;
t_b=1'b0;
#10
t_c=1'b0;
t_a=1'b1;
t_b=1'b1;

end
endmodule


