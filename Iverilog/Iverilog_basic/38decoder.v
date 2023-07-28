module nand4(input wire a,b,c,e,output wire d);
assign d=~(a&b&c&e);
endmodule

module decoder38(input wire a,b,c,d,output wire e,f,g,h,i,j,k,l);
wire t1,t2,t3,t4;
assign t1=~a;
assign t2=~b;
assign t3=~c;
assign t4=~d;

nand4 n0(t1,t2,t3,t4,e);
nand4 n1(t1,t2,c,t4,f);
nand4 n2(t1,b,t3,t4,g);
nand4 n3(t1,b,c,t4,h);
nand4 n4(a,t2,t3,t4,i);
nand4 n5(a,t2,c,t4,j);
nand4 n6(a,b,t3,t4,k);
nand4 n7(a,b,c,t4,l);

endmodule
