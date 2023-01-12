module mux41(input wire a,b,c,d,s0,s1,output wire o);
assign o=s1?(s0?d:c):(s0?b:a);
endmodule
