#include "helpers.h"
#include "cpu.h"

uint16_t FormWord(uint8_t high, uint8_t low) {
    return static_cast<uint16_t>(high << 8 | low & 0x00FF);
}

uint8_t FormByte(uint8_t high, uint8_t low) {
    return static_cast<uint8_t>(high << 4 | low);
}

void CPU::DebugRegisters() {
    std::cout << "PC: " << PC << std::endl;
    std::cout << "SP: " << +SP << std::endl;
    std::cout << "AF: " << std::bitset<8>(AF.GetRegister()) << std::endl;
    std::cout << "BC: " << std::bitset<8>(BC.GetRegister()) << std::endl;
    std::cout << "DE: " << std::bitset<8>(DE.GetRegister()) << std::endl;
    std::cout << "HL: " << std::bitset<8>(HL.GetRegister()) << std::endl;
}

void CPU::DebugInstruction(uint8_t inst) {
    std::cout << "Instruction 0x" << (inst < 0x10 ? "0" : "") << std::hex << std::uppercase << +inst << std::endl;
}

