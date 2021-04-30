#include "helpers.h"

uint16_t FormWord(uint8_t high, uint8_t low) {
    return (high << 8) | (low & 0x00FF);
}