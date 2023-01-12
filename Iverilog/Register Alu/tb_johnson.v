module tb;
reg clk,reset;
wire [4:0] out;

jhonson x(.clk(clk),.reset(reset),.out(out));
initial begin
$dumpfile("dump_jhon.vcd");
$dumpvars(0,tb);
end
initial begin
$monitor("  ",out[0],"  ",out[1],"  ",out[2],"  ",out[3],"  ",out[4],);

clk=1'b0;
reset=1'b1;
#10;
clk=1'b1;
reset=1'b1;
#10;
clk=1'b0;
reset=1'b0;
#10;
clk=1'b1;

#10;
clk=1'b0;
#10;
clk=1'b1;
#10;

clk=1'b0;
#10;
clk=1'b1;
#10;


clk=1'b0;
#10;
clk=1'b1;
#10;

clk=1'b0;
#10;
clk=1'b1;
#10;

clk=1'b0;
#10;
clk=1'b1;
#10;

clk=1'b0;
#10;
clk=1'b1;
#10;

clk=1'b0;
#10;
clk=1'b1;
#10;

clk=1'b0;
#10;
clk=1'b1;
#10;

clk=1'b0;
#10;
clk=1'b1;
#10;



end
endmodule

