#pragma once
#include "definitions.h"

class MMU {
    public:
        MMU();
        uint8_t Memory[GB_MEMORY_MAX];
        uint32_t SizeROM = 0;

        void LoadROM(MMU* mmu, char *Filename);
};