#include "definitions.h"
#include "mmu.h"
#pragma once

class PPU {
    public:
        MMU* _mmu;
        PPU(MMU* mmu);
        ~PPU();
        void Update();
        
    private: 
        SDL_Window* window;
        SDL_Renderer* renderer;
        SDL_Texture* texture;

        std::bitset<8> LCDControl;
        std::bitset<8> LCDStatus;
        uint8_t backgroundPalette[4];
        uint8_t spritePaletteZero[4];
        uint8_t spritePaletteOne[4];
        uint8_t currentScanline;
        uint8_t tileSize;

        uint16_t pixels[GB_WIDTH * GB_HEIGHT] = { 0x0000 };
        uint16_t colours[4] = { 0x0000 };

        // LCDC 
        bool enabledLCD;
        bool enabledWindow;
        bool enabledSprites;
        bool tileAddressingMode;
        bool enabledWindowBackground;
        uint8_t spriteHeight;
        uint16_t tilemapAreaWindow;
        uint16_t tilemapAreaBackground;
        
        void UpdateLCDC();
        void LoadPalettes();
        void UpdateRenderer();
        void RenderBackground();
        void IncrementScanline();
        uint8_t GetColour(int8_t colourValue, uint16_t palette);
};