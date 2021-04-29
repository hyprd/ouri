#include "definitions.h"
#include "mmu.h"

int main(int argc, char *argv[]) {
    char *filename = argv[1];
    MMU* mmu = new MMU;
    mmu->ROM_LOAD(mmu, filename);

    return 0;
}