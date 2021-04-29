#pragma once
#include "definitions.h"

class MMU {
    public:
        uint8_t MEMORY[GB_MEMORY_MAX];
        uint32_t ROM_SIZE = 0;

        void ROM_LOAD(MMU* mmu, char *filename);
};