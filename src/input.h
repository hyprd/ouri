#pragma once
#include "definitions.h"
#include "mmu.h"

class Input {
    public:
        enum Keys { 
            RIGHT, LEFT, UP, DOWN, 
            A, B, SELECT, START
        };
        MMU* _mmu;
        Input(MMU* mmu);
        uint8_t joypad; 
        std::bitset<8> currentContext;
        std::bitset<8> contextAction;
        std::bitset<8> contextDirection;
        void Pressed(Keys k);
        void Released(Keys k);
        void WriteState();

};