#include "mmu.h"

MMU::MMU(){}

void MMU::LoadROM(MMU* mmu, char *Filename) {
    FILE* f = fopen(Filename, "rb");
    fseek(f, 0, SEEK_END);
    SizeROM = ftell(f);
    rewind(f);
    fread(mmu->Memory, 1, SizeROM, f);
    fclose(f);
}

uint16_t MMU::ReadMemory(uint16_t Address) {
    return Memory[Address];
}

void MMU::SetMemory(uint16_t Address, uint8_t Value) {
     Memory[Address] = Value;
} 