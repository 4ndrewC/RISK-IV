#include "registers.h"
#include "formatting.h"
#include "memory.h"

#define setCf SRAM[sreg]|=1
#define setZf SRAM[sreg]|=2
#define setIf SRAM[sreg]|=4
#define setNf SRAM[sreg]|=8

#define unsetCf SRAM[sreg]&=0b11111110
#define unsetZf SRAM[sreg]&=0b11111101
#define unsetIf SRAM[sreg]&=0b11111011
#define unsetNf SRAM[sreg]&=0b11110111

#define bit1(byt) (byt&1)
#define bit2(byt) ((byt&2)>>1)
#define bit3(byt) ((byt&4)>>2)
#define bit4(byt) ((byt&8)>>3)
#define bit5(byt) ((byt&16)>>4)
#define bit6(byt) ((byt&32)>>5)
#define bit7(byt) ((byt&64)>>6)
#define bit8(byt) ((byt&128)>>7)
#define bit9(byt) ((byt&256)>>8)
#define bit10(byt) ((byt&512)>>9)
#define bit11(byt) ((byt&1024)>>10)
#define bit12(byt) ((byt&2048)>>11)
#define bit13(byt) ((byt&4096)>>12)
#define bit14(byt) ((byt&8192)>>13)
#define bit15(byt) ((byt&16384)>>14)
#define bit16(byt) ((byt&32768)>>15)

#define set_bit1(byt) (byt|=1)
#define set_bit2(byt) ((byt|=2))
#define set_bit3(byt) ((byt|=4))
#define set_bit4(byt) ((byt|=8))
#define set_bit5(byt) ((byt|=16))
#define set_bit6(byt) ((byt|=32))
#define set_bit7(byt) ((byt|=64))
#define set_bit8(byt) ((byt|=128))
#define set_bit9(byt) ((byt|=256))
#define set_bit10(byt) ((byt|=512))
#define set_bit11(byt) ((byt|=1024))
#define set_bit12(byt) ((byt|=2048))
#define set_bit13(byt) ((byt|=4096))
#define set_bit14(byt) ((byt|=8192))
#define set_bit15(byt) ((byt|=16384))
#define set_bit16(byt) ((byt|=32768))

#define Cf bit1(SRAM[sreg])
#define Zf bit2(SRAM[sreg])
#define If bit3(SRAM[sreg])
#define Nf bit5(SRAM[sreg])


void add(u8 r, u8 d){
    u16 res = SRAM[r]+SRAM[d];
    if(!res) setZf; else unsetZf;
    if((bit8(SRAM[d])&bit8(SRAM[r])) + (bit8(SRAM[r])&~bit8(res)) + (~bit8(res)&bit8(SRAM[d]))) setCf; else unsetCf;
    // if(bit8(res)) setNf; else unsetNf;
    SRAM[r] = res;
}

void addi(u8 r){
    PC++;
    u16 imm = SRAM[PC];
    u16 res = SRAM[r]+imm;
    if(!res) setZf; else unsetZf;
    if((bit8(imm)&bit8(SRAM[r])) + (bit8(SRAM[r])&~bit8(res)) + (~bit8(res)&bit8(imm))) setCf; else unsetCf;
    // if(bit8(res)) setNf; else unsetNf;
    SRAM[r] = res;
}

void sub(u8 r, u8 d){
    u16 res = SRAM[r]-SRAM[d];
    if(res) unsetZf;
    if((~bit8(SRAM[d])&bit8(SRAM[r])) + (bit8(SRAM[r])&bit8(res)) + (bit8(res)&~bit8(SRAM[d]))) setCf; else unsetCf;
    SRAM[r] = res;
}

void subi(u8 r){
    PC++;
    u16 imm = SRAM[PC];
    u16 res = SRAM[r]-imm;
    if(res) unsetZf;
    if((~bit8(imm)&bit8(SRAM[r])) + (bit8(SRAM[r])&bit8(res)) + (bit8(res)&~bit8(imm))) setCf; else unsetCf;
    SRAM[r] = res;
}

void ldi(u8 reg){
    PC++;
    u16 imm = SRAM[PC];
    SRAM[reg] = imm;
}

void lda(u8 reg){
    PC++;
    u16 addr = SRAM[PC];
    SRAM[reg] = SRAM[addr];
}

void ldw(u8 reg){
    PC++;
    u16 addr = SRAM[PC];
    SRAM[addr] = SRAM[reg];
}

void cmp(u8 r, u8 d){
    u16 res = SRAM[d]-SRAM[r];
    if(!res) setZf; else unsetZf;
}

void cmpi(u8 reg){
    PC++;
    u16 imm = SRAM[PC];
    u16 res = imm-SRAM[reg];
    if(!res) setZf; else unsetZf;
}

void jmp(){
    PC++;
    u16 addr = SRAM[PC];
    PC = addr - 1;
}

void rjmp(){
    PC++;
    u16 rel = SRAM[PC]&0b0111111111111111;
    // cout<<(int)SRAM[PC]<<endl;
    u8 sign = bit16(SRAM[PC]);
    // cout<<(int)sign<<endl;
    u16 newpos = sign==0 ? PC+rel-2: PC-rel-2;
    PC = newpos;
}

void breq(){
    PC++;
    u16 addr = SRAM[PC];
    if(Zf) PC = addr - 1;
}

void mov(u8 d, u8 r){
    SRAM[d] = SRAM[r];
}

void clr(u8 reg){
    SRAM[reg] = 0;
    setZf;
}

void clc(){unsetCf;}
void clz(){unsetZf;}
void cln(){unsetNf;}
void cli(){unsetIf;}
void slc(){setCf;}
void slz(){setZf;}
void sln(){setNf;}
void sli(){setIf;}

void an(u8 reg1, u8 reg2){
    // cout<<"and executed"<<endl;
    u16 res = SRAM[reg1]&SRAM[reg2];
    if(!res) setZf; else unsetZf;
    SRAM[reg1] = res;
}

void andi(u8 reg1){
    PC++;
    u16 imm = SRAM[PC];
    u16 res = SRAM[reg1]&imm;
    if(!res) setZf; else unsetZf;
    SRAM[reg1] = res;
}

void orr(u8 reg1, u8 reg2){
    u16 res = SRAM[reg1]|SRAM[reg2];
    if(!res) setZf; else unsetZf;
    SRAM[reg1] = res;
}

void ori(u8 reg1){
    PC++;
    u16 imm = SRAM[PC];
    u16 res = SRAM[reg1]|imm;
    if(!res) setZf; else unsetZf;
    SRAM[reg1] = res;
}

void xo(u8 reg1, u8 reg2){
    u16 res = SRAM[reg1]^SRAM[reg2];
    if(!res) setZf; else unsetZf;
    SRAM[reg1] = res;
}

void xori(u8 reg1){
    PC++;
    u16 imm = SRAM[PC];
    u16 res = SRAM[reg1]^imm;
    if(!res) setZf; else unsetZf;
    SRAM[reg1] = res;
}