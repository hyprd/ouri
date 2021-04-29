#include "cpu.h"

Register::Register(){}
Register::Register(uint8_t *hi, uint8_t *lo){ 
    high = hi; 
    low = lo;
}

uint16_t Register::GetRegister() { 
    return *high << 8 | (*low & 0x00FF);    
}

void Register::SetRegister(uint16_t value) {
    *low = value & 0x00FF;
    *high = value >> 8;
}

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
    std::cout << "[INFO] Initialising CPU..." << std::endl;
    PC = 0x0100;
    SP = 0xFFFE;
}