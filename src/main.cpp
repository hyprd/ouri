#define SDL_MAIN_HANDLED
#include "definitions.h"
#include "mmu.h"
#include "cpu.h"
#include "input.h"
#include "ppu.h"

int main(int argc, char *argv[]) {
    if(strlen(argv[1]) < 1) {
        std::cout << "[ERROR] Please specify a valid ROM file \n" << " [INFO] Usage: ./ouri [file]" << std::endl; 
        return 1;
    }
    std::string filename = argv[1];
    
    MMU* mmu = new MMU;
    mmu->LoadROM(mmu, filename);
    CPU* cpu = new CPU(mmu);
    Input* io = new Input(mmu);
    PPU* ppu = new PPU(mmu);
    SDL_Event event;
    
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        std::cout << "[ERROR] Couldn't initlialise SDL!" << std::endl;
        return 1;
    } else {
        for(;;) {
            //cpu->Cycle();
            ppu->Update();
            while(SDL_PollEvent(&event)) {
                if(event.type == SDL_KEYDOWN) {
                    switch(event.key.keysym.sym) {
                        case SDLK_LEFT:
                            io->Pressed(Input::Keys::LEFT);
                            break;
                        case SDLK_RIGHT:
                            io->Pressed(Input::Keys::RIGHT);
                            break;
                        case SDLK_UP:
                            io->Pressed(Input::Keys::UP);
                            break;
                        case SDLK_DOWN:
                            io->Pressed(Input::Keys::DOWN);
                            break;
                        case SDLK_z:
                            io->Pressed(Input::Keys::A);
                            break;
                        case SDLK_x:
                            io->Pressed(Input::Keys::B);
                            break;
                        case SDLK_ESCAPE:
                            io->Pressed(Input::Keys::START);
                            break;
                        case SDLK_F1:
                            io->Pressed(Input::Keys::SELECT);
                            break;
                    }
                } else if(event.type == SDL_KEYUP) {
                    switch(event.key.keysym.sym) {
                        case SDLK_LEFT:
                            io->Released(Input::Keys::LEFT);
                            break;
                        case SDLK_RIGHT:
                            io->Released(Input::Keys::RIGHT);
                            break;
                        case SDLK_UP:
                            io->Released(Input::Keys::UP);
                            break;
                        case SDLK_DOWN:
                            io->Released(Input::Keys::DOWN);
                            break;
                        case SDLK_z:
                            io->Released(Input::Keys::A);
                            break;
                        case SDLK_x:
                            io->Released(Input::Keys::B);
                            break;
                        case SDLK_ESCAPE:
                            io->Released(Input::Keys::START);
                            break;
                        case SDLK_F1:
                            io->Released(Input::Keys::SELECT);
                            break;
                    }
                } else if(event.type == SDL_QUIT) {
                    delete(io);
                    delete(mmu);
                    delete(cpu);
                    delete(ppu);
                    return 0;
                }
            }
        }
    }
    return 0;
}
