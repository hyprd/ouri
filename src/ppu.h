#include "definitions.h"
#include "mmu.h"
#pragma once

class PPU {
    public:
        MMU* _mmu;
        PPU(MMU* mmu);
        ~PPU();
        
    private: 
        SDL_Window* window;
        SDL_Renderer* renderer;

        std::bitset<8> LCDControl;
        std::bitset<8> LCDStatus;
        uint8_t backgroundPalette[4];
        uint8_t spritePaletteZero[4];
        uint8_t spritePaletteOne[4];

        // LCDC 
        bool enabledLCD;
        bool enabledWindow;
        bool enabledSprites;
        bool tileAddressingMode;
        bool enabledWindowBackground;
        uint8_t spriteHeight;
        uint16_t tilemapAreaWindow;
        uint16_t tilemapAreaBackground;
        
        void RenderSprites();
        void Update();
};