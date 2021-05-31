#define SDL_MAIN_HANDLED
#include "definitions.h"
#include "mmu.h"
#include "cpu.h"
#include "input.h"

int main(int argc, char *argv[]) {
    if(strlen(argv[1]) < 1) {
        std::cout << "[ERROR] Please specify a valid ROM file \n" << " [INFO] Usage: ./ouri [file]" << std::endl; 
        return 1;
    }
    std::string filename = argv[1];
    SDL_Event event;
    SDL_Window* window;
    SDL_Renderer* renderer;
    MMU* mmu = new MMU;
    mmu->LoadROM(mmu, filename);
    CPU* cpu = new CPU(mmu);
    Input* io = new Input(mmu);
    
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        std::cout << "[ERROR] Couldn't initlialise SDL!" << std::endl;
        return 1;
    } else {
        window = SDL_CreateWindow("ouri", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, 0);
        renderer = SDL_CreateRenderer(window, -1, 0); 
        
        for(;;) {
            //cpu->Cycle();
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
                    return 0;
                }
            }
        }
    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    delete(io);
    delete(mmu);
    delete(cpu);
    return 0;
}