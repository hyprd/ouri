#include "definitions.h"
#include "mmu.h"
#include "cpu.h"

int main(int argc, char *argv[]) {
    char *Filename = argv[1];
    MMU* mmu = new MMU;
    CPU* cpu = new CPU(mmu);
    mmu->LoadROM(mmu, Filename);
    return 0;
}