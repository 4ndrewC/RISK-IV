#include "../display/display.cpp"
#include "../cpu/loadinstr.h"
#include <thread>

CPU cpu;

void sample(){
    instr_ldi(ri, 0x03E7);
    instr_ldi(rb, 0xFFFF);
    instr_addi(ry, 1);// 34 35
    instr_cmpi(ry, 255); //36 37
    instr_breq(50); // 38 39
    instr_rjmp(-6); // 40 41

    instr_ldi(ry, 0); // 42 43
    instr_addi(rx, 1); // 44 45
    instr_rjmp(-12); // 46 47

    instr_cmpi(rx, 255); // 48 49
    instr_breq(56); // 50 51
    instr_rjmp(-10); // 52 53
    instr_mov(ra, ri); // 54 55
    instr_mov(ri, rb); //56 57
    instr_mov(rb, ra); // 58 59
    instr_ldi(rx, 0); // 60 61
    instr_ldi(ry, 0); // 62 63
    instr_jmp(36); // 64 65
}

void sign_test_rjmp(){
    instr_ldi(ra, 13);
    instr_rjmp(-3);
}

void cpu_run(){
    while(1){
        cpu.fetch();
        pixels[SRAM[rx]][SRAM[ry]] = SRAM[ri];
    }
}

void test(int rep){
    for(int i = 0; i<rep; i++){
        cpu.fetch();
        cout<<"program counter: "<<dec<<PC<<endl;
    }
}

int main(int argc, char* args[]){
    cpu = CPU();

    // sign_test_rjmp();
    // test(3);
    init(); // initialize display
    sample(); // load program
    thread disp(display_run); // display thread
    thread processor(cpu_run); // cpu thread
    
    disp.join();
    processor.join();
    
    
    return 0;
}