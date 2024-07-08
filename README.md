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
void sample(CPU& cpu){
    instr_ldi(rp, 0xF00F);
    instr_addi(ry, 1);
    instr_cmpi(ry, 255);
    instr_breq(42);
    instr_jmp(34);

    instr_ldi(ry, 0);
    instr_addi(rx, 1);
    instr_jmp(34);
}
```
Then load ```sample()``` into memory in the main function:
```cpp 
sample(cpu);
```
