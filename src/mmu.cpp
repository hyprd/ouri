#include "mmu.h"

MMU::MMU(){}

void MMU::LoadROM(MMU* mmu, char *filename) {
    FILE* f = fopen(filename, "rb");
    fseek(f, 0, SEEK_END);
    SizeROM = ftell(f);
    rewind(f);
    fread(mmu->Memory, 1, SizeROM, f);
    fclose(f);
}