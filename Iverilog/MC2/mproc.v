module nor5 (input wire [0:4] i, output wire o);
  wire t;
  or3 or3_0 (i[0], i[1], i[2], t);
  nor3 nor3_0 (t, i[3], i[4], o);
endmodule

module ir (input wire clk, reset, load, input wire [15:0] din, output wire [15:0] dout);
  dfrl dfrl_0 (clk, reset, load, din['h0], dout['h0]);
  dfrl dfrl_1 (clk, reset, load, din['h1], dout['h1]);
  dfrl dfrl_2 (clk, reset, load, din['h2], dout['h2]);
  dfrl dfrl_3 (clk, reset, load, din['h3], dout['h3]);
  dfrl dfrl_4 (clk, reset, load, din['h4], dout['h4]);
  dfrl dfrl_5 (clk, reset, load, din['h5], dout['h5]);
  dfrl dfrl_6 (clk, reset, load, din['h6], dout['h6]);
  dfrl dfrl_7 (clk, reset, load, din['h7], dout['h7]);
  dfrl dfrl_8 (clk, reset, load, din['h8], dout['h8]);
  dfrl dfrl_9 (clk, reset, load, din['h9], dout['h9]);
  dfrl dfrl_a (clk, reset, load, din['ha], dout['ha]);
  dfrl dfrl_b (clk, reset, load, din['hb], dout['hb]);
  dfrl dfrl_c (clk, reset, load, din['hc], dout['hc]);
  dfrl dfrl_d (clk, reset, load, din['hd], dout['hd]);
  dfrl dfrl_e (clk, reset, load, din['he], dout['he]);
  dfrl dfrl_f (clk, reset, load, din['hf], dout['hf]);
endmodule

module control_logic (input wire clk, reset, input wire [15:0] cur_ins, output wire [2:0] rd_addr_a, rd_addr_b, wr_addr,
  output wire [1:0] op, output wire sel, jump, pc_inc, load_ir, wr_reg);

wire eo,ld_ins_, alu_ins,s,ld_ins,w,u,pc,ef,wr1,wr2,lo,fi,el;

assign s=!cur_ins[14]; 

assign u=!cur_ins[15]; 

nor5 n0(cur_ins[15:11], alu_ins); 

assign w=!cur_ins[10]; 

and2 a0(cur_ins[15],s,ld_ins); 

assign ld_ins_=!ld_ins;  

dfsl fetch(clk, reset, 1'b1,fi, pc); 
  
assign load_ir=pc;   

or2 o0(pc,el,pc_inc); 
  
dfrl dec_exec (clk, reset, 1'b1, load_ir, eo); 
  
and2 a1(ld_ins_,eo,ef); 

and2 a2(ef, alu_ins, wr1); 

and2 a3(eo,ld_ins,el); 

and2 a4(ld_ins,el,wr2); 

or2 o1(wr1,wr2,wr_reg); 

and3 a5(cur_ins[14],u,ef,jump); 

assign rd_addr_a = cur_ins[2:0];
 
assign rd_addr_b = cur_ins[5:3];
  
assign wr_addr = cur_ins[8:6];
  
assign op = cur_ins[10:9];

nand2 n1(ld_ins,el,sel);

dfrl d0(clk,reset,1'b1,el,lo);

or2 o2(ef,lo,fi);

endmodule

module mproc (input wire clk, reset, input wire [15:0] d_in, output wire [6:0] addr, output wire [15:0] d_out);
  wire pc_inc, cout, cout_, sub, sel, sel_addr; wire [2:0] rd_addr_a, rd_addr_b, wr_addr; wire [1:0] op; wire [8:0] _addr;
  wire [15:0] cur_ins, d_out_a, d_out_b;

  and2 and2_0 (jump, cout, sub);
  pc pc_0 (clk, reset, pc_inc, 1'b0, sub, {8'b0, cur_ins[7:0]}, {_addr, addr});
  ir ir_0 (clk, reset, load_ir, d_in, cur_ins);
  control_logic control_logic_0 (clk, reset, cur_ins, rd_addr_a, rd_addr_b, wr_addr, op, sel, jump, pc_inc, load_ir, wr_reg);
  reg_alu reg_alu_0 (clk, reset, sel, wr_reg, op, rd_addr_a, rd_addr_b, wr_addr, d_in, d_out_a, d_out_b, cout);
  assign d_out = d_out_a;
endmodule
