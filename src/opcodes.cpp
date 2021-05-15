#include "opcodes.h"

#include "helpers.h"

void CPU::PopulateOpcodes() {
  std::cout << "[INFO] Populating opcodes..." << std::endl;
  Opcodes[0x00] = &CPU::Opcode0x00;
  Opcodes[0x01] = &CPU::Opcode0x01;
  Opcodes[0x02] = &CPU::Opcode0x02;
  Opcodes[0x03] = &CPU::Opcode0x03;
  Opcodes[0x04] = &CPU::Opcode0x04;
  Opcodes[0x05] = &CPU::Opcode0x05;
  Opcodes[0x06] = &CPU::Opcode0x06;
  Opcodes[0x07] = &CPU::Opcode0x07;
  Opcodes[0x08] = &CPU::Opcode0x08;
  Opcodes[0x09] = &CPU::Opcode0x09;
  Opcodes[0x0A] = &CPU::Opcode0x0A;
  Opcodes[0x0B] = &CPU::Opcode0x0B;
  Opcodes[0x0C] = &CPU::Opcode0x0C;
  Opcodes[0x0D] = &CPU::Opcode0x0D;
  Opcodes[0x0E] = &CPU::Opcode0x0E;
  Opcodes[0x0F] = &CPU::Opcode0x0F;
  Opcodes[0x10] = &CPU::Opcode0x10;
  Opcodes[0x11] = &CPU::Opcode0x11;
  Opcodes[0x12] = &CPU::Opcode0x12;
  Opcodes[0x13] = &CPU::Opcode0x13;
  Opcodes[0x14] = &CPU::Opcode0x14;
  Opcodes[0x15] = &CPU::Opcode0x15;
  Opcodes[0x16] = &CPU::Opcode0x16;
  Opcodes[0x17] = &CPU::Opcode0x17;
  Opcodes[0x18] = &CPU::Opcode0x18;
  Opcodes[0x19] = &CPU::Opcode0x19;
  Opcodes[0x1A] = &CPU::Opcode0x1A;
  Opcodes[0x1B] = &CPU::Opcode0x1B;
  Opcodes[0x1C] = &CPU::Opcode0x1C;
  Opcodes[0x1D] = &CPU::Opcode0x1D;
  Opcodes[0x1E] = &CPU::Opcode0x1E;
  Opcodes[0x1F] = &CPU::Opcode0x1F;
  Opcodes[0x20] = &CPU::Opcode0x20;
  Opcodes[0x21] = &CPU::Opcode0x21;
  Opcodes[0x22] = &CPU::Opcode0x22;
  Opcodes[0x23] = &CPU::Opcode0x23;
  Opcodes[0x24] = &CPU::Opcode0x24;
  Opcodes[0x25] = &CPU::Opcode0x25;
  Opcodes[0x26] = &CPU::Opcode0x26;
  Opcodes[0x27] = &CPU::Opcode0x27;
  Opcodes[0x28] = &CPU::Opcode0x28;
  Opcodes[0x29] = &CPU::Opcode0x29;
  Opcodes[0x2A] = &CPU::Opcode0x2A;
  Opcodes[0x2B] = &CPU::Opcode0x2B;
  Opcodes[0x2C] = &CPU::Opcode0x2C;
  Opcodes[0x2D] = &CPU::Opcode0x2D;
  Opcodes[0x2E] = &CPU::Opcode0x2E;
  Opcodes[0x2F] = &CPU::Opcode0x2F;
  Opcodes[0x30] = &CPU::Opcode0x30;
  Opcodes[0x31] = &CPU::Opcode0x31;
  Opcodes[0x32] = &CPU::Opcode0x32;
  Opcodes[0x33] = &CPU::Opcode0x33;
  Opcodes[0x34] = &CPU::Opcode0x34;
  Opcodes[0x35] = &CPU::Opcode0x35;
  Opcodes[0x36] = &CPU::Opcode0x36;
  Opcodes[0x37] = &CPU::Opcode0x37;
  Opcodes[0x38] = &CPU::Opcode0x38;
  Opcodes[0x39] = &CPU::Opcode0x39;
  Opcodes[0x3A] = &CPU::Opcode0x3A;
  Opcodes[0x3B] = &CPU::Opcode0x3B;
  Opcodes[0x3C] = &CPU::Opcode0x3C;
  Opcodes[0x3D] = &CPU::Opcode0x3D;
  Opcodes[0x3E] = &CPU::Opcode0x3E;
  Opcodes[0x3F] = &CPU::Opcode0x3F;
  Opcodes[0x40] = &CPU::Opcode0x40;
  Opcodes[0x41] = &CPU::Opcode0x41;
  Opcodes[0x42] = &CPU::Opcode0x42;
  Opcodes[0x43] = &CPU::Opcode0x43;
  Opcodes[0x44] = &CPU::Opcode0x44;
  Opcodes[0x45] = &CPU::Opcode0x45;
  Opcodes[0x46] = &CPU::Opcode0x46;
  Opcodes[0x47] = &CPU::Opcode0x47;
  Opcodes[0x48] = &CPU::Opcode0x48;
  Opcodes[0x49] = &CPU::Opcode0x49;
  Opcodes[0x4A] = &CPU::Opcode0x4A;
  Opcodes[0x4B] = &CPU::Opcode0x4B;
  Opcodes[0x4C] = &CPU::Opcode0x4C;
  Opcodes[0x4D] = &CPU::Opcode0x4D;
  Opcodes[0x4E] = &CPU::Opcode0x4E;
  Opcodes[0x4F] = &CPU::Opcode0x4F;
  Opcodes[0x50] = &CPU::Opcode0x50;
  Opcodes[0x51] = &CPU::Opcode0x51;
  Opcodes[0x52] = &CPU::Opcode0x52;
  Opcodes[0x53] = &CPU::Opcode0x53;
  Opcodes[0x54] = &CPU::Opcode0x54;
  Opcodes[0x55] = &CPU::Opcode0x55;
  Opcodes[0x56] = &CPU::Opcode0x56;
  Opcodes[0x57] = &CPU::Opcode0x57;
  Opcodes[0x58] = &CPU::Opcode0x58;
  Opcodes[0x59] = &CPU::Opcode0x59;
  Opcodes[0x5A] = &CPU::Opcode0x5A;
  Opcodes[0x5B] = &CPU::Opcode0x5B;
  Opcodes[0x5C] = &CPU::Opcode0x5C;
  Opcodes[0x5D] = &CPU::Opcode0x5D;
  Opcodes[0x5E] = &CPU::Opcode0x5E;
  Opcodes[0x5F] = &CPU::Opcode0x5F;
  Opcodes[0x60] = &CPU::Opcode0x60;
  Opcodes[0x61] = &CPU::Opcode0x61;
  Opcodes[0x62] = &CPU::Opcode0x62;
  Opcodes[0x63] = &CPU::Opcode0x63;
  Opcodes[0x64] = &CPU::Opcode0x64;
  Opcodes[0x65] = &CPU::Opcode0x65;
  Opcodes[0x66] = &CPU::Opcode0x66;
  Opcodes[0x67] = &CPU::Opcode0x67;
  Opcodes[0x68] = &CPU::Opcode0x68;
  Opcodes[0x69] = &CPU::Opcode0x69;
  Opcodes[0x6A] = &CPU::Opcode0x6A;
  Opcodes[0x6B] = &CPU::Opcode0x6B;
  Opcodes[0x6C] = &CPU::Opcode0x6C;
  Opcodes[0x6D] = &CPU::Opcode0x6D;
  Opcodes[0x6E] = &CPU::Opcode0x6E;
  Opcodes[0x6F] = &CPU::Opcode0x6F;
  Opcodes[0x70] = &CPU::Opcode0x70;
  Opcodes[0x71] = &CPU::Opcode0x71;
  Opcodes[0x72] = &CPU::Opcode0x72;
  Opcodes[0x73] = &CPU::Opcode0x73;
  Opcodes[0x74] = &CPU::Opcode0x74;
  Opcodes[0x75] = &CPU::Opcode0x75;
  Opcodes[0x76] = &CPU::Opcode0x76;
  Opcodes[0x77] = &CPU::Opcode0x77;
  Opcodes[0x78] = &CPU::Opcode0x78;
  Opcodes[0x79] = &CPU::Opcode0x79;
  Opcodes[0x7A] = &CPU::Opcode0x7A;
  Opcodes[0x7B] = &CPU::Opcode0x7B;
  Opcodes[0x7C] = &CPU::Opcode0x7C;
  Opcodes[0x7D] = &CPU::Opcode0x7D;
  Opcodes[0x7E] = &CPU::Opcode0x7E;
  Opcodes[0x7F] = &CPU::Opcode0x7F;
  Opcodes[0x80] = &CPU::Opcode0x80;
  Opcodes[0x81] = &CPU::Opcode0x81;
  Opcodes[0x82] = &CPU::Opcode0x82;
  Opcodes[0x83] = &CPU::Opcode0x83;
  Opcodes[0x84] = &CPU::Opcode0x84;
  Opcodes[0x85] = &CPU::Opcode0x85;
  Opcodes[0x86] = &CPU::Opcode0x86;
  Opcodes[0x87] = &CPU::Opcode0x87;
  Opcodes[0x88] = &CPU::Opcode0x88;
  Opcodes[0x89] = &CPU::Opcode0x89;
  Opcodes[0x8A] = &CPU::Opcode0x8A;
  Opcodes[0x8B] = &CPU::Opcode0x8B;
  Opcodes[0x8C] = &CPU::Opcode0x8C;
  Opcodes[0x8D] = &CPU::Opcode0x8D;
  Opcodes[0x8E] = &CPU::Opcode0x8E;
  Opcodes[0x8F] = &CPU::Opcode0x8F;
  Opcodes[0x90] = &CPU::Opcode0x90;
  Opcodes[0x91] = &CPU::Opcode0x91;
  Opcodes[0x92] = &CPU::Opcode0x92;
  Opcodes[0x93] = &CPU::Opcode0x93;
  Opcodes[0x94] = &CPU::Opcode0x94;
  Opcodes[0x95] = &CPU::Opcode0x95;
  Opcodes[0x96] = &CPU::Opcode0x96;
  Opcodes[0x97] = &CPU::Opcode0x97;
  Opcodes[0x98] = &CPU::Opcode0x98;
  Opcodes[0x99] = &CPU::Opcode0x99;
  Opcodes[0x9A] = &CPU::Opcode0x9A;
  Opcodes[0x9B] = &CPU::Opcode0x9B;
  Opcodes[0x9C] = &CPU::Opcode0x9C;
  Opcodes[0x9D] = &CPU::Opcode0x9D;
  Opcodes[0x9E] = &CPU::Opcode0x9E;
  Opcodes[0x9F] = &CPU::Opcode0x9F;
  Opcodes[0xA0] = &CPU::Opcode0xA0;
  Opcodes[0xA1] = &CPU::Opcode0xA1;
  Opcodes[0xA2] = &CPU::Opcode0xA2;
  Opcodes[0xA3] = &CPU::Opcode0xA3;
  Opcodes[0xA4] = &CPU::Opcode0xA4;
  Opcodes[0xA5] = &CPU::Opcode0xA5;
  Opcodes[0xA6] = &CPU::Opcode0xA6;
  Opcodes[0xA7] = &CPU::Opcode0xA7;
  Opcodes[0xA8] = &CPU::Opcode0xA8;
  Opcodes[0xA9] = &CPU::Opcode0xA9;
  Opcodes[0xAA] = &CPU::Opcode0xAA;
  Opcodes[0xAB] = &CPU::Opcode0xAB;
  Opcodes[0xAC] = &CPU::Opcode0xAC;
  Opcodes[0xAD] = &CPU::Opcode0xAD;
  Opcodes[0xAE] = &CPU::Opcode0xAE;
  Opcodes[0xAF] = &CPU::Opcode0xAF;
  Opcodes[0xB0] = &CPU::Opcode0xB0;
  Opcodes[0xB1] = &CPU::Opcode0xB1;
  Opcodes[0xB2] = &CPU::Opcode0xB2;
  Opcodes[0xB3] = &CPU::Opcode0xB3;
  Opcodes[0xB4] = &CPU::Opcode0xB4;
  Opcodes[0xB5] = &CPU::Opcode0xB5;
  Opcodes[0xB6] = &CPU::Opcode0xB6;
  Opcodes[0xB7] = &CPU::Opcode0xB7;
  Opcodes[0xB8] = &CPU::Opcode0xB8;
  Opcodes[0xB9] = &CPU::Opcode0xB9;
  Opcodes[0xBA] = &CPU::Opcode0xBA;
  Opcodes[0xBB] = &CPU::Opcode0xBB;
  Opcodes[0xBC] = &CPU::Opcode0xBC;
  Opcodes[0xBD] = &CPU::Opcode0xBD;
  Opcodes[0xBE] = &CPU::Opcode0xBE;
  Opcodes[0xBF] = &CPU::Opcode0xBF;
  Opcodes[0xC0] = &CPU::Opcode0xC0;
  Opcodes[0xC1] = &CPU::Opcode0xC1;
  Opcodes[0xC2] = &CPU::Opcode0xC2;
  Opcodes[0xC3] = &CPU::Opcode0xC3;
  Opcodes[0xC4] = &CPU::Opcode0xC4;
  Opcodes[0xC5] = &CPU::Opcode0xC5;
  Opcodes[0xC6] = &CPU::Opcode0xC6;
  Opcodes[0xC7] = &CPU::Opcode0xC7;
  Opcodes[0xC8] = &CPU::Opcode0xC8;
  Opcodes[0xC9] = &CPU::Opcode0xC9;
  Opcodes[0xCA] = &CPU::Opcode0xCA;
  Opcodes[0xCB] = &CPU::Opcode0xCB;
  Opcodes[0xCC] = &CPU::Opcode0xCC;
  Opcodes[0xCD] = &CPU::Opcode0xCD;
  Opcodes[0xCE] = &CPU::Opcode0xCE;
  Opcodes[0xCF] = &CPU::Opcode0xCF;
  Opcodes[0xD0] = &CPU::Opcode0xD0;
  Opcodes[0xD1] = &CPU::Opcode0xD1;
  Opcodes[0xD2] = &CPU::Opcode0xD2;
  Opcodes[0xD3] = &CPU::Opcode0xD3;
  Opcodes[0xD4] = &CPU::Opcode0xD4;
  Opcodes[0xD5] = &CPU::Opcode0xD5;
  Opcodes[0xD6] = &CPU::Opcode0xD6;
  Opcodes[0xD7] = &CPU::Opcode0xD7;
  Opcodes[0xD8] = &CPU::Opcode0xD8;
  Opcodes[0xD9] = &CPU::Opcode0xD9;
  Opcodes[0xDA] = &CPU::Opcode0xDA;
  Opcodes[0xDB] = &CPU::Opcode0xDB;
  Opcodes[0xDC] = &CPU::Opcode0xDC;
  Opcodes[0xDD] = &CPU::Opcode0xDD;
  Opcodes[0xDE] = &CPU::Opcode0xDE;
  Opcodes[0xDF] = &CPU::Opcode0xDF;
  Opcodes[0xE0] = &CPU::Opcode0xE0;
  Opcodes[0xE1] = &CPU::Opcode0xE1;
  Opcodes[0xE2] = &CPU::Opcode0xE2;
  Opcodes[0xE3] = &CPU::Opcode0xE3;
  Opcodes[0xE4] = &CPU::Opcode0xE4;
  Opcodes[0xE5] = &CPU::Opcode0xE5;
  Opcodes[0xE6] = &CPU::Opcode0xE6;
  Opcodes[0xE7] = &CPU::Opcode0xE7;
  Opcodes[0xE8] = &CPU::Opcode0xE8;
  Opcodes[0xE9] = &CPU::Opcode0xE9;
  Opcodes[0xEA] = &CPU::Opcode0xEA;
  Opcodes[0xEB] = &CPU::Opcode0xEB;
  Opcodes[0xEC] = &CPU::Opcode0xEC;
  Opcodes[0xED] = &CPU::Opcode0xED;
  Opcodes[0xEE] = &CPU::Opcode0xEE;
  Opcodes[0xEF] = &CPU::Opcode0xEF;
  Opcodes[0xF0] = &CPU::Opcode0xF0;
  Opcodes[0xF1] = &CPU::Opcode0xF1;
  Opcodes[0xF2] = &CPU::Opcode0xF2;
  Opcodes[0xF3] = &CPU::Opcode0xF3;
  Opcodes[0xF4] = &CPU::Opcode0xF4;
  Opcodes[0xF5] = &CPU::Opcode0xF5;
  Opcodes[0xF6] = &CPU::Opcode0xF6;
  Opcodes[0xF7] = &CPU::Opcode0xF7;
  Opcodes[0xF8] = &CPU::Opcode0xF8;
  Opcodes[0xF9] = &CPU::Opcode0xF9;
  Opcodes[0xFA] = &CPU::Opcode0xFA;
  Opcodes[0xFB] = &CPU::Opcode0xFB;
  Opcodes[0xFC] = &CPU::Opcode0xFC;
  Opcodes[0xFD] = &CPU::Opcode0xFD;
  Opcodes[0xFE] = &CPU::Opcode0xFE;
  Opcodes[0xFF] = &CPU::Opcode0xFF;
  std::cout << "[INFO] Done." << std::endl;
}

/* --------------------------------------------------------------------*/
/* ------------------------------   BITS  -----------------------------*/
/* --------------------------------------------------------------------*/
void CPU::SetBit(uint8_t &byte, uint8_t bit) {
  byte |= 1UL << bit;
}

void CPU::ClearBit(uint8_t &byte, uint8_t bit) {
  byte &= ~(1UL << bit);
}

void CPU::ToggleBit(uint8_t &byte, uint8_t bit) {
  byte ^= 1UL << bit;
}

uint8_t CPU::GetBit(uint8_t byte, uint8_t bit) {
  return !!(byte >> bit);
}

/* --------------------------------------------------------------------*/
/* ----------------------------  FUNCTIONS  ---------------------------*/
/* --------------------------------------------------------------------*/

uint16_t CPU::READ_STACK() {
  uint16_t low = mmu->ReadMemory(SP);
  SP++;
  uint16_t high = mmu->ReadMemory(SP);
  SP++;
  return FormWord(high, low);
}

void CPU::PUSH_STACK(Register &reg) {
  SP--;
  mmu->SetMemory(SP, * reg.high);
  SP -= 2;
  mmu->SetMemory(SP, * reg.low);
  SP -= 2;
}

void CPU::PUSH_STACK16(uint16_t value) {
  uint8_t upper = static_cast <uint8_t> (value & 0xFF00);
  uint8_t lower = static_cast <uint8_t> (value & 0x00FF);
  SP--;
  mmu->SetMemory(SP, upper);
  SP -= 2;
  mmu->SetMemory(SP, lower);
  SP -= 2;
}

void CPU::POP_STACK(Register &reg) {
  uint8_t low = mmu->ReadMemory(SP);
  SP++;
  reg.low = &low;
  uint8_t high = mmu->ReadMemory(SP);
  SP++;
  reg.high = &high;
}

void CPU::POP_STACK16() {
  uint8_t low = mmu->ReadMemory(SP);
  SP++;
  uint8_t high = mmu->ReadMemory(SP);
  SP++;
  PC = FormWord(high, low);
}

void CPU::LD(uint8_t &reg1, uint8_t reg2) {
  reg1 = reg2;
}

void CPU::LD(uint16_t address, uint8_t reg) {
  mmu->SetMemory(address, reg);
}

void CPU::LD(uint8_t &reg1, uint16_t address) {
  reg1 = mmu->ReadMemory(address);
}

void CPU::ADD(uint8_t reg2) {
  uint8_t evaluation = static_cast <uint8_t> (A + reg2);
  if (evaluation == 0) SetBit(F, FLAG_Z);
  ClearBit(F, FLAG_N);
  if ((A & 0x0F) + (reg2 & 0x0F) > 0x0F) SetBit(F, FLAG_H);
  if (evaluation > 0xFF) SetBit(F, FLAG_C);
  A = evaluation;
}

void CPU::ADD_HL(uint16_t reg2) {
  ClearBit(F, FLAG_N);
  uint16_t evaluation = static_cast <uint16_t> ((HL.GetRegister() + reg2) & 0x0FFF);
  (evaluation > 0x0FFF) ? SetBit(F, FLAG_H): ClearBit(F, FLAG_H);
  (HL.GetRegister() + reg2) > 0xFFFF ? SetBit(F, FLAG_C) : ClearBit(F, FLAG_C);
  HL.SetRegister(evaluation);
}

void CPU::ADD_SP() {
  int8_t imm = mmu->ReadMemory(PC);
  PC++;
  ClearBit(F, FLAG_Z);
  ClearBit(F, FLAG_N);
  ((SP & 0x0FFF) + imm) > 0x0FFF ? SetBit(F, FLAG_H) : ClearBit(F, FLAG_H);
  (SP + imm) > 0xFFFF ? SetBit(F, FLAG_C) : SetBit(F, FLAG_C);
  SP += static_cast <int16_t> (imm);
}

void CPU::ADC(uint8_t reg2) {
  uint8_t carry = GetBit(F, FLAG_C);
  ClearBit(F, FLAG_N);
  uint8_t evaluation = static_cast <uint8_t> (A + reg2 + carry);
  evaluation == 0 ? SetBit(F, FLAG_Z) : ClearBit(F, FLAG_Z);
  (A + reg2) & 0x0F + carry > 0x0F ? SetBit(F, FLAG_H) : ClearBit(F, FLAG_H);
  evaluation > 0xFF ? SetBit(F, FLAG_C) : ClearBit(F, FLAG_C);
  A = evaluation;
}

void CPU::SUB(uint8_t reg2) {
  uint8_t evaluation = static_cast <uint8_t> (A - reg2);
  if (evaluation == 0) SetBit(F, FLAG_Z);
  SetBit(F, FLAG_N);
  (A & 0x0F) > (reg2 &0x0F) ? SetBit(F, FLAG_H): ClearBit(F, FLAG_H);
  if (evaluation < 0x00) SetBit(F, FLAG_C);
  A = evaluation;
}

void CPU::SBC(uint8_t reg2) {
  uint8_t carry = GetBit(F, FLAG_C);
  uint8_t evaluation = static_cast <uint8_t> (A - (reg2 + carry));
  SetBit(F, FLAG_N);
  (reg2 & 0x0F + carry > A & 0x0F) ? SetBit(F, FLAG_H): ClearBit(F, FLAG_H);
  evaluation < 0 ? SetBit(F, FLAG_C) : ClearBit(F, FLAG_C);
  A = evaluation;
}

void CPU::AND(uint8_t reg2) {
  A &= reg2;
  A == 0 ? SetBit(F, FLAG_Z) : ClearBit(F, FLAG_Z);
  ClearBit(F, FLAG_N);
  SetBit(F, FLAG_H);
  ClearBit(F, FLAG_C);
}

void CPU::XOR(uint8_t reg2) {
  A ^= reg2;
  A == 0 ? SetBit(F, FLAG_Z) : ClearBit(F, FLAG_Z);
  ClearBit(F, FLAG_N);
  ClearBit(F, FLAG_H);
  ClearBit(F, FLAG_C);
}

void CPU::OR(uint8_t reg2) {
  A |= reg2;
  A == 0 ? SetBit(F, FLAG_Z) : ClearBit(F, FLAG_Z);
  ClearBit(F, FLAG_N);
  ClearBit(F, FLAG_H);
  ClearBit(F, FLAG_C);
}

void CPU::CP(uint8_t reg) {
  uint8_t evaluation = static_cast <uint8_t> (A - reg);
  evaluation == 0 ? SetBit(F, FLAG_Z) : ClearBit(F, FLAG_Z);
  SetBit(F, FLAG_N);
  ((A - reg) & 0x0F < 0) ? SetBit(F, FLAG_H): ClearBit(F, FLAG_H);
  A < reg ? SetBit(F, FLAG_C) : ClearBit(F, FLAG_C);
}

void CPU::INC(uint8_t &reg) {
  reg & 0xF == 0xF ? SetBit(F, FLAG_H) : ClearBit(F, FLAG_H);
  reg += 1;
  reg == 0 ? SetBit(F, FLAG_Z) : ClearBit(F, FLAG_Z);
  ClearBit(F, FLAG_N);
}

void CPU::INC(Register reg) {
  uint16_t address = reg.GetRegister();
  reg.SetRegister(address + 1);
}

void CPU::INC_SP() {
  SP += 1;
}

void CPU::DEC(uint8_t &reg) {
  reg & 0xF == 0 ? SetBit(F, FLAG_H) : ClearBit(F, FLAG_H);
  reg -= 1;
  reg == 0 ? SetBit(F, FLAG_Z) : ClearBit(F, FLAG_Z);
  ClearBit(F, FLAG_N);
}

void CPU::DEC(Register reg) {
  uint16_t address = reg.GetRegister();
  reg.SetRegister(address - 1);
}

void CPU::DEC_SP() {
  SP -= 1;
}

void CPU::RET() {
  PC = READ_STACK();
}

void CPU::RST(uint8_t byte) {
  PUSH_STACK16(PC);
  PC = RSTVectors[byte];
}

void CPU::CALL() {
  uint8_t high = mmu->ReadMemory(PC);
  PC++;
  uint8_t low = mmu->ReadMemory(PC);
  PC++;
  uint16_t imm = FormWord(high, low);
  PUSH_STACK16(PC);
  PC = imm;
}

void CPU::JR() {
  int8_t steps = static_cast<int8_t>(mmu->ReadMemory(PC));
  PC++;
  PC += steps;
}

void CPU::JP() {
  uint8_t low = mmu->ReadMemory(PC);
  PC++;
  uint8_t high = mmu->ReadMemory(PC);
  PC = FormWord(high, low);
}

void CPU::JP_HL() {
  PC = HL.GetRegister();
}

void CPU::RL(uint8_t &reg, bool isA = false) {
  uint8_t carry = GetBit(F, FLAG_C);
  reg << 1 | reg >> (-1 & 7);
  if (GetBit(reg, 7) != carry) ToggleBit(reg, 7);
  isA ? ClearBit(F, FLAG_Z) : SetBit(F, FLAG_Z);
  ClearBit(F, FLAG_N);
  ClearBit(F, FLAG_H);
  carry ? SetBit(F, FLAG_C) : ClearBit(F, FLAG_C);
}

void CPU::RLC(uint8_t &reg, bool isA = false) {
  uint8_t bit = GetBit(reg, 7);
  reg <<= 1;
  if(bit) {
    SetBit(F, FLAG_C);
    SetBit(reg, 0);
  } else {
    ClearBit(F, FLAG_C);
  }
  !isA ? SetBit(F, FLAG_Z) : ClearBit(F, FLAG_Z);
}

void CPU::RR(uint8_t &reg, bool isA = false) {
  uint8_t carry = GetBit(F, FLAG_C);
  reg >> 1 | reg << (-1 & 7);
  if (GetBit(reg, 7) != carry) ToggleBit(reg, 7);
  isA ? ClearBit(F, FLAG_Z) : SetBit(F, FLAG_Z);
  ClearBit(F, FLAG_N);
  ClearBit(F, FLAG_H);
  carry ? SetBit(F, FLAG_C) : ClearBit(F, FLAG_C);
}

void CPU::RRC(uint8_t &reg, bool isA = false) {
  RR(reg);
  uint8_t bit = GetBit(reg, 7);
  if (bit != GetBit(F, FLAG_C)) ToggleBit(F, FLAG_C);
  if (bit != GetBit(reg, 0)) ToggleBit(reg, 0);
  if (isA) ClearBit(F, FLAG_Z);
}

void CPU::SLA(uint8_t &reg) {
  uint8_t bit = GetBit(reg, 7);
  reg << 1;
  reg == 0 ? ClearBit(F, FLAG_Z) : SetBit(F, FLAG_Z);
  ClearBit(F, FLAG_N);
  ClearBit(F, FLAG_H);
  if (GetBit(F, FLAG_C) != bit) ToggleBit(F, FLAG_C);
  ClearBit(reg, 0);
}

void CPU::SRA(uint8_t &reg) {
  uint8_t bit = GetBit(reg, 0);
  reg >> 1;
  reg == 0 ? ClearBit(F, FLAG_Z) : SetBit(F, FLAG_Z);
  ClearBit(F, FLAG_N);
  ClearBit(F, FLAG_H);
  if (GetBit(F, FLAG_C) != bit) ToggleBit(F, FLAG_C);
}

void CPU::SRL(uint8_t &reg) {
  SRA(reg);
  ClearBit(reg, 7);
}

void CPU::SWAP(uint8_t &reg) {
  reg = (reg & 0x0F) << 4 | reg >> 4;
  reg == 0 ? SetBit(F, FLAG_Z) : ClearBit(F, FLAG_Z);
}

void CPU::BIT(uint8_t &reg, uint8_t bit) {
  GetBit(reg, bit) == 0 ? SetBit(F, FLAG_Z) : ClearBit(F, FLAG_Z);
  ClearBit(F, FLAG_N);
  SetBit(F, FLAG_H);
}

void CPU::RES(uint8_t &reg, uint8_t bit) {
  ClearBit(reg, bit);
}

void CPU::SET(uint8_t &reg, uint8_t bit) {
  SetBit(reg, bit);
}

void CPU::DI() {
  interruptsEnabled = false;
}

void CPU::EI() {
  interruptsEnabled = true;
}

void CPU::STOP() {
  stopped = true;
}

void CPU::HALT() {
  halted = true;
}

void CPU::SCF() {
  SetBit(F, FLAG_C);
}

void CPU::CPL() {
  A = ~A;
  SetBit(F, FLAG_N);
  SetBit(F, FLAG_H);
}

void CPU::CCF() {
  ToggleBit(F, FLAG_C);
}

void CPU::DAA() {
  uint8_t sub = GetBit(F, FLAG_N);
  uint8_t half = GetBit(F, FLAG_H);
  uint8_t carry = GetBit(F, FLAG_C);

  // adjust if carry occurred or result overflows uint8 after add
  if (!sub) {
    // 0x60 for full carry, 0x06 when half carry occurs
    if (carry || A > 0x99) {
      A += 0x60;
      SetBit(F, FLAG_C);
    }
    if (half || (A & 0x0F) > 0x09) {
      A += 0x06;
    }
    // adjust if carry occurred after sub
  } else {
    if (carry) {
      A -= 0x60;
    }
    if (half) {
      A -= 0x06;
    }
  }
  A == 0 ? SetBit(F, FLAG_Z) : ClearBit(F, FLAG_Z);
  ClearBit(F, FLAG_H);
}

/* --------------------------------------------------------------------*/
/* ------------------------------ OPCODES -----------------------------*/
/* --------------------------------------------------------------------*/
void CPU::Opcode0x00() {
  // NOP
}

void CPU::Opcode0x01() {
  uint8_t high = mmu->ReadMemory(PC);
  PC++;
  uint8_t low = mmu->ReadMemory(PC);
  PC++;
  BC.SetRegister(FormWord(high, low));
}

void CPU::Opcode0x02() {
  LD(BC.GetRegister(), A);
}

void CPU::Opcode0x03() {
  INC(BC);
}

void CPU::Opcode0x04() {
  INC(B);
}

void CPU::Opcode0x05() {
  DEC(B);
}

void CPU::Opcode0x06() {
  LD(B, mmu->ReadMemory(PC++));
}

void CPU::Opcode0x07() {
  RLC(A, true);
}

void CPU::Opcode0x08() {
  uint8_t high = mmu->ReadMemory(PC);
  PC++;
  uint8_t low = mmu->ReadMemory(PC);
  PC++;
  uint16_t Word = FormWord(high, low);
  LD(mmu->ReadMemory(FormWord(high, low)), SP);
}

void CPU::Opcode0x09() {
  ADD_HL(BC.GetRegister());
}

void CPU::Opcode0x0A() {
  LD(A, mmu->ReadMemory(BC.GetRegister()));
}

void CPU::Opcode0x0B() {
  DEC(BC);
}

void CPU::Opcode0x0C() {
  INC(C);
}

void CPU::Opcode0x0D() {
  DEC(C);
}

void CPU::Opcode0x0E() {
  LD(C, mmu->ReadMemory(PC));
  PC++;
}

void CPU::Opcode0x0F() {
  RRC(A, true);
}

void CPU::Opcode0x10() {
  STOP();
}

void CPU::Opcode0x11() {
  uint8_t high = mmu->ReadMemory(PC);
  PC++;
  uint8_t low = mmu->ReadMemory(PC);
  PC++;
  DE.SetRegister(FormWord(high, low));
}

void CPU::Opcode0x12() {
  LD(mmu->ReadMemory(DE.GetRegister()), A);
}

void CPU::Opcode0x13() {
  INC(DE);
}

void CPU::Opcode0x14() {
  INC(D);
}

void CPU::Opcode0x15() {
  DEC(D);
}

void CPU::Opcode0x16() {
  LD(D, mmu->ReadMemory(PC++));
}

void CPU::Opcode0x17() {
  RL(A, true);
}

void CPU::Opcode0x18() {
  JR();
}

void CPU::Opcode0x19() {
  ADD_HL(DE.GetRegister());
}

void CPU::Opcode0x1A() {
  LD(A, DE.GetRegister());
}

void CPU::Opcode0x1B() {
  DEC(DE);
}

void CPU::Opcode0x1C() {
  INC(E);
}

void CPU::Opcode0x1D() {
  DEC(E);
}

void CPU::Opcode0x1E() {
  LD(E, mmu->ReadMemory(PC));
  PC++;
}

void CPU::Opcode0x1F() {
  RR(A, true);
}

void CPU::Opcode0x20() {
  if (!GetBit(F, FLAG_Z)) {
    JR();
  } else {
    PC++;
  }
}

void CPU::Opcode0x21() {
  uint8_t high = mmu->ReadMemory(PC);
  PC++;
  uint8_t low = mmu->ReadMemory(PC);
  PC++;
  HL.SetRegister(FormWord(high, low));
}

void CPU::Opcode0x22() {
  LD(HL.GetRegister(), A);
  HL.SetRegister(HL.GetRegister() + 1);
}

void CPU::Opcode0x23() {
  INC(HL);
}

void CPU::Opcode0x24() {
  INC(H);
}

void CPU::Opcode0x25() {
  DEC(H);
}

void CPU::Opcode0x26() {
  LD(H, mmu->ReadMemory(PC));
  PC++;
}

void CPU::Opcode0x27() {
  DAA();
}

void CPU::Opcode0x28() {
  if (GetBit(F, FLAG_Z)) {
    JR();
  } else {
    PC++;
  }
}

void CPU::Opcode0x29() {
  ADD_HL(HL.GetRegister());
}

void CPU::Opcode0x2A() {
  LD(A, HL.GetRegister());
  HL.SetRegister(HL.GetRegister() + 1);
}

void CPU::Opcode0x2B() {
  DEC(HL);
}

void CPU::Opcode0x2C() {
  INC(L);
}

void CPU::Opcode0x2D() {
  DEC(L);
}

void CPU::Opcode0x2E() {
  LD(L, mmu->ReadMemory(PC++));
}

void CPU::Opcode0x2F() {
  CPL();
}

void CPU::Opcode0x30() {
  if (!GetBit(F, FLAG_C)) {
    JR();
  } else {
    PC++;
  }
}

void CPU::Opcode0x31() {
  uint8_t high = mmu->ReadMemory(PC);
  PC++;
  uint8_t low = mmu->ReadMemory(PC);
  PC++;
  this -> SP = FormWord(high, low);
}

void CPU::Opcode0x32() {
  LD(HL.GetRegister(), A);
  HL.SetRegister(HL.GetRegister() - 1);
}

void CPU::Opcode0x33() {
  INC_SP();
}

void CPU::Opcode0x34() {
  uint8_t reg = mmu->ReadMemory(HL.GetRegister());
  INC(reg);
}

void CPU::Opcode0x35() {
  uint8_t reg = mmu->ReadMemory(HL.GetRegister());
  DEC(reg);
}

void CPU::Opcode0x36() {
  LD(HL.GetRegister(), mmu->ReadMemory(PC++));
}

void CPU::Opcode0x37() {
  SCF();
}

void CPU::Opcode0x38() {
  if (GetBit(F, FLAG_C)) {
    JR();
  } else {
    PC++;
  }
}

void CPU::Opcode0x39() {
  ADD_HL(SP);
}

void CPU::Opcode0x3A() {
  LD(A, HL.GetRegister());
  HL.SetRegister(HL.GetRegister() - 1);
}

void CPU::Opcode0x3B() {
  DEC_SP();
}

void CPU::Opcode0x3C() {
  INC(A);
}

void CPU::Opcode0x3D() {
  DEC(A);
}

void CPU::Opcode0x3E() {
  LD(A, mmu->ReadMemory(PC++));
}

void CPU::Opcode0x3F() {
  CCF();
}

void CPU::Opcode0x40() {
  LD(B, B);
}

void CPU::Opcode0x41() {
  LD(B, C);
}

void CPU::Opcode0x42() {
  LD(B, D);
}

void CPU::Opcode0x43() {
  LD(B, E);
}

void CPU::Opcode0x44() {
  LD(B, H);
}

void CPU::Opcode0x45() {
  LD(B, L);
}

void CPU::Opcode0x46() {
  LD(B, HL.GetRegister());
}

void CPU::Opcode0x47() {
  LD(B, A);
}

void CPU::Opcode0x48() {
  LD(C, B);
}

void CPU::Opcode0x49() {
  LD(C, C);
}

void CPU::Opcode0x4A() {
  LD(C, D);
}

void CPU::Opcode0x4B() {
  LD(C, E);
}

void CPU::Opcode0x4C() {
  LD(C, H);
}

void CPU::Opcode0x4D() {
  LD(C, L);
}

void CPU::Opcode0x4E() {
  LD(E, HL.GetRegister());
}

void CPU::Opcode0x4F() {
  LD(C, A);
}

void CPU::Opcode0x50() {
  LD(D, B);
}

void CPU::Opcode0x51() {
  LD(D, C);
}

void CPU::Opcode0x52() {
  LD(D, D);
}

void CPU::Opcode0x53() {
  LD(D, E);
}

void CPU::Opcode0x54() {
  LD(D, H);
}

void CPU::Opcode0x55() {
  LD(D, L);
}

void CPU::Opcode0x56() {
  LD(D, HL.GetRegister());
}

void CPU::Opcode0x57() {
  LD(D, A);
}

void CPU::Opcode0x58() {
  LD(E, B);
}

void CPU::Opcode0x59() {
  LD(E, C);
}

void CPU::Opcode0x5A() {
  LD(E, D);
}

void CPU::Opcode0x5B() {
  LD(E, E);
}

void CPU::Opcode0x5C() {
  LD(E, H);
}

void CPU::Opcode0x5D() {
  LD(E, L);
}

void CPU::Opcode0x5E() {
  LD(E, HL.GetRegister());
}

void CPU::Opcode0x5F() {
  LD(E, A);
}

void CPU::Opcode0x60() {
  LD(H, B);
}

void CPU::Opcode0x61() {
  LD(H, C);
}

void CPU::Opcode0x62() {
  LD(H, D);
}

void CPU::Opcode0x63() {
  LD(H, E);
}

void CPU::Opcode0x64() {
  LD(H, H);
}

void CPU::Opcode0x65() {
  LD(H, L);
}

void CPU::Opcode0x66() {
  LD(H, HL.GetRegister());
}

void CPU::Opcode0x67() {
  LD(H, A);
}

void CPU::Opcode0x68() {
  LD(L, B);
}

void CPU::Opcode0x69() {
  LD(L, C);
}

void CPU::Opcode0x6A() {
  LD(L, D);
}

void CPU::Opcode0x6B() {
  LD(L, E);
}

void CPU::Opcode0x6C() {
  LD(L, H);
}

void CPU::Opcode0x6D() {
  LD(L, L);
}

void CPU::Opcode0x6E() {
  LD(L, HL.GetRegister());
}

void CPU::Opcode0x6F() {
  LD(L, A);
}

void CPU::Opcode0x70() {
  LD(HL.GetRegister(), B);
}

void CPU::Opcode0x71() {
  LD(HL.GetRegister(), C);
}

void CPU::Opcode0x72() {
  LD(HL.GetRegister(), D);
}

void CPU::Opcode0x73() {
  LD(HL.GetRegister(), E);
}

void CPU::Opcode0x74() {
  LD(HL.GetRegister(), H);
}

void CPU::Opcode0x75() {
  LD(HL.GetRegister(), L);
}

void CPU::Opcode0x76() {
  HALT();
}

void CPU::Opcode0x77() {
  LD(HL.GetRegister(), A);
}

void CPU::Opcode0x78() {
  LD(A, B);
}

void CPU::Opcode0x79() {
  LD(A, C);
}

void CPU::Opcode0x7A() {
  LD(A, D);
}

void CPU::Opcode0x7B() {
  LD(A, E);
}

void CPU::Opcode0x7C() {
  LD(A, H);
}

void CPU::Opcode0x7D() {
  LD(A, L);
}

void CPU::Opcode0x7E() {
  LD(A, HL.GetRegister());
}

void CPU::Opcode0x7F() {
  LD(A, A);
}

void CPU::Opcode0x80() {
  ADD(B);
}

void CPU::Opcode0x81() {
  ADD(C);
}

void CPU::Opcode0x82() {
  ADD(D);
}

void CPU::Opcode0x83() {
  ADD(E);
}

void CPU::Opcode0x84() {
  ADD(H);
}

void CPU::Opcode0x85() {
  ADD(L);
}

void CPU::Opcode0x86() {
  ADD(mmu->ReadMemory(PC));
  PC++;
}

void CPU::Opcode0x87() {
  ADD(A);
}

void CPU::Opcode0x88() {
  ADC(B);
}

void CPU::Opcode0x89() {
  ADC(C);
}

void CPU::Opcode0x8A() {
  ADC(D);
}

void CPU::Opcode0x8B() {
  ADC(E);
}

void CPU::Opcode0x8C() {
  ADC(H);
}

void CPU::Opcode0x8D() {
  ADC(L);
}

void CPU::Opcode0x8E() {
  ADC(mmu->ReadMemory(HL.GetRegister()));
}

void CPU::Opcode0x8F() {
  ADC(A);
}

void CPU::Opcode0x90() {
  SUB(B);
}
void CPU::Opcode0x91() {
  SUB(C);
}
void CPU::Opcode0x92() {
  SUB(D);
}
void CPU::Opcode0x93() {
  SUB(E);
}
void CPU::Opcode0x94() {
  SUB(H);
}
void CPU::Opcode0x95() {
  SUB(L);
}
void CPU::Opcode0x96() {
  SUB(mmu->ReadMemory(HL.GetRegister()));
}
void CPU::Opcode0x97() {
  SUB(A);
}
void CPU::Opcode0x98() {
  SBC(B);
}
void CPU::Opcode0x99() {
  SBC(C);
}
void CPU::Opcode0x9A() {
  SBC(D);
}
void CPU::Opcode0x9B() {
  SBC(E);
}
void CPU::Opcode0x9C() {
  SBC(H);
}
void CPU::Opcode0x9D() {
  SBC(L);
}
void CPU::Opcode0x9E() {
  SBC(mmu->ReadMemory(HL.GetRegister()));
}
void CPU::Opcode0x9F() {
  SBC(A);
}
void CPU::Opcode0xA0() {
  AND(B);
}
void CPU::Opcode0xA1() {
  AND(C);
}
void CPU::Opcode0xA2() {
  AND(D);
}
void CPU::Opcode0xA3() {
  AND(E);
}
void CPU::Opcode0xA4() {
  AND(H);
}
void CPU::Opcode0xA5() {
  AND(L);
}
void CPU::Opcode0xA6() {
  AND(mmu->ReadMemory(HL.GetRegister()));
}
void CPU::Opcode0xA7() {
  AND(A);
}
void CPU::Opcode0xA8() {
  XOR(B);
}
void CPU::Opcode0xA9() {
  XOR(C);
}
void CPU::Opcode0xAA() {
  XOR(D);
}
void CPU::Opcode0xAB() {
  XOR(E);
}
void CPU::Opcode0xAC() {
  XOR(H);
}
void CPU::Opcode0xAD() {
  XOR(L);
}
void CPU::Opcode0xAE() {
  XOR(mmu->ReadMemory(HL.GetRegister()));
}
void CPU::Opcode0xAF() {
  XOR(A);
}
void CPU::Opcode0xB0() {
  OR(B);
}
void CPU::Opcode0xB1() {
  OR(C);
}
void CPU::Opcode0xB2() {
  OR(D);
}
void CPU::Opcode0xB3() {
  OR(E);
}
void CPU::Opcode0xB4() {
  OR(H);
}
void CPU::Opcode0xB5() {
  OR(L);
}
void CPU::Opcode0xB6() {
  OR(mmu->ReadMemory(HL.GetRegister()));
}
void CPU::Opcode0xB7() {
  OR(A);
}
void CPU::Opcode0xB8() {
  CP(B);
}
void CPU::Opcode0xB9() {
  CP(C);
}
void CPU::Opcode0xBA() {
  CP(D);
}
void CPU::Opcode0xBB() {
  CP(E);
}
void CPU::Opcode0xBC() {
  CP(H);
}
void CPU::Opcode0xBD() {
  CP(L);
}
void CPU::Opcode0xBE() {
  CP(mmu->ReadMemory(HL.GetRegister()));
}
void CPU::Opcode0xBF() {
  CP(A);
}
void CPU::Opcode0xC0() {
  if (!GetBit(F, FLAG_Z)) {
    POP_STACK16();
  }
}
void CPU::Opcode0xC1() {
  POP_STACK(BC);
}
void CPU::Opcode0xC2() {
  if (!GetBit(F, FLAG_Z)) {
    JP();
  } else {
    PC++;
    PC++;
  }
}
void CPU::Opcode0xC3() {
  JP();
}
void CPU::Opcode0xC4() {
  if (!GetBit(F, FLAG_Z)) {
    CALL();
  } else {
    PC++;
    PC++;
  }
}
void CPU::Opcode0xC5() {
  PUSH_STACK(BC);
}
void CPU::Opcode0xC6() {
  ADD(mmu->ReadMemory(PC));
  PC++;
}
void CPU::Opcode0xC7() {
  RST(0);
}
void CPU::Opcode0xC8() {
  if (GetBit(F, FLAG_Z)) {
    RET();
  }
}
void CPU::Opcode0xC9() {
  RET();
}
void CPU::Opcode0xCA() {
  if (GetBit(F, FLAG_Z)) {
    JP();
  } else {
    PC++;
    PC++;
  }
}
void CPU::Opcode0xCB() { /* cb-prefix inst*/ }
void CPU::Opcode0xCC() {
  if (GetBit(F, FLAG_Z)) {
    CALL();
  } else {
    PC++;
    PC++;
  }
}
void CPU::Opcode0xCD() {
  CALL();
}
void CPU::Opcode0xCE() {
  ADC(mmu->ReadMemory(PC));
  PC++;
}
void CPU::Opcode0xCF() {
  RST(1);
}
void CPU::Opcode0xD0() {
  if (!GetBit(F, FLAG_C)) {
    RET();
  }
}
void CPU::Opcode0xD1() {
  POP_STACK(DE);
}
void CPU::Opcode0xD2() {
  if (!GetBit(F, FLAG_C)) {
    JP();
  } else {
    PC++;
    PC++;
  }
}
void CPU::Opcode0xD3() {}
void CPU::Opcode0xD4() {
  if (!GetBit(F, FLAG_C)) {
    CALL();
  } else {
    PC++;
    PC++;
  }
}
void CPU::Opcode0xD5() {
  POP_STACK(DE);
}
void CPU::Opcode0xD6() {
  SUB(mmu->ReadMemory(PC));
  PC++;
}
void CPU::Opcode0xD7() {
  RST(2);
}
void CPU::Opcode0xD8() {
  if (GetBit(F, FLAG_C)) {
    RET();
  }
}

void CPU::Opcode0xD9() {
  RET();
  interruptsEnabled = !interruptsEnabled;
}
void CPU::Opcode0xDA() {
  if (GetBit(F, FLAG_C)) {
    JP();
  } else {
    PC++;
    PC++;
  }
}
void CPU::Opcode0xDB() {}
void CPU::Opcode0xDC() {
  if (GetBit(F, FLAG_C)) {
    CALL();
  } else {
    PC++;
    PC++;
  }
}
void CPU::Opcode0xDD() {}
void CPU::Opcode0xDE() {
  SBC(mmu->ReadMemory(PC));
  PC++;
}
void CPU::Opcode0xDF() {
  RST(3);
}

void CPU::Opcode0xE0() {
  LD(static_cast <uint16_t> (0xFF00 + mmu->ReadMemory(PC)), A);
  PC++;
}
void CPU::Opcode0xE1() {
  POP_STACK(HL);
}
void CPU::Opcode0xE2() {
  LD(static_cast <uint16_t> (0xFF00 + C), A);
}
void CPU::Opcode0xE3() {}
void CPU::Opcode0xE4() {}
void CPU::Opcode0xE5() {
  PUSH_STACK(HL);
}
void CPU::Opcode0xE6() {
  AND(mmu->ReadMemory(PC));
  PC++;
}
void CPU::Opcode0xE7() {
  RST(4);
}
void CPU::Opcode0xE8() {
  ADD_SP();
}
void CPU::Opcode0xE9() {
  JP_HL();
}
void CPU::Opcode0xEA() {
  mmu->SetMemory(FormWord(mmu->ReadMemory(PC), mmu->ReadMemory(PC + 1)), A);
  PC += 2;
}
void CPU::Opcode0xEB() {}
void CPU::Opcode0xEC() {}
void CPU::Opcode0xED() {}
void CPU::Opcode0xEE() {
  XOR(mmu->ReadMemory(PC));
  PC++;
}
void CPU::Opcode0xEF() {
  RST(7);
}
void CPU::Opcode0xF0() {
  LD(A, static_cast <uint16_t> (0xFF00 + mmu->ReadMemory(PC)));
  PC++;
}
void CPU::Opcode0xF1() {
  POP_STACK(AF);
}
void CPU::Opcode0xF2() {
  LD(A, static_cast <uint16_t> (0xFF00 + C));
}
void CPU::Opcode0xF3() {
  interruptsEnabled = false;
}
void CPU::Opcode0xF4() {}
void CPU::Opcode0xF5() {
  PUSH_STACK(AF);
}
void CPU::Opcode0xF6() {
  OR(mmu->ReadMemory(PC));
  PC++;
}
void CPU::Opcode0xF7() {
  RST(6);
}
void CPU::Opcode0xF8() {
  int16_t data = SP + mmu->ReadMemory(PC);;
  ClearBit(F, FLAG_Z);
  ClearBit(F, FLAG_N);
  data > 0x0FFF ? SetBit(F, FLAG_H) : ClearBit(F, FLAG_H);
  data > 0xFFFF ? SetBit(F, FLAG_C) : ClearBit(F, FLAG_C);
  HL.SetRegister(data);
  PC++;
}
void CPU::Opcode0xF9() {
  SP = HL.GetRegister();
}
void CPU::Opcode0xFA() {
  LD(A, FormWord(mmu->ReadMemory(PC), mmu->ReadMemory(PC + 1)));
  PC += 2;
}
void CPU::Opcode0xFB() {
  interruptsEnabled = true;
}
void CPU::Opcode0xFC() {}
void CPU::Opcode0xFD() {}
void CPU::Opcode0xFE() {
  CP(mmu->ReadMemory(PC));
  PC++;
}
void CPU::Opcode0xFF() {
  RST(7);
}