#include "ppu.h"
#include "helpers.h"

PPU::PPU(MMU* mmu) {
    _mmu = mmu;
    LCDControl = _mmu->ReadMemory(0xFF40);
    LCDStatus = _mmu->ReadMemory(0xFF41);
    // SDL  
    window = SDL_CreateWindow("ouri", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 160, 144, 0);
    renderer = SDL_CreateRenderer(window, -1, 0); 
    // LCDC
    enabledWindowBackground = false;    // LCDC.0
    enabledSprites = false;             // LCDC.1
    spriteHeight = 8;                   // LCDC.2
    tilemapAreaBackground = 0;          // LCDC.3
    tileAddressingMode = false;         // LCDC.4
    enabledWindow = false;              // LCDC.5
    tilemapAreaWindow = 0;              // LCDC.6
    enabledLCD = false;                 // LCDC.7
}

PPU::~PPU() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
 }

void PPU::Update() {
    // LCDC functions
    LCDControl = _mmu->ReadMemory(0xFF40);
    // Test addressing mode + tilemap areas
    tileAddressingMode = LCDControl.test(4) ? true : false;
    tilemapAreaBackground = LCDControl.test(3) ? 0x9800 : 0x9C00;
    tilemapAreaWindow = LCDControl.test(6) ? 0x9800: 0x9C00;
    LCDControl.test(2) ? spriteHeight = 16 : spriteHeight = 8;
    // Test enables
    enabledWindowBackground = LCDControl.test(0) ? true : false;
    enabledSprites = LCDControl.test(1) ? true : false;
    enabledWindow = LCDControl.test(5) ? true : false;
    enabledLCD = LCDControl.test(7) ? true : false; 
    if(enabledWindowBackground) {
        std::bitset<8> BGP = _mmu->ReadMemory(0xFF47);
        backgroundPalette[0] = FormByte(BGP[0], BGP[1]);
        backgroundPalette[1] = FormByte(BGP[2], BGP[3]);
        backgroundPalette[2] = FormByte(BGP[4], BGP[5]);
        backgroundPalette[3] = FormByte(BGP[6], BGP[7]);
    } 
    if(enabledSprites) {
        std::bitset<8> OBP0 = _mmu->ReadMemory(0xFF48);
        std::bitset<8> OBP1 = _mmu->ReadMemory(0xFF49);
        // lowest 2 bits are ignored as index 00 means transparent
        spritePaletteZero[1] = FormByte(OBP0[2], OBP0[3]);
        spritePaletteZero[2] = FormByte(OBP0[4], OBP0[5]);
        spritePaletteZero[3] = FormByte(OBP0[6], OBP0[7]);
    
        spritePaletteOne[1] = FormByte(OBP1[2], OBP1[3]);
        spritePaletteOne[2] = FormByte(OBP1[4], OBP1[5]);
        spritePaletteOne[3] = FormByte(OBP1[6], OBP1[7]);
    }
}

void PPU::RenderSprites() {
    LCDControl = _mmu->ReadMemory(0xFF40);
    /* 
     * PPU can display up to 40 sprites (10 per scanline).
     * Sprites are in the same format as BG tiles however
     * they are sourced from the sprite tiles table at 0x8000 - 0x8FFF.
     * 
     * OAM resides at 0xFE00 - 0xFE9F.
     *   Byte 0 = Y
     *   Byte 1 = X
     *   Byte 2 = Tile index
     *   Byte 3 = Attrs/flags
     * 
     * Y byte offsets 16 (since sprite height can be 16px)
     * X byte offsets 8 (for the sprite width)
     */

}


