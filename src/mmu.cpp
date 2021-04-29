#include "mmu.h"

MMU::MMU(){}

void MMU::ROM_LOAD(MMU* mmu, char *filename) {
    FILE* f = fopen(filename, "rb");
    fseek(f, 0, SEEK_END);
    ROM_SIZE = ftell(f);
    rewind(f);
    fread(mmu->MEMORY, 1, ROM_SIZE, f);
    fclose(f);
}