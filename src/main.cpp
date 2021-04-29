#include "definitions.h"
#include "mmu.h"
#include "cpu.h"

int main(int argc, char *argv[]) {
    char *filename = argv[1];
    MMU* mmu = new MMU;
    CPU* cpu = new CPU;
    mmu->ROM_LOAD(mmu, filename);
    return 0;
}