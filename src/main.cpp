#include "definitions.h"
#include "mmu.h"
#include "cpu.h"

int main(int argc, char *argv[]) {
    char *Filename = argv[1];
    MMU* mmu = new MMU;
    mmu->LoadROM(mmu, Filename);
    CPU* cpu = new CPU(mmu);
    //mmu->DumpMemory(mmu);
    for(;;) {
        cpu->Cycle();
    }
    return 0;
}