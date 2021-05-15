#pragma once
#include "definitions.h"

class MMU {
    public:
        MMU();
        uint8_t Memory[GB_MEMORY_MAX];
        uint32_t sizeROM = 0;

        void LoadROM(MMU* mmu, char *Filename);
        void DumpMemory(MMU* mmu);
        
        uint8_t ReadMemory(uint16_t Address);
        void SetMemory(uint16_t Address, uint8_t Value);
};