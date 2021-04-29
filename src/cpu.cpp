#include "cpu.h"

CPU::CPU(MMU* mmu) {
    A = B = C = D = E = F = H = L = 0x00;
    SP = PC = 0x0000;
    AF = Register(&A, &F);
    BC = Register(&B, &C);
    DE = Register(&D, &E);
    HL = Register(&H, &L);
    
    Initialise();
} 

void CPU::Initialise() {
    PC = 0x0100;
    SP = 0xFFFE;
}