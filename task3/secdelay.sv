module secdelay #(
    parameter D_WIDTH = 8,
              N_WIDTH = 16
)(    input  logic             clk,      // clock 
    input  logic             rst,      // reset
    input  logic             en,       // enable signal
    input  logic [N_WIDTH-1:0] N,     	 // clock divided by N+1
    output logic [D_WIDTH-1:0] data_out
);

    logic delayen;

clktick timer (
    .clk (clk),
    .rst (rst),
    .en (en),
    .N (N),
    .tick (delayen)
);

f1_fsm lightcontrol (
    .clk (clk),
    .rst (rst),
    .en (delayen),
    .data_out(data_out)
);
endmodule
