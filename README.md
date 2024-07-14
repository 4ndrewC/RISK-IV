# RISK_IV

Custom 16-bit Architecture in C++

To run:

```
cd run
make
main
```

Write your own code in ```cpu/main.cpp```

**Sample**
```cpp
void sample(){
    instr_ldi(ri, 0x03E7);
    instr_ldi(rb, 0xFFFF);
    instr_addi(ry, 1);
    instr_cmpi(ry, 255); 
    instr_breq(50); 
    instr_rjmp(-6); 

    instr_ldi(ry, 0); 
    instr_addi(rx, 1); 
    instr_rjmp(-12); 

    instr_cmpi(rx, 255); 
    instr_breq(56); 
    instr_rjmp(-10); 
    instr_mov(ra, ri); 
    instr_mov(ri, rb); 
    instr_mov(rb, ra); 
    instr_ldi(rx, 0); 
    instr_ldi(ry, 0); 
    instr_jmp(36); 
}
```
Then load ```sample()``` into memory in the main function:
```cpp 
sample(cpu);
```
