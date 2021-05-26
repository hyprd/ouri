#define SDL_MAIN_HANDLED
#include "definitions.h"
#include "mmu.h"
#include "cpu.h"

int main(int argc, char *argv[]) {
    if(strlen(argv[1]) < 1) {
        std::cout << "[ERROR] Please specify a valid ROM file \n" << " [INFO] Usage: ./ouri [file]" << std::endl; 
        return 1;
    }
    std::string filename = argv[1];
    
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        std::cout << "[ERROR] Couldn't initlialise SDL!" << std::endl;
        return 1;
    } else {
    MMU* mmu = new MMU;
    mmu->LoadROM(mmu, filename);
    CPU* cpu = new CPU(mmu);
    for(;;) {
        cpu->Cycle();
    }
   }
    return 0;
}