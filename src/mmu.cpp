#include "mmu.h"
#include "helpers.h"

MMU::MMU(){}

void MMU::LoadROM(MMU* mmu, std::string filename) {
    const char* fname = filename.c_str();
    std::cout << "[INFO] Loading cartridge..." << std::endl;
    FILE* f = fopen(fname, "rb");
    fseek(f, 0, SEEK_END);
    sizeROM = ftell(f);
    rewind(f);
    fread(mmu->Memory, 1, sizeROM, f);
    fclose(f);
    std::cout << "[INFO] Loaded cartridge " << fname << ", Size: " << sizeROM << " bytes.";
}

void MMU::DumpMemory(MMU* mmu) {
    for(int i = 0 ; i < mmu->sizeROM; i++) {
        std::cout << std::hex << std::uppercase << +Memory[i] << "\t"; 
    }
}

uint8_t MMU::ReadMemory(uint16_t address) {
    return Memory[address];
}

void MMU::SetMemory(uint16_t address, uint8_t value) {
     Memory[address] = value;
} 