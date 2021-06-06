#include "input.h"

Input::Input(MMU* mmu){
    _mmu = mmu;
    joypad = mmu->ReadMemory(0xFF00);
    contextAction = std::bitset<8>().set();
    contextDirection = std::bitset<8>().set();
}

void Input::Pressed(Keys k) {
    if(k == LEFT || k == RIGHT || k == UP || k == DOWN) {
        contextDirection.reset(k); 
        currentContext = contextDirection;
    } else {
        // enum attributes are inherently integers so subtract to 
        // bring value down from upper to lower, since only lower
        // nibbles need to be changed.
        contextAction.reset(k - 4); 
        currentContext = contextAction;
    }
    WriteState();
}

void Input::Released(Keys k) {
    if(k == LEFT || k == RIGHT || k == UP || k == DOWN) {
        contextDirection.set(k); 
        currentContext = contextDirection;
    } else {
        contextAction.set(k - 4);
        currentContext = contextAction;
    }
    WriteState();
}

void Input::WriteState() {
    //std::cout << std::uppercase << std::hex << currentContext.to_ulong() << std::endl;
    joypad = static_cast<uint8_t>(currentContext.to_ulong());
    _mmu->SetMemory(0xFF00, joypad);
}


