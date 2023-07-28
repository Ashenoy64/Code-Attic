module mux21(input wire a,b,s,output wire c);
assign c=s?b:a;
endmodule


module mux41(input wire a,b,c,d,s0,s1,output wire o);
assign o=s1?(s0?d:c):(s0?b:a);
endmodule

module mux81(input wire a,b,c,d,e,f,g,h,s0,s1,s2,output wire o);
assign o=s2?(s1?(s0?h:g):(s0?f:e)):(s1?(s0?d:c):(s0?b:a));
endmodule
