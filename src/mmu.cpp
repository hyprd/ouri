#include "mmu.h"

MMU::MMU(){}

void MMU::LoadROM(MMU* mmu, char *Filename) {
    std::cout << "[INFO] Loading cartridge..." << std::endl;
    FILE* f = fopen(Filename, "rb");
    fseek(f, 0, SEEK_END);
    sizeROM = ftell(f);
    rewind(f);
    fread(mmu->Memory, 1, sizeROM, f);
    fclose(f);
    std::cout << "[INFO] Loaded cartridge " << Filename << ", Size: " << sizeROM << " bytes.";
}

void MMU::DumpMemory(MMU* mmu) {
    for(int i = 0 ; i < mmu->sizeROM; i++) {
        std::cout << std::hex << std::uppercase << +Memory[i] << "\t"; 
    }
}

uint8_t MMU::ReadMemory(uint16_t Address) {
    return Memory[Address];
}

void MMU::SetMemory(uint16_t Address, uint8_t Value) {
     Memory[Address] = Value;
} 