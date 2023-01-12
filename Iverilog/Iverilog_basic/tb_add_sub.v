module tb;
reg t_a,t_b,t_c;
wire t_x,t_y;

add_sub32 x(.a(t_a),.b(t_b),.cin(t_c),.s(t_x),.cout(t_y));
initial begin
$dumpfile("dump_add_sub.vcd");
$dumpvars(0,tb);
end
initial begin
$monitor(t_a,t_b,t_c,t_x,t_y);

t_a=1'b0;
t_b=1'b0;
t_c=1'b0;
#10
t_a=1'b0;
t_b=1'b0;
t_c=1'b1;
#10
t_a=1'b0;
t_b=1'b1;
t_c=1'b0;
#10
t_a=1'b0;
t_b=1'b1;
t_c=1'b1;
#10
t_a=1'b1;
t_b=1'b0;
t_c=1'b0;
#10
t_a=1'b1;
t_b=1'b0;
t_c=1'b1;
#10
t_a=1'b1;
t_b=1'b1;
t_c=1'b0;
#10
t_a=1'b1;
t_b=1'b1;
t_c=1'b1;
end
endmodule

