module nand3(input wire a,b,c,output wire d);
assign d=~(a&b&c);
endmodule

module decoder24(input wire a,b,c,output wire d,e,f,g);
wire t1,t2,t3;
assign t1=~a;
assign t2=~b;
assign t3=~c;

nand3 n0(t1,t2,t3,d);
nand3 n1(t1,b,t3,e);
nand3 n2(a,t2,t3,f);
nand3 n3(a,b,t3,g);

endmodule
