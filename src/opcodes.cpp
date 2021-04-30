#include "opcodes.h"

void CPU::PopulateOpcodes() {
    Opcodes[0x00] = &CPU::Opcode0x00;
}

void CPU::Opcode0x00() {
    std::cout << "NOP" << std::endl;
}