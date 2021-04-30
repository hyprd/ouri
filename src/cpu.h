#pragma once
#include "definitions.h"
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
        Opcode Opcodes[0x100];
        void PopulateOpcodes();
    
    private:
        void Opcode0x00();

        void LD(uint8_t &Reg1, uint8_t Reg2);
        void LD(uint16_t Address, uint8_t Reg);
        void LD(uint8_t &Reg1, uint16_t Address);
};

