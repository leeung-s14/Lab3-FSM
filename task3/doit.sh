rm -rf obj_dir
rm -f secdelay.vcd

verilator -Wall --cc --trace secdelay.sv clktick.sv f1_fsm.sv --exe secdelay_tb.cpp




make -j -C obj_dir/ -f  Vsecdelay.mk Vsecdelay


obj_dir/Vsecdelay