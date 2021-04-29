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

        CPU(MMU* mmu);
        Register AF, BC, DE, HL;

        void Initialise();
};

