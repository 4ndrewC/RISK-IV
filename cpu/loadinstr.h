#include "CPU.cpp"

#define reg_reg(instr, reg1, reg2) (((((instr<<3)+reg1)<<3)+reg2)<<5)
#define one_reg(instr, reg) (((instr<<3)+reg)<<8)
#define instr_only(instr) (instr<<11)

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
    SRAM[pos] = (u16)(abs(rel));
    if(rel<0) set_bit16(SRAM[pos]);
    // cout<<(rel<0)?1:0;
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

void instr_and(u8 reg1, u8 reg2){
    u16 instr = reg_reg(0b11000, reg1, reg2);
    SRAM[pos] = instr;
    pos++;
}

void instr_andi(u8 reg1, u16 imm){
    u16 instr = one_reg(0b11001, reg1); 
    SRAM[pos] = instr;
    pos++;
    SRAM[pos] = imm;
    pos++;
}

void instr_or(u8 reg1, u8 reg2){
    u16 instr = reg_reg(0b11010, reg1, reg2);
    SRAM[pos] = instr;
    pos++;
}

void instr_ori(u8 reg1, u16 imm){
    u16 instr = one_reg(0b11011, reg1); 
    SRAM[pos] = instr;
    pos++;
    SRAM[pos] = imm;
    pos++;
}

void instr_xor(u8 reg1, u8 reg2){
    u16 instr = reg_reg(0b11100, reg1, reg2);
    SRAM[pos] = instr;
    pos++;
}

void instr_xori(u8 reg1, u16 imm){
    u16 instr = one_reg(0b11101, reg1); 
    SRAM[pos] = instr;
    pos++;
    SRAM[pos] = imm;
    pos++;
}

void instr_clr(u8 reg){
    SRAM[reg] = 0;
    pos++;
}