#include "Vf1_fsm.h"
#include "verilated.h"
#include "verilated_vcd_c.h"
#include "vbuddy.cpp"

int main(int argc, char **argv, char **env) {
    int i;              //# of cycles to simulate
    int clk;

    Verilated::commandArgs(argc, argv);
    // init top verilog instance
    Vf1_fsm* top = new Vf1_fsm;
    // init trace dump
    Verilated::traceEverOn(true);
    VerilatedVcdC* tfp = new VerilatedVcdC;
    top->trace (tfp,99);
    tfp->open ("f1_fsm.vcd");

    //init Vbuddy
    if (vbdOpen()!=1) return (-1);
    vbdHeader("Lab 3: F1");

    //initialize simulation inputs
    top->clk = 1;
    top->rst = 1;
    top->en = 0;

    //run simulation for many clock cycles
    for (i=0; i<200;i++) {
        //dump variables into VCD file and toggle clock
        for (clk =0;clk<2;clk++) { tfp->dump (2*i+clk);
            top->clk = !top->clk;
            top->eval();
        }

        //Send count value to Vbuddy
        // vbdHex(4,(int(top->count) >> 16) & 0xF);
        // vbdHex(3,(int(top->count) >> 8) & 0xF);
        // vbdHex(2,(int(top->count) >> 4) & 0xF);
        // vbdHex(1,(int(top->count)) & 0xF);
        vbdBar(top->data_out & 0xFF);
        vbdCycle(i+1);

        
        top->rst = false ;
        top->en = vbdFlag();
    // either simulation finished, or 'q' is pressed
    if ((Verilated::gotFinish()) || (vbdGetkey()=='q')) 
      exit(0);                // ... exit if finish OR 'q' pressed    
    }

    vbdClose();
    tfp->close();
    exit(0);
}