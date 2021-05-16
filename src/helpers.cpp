#include "helpers.h"

uint16_t FormWord(uint8_t high, uint8_t low) {
    uint16_t word = high << 8 | low & 0x00FF; 
    return word;
}
