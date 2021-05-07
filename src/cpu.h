#pragma once
#include "mmu.h"

class Register {
        public:
            uint8_t *low;
            uint8_t *high;
            Register();
            Register(uint8_t *high, uint8_t *low);
            uint16_t GetRegister();
            void SetRegister(uint16_t value);
};

class CPU {
    public:
        uint8_t FLAG_Z = 7;
        uint8_t FLAG_N = 6;
        uint8_t FLAG_H = 5;
        uint8_t FLAG_C = 4;
        uint8_t A, B, C, D, E, F, H, L;
        uint16_t SP;
        uint16_t PC;

        MMU* mmu;

        CPU(MMU* mmu);
        Register AF, BC, DE, HL;

        void Initialise();
        void Cycle();
        void Execute(uint8_t Instruction);

        typedef void (CPU::*Opcode)(void);
        Opcode Opcodes[0x100] = {0};
        void PopulateOpcodes();
    
    private:
        void SetBit(uint8_t &byte, uint8_t bit);
        void ClearBit(uint8_t &byte, uint8_t bit);
        void ToggleBit(uint8_t &byte, uint8_t bit);
        uint8_t GetBit(uint8_t byte, uint8_t bit);

        void PUSH_STACK(Register &reg);
        void PUSH_STACK16(uint16_t value);
        void POP_STACK(Register &reg);
        uint16_t READ_STACK();

        void LD(uint8_t &reg1, uint8_t reg2);
        void LD(uint16_t address, uint8_t reg);
        void LD(uint8_t &reg1, uint16_t address);
        void ADD(uint8_t reg2);
        void ADD_HL(uint16_t reg2);
        void ADD_SP();
        void ADC(uint8_t reg2);
        void SUB(uint8_t reg2);
        void SBC(uint8_t reg2);
        void AND(uint8_t reg2);
        void XOR(uint8_t reg2);
        void OR(uint8_t reg2);
        void INC(uint8_t &reg);
        void INC(Register reg);
        void INC_SP();
        void DEC(uint8_t &reg);
        void DEC(Register reg);
        void DEC_SP();
        void RET();
        void RET_TRUE(uint8_t flag);
        void RET_FALSE(uint8_t flag);

        void Opcode0x00();
        void Opcode0x01();
        void Opcode0x02();
        void Opcode0x06();
        void Opcode0x08();
        void Opcode0x09();
        void Opcode0x0A();
        void Opcode0x0E();
        void Opcode0x11();
        void Opcode0x12();
        void Opcode0x16();
        void Opcode0x19();
        void Opcode0x1A();
        void Opcode0x1E();
        void Opcode0x21();
        void Opcode0x22();
        void Opcode0x26();
        void Opcode0x29();
        void Opcode0x2A();
        void Opcode0x2E();
        void Opcode0x31();
        void Opcode0x32();
        void Opcode0x36();
        void Opcode0x39();
        void Opcode0x3A();
        void Opcode0x3E();
        void Opcode0x40();
        void Opcode0x41();
        void Opcode0x42();
        void Opcode0x43();
        void Opcode0x44();
        void Opcode0x45();
        void Opcode0x46();
        void Opcode0x47();
        void Opcode0x48();
        void Opcode0x49();
        void Opcode0x4A();
        void Opcode0x4B();
        void Opcode0x4C();
        void Opcode0x4D();
        void Opcode0x4E();
        void Opcode0x4F();
        void Opcode0x50();
        void Opcode0x51();
        void Opcode0x52();
        void Opcode0x53();
        void Opcode0x54();
        void Opcode0x55();
        void Opcode0x56();
        void Opcode0x57();
        void Opcode0x58();
        void Opcode0x59();
        void Opcode0x5A();
        void Opcode0x5B();
        void Opcode0x5C();
        void Opcode0x5D();
        void Opcode0x5E();
        void Opcode0x5F();
        void Opcode0x60();
        void Opcode0x61();
        void Opcode0x62();
        void Opcode0x63();
        void Opcode0x64();
        void Opcode0x65();
        void Opcode0x66();
        void Opcode0x67();
        void Opcode0x68();
        void Opcode0x69();
        void Opcode0x6A();
        void Opcode0x6B();
        void Opcode0x6C();
        void Opcode0x6D();
        void Opcode0x6E();
        void Opcode0x6F();
        void Opcode0x70();
        void Opcode0x71();
        void Opcode0x72();
        void Opcode0x73();
        void Opcode0x74();
        void Opcode0x75();
        void Opcode0x76();
        void Opcode0x77();
        void Opcode0x78();
        void Opcode0x79();
        void Opcode0x7A();
        void Opcode0x7B();
        void Opcode0x7C();
        void Opcode0x7D();
        void Opcode0x7E();
        void Opcode0x7F();    
        void Opcode0x80();
        void Opcode0x81();
        void Opcode0x82();
        void Opcode0x83();
        void Opcode0x84();
        void Opcode0x85();
        void Opcode0x86();
        void Opcode0x87();
        void Opcode0x88();
        void Opcode0x89();
        void Opcode0x8A();
        void Opcode0x8B();
        void Opcode0x8C();
        void Opcode0x8D();
        void Opcode0x8E();
        void Opcode0x8F();    
        void Opcode0xE0(); 
        void Opcode0xE2(); 
        void Opcode0xEA(); 
        void Opcode0xF0(); 
        void Opcode0xF2(); 
        void Opcode0xFA(); 
};

