#include "ppu.h"
#include "helpers.h"

PPU::PPU(MMU* mmu) {
    _mmu = mmu;
    LCDControl = _mmu->ReadMemory(0xFF40);
    LCDStatus = _mmu->ReadMemory(0xFF41);
    // SDL  
    window = SDL_CreateWindow("ouri", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 160, 144, 0);
    renderer = SDL_CreateRenderer(window, -1, 0); 
    texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB4444, SDL_TEXTUREACCESS_STREAMING, 160, 144);
    // LCDC
    enabledWindowBackground = false;    // LCDC.0
    enabledSprites = false;             // LCDC.1
    spriteHeight = 8;                   // LCDC.2
    tilemapAreaBackground = 0;          // LCDC.3
    tileAddressingMode = false;         // LCDC.4
    enabledWindow = false;              // LCDC.5
    tilemapAreaWindow = 0;              // LCDC.6
    enabledLCD = false;                 // LCDC.7
    currentScanline = 0;
    tileSize = 16;
}

PPU::~PPU() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
 }

void PPU::Update() {
    UpdateLCDC();
    LoadPalettes();
    UpdateRenderer();
    RenderBackground();
    IncrementScanline();
}

inline void PPU::IncrementScanline() {
    _mmu->SetMemory(0xFF44, _mmu->ReadMemory(0xFF44) + 1);
}

inline void PPU::UpdateRenderer() {
    SDL_UpdateTexture(texture, NULL, pixels, 2 * GB_WIDTH);
    SDL_RenderCopy(renderer, texture, NULL, NULL);
    SDL_RenderPresent(renderer);
}

inline void PPU::UpdateLCDC() {
    // LCDC functions
    LCDControl = _mmu->ReadMemory(0xFF40);
    enabledWindowBackground = LCDControl.test(0) ? true : false;
    enabledSprites = LCDControl.test(1) ? true : false;
    LCDControl.test(2) ? spriteHeight = 16 : spriteHeight = 8;
    tilemapAreaBackground = LCDControl.test(3) ? 0x9800 : 0x9C00;
    tileAddressingMode = LCDControl.test(4) ? true : false;
    enabledWindow = LCDControl.test(5) ? true : false;
    tilemapAreaWindow = LCDControl.test(6) ? 0x9800: 0x9C00;
    enabledLCD = LCDControl.test(7) ? true : false; 
}

inline void PPU::LoadPalettes() {
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
        // lowest 2 bits are ignored as index 0 is transparent
        spritePaletteZero[1] = FormByte(OBP0[2], OBP0[3]);
        spritePaletteZero[2] = FormByte(OBP0[4], OBP0[5]);
        spritePaletteZero[3] = FormByte(OBP0[6], OBP0[7]);
        
        spritePaletteOne[1] = FormByte(OBP1[2], OBP1[3]);
        spritePaletteOne[2] = FormByte(OBP1[4], OBP1[5]);
        spritePaletteOne[3] = FormByte(OBP1[6], OBP1[7]);
    }
}

uint8_t PPU::GetColour(int8_t colourValue, uint16_t palette) {
    // int8_t data = _mmu->ReadMemory(palette);
    // return ((data >> (colourValue * 2 + 1)) << 1 | (data >> (colourValue * 2))) & 0x01;
    uint8_t pal = _mmu->ReadMemory(palette);
    int upper = 0, lower = 0;
    // Bit 7 - 6 - Color for index 3
    // Bit 5 - 4 - Color for index 2
    // Bit 3 - 2 - Color for index 1
    // Bit 1 - 0 - Color for index 0
    switch(colourValue) {
        case 0: 
            upper = 1; 
            lower = 0;
            break;
        case 1: 
            upper = 3; 
            lower = 2;
            break;
        case 2: 
            upper = 5; 
            lower = 4;
            break;
        case 3: 
            upper = 7; 
            lower = 6;
            break;
    }
    // return colour from the palette
    // order -> [upper colour, lower colour]
    return ((pal >> upper) << 0x01 | (pal >> lower));
}

void PPU::RenderBackground() {
    const unsigned int offset = 128;
    currentScanline = _mmu->ReadMemory(0xFF44);
    uint8_t SCX = _mmu->ReadMemory(0xFF42);
    uint8_t SCY = _mmu->ReadMemory(0xFF42);
    // resolve which memory region to use based on addressing mode
    uint8_t tilemap = tileAddressingMode ? 0x9C00 : 0x9800;
    uint8_t memoryRegion = tileAddressingMode ? 0x8000 : 0x8800;
    for(int pixel = 0; pixel < GB_WIDTH; pixel++) {
        uint8_t x = pixel + SCX;
        uint8_t y = currentScanline + SCY;
        const uint8_t currentTileRow = (y / 8) * 32;
        const uint8_t currentTileCol = x / 8;
        if(!tileAddressingMode) {
           memoryRegion += _mmu->ReadMemory(tilemap + currentTileRow + currentTileCol) * tileSize;
        }
        else {
            memoryRegion += static_cast<int8_t>((_mmu->ReadMemory(tilemap + currentTileRow + currentTileCol) + offset) * tileSize);
        }     
        uint16_t addr = (y % 8) * 2;
        uint8_t upper = _mmu->ReadMemory(memoryRegion + addr);
        uint8_t lower = _mmu->ReadMemory(memoryRegion + addr + 1);
        int8_t colourBit = ~((x % 8) - 7);
        int8_t colourValue = (lower >> colourBit) << 0x01 | (upper >> colourBit) & 0x01;
        uint8_t colour = GetColour(colourValue, 0xFF47);
        pixels[x + (currentScanline * GB_WIDTH)] = colour;  
    }
}