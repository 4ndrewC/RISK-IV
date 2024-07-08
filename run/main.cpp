#include "../cpu/CPU.cpp"
#include "../display/display.cpp"
#include <thread>

#define reg_reg(instr, reg1, reg2) (((((instr<<3)+reg1)<<3)+reg2)<<5)
#define one_reg(instr, reg) (((instr<<3)+reg)<<8)
#define instr_only(instr) (instr<<11)

CPU cpu;

void instr_add(u8 reg1, u8 reg2){
    u16 instr = reg_reg(0b00000, reg1, reg2);
    SRAM[pos] = instr;
    pos++;
}

void instr_addi(u8 reg1, u16 imm){
    u16 instr = one_reg(0b00001, reg1); 
    SRAM[pos] = instr;
    pos++;
    SRAM[pos] = imm;
    pos++;
}

void instr_sub(u8 reg1, u8 reg2){
    u16 instr = reg_reg(0b00010, reg1, reg2);
    SRAM[pos] = instr;
    pos++;
}

void instr_subi(u8 reg1, u16 imm){
    u16 instr = one_reg(0b00011, reg1); 
    SRAM[pos] = instr;
    pos++;
    SRAM[pos] = imm;
    pos++;
}

void instr_ldi(u8 reg1, u16 imm){
    u16 instr = one_reg(0b00100, reg1);
    SRAM[pos] = instr;
    pos++;
    SRAM[pos] = imm;
    pos++;
}

void instr_lda(u8 reg1, u16 addr){
    u16 instr = one_reg(0b00101, reg1);
    SRAM[pos] = instr;
    pos++;
    SRAM[pos] = addr;
    pos++;
}

void instr_ldw(u8 reg1, u16 addr){
    u16 instr = one_reg(0b00110, reg1);
    SRAM[pos] = instr;
    pos++;
    SRAM[pos] = addr;
    pos++;
}

void instr_jmp(u16 addr){
    u16 instr = instr_only(0b01001);
    SRAM[pos] = instr;
    pos++;
    SRAM[pos] = addr;
    pos++;
}

void instr_rjmp(int rel){
    u16 instr = instr_only(0b01010);
    SRAM[pos] = instr;
    pos++;
    SRAM[pos] = rel;
    pos++;
}

void instr_cmp(u8 reg1, u8 reg2){
    u16 instr = reg_reg(0b00111, reg1, reg2);
    SRAM[pos] = instr;
    pos++;
}

void instr_cmpi(u8 reg1, u16 imm){
    u16 instr = one_reg(0b01000, reg1);
    SRAM[pos] = instr;
    pos++;
    SRAM[pos] = imm;
    pos++;
}

void instr_breq(u16 addr){
    u16 instr = instr_only(0b01011);
    SRAM[pos] = instr;
    pos++;
    SRAM[pos] = addr;
    pos++;
}

void instr_mov(u8 reg1, u8 reg2){
    u16 instr = reg_reg(0b01100, reg1, reg2);
    SRAM[pos] = instr;
    pos++;
}

void sample(CPU& cpu){
    // instr_ldi(rx, 0); // 32 33
    // instr_ldi(ry, 0); // 34 35
    instr_ldi(rp, 0xF00F); // 36 37
    instr_addi(ry, 1); // 38 39
    instr_cmpi(ry, 255); // 40 42
    instr_breq(42); // 42 43
    instr_jmp(34); // 44 45

    instr_ldi(ry, 0); // 46 47
    instr_addi(rx, 1); // 48 49
    instr_jmp(34); // 50 51
}

void cpu_run(){
    while(1){
        cpu.fetch();
        pixels[SRAM[rx]][SRAM[ry]] = SRAM[rp];
    }
}

void debug(){
    cout<<"opcode: "<<hex<<(int)opcode(SRAM[PC])<<endl;
    cout<<"ry: "<<(int)SRAM[ry]<<endl;
}

void test(){
    for(int i = 0; i<100; i++){
        cpu.fetch();
        debug();
    }
}

int main(int argc, char* args[]){
    cpu = CPU();
    init(); // initialize display
    sample(cpu); // load program
    thread disp(display_run); // display thread
    thread processor(cpu_run); // cpu thread
    
    disp.join();
    processor.join();
    
    return 0;
}