#pragma once
#include "definitions.h"

class MMU {
    public:
        MMU();
        uint8_t Memory[GB_MEMORY_MAX];
        uint32_t sizeROM = 0;
        
        void LoadROM(MMU* mmu, std::string filename);
        void DumpMemory(MMU* mmu);
        
        uint8_t ReadMemory(uint16_t address);
        void SetMemory(uint16_t address, uint8_t value);
};