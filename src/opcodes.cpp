#include "opcodes.h"
#include "helpers.h"

/* --------------------------------------------------------------------*/
/* ----------------------------  INTERRUPTS  --------------------------*/
/* --------------------------------------------------------------------*/

void CPU::HandleInterrupts() {
  if(IME) {
    interruptEnables = std::bitset<8>(mmu->ReadMemory(0xFFFF));
    interruptFlags = std::bitset<8>(mmu->ReadMemory(0xFF0F));
    if(interruptFlags.any()) {
      for (int i = 0; i < 5; i++) {
        // If interrupts are enabled for the bit and the request was made
        if(interruptEnables.test(i) && interruptFlags.test(i)) {
          ExecuteInterrupt(i);
        }
      }
    }
  }
}

void CPU::SetInterrupt(uint8_t interrupt) {
  interruptFlags.set(interrupt);
  mmu->SetMemory(0xFF0F, static_cast<uint8_t>(interruptFlags.to_ulong()));
  halted = false;
}

void CPU::ExecuteInterrupt(uint8_t interrupt) {
  // Acknowledge by resetting the interrupt request bit + IME
  interruptFlags.reset(interrupt);
  IME = false;
  // Call the interrupt vector 
  mmu->SetMemory(0xFF0F, static_cast<uint8_t>(interruptFlags.to_ulong()));
  PUSH_STACK16(PC);
  // Bit 0: VBlank    0x40
  // Bit 1: LCD STAT  0x48
  // Bit 2: Timer     0x50
  // Bit 3: Serial    0x58 
  // Bit 4: Joypad    0x60
  PC = InterruptVectors[interrupt];
}

/* --------------------------------------------------------------------*/
/* ------------------------------   BITS  -----------------------------*/
/* --------------------------------------------------------------------*/
void CPU::SetBit(uint8_t & byte, uint8_t bit) {
  byte |= 1UL << bit;
}

void CPU::ClearBit(uint8_t & byte, uint8_t bit) {
  byte &= ~(1UL << bit);
}

void CPU::ToggleBit(uint8_t & byte, uint8_t bit) {
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

void CPU::PUSH_STACK(Register & reg) {
  SP--;
  mmu->SetMemory(SP, * reg.high);
  SP -= 2;
  mmu->SetMemory(SP, * reg.low);
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

void CPU::POP_STACK(Register & reg) {
  uint8_t low = mmu->ReadMemory(SP);
  SP++;
  reg.low = & low;
  uint8_t high = mmu->ReadMemory(SP);
  SP++;
  reg.high = & high;
}

void CPU::POP_STACK16() {
  uint8_t low = mmu->ReadMemory(SP);
  SP++;
  uint8_t high = mmu->ReadMemory(SP);
  SP++;
  PC = FormWord(high, low);
}

void CPU::LD(uint8_t & reg1, uint8_t reg2) {
  reg1 = reg2;
}

void CPU::LD(uint16_t address, uint8_t reg) {
  mmu->SetMemory(address, reg);
}

void CPU::LD(uint8_t & reg1, uint16_t address) {
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
  SP += static_cast < int16_t > (imm);
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
  (A & 0x0F) > (reg2 & 0x0F) ? SetBit(F, FLAG_H): ClearBit(F, FLAG_H);
  if(evaluation < 0x00) SetBit(F, FLAG_C);
  A = evaluation;
}

void CPU::SBC(uint8_t reg2) {
  uint8_t carry = GetBit(F, FLAG_C);
  uint8_t evaluation = static_cast<uint8_t>(A - (reg2 + carry));
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
  uint8_t evaluation = static_cast<uint8_t>(A - reg);
  evaluation == 0 ? SetBit(F, FLAG_Z) : ClearBit(F, FLAG_Z);
  SetBit(F, FLAG_N);
  ((A - reg) & 0x0F < 0) ? SetBit(F, FLAG_H): ClearBit(F, FLAG_H);
  A < reg ? SetBit(F, FLAG_C) : ClearBit(F, FLAG_C);
}

void CPU::INC(uint8_t & reg) {
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

void CPU::DEC(uint8_t & reg) {
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
  PC = PC + 1 + (static_cast < int8_t > (mmu->ReadMemory(PC + 1)));
}

void CPU::JP() {
  uint16_t low = mmu->ReadMemory(PC + 1);
  PC++;
  uint16_t high = mmu->ReadMemory(PC + 1) << 8;
  PC = (low | high) - 1;
}

void CPU::JP_HL() {
  PC = HL.GetRegister();
}

void CPU::RL(uint8_t & reg, bool isA = false) {
  uint8_t carry = GetBit(F, FLAG_C);
  reg << 1 | reg >> (-1 & 7);
  if(GetBit(reg, 7) != carry) ToggleBit(reg, 7);
  isA ? ClearBit(F, FLAG_Z) : SetBit(F, FLAG_Z);
  ClearBit(F, FLAG_N);
  ClearBit(F, FLAG_H);
  carry ? SetBit(F, FLAG_C) : ClearBit(F, FLAG_C);
}

void CPU::RLC(uint8_t & reg, bool isA = false) {
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

void CPU::RR(uint8_t & reg, bool isA = false) {
  uint8_t carry = GetBit(F, FLAG_C);
  reg >> 1 | reg << (-1 & 7);
  if(GetBit(reg, 7) != carry) ToggleBit(reg, 7);
  isA ? ClearBit(F, FLAG_Z) : SetBit(F, FLAG_Z);
  ClearBit(F, FLAG_N);
  ClearBit(F, FLAG_H);
  carry ? SetBit(F, FLAG_C) : ClearBit(F, FLAG_C);
}

void CPU::RRC(uint8_t & reg, bool isA = false) {
  RR(reg);
  uint8_t bit = GetBit(reg, 7);
  if(bit != GetBit(F, FLAG_C)) ToggleBit(F, FLAG_C);
  if(bit != GetBit(reg, 0)) ToggleBit(reg, 0);
  if(isA) ClearBit(F, FLAG_Z);
}

void CPU::SLA(uint8_t & reg) {
  uint8_t bit = GetBit(reg, 7);
  reg << 1;
  reg == 0 ? ClearBit(F, FLAG_Z) : SetBit(F, FLAG_Z);
  ClearBit(F, FLAG_N);
  ClearBit(F, FLAG_H);
  if(GetBit(F, FLAG_C) != bit) ToggleBit(F, FLAG_C);
  ClearBit(reg, 0);
}

void CPU::SRA(uint8_t & reg) {
  uint8_t bit = GetBit(reg, 0);
  reg >> 1;
  reg == 0 ? ClearBit(F, FLAG_Z) : SetBit(F, FLAG_Z);
  ClearBit(F, FLAG_N);
  ClearBit(F, FLAG_H);
  if(GetBit(F, FLAG_C) != bit) ToggleBit(F, FLAG_C);
}

void CPU::SRL(uint8_t & reg) {
  SRA(reg);
  ClearBit(reg, 7);
}

void CPU::SWAP(uint8_t & reg) {
  reg = (reg & 0x0F) << 4 | reg >> 4;
  reg == 0 ? SetBit(F, FLAG_Z) : ClearBit(F, FLAG_Z);
}

void CPU::BIT(uint8_t & reg, uint8_t bit) {
  GetBit(reg, bit) == 0 ? SetBit(F, FLAG_Z) : ClearBit(F, FLAG_Z);
  ClearBit(F, FLAG_N);
  SetBit(F, FLAG_H);
}

void CPU::RES(uint8_t & reg, uint8_t bit) {
  ClearBit(reg, bit);
}

void CPU::SET(uint8_t & reg, uint8_t bit) {
  SetBit(reg, bit);
}

void CPU::DI() {
  IME = false;
}

void CPU::EI() {
  IME = true;
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
  if(!sub) {
    // 0x60 for full carry, 0x06 when half carry occurs
    if(carry || A > 0x99) {
      A += 0x60;
      SetBit(F, FLAG_C);
    }
    if(half || (A & 0x0F) > 0x09) {
      A += 0x06;
    }
    // adjust if carry occurred after sub
  } else {
    if(carry) {
      A -= 0x60;
    }
    if(half) {
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
  if(!GetBit(F, FLAG_Z)) {
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
  if(GetBit(F, FLAG_Z)) {
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
  if(!GetBit(F, FLAG_C)) {
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
  if(GetBit(F, FLAG_C)) {
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
  if(!GetBit(F, FLAG_Z)) {
    POP_STACK16();
  }
}

void CPU::Opcode0xC1() {
  POP_STACK(BC);
}

void CPU::Opcode0xC2() {
  if(!GetBit(F, FLAG_Z)) {
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
  if(!GetBit(F, FLAG_Z)) {
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
  if(GetBit(F, FLAG_Z)) {
    RET();
  }
}

void CPU::Opcode0xC9() {
  RET();
}

void CPU::Opcode0xCA() {
  if(GetBit(F, FLAG_Z)) {
    JP();
  } else {
    PC++;
    PC++;
  }
}

void CPU::Opcode0xCB() {
  extended = true;
}

void CPU::Opcode0xCC() {
  if(GetBit(F, FLAG_Z)) {
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
  if(!GetBit(F, FLAG_C)) {
    RET();
  }
}

void CPU::Opcode0xD1() {
  POP_STACK(DE);
}

void CPU::Opcode0xD2() {
  if(!GetBit(F, FLAG_C)) {
    JP();
  } else {
    PC++;
    PC++;
  }
}

void CPU::Opcode0xD3() {

}

void CPU::Opcode0xD4() {
  if(!GetBit(F, FLAG_C)) {
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
  if(GetBit(F, FLAG_C)) {
    RET();
  }
}

void CPU::Opcode0xD9() {
  RET();
  IME = true;
}

void CPU::Opcode0xDA() {
  if(GetBit(F, FLAG_C)) {
    JP();
  } else {
    PC++;
    PC++;
  }
}

void CPU::Opcode0xDB() {

}

void CPU::Opcode0xDC() {
  if(GetBit(F, FLAG_C)) {
    CALL();
  } else {
    PC++;
    PC++;
  }
}

void CPU::Opcode0xDD() {

}

void CPU::Opcode0xDE() {
  SBC(mmu->ReadMemory(PC));
  PC++;
}

void CPU::Opcode0xDF() {
  RST(3);
}

void CPU::Opcode0xE0() {
  LD(static_cast<uint16_t>(0xFF00 + mmu->ReadMemory(PC)), A);
  PC++;
}

void CPU::Opcode0xE1() {
  POP_STACK(HL);
}

void CPU::Opcode0xE2() {
  LD(static_cast<uint16_t>(0xFF00 + C), A);
}

void CPU::Opcode0xE3() {

}

void CPU::Opcode0xE4() {

}

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
  LD(A, static_cast<uint16_t>(0xFF00 + mmu->ReadMemory(PC)));
  PC++;
}

void CPU::Opcode0xF1() {
  POP_STACK(AF);
}

void CPU::Opcode0xF2() {
  LD(A, static_cast<uint16_t>(0xFF00 + C));
}

void CPU::Opcode0xF3() {
  IME = false;
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
  IME = true;
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

/* --------------------------------------------------------------------*/
/* -------------------------- EXTENDED OPCODES ------------------------*/
/* --------------------------------------------------------------------*/

void CPU::ExtendedOpcode0x00() {
  RLC(B);
}

void CPU::ExtendedOpcode0x01() {
  RLC(C);
}

void CPU::ExtendedOpcode0x02() {
  RLC(D);
}

void CPU::ExtendedOpcode0x03() {
  RLC(E);
}

void CPU::ExtendedOpcode0x04() {
  RLC(H);
}

void CPU::ExtendedOpcode0x05() {
  RLC(L);
}

void CPU::ExtendedOpcode0x06() {
  uint8_t imm = mmu->ReadMemory(HL.GetRegister());
  RLC(imm);
}

void CPU::ExtendedOpcode0x07() {
  RLC(A);
}

void CPU::ExtendedOpcode0x08() {
  RRC(B);
}

void CPU::ExtendedOpcode0x09() {
  RRC(C);
}

void CPU::ExtendedOpcode0x0A() {
  RRC(D);
}

void CPU::ExtendedOpcode0x0B() {
  RRC(E);
}

void CPU::ExtendedOpcode0x0C() {
  RRC(H);
}

void CPU::ExtendedOpcode0x0D() {
  RRC(L);
}

void CPU::ExtendedOpcode0x0E() {
  uint8_t imm = mmu->ReadMemory(HL.GetRegister());
  RRC(imm);
}

void CPU::ExtendedOpcode0x0F() {
  RRC(A);
}

void CPU::ExtendedOpcode0x10() {
  RL(B);
}

void CPU::ExtendedOpcode0x11() {
  RL(C);
}

void CPU::ExtendedOpcode0x12() {
  RL(D);
}

void CPU::ExtendedOpcode0x13() {
  RL(E);
}

void CPU::ExtendedOpcode0x14() {
  RL(H);
}

void CPU::ExtendedOpcode0x15() {
  RL(L);
}

void CPU::ExtendedOpcode0x16() {
  uint8_t imm = mmu->ReadMemory(HL.GetRegister());
  RL(imm);
}

void CPU::ExtendedOpcode0x17() {
  RL(A);
}

void CPU::ExtendedOpcode0x18() {
  RR(B);
}

void CPU::ExtendedOpcode0x19() {
  RR(C);
}

void CPU::ExtendedOpcode0x1A() {
  RR(D);
}

void CPU::ExtendedOpcode0x1B() {
  RR(E);
}

void CPU::ExtendedOpcode0x1C() {
  RR(H);
}

void CPU::ExtendedOpcode0x1D() {
  RR(L);
}

void CPU::ExtendedOpcode0x1E() {
  uint8_t imm = mmu->ReadMemory(HL.GetRegister());
  RR(imm);
}

void CPU::ExtendedOpcode0x1F() {
  RR(A);
}

void CPU::ExtendedOpcode0x20() {
  SLA(B);
}

void CPU::ExtendedOpcode0x21() {
  SLA(C);
}

void CPU::ExtendedOpcode0x22() {
  SLA(D);
}

void CPU::ExtendedOpcode0x23() {
  SLA(E);
}

void CPU::ExtendedOpcode0x24() {
  SLA(H);
}

void CPU::ExtendedOpcode0x25() {
  SLA(L);
}

void CPU::ExtendedOpcode0x26() {
  uint8_t imm = mmu->ReadMemory(HL.GetRegister());
  SLA(imm);
}

void CPU::ExtendedOpcode0x27() {
  SLA(A);
}

void CPU::ExtendedOpcode0x28() {
  SRA(B);
}

void CPU::ExtendedOpcode0x29() {
  SRA(C);
}

void CPU::ExtendedOpcode0x2A() {
  SRA(D);
}

void CPU::ExtendedOpcode0x2B() {
  SRA(E);
}

void CPU::ExtendedOpcode0x2C() {
  SRA(H);
}

void CPU::ExtendedOpcode0x2D() {
  SRA(L);
}

void CPU::ExtendedOpcode0x2E() {
  uint8_t imm = mmu->ReadMemory(HL.GetRegister());
  SRA(imm);
}

void CPU::ExtendedOpcode0x2F() {
  SRA(A);
}

void CPU::ExtendedOpcode0x30() {
  SWAP(B);
}

void CPU::ExtendedOpcode0x31() {
  SWAP(C);
}

void CPU::ExtendedOpcode0x32() {
  SWAP(D);
}

void CPU::ExtendedOpcode0x33() {
  SWAP(E);
}

void CPU::ExtendedOpcode0x34() {
  SWAP(H);
}

void CPU::ExtendedOpcode0x35() {
  SWAP(L);
}

void CPU::ExtendedOpcode0x36() {
  uint8_t imm = mmu->ReadMemory(HL.GetRegister());
  SWAP(imm);
}

void CPU::ExtendedOpcode0x37() {
  SWAP(A);
}

void CPU::ExtendedOpcode0x38() {
  SRL(B);
}

void CPU::ExtendedOpcode0x39() {
  SRL(C);
}

void CPU::ExtendedOpcode0x3A() {
  SRL(D);
}

void CPU::ExtendedOpcode0x3B() {
  SRL(E);
}

void CPU::ExtendedOpcode0x3C() {
  SRL(H);
}

void CPU::ExtendedOpcode0x3D() {
  SRL(L);
}

void CPU::ExtendedOpcode0x3E() {
  uint8_t imm = mmu->ReadMemory(HL.GetRegister());
  SRL(imm);
}

void CPU::ExtendedOpcode0x3F() {
  SRL(A);
}

void CPU::ExtendedOpcode0x40() {
  BIT(B, 0);
}

void CPU::ExtendedOpcode0x41() {
  BIT(C, 0);
}

void CPU::ExtendedOpcode0x42() {
  BIT(D, 0);
}

void CPU::ExtendedOpcode0x43() {
  BIT(E, 0);
}

void CPU::ExtendedOpcode0x44() {
  BIT(H, 0);
}

void CPU::ExtendedOpcode0x45() {
  BIT(L, 0);
}

void CPU::ExtendedOpcode0x46() {
  uint8_t imm = mmu->ReadMemory(HL.GetRegister());
  BIT(imm, 0);
}

void CPU::ExtendedOpcode0x47() {
  BIT(A, 0);
}

void CPU::ExtendedOpcode0x48() {
  BIT(B, 1);
}

void CPU::ExtendedOpcode0x49() {
  BIT(C, 1);
}

void CPU::ExtendedOpcode0x4A() {
  BIT(D, 1);
}

void CPU::ExtendedOpcode0x4B() {
  BIT(E, 1);
}

void CPU::ExtendedOpcode0x4C() {
  BIT(H, 1);
}

void CPU::ExtendedOpcode0x4D() {
  BIT(L, 1);
}

void CPU::ExtendedOpcode0x4E() {
  uint8_t imm = mmu->ReadMemory(HL.GetRegister());
  BIT(imm, 1);
}

void CPU::ExtendedOpcode0x4F() {
  BIT(A, 1);
}

void CPU::ExtendedOpcode0x50() {
  BIT(B, 2);
}

void CPU::ExtendedOpcode0x51() {
  BIT(C, 2);
}

void CPU::ExtendedOpcode0x52() {
  BIT(D, 2);
}

void CPU::ExtendedOpcode0x53() {
  BIT(E, 2);
}

void CPU::ExtendedOpcode0x54() {
  BIT(H, 2);
}

void CPU::ExtendedOpcode0x55() {
  BIT(L, 2);
}

void CPU::ExtendedOpcode0x56() {
  uint8_t imm = mmu->ReadMemory(HL.GetRegister());
  BIT(imm, 2);
}

void CPU::ExtendedOpcode0x57() {
  BIT(A, 2);
}

void CPU::ExtendedOpcode0x58() {
  BIT(B, 3);
}

void CPU::ExtendedOpcode0x59() {
  BIT(C, 3);
}

void CPU::ExtendedOpcode0x5A() {
  BIT(D, 3);
}

void CPU::ExtendedOpcode0x5B() {
  BIT(E, 3);
}

void CPU::ExtendedOpcode0x5C() {
  BIT(H, 3);
}

void CPU::ExtendedOpcode0x5D() {
  BIT(L, 3);
}

void CPU::ExtendedOpcode0x5E() {
  uint8_t imm = mmu->ReadMemory(HL.GetRegister());
  BIT(imm, 3);
}

void CPU::ExtendedOpcode0x5F() {
  BIT(A, 3);
}

void CPU::ExtendedOpcode0x60() {
  BIT(B, 4);
}

void CPU::ExtendedOpcode0x61() {
  BIT(C, 4);
}

void CPU::ExtendedOpcode0x62() {
  BIT(D, 4);
}

void CPU::ExtendedOpcode0x63() {
  BIT(E, 4);
}

void CPU::ExtendedOpcode0x64() {
  BIT(H, 4);
}

void CPU::ExtendedOpcode0x65() {
  BIT(L, 4);
}

void CPU::ExtendedOpcode0x66() {
  uint8_t imm = mmu->ReadMemory(HL.GetRegister());
  BIT(imm, 4);
}

void CPU::ExtendedOpcode0x67() {
  BIT(A, 4);
}

void CPU::ExtendedOpcode0x68() {
  BIT(B, 5);
}

void CPU::ExtendedOpcode0x69() {
  BIT(C, 5);
}

void CPU::ExtendedOpcode0x6A() {
  BIT(D, 5);
}

void CPU::ExtendedOpcode0x6B() {
  BIT(E, 5);
}

void CPU::ExtendedOpcode0x6C() {
  BIT(H, 5);
}

void CPU::ExtendedOpcode0x6D() {
  BIT(L, 5);
}

void CPU::ExtendedOpcode0x6E() {
  uint8_t imm = mmu->ReadMemory(HL.GetRegister());
  BIT(imm, 5);
}

void CPU::ExtendedOpcode0x6F() {
  BIT(A, 5);
}

void CPU::ExtendedOpcode0x70() {
  BIT(B, 6);
}

void CPU::ExtendedOpcode0x71() {
  BIT(C, 6);
}

void CPU::ExtendedOpcode0x72() {
  BIT(D, 6);
}

void CPU::ExtendedOpcode0x73() {
  BIT(E, 6);
}

void CPU::ExtendedOpcode0x74() {
  BIT(H, 6);
}

void CPU::ExtendedOpcode0x75() {
  BIT(L, 6);
}

void CPU::ExtendedOpcode0x76() {
  uint8_t imm = mmu->ReadMemory(HL.GetRegister());
  BIT(imm, 6);
}

void CPU::ExtendedOpcode0x77() {
  BIT(A, 6);
}

void CPU::ExtendedOpcode0x78() {
  BIT(B, 7);
}

void CPU::ExtendedOpcode0x79() {
  BIT(C, 7);
}

void CPU::ExtendedOpcode0x7A() {
  BIT(D, 7);
}

void CPU::ExtendedOpcode0x7B() {
  BIT(E, 7);
}

void CPU::ExtendedOpcode0x7C() {
  BIT(H, 7);
}

void CPU::ExtendedOpcode0x7D() {
  BIT(L, 7);
}

void CPU::ExtendedOpcode0x7E() {
  uint8_t imm = mmu->ReadMemory(HL.GetRegister());
  BIT(imm, 7);
}

void CPU::ExtendedOpcode0x7F() {
  BIT(A, 7);
}

void CPU::ExtendedOpcode0x80() {
  RES(B, 0);
}

void CPU::ExtendedOpcode0x81() {
  RES(C, 0);
}

void CPU::ExtendedOpcode0x82() {
  RES(D, 0);
}

void CPU::ExtendedOpcode0x83() {
  RES(E, 0);
}

void CPU::ExtendedOpcode0x84() {
  RES(H, 0);
}

void CPU::ExtendedOpcode0x85() {
  RES(L, 0);
}

void CPU::ExtendedOpcode0x86() {
  uint8_t imm = mmu->ReadMemory(HL.GetRegister());
  RES(imm, 0);
}

void CPU::ExtendedOpcode0x87() {
  RES(A, 0);
}

void CPU::ExtendedOpcode0x88() {
  RES(B, 1);
}

void CPU::ExtendedOpcode0x89() {
  RES(C, 1);
}

void CPU::ExtendedOpcode0x8A() {
  RES(D, 1);
}

void CPU::ExtendedOpcode0x8B() {
  RES(E, 1);
}

void CPU::ExtendedOpcode0x8C() {
  RES(H, 1);
}

void CPU::ExtendedOpcode0x8D() {
  RES(L, 1);
}

void CPU::ExtendedOpcode0x8E() {
  uint8_t imm = mmu->ReadMemory(HL.GetRegister());
  RES(imm, 1);
}

void CPU::ExtendedOpcode0x8F() {
  RES(A, 1);
}

void CPU::ExtendedOpcode0x90() {
  RES(B, 2);
}

void CPU::ExtendedOpcode0x91() {
  RES(C, 2);
}

void CPU::ExtendedOpcode0x92() {
  RES(D, 2);
}

void CPU::ExtendedOpcode0x93() {
  RES(E, 2);
}

void CPU::ExtendedOpcode0x94() {
  RES(H, 2);
}

void CPU::ExtendedOpcode0x95() {
  RES(L, 2);
}

void CPU::ExtendedOpcode0x96() {
  uint8_t imm = mmu->ReadMemory(HL.GetRegister());
  RES(imm, 2);
}

void CPU::ExtendedOpcode0x97() {
  RES(A, 2);
}

void CPU::ExtendedOpcode0x98() {
  RES(B, 3);
}

void CPU::ExtendedOpcode0x99() {
  RES(C, 3);
}

void CPU::ExtendedOpcode0x9A() {
  RES(D, 3);
}

void CPU::ExtendedOpcode0x9B() {
  RES(E, 3);
}

void CPU::ExtendedOpcode0x9C() {
  RES(H, 3);
}

void CPU::ExtendedOpcode0x9D() {
  RES(L, 3);
}

void CPU::ExtendedOpcode0x9E() {
  uint8_t imm = mmu->ReadMemory(HL.GetRegister());
  RES(imm, 3);
}

void CPU::ExtendedOpcode0x9F() {
  RES(A, 3);
}

void CPU::ExtendedOpcode0xA0() {
  RES(B, 4);
}

void CPU::ExtendedOpcode0xA1() {
  RES(C, 4);
}

void CPU::ExtendedOpcode0xA2() {
  RES(D, 4);
}

void CPU::ExtendedOpcode0xA3() {
  RES(E, 4);
}

void CPU::ExtendedOpcode0xA4() {
  RES(H, 4);
}

void CPU::ExtendedOpcode0xA5() {
  RES(L, 4);
}

void CPU::ExtendedOpcode0xA6() {
  uint8_t imm = mmu->ReadMemory(HL.GetRegister());
  RES(imm, 4);
}

void CPU::ExtendedOpcode0xA7() {
  RES(A, 4);
}

void CPU::ExtendedOpcode0xA8() {
  RES(B, 5);
}

void CPU::ExtendedOpcode0xA9() {
  RES(C, 5);
}

void CPU::ExtendedOpcode0xAA() {
  RES(D, 5);
}

void CPU::ExtendedOpcode0xAB() {
  RES(E, 5);
}

void CPU::ExtendedOpcode0xAC() {
  RES(H, 5);
}

void CPU::ExtendedOpcode0xAD() {
  RES(L, 5);
}

void CPU::ExtendedOpcode0xAE() {
  uint8_t imm = mmu->ReadMemory(HL.GetRegister());
  RES(imm, 5);
}

void CPU::ExtendedOpcode0xAF() {
  RES(A, 5);
}

void CPU::ExtendedOpcode0xB0() {
  RES(B, 6);
}

void CPU::ExtendedOpcode0xB1() {
  RES(C, 6);
}

void CPU::ExtendedOpcode0xB2() {
  RES(D, 6);
}

void CPU::ExtendedOpcode0xB3() {
  RES(E, 6);
}

void CPU::ExtendedOpcode0xB4() {
  RES(H, 6);
}

void CPU::ExtendedOpcode0xB5() {
  RES(L, 6);
}

void CPU::ExtendedOpcode0xB6() {
  uint8_t imm = mmu->ReadMemory(HL.GetRegister());
  RES(imm, 6);
}

void CPU::ExtendedOpcode0xB7() {
  RES(A, 6);
}

void CPU::ExtendedOpcode0xB8() {
  RES(B, 7);
}

void CPU::ExtendedOpcode0xB9() {
  RES(C, 7);
}

void CPU::ExtendedOpcode0xBA() {
  RES(D, 7);
}

void CPU::ExtendedOpcode0xBB() {
  RES(E, 7);
}

void CPU::ExtendedOpcode0xBC() {
  RES(H, 7);
}

void CPU::ExtendedOpcode0xBD() {
  RES(L, 7);
}

void CPU::ExtendedOpcode0xBE() {
  uint8_t imm = mmu->ReadMemory(HL.GetRegister());
  RES(imm, 7);
}

void CPU::ExtendedOpcode0xBF() {
  RES(A, 7);
}

void CPU::ExtendedOpcode0xC0() {
  SET(B, 0);
}

void CPU::ExtendedOpcode0xC1() {
  SET(C, 0);
}

void CPU::ExtendedOpcode0xC2() {
  SET(D, 0);
}

void CPU::ExtendedOpcode0xC3() {
  SET(E, 0);
}

void CPU::ExtendedOpcode0xC4() {
  SET(H, 0);
}

void CPU::ExtendedOpcode0xC5() {
  SET(L, 0);
}

void CPU::ExtendedOpcode0xC6() {
  uint8_t imm = mmu->ReadMemory(HL.GetRegister());
  SET(imm, 0);
}

void CPU::ExtendedOpcode0xC7() {
  SET(A, 0);
}

void CPU::ExtendedOpcode0xC8() {
  SET(B, 1);
}

void CPU::ExtendedOpcode0xC9() {
  SET(C, 1);
}

void CPU::ExtendedOpcode0xCA() {
  SET(D, 1);
}

void CPU::ExtendedOpcode0xCB() {
  SET(E, 1);
}

void CPU::ExtendedOpcode0xCC() {
  SET(H, 1);
}

void CPU::ExtendedOpcode0xCD() {
  SET(L, 1);
}

void CPU::ExtendedOpcode0xCE() {
  uint8_t imm = mmu->ReadMemory(HL.GetRegister());
  SET(imm, 1);
}

void CPU::ExtendedOpcode0xCF() {
  SET(A, 1);
}

void CPU::ExtendedOpcode0xD0() {
  SET(B, 2);
}

void CPU::ExtendedOpcode0xD1() {
  SET(C, 2);
}

void CPU::ExtendedOpcode0xD2() {
  SET(D, 2);
}

void CPU::ExtendedOpcode0xD3() {
  SET(E, 2);
}

void CPU::ExtendedOpcode0xD4() {
  SET(H, 2);
}

void CPU::ExtendedOpcode0xD5() {
  SET(L, 2);
}

void CPU::ExtendedOpcode0xD6() {
  uint8_t imm = mmu->ReadMemory(HL.GetRegister());
  SET(imm, 2);
}

void CPU::ExtendedOpcode0xD7() {
  SET(A, 2);
}

void CPU::ExtendedOpcode0xD8() {
  SET(B, 3);
}

void CPU::ExtendedOpcode0xD9() {
  SET(C, 3);
}

void CPU::ExtendedOpcode0xDA() {
  SET(D, 3);
}

void CPU::ExtendedOpcode0xDB() {
  SET(E, 3);
}

void CPU::ExtendedOpcode0xDC() {
  SET(H, 3);
}

void CPU::ExtendedOpcode0xDD() {
  SET(L, 3);
}

void CPU::ExtendedOpcode0xDE() {
  uint8_t imm = mmu->ReadMemory(HL.GetRegister());
  SET(imm, 3);
}

void CPU::ExtendedOpcode0xDF() {
  SET(A, 3);
}

void CPU::ExtendedOpcode0xE0() {
  SET(B, 4);
}

void CPU::ExtendedOpcode0xE1() {
  SET(C, 4);
}

void CPU::ExtendedOpcode0xE2() {
  SET(D, 4);
}

void CPU::ExtendedOpcode0xE3() {
  SET(E, 4);
}

void CPU::ExtendedOpcode0xE4() {
  SET(H, 4);
}

void CPU::ExtendedOpcode0xE5() {
  SET(L, 4);
}

void CPU::ExtendedOpcode0xE6() {
  uint8_t imm = mmu->ReadMemory(HL.GetRegister());
  SET(imm, 4);
}

void CPU::ExtendedOpcode0xE7() {
  SET(A, 4);
}

void CPU::ExtendedOpcode0xE8() {
  SET(B, 5);
}

void CPU::ExtendedOpcode0xE9() {
  SET(C, 5);
}

void CPU::ExtendedOpcode0xEA() {
  SET(D, 5);
}

void CPU::ExtendedOpcode0xEB() {
  SET(E, 5);
}

void CPU::ExtendedOpcode0xEC() {
  SET(H, 5);
}

void CPU::ExtendedOpcode0xED() {
  SET(L, 5);
}

void CPU::ExtendedOpcode0xEE() {
  uint8_t imm = mmu->ReadMemory(HL.GetRegister());
  SET(imm, 5);
}

void CPU::ExtendedOpcode0xEF() {
  SET(A, 5);
}

void CPU::ExtendedOpcode0xF0() {
  SET(B, 6);
}

void CPU::ExtendedOpcode0xF1() {
  SET(C, 6);
}

void CPU::ExtendedOpcode0xF2() {
  SET(D, 6);
}

void CPU::ExtendedOpcode0xF3() {
  SET(E, 6);
}

void CPU::ExtendedOpcode0xF4() {
  SET(H, 6);
}

void CPU::ExtendedOpcode0xF5() {
  SET(L, 6);
}

void CPU::ExtendedOpcode0xF6() {
  uint8_t imm = mmu->ReadMemory(HL.GetRegister());
  SET(imm, 6);
}

void CPU::ExtendedOpcode0xF7() {
  SET(A, 6);
}

void CPU::ExtendedOpcode0xF8() {
  SET(B, 7);
}

void CPU::ExtendedOpcode0xF9() {
  SET(C, 7);
}

void CPU::ExtendedOpcode0xFA() {
  SET(D, 7);
}

void CPU::ExtendedOpcode0xFB() {
  SET(E, 7);
}

void CPU::ExtendedOpcode0xFC() {
  SET(H, 7);
}

void CPU::ExtendedOpcode0xFD() {
  SET(L, 7);
}

void CPU::ExtendedOpcode0xFE() {
  uint8_t imm = mmu->ReadMemory(HL.GetRegister());
  SET(imm, 7);
}

void CPU::ExtendedOpcode0xFF() {
  SET(A, 7);
}


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

void CPU::PopulateExtendedOpcodes() {
  std::cout << "[INFO] Populating extended opcodes..." << std::endl;
  ExtendedOpcodes[0x00] = &CPU::ExtendedOpcode0x00;
  ExtendedOpcodes[0x01] = &CPU::ExtendedOpcode0x01;
  ExtendedOpcodes[0x02] = &CPU::ExtendedOpcode0x02;
  ExtendedOpcodes[0x03] = &CPU::ExtendedOpcode0x03;
  ExtendedOpcodes[0x04] = &CPU::ExtendedOpcode0x04;
  ExtendedOpcodes[0x05] = &CPU::ExtendedOpcode0x05;
  ExtendedOpcodes[0x06] = &CPU::ExtendedOpcode0x06;
  ExtendedOpcodes[0x07] = &CPU::ExtendedOpcode0x07;
  ExtendedOpcodes[0x08] = &CPU::ExtendedOpcode0x08;
  ExtendedOpcodes[0x09] = &CPU::ExtendedOpcode0x09;
  ExtendedOpcodes[0x0A] = &CPU::ExtendedOpcode0x0A;
  ExtendedOpcodes[0x0B] = &CPU::ExtendedOpcode0x0B;
  ExtendedOpcodes[0x0C] = &CPU::ExtendedOpcode0x0C;
  ExtendedOpcodes[0x0D] = &CPU::ExtendedOpcode0x0D;
  ExtendedOpcodes[0x0E] = &CPU::ExtendedOpcode0x0E;
  ExtendedOpcodes[0x0F] = &CPU::ExtendedOpcode0x0F;
  ExtendedOpcodes[0x10] = &CPU::ExtendedOpcode0x10;
  ExtendedOpcodes[0x11] = &CPU::ExtendedOpcode0x11;
  ExtendedOpcodes[0x12] = &CPU::ExtendedOpcode0x12;
  ExtendedOpcodes[0x13] = &CPU::ExtendedOpcode0x13;
  ExtendedOpcodes[0x14] = &CPU::ExtendedOpcode0x14;
  ExtendedOpcodes[0x15] = &CPU::ExtendedOpcode0x15;
  ExtendedOpcodes[0x16] = &CPU::ExtendedOpcode0x16;
  ExtendedOpcodes[0x17] = &CPU::ExtendedOpcode0x17;
  ExtendedOpcodes[0x18] = &CPU::ExtendedOpcode0x18;
  ExtendedOpcodes[0x19] = &CPU::ExtendedOpcode0x19;
  ExtendedOpcodes[0x1A] = &CPU::ExtendedOpcode0x1A;
  ExtendedOpcodes[0x1B] = &CPU::ExtendedOpcode0x1B;
  ExtendedOpcodes[0x1C] = &CPU::ExtendedOpcode0x1C;
  ExtendedOpcodes[0x1D] = &CPU::ExtendedOpcode0x1D;
  ExtendedOpcodes[0x1E] = &CPU::ExtendedOpcode0x1E;
  ExtendedOpcodes[0x1F] = &CPU::ExtendedOpcode0x1F;
  ExtendedOpcodes[0x20] = &CPU::ExtendedOpcode0x20;
  ExtendedOpcodes[0x21] = &CPU::ExtendedOpcode0x21;
  ExtendedOpcodes[0x22] = &CPU::ExtendedOpcode0x22;
  ExtendedOpcodes[0x23] = &CPU::ExtendedOpcode0x23;
  ExtendedOpcodes[0x24] = &CPU::ExtendedOpcode0x24;
  ExtendedOpcodes[0x25] = &CPU::ExtendedOpcode0x25;
  ExtendedOpcodes[0x26] = &CPU::ExtendedOpcode0x26;
  ExtendedOpcodes[0x27] = &CPU::ExtendedOpcode0x27;
  ExtendedOpcodes[0x28] = &CPU::ExtendedOpcode0x28;
  ExtendedOpcodes[0x29] = &CPU::ExtendedOpcode0x29;
  ExtendedOpcodes[0x2A] = &CPU::ExtendedOpcode0x2A;
  ExtendedOpcodes[0x2B] = &CPU::ExtendedOpcode0x2B;
  ExtendedOpcodes[0x2C] = &CPU::ExtendedOpcode0x2C;
  ExtendedOpcodes[0x2D] = &CPU::ExtendedOpcode0x2D;
  ExtendedOpcodes[0x2E] = &CPU::ExtendedOpcode0x2E;
  ExtendedOpcodes[0x2F] = &CPU::ExtendedOpcode0x2F;
  ExtendedOpcodes[0x30] = &CPU::ExtendedOpcode0x30;
  ExtendedOpcodes[0x31] = &CPU::ExtendedOpcode0x31;
  ExtendedOpcodes[0x32] = &CPU::ExtendedOpcode0x32;
  ExtendedOpcodes[0x33] = &CPU::ExtendedOpcode0x33;
  ExtendedOpcodes[0x34] = &CPU::ExtendedOpcode0x34;
  ExtendedOpcodes[0x35] = &CPU::ExtendedOpcode0x35;
  ExtendedOpcodes[0x36] = &CPU::ExtendedOpcode0x36;
  ExtendedOpcodes[0x37] = &CPU::ExtendedOpcode0x37;
  ExtendedOpcodes[0x38] = &CPU::ExtendedOpcode0x38;
  ExtendedOpcodes[0x39] = &CPU::ExtendedOpcode0x39;
  ExtendedOpcodes[0x3A] = &CPU::ExtendedOpcode0x3A;
  ExtendedOpcodes[0x3B] = &CPU::ExtendedOpcode0x3B;
  ExtendedOpcodes[0x3C] = &CPU::ExtendedOpcode0x3C;
  ExtendedOpcodes[0x3D] = &CPU::ExtendedOpcode0x3D;
  ExtendedOpcodes[0x3E] = &CPU::ExtendedOpcode0x3E;
  ExtendedOpcodes[0x3F] = &CPU::ExtendedOpcode0x3F;
  ExtendedOpcodes[0x40] = &CPU::ExtendedOpcode0x40;
  ExtendedOpcodes[0x41] = &CPU::ExtendedOpcode0x41;
  ExtendedOpcodes[0x42] = &CPU::ExtendedOpcode0x42;
  ExtendedOpcodes[0x43] = &CPU::ExtendedOpcode0x43;
  ExtendedOpcodes[0x44] = &CPU::ExtendedOpcode0x44;
  ExtendedOpcodes[0x45] = &CPU::ExtendedOpcode0x45;
  ExtendedOpcodes[0x46] = &CPU::ExtendedOpcode0x46;
  ExtendedOpcodes[0x47] = &CPU::ExtendedOpcode0x47;
  ExtendedOpcodes[0x48] = &CPU::ExtendedOpcode0x48;
  ExtendedOpcodes[0x49] = &CPU::ExtendedOpcode0x49;
  ExtendedOpcodes[0x4A] = &CPU::ExtendedOpcode0x4A;
  ExtendedOpcodes[0x4B] = &CPU::ExtendedOpcode0x4B;
  ExtendedOpcodes[0x4C] = &CPU::ExtendedOpcode0x4C;
  ExtendedOpcodes[0x4D] = &CPU::ExtendedOpcode0x4D;
  ExtendedOpcodes[0x4E] = &CPU::ExtendedOpcode0x4E;
  ExtendedOpcodes[0x4F] = &CPU::ExtendedOpcode0x4F;
  ExtendedOpcodes[0x50] = &CPU::ExtendedOpcode0x50;
  ExtendedOpcodes[0x51] = &CPU::ExtendedOpcode0x51;
  ExtendedOpcodes[0x52] = &CPU::ExtendedOpcode0x52;
  ExtendedOpcodes[0x53] = &CPU::ExtendedOpcode0x53;
  ExtendedOpcodes[0x54] = &CPU::ExtendedOpcode0x54;
  ExtendedOpcodes[0x55] = &CPU::ExtendedOpcode0x55;
  ExtendedOpcodes[0x56] = &CPU::ExtendedOpcode0x56;
  ExtendedOpcodes[0x57] = &CPU::ExtendedOpcode0x57;
  ExtendedOpcodes[0x58] = &CPU::ExtendedOpcode0x58;
  ExtendedOpcodes[0x59] = &CPU::ExtendedOpcode0x59;
  ExtendedOpcodes[0x5A] = &CPU::ExtendedOpcode0x5A;
  ExtendedOpcodes[0x5B] = &CPU::ExtendedOpcode0x5B;
  ExtendedOpcodes[0x5C] = &CPU::ExtendedOpcode0x5C;
  ExtendedOpcodes[0x5D] = &CPU::ExtendedOpcode0x5D;
  ExtendedOpcodes[0x5E] = &CPU::ExtendedOpcode0x5E;
  ExtendedOpcodes[0x5F] = &CPU::ExtendedOpcode0x5F;
  ExtendedOpcodes[0x60] = &CPU::ExtendedOpcode0x60;
  ExtendedOpcodes[0x61] = &CPU::ExtendedOpcode0x61;
  ExtendedOpcodes[0x62] = &CPU::ExtendedOpcode0x62;
  ExtendedOpcodes[0x63] = &CPU::ExtendedOpcode0x63;
  ExtendedOpcodes[0x64] = &CPU::ExtendedOpcode0x64;
  ExtendedOpcodes[0x65] = &CPU::ExtendedOpcode0x65;
  ExtendedOpcodes[0x66] = &CPU::ExtendedOpcode0x66;
  ExtendedOpcodes[0x67] = &CPU::ExtendedOpcode0x67;
  ExtendedOpcodes[0x68] = &CPU::ExtendedOpcode0x68;
  ExtendedOpcodes[0x69] = &CPU::ExtendedOpcode0x69;
  ExtendedOpcodes[0x6A] = &CPU::ExtendedOpcode0x6A;
  ExtendedOpcodes[0x6B] = &CPU::ExtendedOpcode0x6B;
  ExtendedOpcodes[0x6C] = &CPU::ExtendedOpcode0x6C;
  ExtendedOpcodes[0x6D] = &CPU::ExtendedOpcode0x6D;
  ExtendedOpcodes[0x6E] = &CPU::ExtendedOpcode0x6E;
  ExtendedOpcodes[0x6F] = &CPU::ExtendedOpcode0x6F;
  ExtendedOpcodes[0x70] = &CPU::ExtendedOpcode0x70;
  ExtendedOpcodes[0x71] = &CPU::ExtendedOpcode0x71;
  ExtendedOpcodes[0x72] = &CPU::ExtendedOpcode0x72;
  ExtendedOpcodes[0x73] = &CPU::ExtendedOpcode0x73;
  ExtendedOpcodes[0x74] = &CPU::ExtendedOpcode0x74;
  ExtendedOpcodes[0x75] = &CPU::ExtendedOpcode0x75;
  ExtendedOpcodes[0x76] = &CPU::ExtendedOpcode0x76;
  ExtendedOpcodes[0x77] = &CPU::ExtendedOpcode0x77;
  ExtendedOpcodes[0x78] = &CPU::ExtendedOpcode0x78;
  ExtendedOpcodes[0x79] = &CPU::ExtendedOpcode0x79;
  ExtendedOpcodes[0x7A] = &CPU::ExtendedOpcode0x7A;
  ExtendedOpcodes[0x7B] = &CPU::ExtendedOpcode0x7B;
  ExtendedOpcodes[0x7C] = &CPU::ExtendedOpcode0x7C;
  ExtendedOpcodes[0x7D] = &CPU::ExtendedOpcode0x7D;
  ExtendedOpcodes[0x7E] = &CPU::ExtendedOpcode0x7E;
  ExtendedOpcodes[0x7F] = &CPU::ExtendedOpcode0x7F;
  ExtendedOpcodes[0x80] = &CPU::ExtendedOpcode0x80;
  ExtendedOpcodes[0x81] = &CPU::ExtendedOpcode0x81;
  ExtendedOpcodes[0x82] = &CPU::ExtendedOpcode0x82;
  ExtendedOpcodes[0x83] = &CPU::ExtendedOpcode0x83;
  ExtendedOpcodes[0x84] = &CPU::ExtendedOpcode0x84;
  ExtendedOpcodes[0x85] = &CPU::ExtendedOpcode0x85;
  ExtendedOpcodes[0x86] = &CPU::ExtendedOpcode0x86;
  ExtendedOpcodes[0x87] = &CPU::ExtendedOpcode0x87;
  ExtendedOpcodes[0x88] = &CPU::ExtendedOpcode0x88;
  ExtendedOpcodes[0x89] = &CPU::ExtendedOpcode0x89;
  ExtendedOpcodes[0x8A] = &CPU::ExtendedOpcode0x8A;
  ExtendedOpcodes[0x8B] = &CPU::ExtendedOpcode0x8B;
  ExtendedOpcodes[0x8C] = &CPU::ExtendedOpcode0x8C;
  ExtendedOpcodes[0x8D] = &CPU::ExtendedOpcode0x8D;
  ExtendedOpcodes[0x8E] = &CPU::ExtendedOpcode0x8E;
  ExtendedOpcodes[0x8F] = &CPU::ExtendedOpcode0x8F;
  ExtendedOpcodes[0x90] = &CPU::ExtendedOpcode0x90;
  ExtendedOpcodes[0x91] = &CPU::ExtendedOpcode0x91;
  ExtendedOpcodes[0x92] = &CPU::ExtendedOpcode0x92;
  ExtendedOpcodes[0x93] = &CPU::ExtendedOpcode0x93;
  ExtendedOpcodes[0x94] = &CPU::ExtendedOpcode0x94;
  ExtendedOpcodes[0x95] = &CPU::ExtendedOpcode0x95;
  ExtendedOpcodes[0x96] = &CPU::ExtendedOpcode0x96;
  ExtendedOpcodes[0x97] = &CPU::ExtendedOpcode0x97;
  ExtendedOpcodes[0x98] = &CPU::ExtendedOpcode0x98;
  ExtendedOpcodes[0x99] = &CPU::ExtendedOpcode0x99;
  ExtendedOpcodes[0x9A] = &CPU::ExtendedOpcode0x9A;
  ExtendedOpcodes[0x9B] = &CPU::ExtendedOpcode0x9B;
  ExtendedOpcodes[0x9C] = &CPU::ExtendedOpcode0x9C;
  ExtendedOpcodes[0x9D] = &CPU::ExtendedOpcode0x9D;
  ExtendedOpcodes[0x9E] = &CPU::ExtendedOpcode0x9E;
  ExtendedOpcodes[0x9F] = &CPU::ExtendedOpcode0x9F;
  ExtendedOpcodes[0xA0] = &CPU::ExtendedOpcode0xA0;
  ExtendedOpcodes[0xA1] = &CPU::ExtendedOpcode0xA1;
  ExtendedOpcodes[0xA2] = &CPU::ExtendedOpcode0xA2;
  ExtendedOpcodes[0xA3] = &CPU::ExtendedOpcode0xA3;
  ExtendedOpcodes[0xA4] = &CPU::ExtendedOpcode0xA4;
  ExtendedOpcodes[0xA5] = &CPU::ExtendedOpcode0xA5;
  ExtendedOpcodes[0xA6] = &CPU::ExtendedOpcode0xA6;
  ExtendedOpcodes[0xA7] = &CPU::ExtendedOpcode0xA7;
  ExtendedOpcodes[0xA8] = &CPU::ExtendedOpcode0xA8;
  ExtendedOpcodes[0xA9] = &CPU::ExtendedOpcode0xA9;
  ExtendedOpcodes[0xAA] = &CPU::ExtendedOpcode0xAA;
  ExtendedOpcodes[0xAB] = &CPU::ExtendedOpcode0xAB;
  ExtendedOpcodes[0xAC] = &CPU::ExtendedOpcode0xAC;
  ExtendedOpcodes[0xAD] = &CPU::ExtendedOpcode0xAD;
  ExtendedOpcodes[0xAE] = &CPU::ExtendedOpcode0xAE;
  ExtendedOpcodes[0xAF] = &CPU::ExtendedOpcode0xAF;
  ExtendedOpcodes[0xB0] = &CPU::ExtendedOpcode0xB0;
  ExtendedOpcodes[0xB1] = &CPU::ExtendedOpcode0xB1;
  ExtendedOpcodes[0xB2] = &CPU::ExtendedOpcode0xB2;
  ExtendedOpcodes[0xB3] = &CPU::ExtendedOpcode0xB3;
  ExtendedOpcodes[0xB4] = &CPU::ExtendedOpcode0xB4;
  ExtendedOpcodes[0xB5] = &CPU::ExtendedOpcode0xB5;
  ExtendedOpcodes[0xB6] = &CPU::ExtendedOpcode0xB6;
  ExtendedOpcodes[0xB7] = &CPU::ExtendedOpcode0xB7;
  ExtendedOpcodes[0xB8] = &CPU::ExtendedOpcode0xB8;
  ExtendedOpcodes[0xB9] = &CPU::ExtendedOpcode0xB9;
  ExtendedOpcodes[0xBA] = &CPU::ExtendedOpcode0xBA;
  ExtendedOpcodes[0xBB] = &CPU::ExtendedOpcode0xBB;
  ExtendedOpcodes[0xBC] = &CPU::ExtendedOpcode0xBC;
  ExtendedOpcodes[0xBD] = &CPU::ExtendedOpcode0xBD;
  ExtendedOpcodes[0xBE] = &CPU::ExtendedOpcode0xBE;
  ExtendedOpcodes[0xBF] = &CPU::ExtendedOpcode0xBF;
  ExtendedOpcodes[0xC0] = &CPU::ExtendedOpcode0xC0;
  ExtendedOpcodes[0xC1] = &CPU::ExtendedOpcode0xC1;
  ExtendedOpcodes[0xC2] = &CPU::ExtendedOpcode0xC2;
  ExtendedOpcodes[0xC3] = &CPU::ExtendedOpcode0xC3;
  ExtendedOpcodes[0xC4] = &CPU::ExtendedOpcode0xC4;
  ExtendedOpcodes[0xC5] = &CPU::ExtendedOpcode0xC5;
  ExtendedOpcodes[0xC6] = &CPU::ExtendedOpcode0xC6;
  ExtendedOpcodes[0xC7] = &CPU::ExtendedOpcode0xC7;
  ExtendedOpcodes[0xC8] = &CPU::ExtendedOpcode0xC8;
  ExtendedOpcodes[0xC9] = &CPU::ExtendedOpcode0xC9;
  ExtendedOpcodes[0xCA] = &CPU::ExtendedOpcode0xCA;
  ExtendedOpcodes[0xCB] = &CPU::ExtendedOpcode0xCB;
  ExtendedOpcodes[0xCC] = &CPU::ExtendedOpcode0xCC;
  ExtendedOpcodes[0xCD] = &CPU::ExtendedOpcode0xCD;
  ExtendedOpcodes[0xCE] = &CPU::ExtendedOpcode0xCE;
  ExtendedOpcodes[0xCF] = &CPU::ExtendedOpcode0xCF;
  ExtendedOpcodes[0xD0] = &CPU::ExtendedOpcode0xD0;
  ExtendedOpcodes[0xD1] = &CPU::ExtendedOpcode0xD1;
  ExtendedOpcodes[0xD2] = &CPU::ExtendedOpcode0xD2;
  ExtendedOpcodes[0xD3] = &CPU::ExtendedOpcode0xD3;
  ExtendedOpcodes[0xD4] = &CPU::ExtendedOpcode0xD4;
  ExtendedOpcodes[0xD5] = &CPU::ExtendedOpcode0xD5;
  ExtendedOpcodes[0xD6] = &CPU::ExtendedOpcode0xD6;
  ExtendedOpcodes[0xD7] = &CPU::ExtendedOpcode0xD7;
  ExtendedOpcodes[0xD8] = &CPU::ExtendedOpcode0xD8;
  ExtendedOpcodes[0xD9] = &CPU::ExtendedOpcode0xD9;
  ExtendedOpcodes[0xDA] = &CPU::ExtendedOpcode0xDA;
  ExtendedOpcodes[0xDB] = &CPU::ExtendedOpcode0xDB;
  ExtendedOpcodes[0xDC] = &CPU::ExtendedOpcode0xDC;
  ExtendedOpcodes[0xDD] = &CPU::ExtendedOpcode0xDD;
  ExtendedOpcodes[0xDE] = &CPU::ExtendedOpcode0xDE;
  ExtendedOpcodes[0xDF] = &CPU::ExtendedOpcode0xDF;
  ExtendedOpcodes[0xE0] = &CPU::ExtendedOpcode0xE0;
  ExtendedOpcodes[0xE1] = &CPU::ExtendedOpcode0xE1;
  ExtendedOpcodes[0xE2] = &CPU::ExtendedOpcode0xE2;
  ExtendedOpcodes[0xE3] = &CPU::ExtendedOpcode0xE3;
  ExtendedOpcodes[0xE4] = &CPU::ExtendedOpcode0xE4;
  ExtendedOpcodes[0xE5] = &CPU::ExtendedOpcode0xE5;
  ExtendedOpcodes[0xE6] = &CPU::ExtendedOpcode0xE6;
  ExtendedOpcodes[0xE7] = &CPU::ExtendedOpcode0xE7;
  ExtendedOpcodes[0xE8] = &CPU::ExtendedOpcode0xE8;
  ExtendedOpcodes[0xE9] = &CPU::ExtendedOpcode0xE9;
  ExtendedOpcodes[0xEA] = &CPU::ExtendedOpcode0xEA;
  ExtendedOpcodes[0xEB] = &CPU::ExtendedOpcode0xEB;
  ExtendedOpcodes[0xEC] = &CPU::ExtendedOpcode0xEC;
  ExtendedOpcodes[0xED] = &CPU::ExtendedOpcode0xED;
  ExtendedOpcodes[0xEE] = &CPU::ExtendedOpcode0xEE;
  ExtendedOpcodes[0xEF] = &CPU::ExtendedOpcode0xEF;
  ExtendedOpcodes[0xF0] = &CPU::ExtendedOpcode0xF0;
  ExtendedOpcodes[0xF1] = &CPU::ExtendedOpcode0xF1;
  ExtendedOpcodes[0xF2] = &CPU::ExtendedOpcode0xF2;
  ExtendedOpcodes[0xF3] = &CPU::ExtendedOpcode0xF3;
  ExtendedOpcodes[0xF4] = &CPU::ExtendedOpcode0xF4;
  ExtendedOpcodes[0xF5] = &CPU::ExtendedOpcode0xF5;
  ExtendedOpcodes[0xF6] = &CPU::ExtendedOpcode0xF6;
  ExtendedOpcodes[0xF7] = &CPU::ExtendedOpcode0xF7;
  ExtendedOpcodes[0xF8] = &CPU::ExtendedOpcode0xF8;
  ExtendedOpcodes[0xF9] = &CPU::ExtendedOpcode0xF9;
  ExtendedOpcodes[0xFA] = &CPU::ExtendedOpcode0xFA;
  ExtendedOpcodes[0xFB] = &CPU::ExtendedOpcode0xFB;
  ExtendedOpcodes[0xFC] = &CPU::ExtendedOpcode0xFC;
  ExtendedOpcodes[0xFD] = &CPU::ExtendedOpcode0xFD;
  ExtendedOpcodes[0xFE] = &CPU::ExtendedOpcode0xFE;
  ExtendedOpcodes[0xFF] = &CPU::ExtendedOpcode0xFF;
  std::cout << "[INFO] Done." << std::endl;
}
