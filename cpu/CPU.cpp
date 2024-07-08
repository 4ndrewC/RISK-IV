#include "decoder.cpp"

u16 pos;

class CPU{
public:

    CPU(){
        PC = pc_offset;
        pos = 32;
        assemble();
    }

    void fetch(){
        u16 instr = SRAM[PC];
        decodenexecute(instr);
        PC++;
    }
};