#include "instructions.cpp"
#include "assembler.cpp"

#define opcode(instr) (instr>>11)
#define reg1(instr) ((instr&0b0000011100000000)>>8)
#define reg2(instr) ((instr&0b0000000011100000)>>5)

void decodenexecute(u16 instr){
    cout<<"opcode: "<<bitset<5>(opcode(instr))<<endl;
    // cout<<endl;
    // cout<<"opcode: "<<(int)opcode(instr)<<endl;
    switch(opcode(instr)){
        case 0b00000:
            add(reg1(instr), reg2(instr));
            cout<<SRAM[ra]<<endl;
            break;
        case 0b00001:
            addi(reg1(instr));
            break;
        case 0b00010:
            sub(reg1(instr), reg2(instr));
            break;
        case 0b00011:
            subi(reg1(instr));
            break;
        case 0b00100:
            // cout<<(int)opcode(instr)<<endl;
            // cout<<"LDI!!"<<endl;
            ldi(reg1(instr));
            break;
        case 0b00101:
            lda(reg1(instr));
            break;
        case 0b00110:
            ldw(reg1(instr));
            break;
        case 0b00111:
            cmp(reg1(instr), reg2(instr));
            break;
        case 0b01000:
            cmpi(reg1(instr));
            break;
        case 0b01001:
            jmp();
            break;
        case 0b01010:
            rjmp();
            break;
        case 0b01011:
            breq();
            break;
        case 0b01100:
            mov(reg1(instr), reg2(instr));
            break;
        case 0b01101:
            clr(reg1(instr));
            break;
        case 0b01110:
            clc();
            break;
        case 0b01111:
            clz();
            break;
        case 0b10000:
            cln();
            break;
        case 0b10010:
            cli();
            break;
        case 0b10011:
            slc();
            break;
        case 0b10100:
            slz();
            break;
        case 0b10101:
            sln();
            break;
        case 0b10111:
            sli();
            break;
        case 0b11000:
            cout<<"here"<<endl;
            an(reg1(instr), reg2(instr));
            break;
        case 0b11001:
            andi(reg1(instr));
            break;
        case 0b11010:
            orr(reg1(instr), reg2(instr));
            break;
        case 0b11011:
            ori(reg1(instr));
            break;
        case 0b11100:
            xo(reg1(instr), reg2(instr));
            break;
        case 0b11101:
            xori(reg1(instr));
            break;
    }
}
