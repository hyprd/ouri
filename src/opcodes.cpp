#include "opcodes.h"
#include "helpers.h"

void CPU::PopulateOpcodes() {
  Opcodes[0x00] = &CPU::Opcode0x00;
  Opcodes[0x01] = &CPU::Opcode0x01;
  Opcodes[0x02] = &CPU::Opcode0x02;
  Opcodes[0x06] = &CPU::Opcode0x06;
  Opcodes[0x08] = &CPU::Opcode0x08;
  Opcodes[0x0A] = &CPU::Opcode0x0A;
  Opcodes[0x0E] = &CPU::Opcode0x0E;
  Opcodes[0x11] = &CPU::Opcode0x11;
  Opcodes[0x12] = &CPU::Opcode0x12;
  Opcodes[0x16] = &CPU::Opcode0x16;
  Opcodes[0x1A] = &CPU::Opcode0x1A;
  Opcodes[0x1E] = &CPU::Opcode0x1E;
  Opcodes[0x21] = &CPU::Opcode0x21;
  Opcodes[0x22] = &CPU::Opcode0x22;
  Opcodes[0x26] = &CPU::Opcode0x26;
  Opcodes[0x2A] = &CPU::Opcode0x2A;
  Opcodes[0x2E] = &CPU::Opcode0x2E;
  Opcodes[0x31] = &CPU::Opcode0x31;
  Opcodes[0x32] = &CPU::Opcode0x32;
  Opcodes[0x36] = &CPU::Opcode0x36;
  Opcodes[0x3A] = &CPU::Opcode0x3A;
  Opcodes[0x3E] = &CPU::Opcode0x3E;
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
  
  Opcodes[0xE0] = &CPU::Opcode0xE0;
  Opcodes[0xE2] = &CPU::Opcode0xE2;
  Opcodes[0xEA] = &CPU::Opcode0xEA;
  Opcodes[0xF0] = &CPU::Opcode0xF0;
  Opcodes[0xF2] = &CPU::Opcode0xF2;
  Opcodes[0xFA] = &CPU::Opcode0xFA;

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
  uint16_t Low = mmu->ReadMemory(SP);
  SP++;
  uint16_t High = mmu->ReadMemory(SP);
  SP++;
  return FormWord(High, Low);
}

void CPU::PUSH_STACK(Register &reg) {
  SP--;
  mmu->SetMemory(SP, *reg.high);
  SP -= 2;
  mmu->SetMemory(SP, *reg.low);
  SP -= 2;
}

void CPU::PUSH_STACK16(uint16_t value) {
  uint8_t upper = static_cast<uint8_t>(value & 0xFF00);
  uint8_t lower = static_cast<uint8_t>(value & 0x00FF);
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
  uint8_t evaluation = static_cast<uint8_t>(A + reg2);
  if(evaluation == 0) SetBit(F, FLAG_Z);
  ClearBit(F, FLAG_N);
  if((A & 0x0F) + (reg2 & 0x0F) > 0x0F) SetBit(F, FLAG_H);
  if(evaluation > 0xFF) SetBit(F, FLAG_C);
  A = evaluation;
}

void CPU::ADD_HL(uint16_t reg2) {
  ClearBit(F, FLAG_N);
  uint16_t evaluation = static_cast<uint16_t>((HL.GetRegister() + reg2) & 0x0FFF);
  (evaluation > 0x0FFF) ? SetBit(F, FLAG_H) : ClearBit(F, FLAG_H); 
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
  SP += imm;
}

void CPU::ADC(uint8_t reg2) {
  uint8_t carry = GetBit(F, FLAG_C);
  ClearBit(F, FLAG_N);
  uint8_t evaluation = static_cast<uint8_t>(A + reg2 + carry);
  evaluation == 0 ? SetBit(F, FLAG_Z) : ClearBit(F, FLAG_Z); 
  (A + reg2) & 0x0F + carry > 0x0F ? SetBit(F, FLAG_H) : ClearBit(F, FLAG_H);
  evaluation > 0xFF ? SetBit(F, FLAG_C) : ClearBit(F, FLAG_C);
  A = evaluation;
}

void CPU::SUB(uint8_t reg2) {
  uint8_t evaluation = static_cast<uint8_t>(A - reg2);
  if(evaluation == 0) SetBit(F, FLAG_Z);
  SetBit(F, FLAG_N);
  (A & 0x0F) > (reg2 & 0x0F) ? SetBit(F, FLAG_H) : ClearBit(F, FLAG_H);
  if(evaluation < 0x00) SetBit(F, FLAG_C);
  A = evaluation;
}

void CPU::SBC(uint8_t reg2) {
  uint8_t carry = GetBit(F, FLAG_C);
  uint8_t evaluation = static_cast<uint8_t>(A - (reg2 + carry));
  SetBit(F, FLAG_N);
  (reg2 & 0x0F + carry > A & 0x0F) ? SetBit(F, FLAG_H) : ClearBit(F, FLAG_H);
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
  uint8_t evaluation = static_cast<uint8_t>(A - reg);
  evaluation == 0 ? SetBit(F, FLAG_Z) : ClearBit(F, FLAG_Z);
  SetBit(F, FLAG_N);
  ((A - reg) & 0x0F < 0) ? SetBit(F, FLAG_H) : ClearBit(F, FLAG_H);
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
  uint8_t steps = mmu->ReadMemory(PC);
  PC++;
  PC += steps;
}

void CPU::JP() {
  uint8_t low = mmu->ReadMemory(PC);
  PC++;
  uint8_t high = mmu->ReadMemory(PC);
  PC = FormWord(high, low);
}

void CPU::RL(uint8_t &reg, bool isA = false) {
  uint8_t carry = GetBit(F, FLAG_C);
  reg << 1 | reg >> (-1 & 7);
  if(GetBit(reg, 7) != carry) ToggleBit(reg, 7);
  isA ? ClearBit(F, FLAG_Z) : SetBit(F, FLAG_Z);
  ClearBit(F, FLAG_N);
  ClearBit(F, FLAG_H);
  carry ? SetBit(F, FLAG_C) : ClearBit(F, FLAG_C);
}

void CPU::RLC(uint8_t &reg, bool isA = false) {
  RL(reg);
  uint8_t bit = GetBit(reg, 7);
  if(bit != GetBit(F, FLAG_C)) ToggleBit(F, FLAG_C);
  if(bit != GetBit(reg, 0)) ToggleBit(reg, 0);
  // set isA to true for opcode 0x07, false otherwise
  // RLC in 0x07 clears the zero flag, RLC in CB-prefixed instructions don't
  if(isA) ClearBit(F, FLAG_Z);
} 

void CPU::RR(uint8_t &reg, bool isA = false) {
  uint8_t carry = GetBit(F, FLAG_C);
  reg >> 1 | reg << (-1 & 7);
  if(GetBit(reg, 7) != carry) ToggleBit(reg, 7);
  isA ? ClearBit(F, FLAG_Z) : SetBit(F, FLAG_Z);
  ClearBit(F, FLAG_N);
  ClearBit(F, FLAG_H);
  carry ? SetBit(F, FLAG_C) : ClearBit(F, FLAG_C);
}

void CPU::RRC(uint8_t &reg, bool isA = false) {
  RR(reg);
  uint8_t bit = GetBit(reg, 7);
  if(bit != GetBit(F, FLAG_C)) ToggleBit(F, FLAG_C);
  if(bit != GetBit(reg, 0)) ToggleBit(reg, 0);
  if(isA) ClearBit(F, FLAG_Z);
} 

/* --------------------------------------------------------------------*/
/* ------------------------------ OPCODES -----------------------------*/
/* --------------------------------------------------------------------*/
void CPU::Opcode0x00() {
  std::cout << "NOP" << std::endl;
}

void CPU::Opcode0x01() {
    uint8_t High = mmu->ReadMemory(PC);
    PC++;
    uint8_t Low = mmu->ReadMemory(PC);
    PC++;
    BC.SetRegister(FormWord(High, Low));
}

void CPU::Opcode0x02() {
  LD(BC.GetRegister(), A);
}

void CPU::Opcode0x06() {
  LD(B, mmu -> ReadMemory(PC++));
}

void CPU::Opcode0x08() {
    uint8_t High = mmu->ReadMemory(PC);
    PC++;
    uint8_t Low = mmu->ReadMemory(PC);
    PC++;
    uint16_t Word = FormWord(High, Low);
    LD(mmu->ReadMemory(FormWord(High, Low)), SP);
}

void CPU::Opcode0x09() {
  ADD_HL(BC.GetRegister());
}

void CPU::Opcode0x11() {
    uint8_t High = mmu->ReadMemory(PC);
    PC++;
    uint8_t Low = mmu->ReadMemory(PC);
    PC++;
    DE.SetRegister(FormWord(High, Low));
}

void CPU::Opcode0x0A() {
  LD(A, BC.GetRegister());
}

void CPU::Opcode0x0E() {
  LD(C, mmu -> ReadMemory(PC++));
}

void CPU::Opcode0x12() {
  LD(DE.GetRegister(), A);
}

void CPU::Opcode0x16() {
  LD(D, mmu -> ReadMemory(PC++));
}

void CPU::Opcode0x19() {
  ADD_HL(DE.GetRegister());
}

void CPU::Opcode0x1A() {
  LD(A, DE.GetRegister());
}

void CPU::Opcode0x1E() {
  LD(E, mmu -> ReadMemory(PC++));
}

void CPU::Opcode0x21() {
    uint8_t High = mmu->ReadMemory(PC);
    PC++;
    uint8_t Low = mmu->ReadMemory(PC);
    PC++;
    HL.SetRegister(FormWord(High, Low));
}

void CPU::Opcode0x22() {
  LD(HL.GetRegister(), A);
  HL.SetRegister(HL.GetRegister() + 1);
}

void CPU::Opcode0x26() {
  LD(H, mmu -> ReadMemory(PC++));
}

void CPU::Opcode0x29() {
  ADD_HL(HL.GetRegister());
}

void CPU::Opcode0x2A() {
  LD(A, HL.GetRegister());
  HL.SetRegister(HL.GetRegister() + 1);
}

void CPU::Opcode0x2E() {
  LD(L, mmu -> ReadMemory(PC++));
}

void CPU::Opcode0x31() {
    uint8_t High = mmu->ReadMemory(PC);
    PC++;
    uint8_t Low = mmu->ReadMemory(PC);
    PC++;
    this->SP = FormWord(High, Low);
}

void CPU::Opcode0x32() {
  LD(HL.GetRegister(), A);
  HL.SetRegister(HL.GetRegister() - 1);
}

void CPU::Opcode0x36() {
  LD(HL.GetRegister(), mmu -> ReadMemory(PC++));
}

void CPU::Opcode0x39() {
  ADD_HL(SP);
}

void CPU::Opcode0x3A() {
  LD(A, HL.GetRegister());
  HL.SetRegister(HL.GetRegister() - 1);
}

void CPU::Opcode0x3E() {
  LD(A, mmu -> ReadMemory(PC++));
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
  /*halt*/ 
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
  //ADC A, B
}

void CPU::Opcode0x89() {
  //ADC 
}

void CPU::Opcode0x8A() {
  //ADC 
}

void CPU::Opcode0x8B() {
  //ADC 
}

void CPU::Opcode0x8C() {
  //ADC 
}

void CPU::Opcode0x8D() {
  //ADC 
}

void CPU::Opcode0x8E() {
  //ADC 
}

void CPU::Opcode0x8F() {
  //ADC 
}

void CPU::Opcode0xE0() {
  LD(mmu -> ReadMemory(PC++), A);
}

void CPU::Opcode0xE2() {
  LD(mmu -> ReadMemory(C), A);
}

void CPU::Opcode0xEA() {
  uint8_t High = mmu -> ReadMemory(PC);
  PC++;
  uint8_t Low = mmu -> ReadMemory(PC);
  PC++;
  LD(FormWord(High, Low), A);
}
void CPU::Opcode0xF0() {
  LD(A, mmu -> ReadMemory(PC++));
}
void CPU::Opcode0xF2() {
  LD(A, mmu -> ReadMemory(C));
}
void CPU::Opcode0xFA() {
  uint8_t High = mmu -> ReadMemory(PC);
  PC++;
  uint8_t Low = mmu -> ReadMemory(PC);
  PC++;
  LD(A, mmu -> ReadMemory(FormWord(High, Low)));
}