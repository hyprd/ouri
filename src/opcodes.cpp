#include "opcodes.h"

void CPU::PopulateOpcodes() {
    Opcodes[0x00] = &CPU::Opcode0x00;
}

void CPU::Opcode0x00() {
    std::cout << "NOP" << std::endl;
}

void CPU::LD(uint8_t &Reg1, uint8_t Reg2) {
    Reg1 = Reg2;
}

void CPU::LD(uint16_t Address, uint8_t Reg) {
    mmu->SetMemory(Address, Reg);
}

void CPU::LD(uint8_t &Reg1, uint16_t Address) {
    Reg1 = mmu->ReadMemory(Address);
}