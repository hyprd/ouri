#pragma once
#include "mmu.h"

class Register {
        public:
            uint8_t *low;
            uint8_t *high;
            Register();
            Register(uint8_t *high, uint8_t *low);
            uint16_t GetRegister();
            void SetRegister(uint16_t value);
};

class CPU {
    public:
        uint8_t FLAG_Z = 7;
        uint8_t FLAG_N = 6;
        uint8_t FLAG_H = 5;
        uint8_t FLAG_C = 4;
        uint8_t A, B, C, D, E, F, H, L;
        uint16_t SP;
        uint16_t PC;
        
        uint16_t RSTVectors[8] = { 0x0000, 0x0008, 0x0010, 0x0018, 0x0020, 0x0028, 0x0030, 0x0038 };
        uint8_t InterruptJumpVectors[5] = {0x0040, 0x0048, 0x0050, 0x0058, 0x0060};

        MMU* mmu;

        CPU(MMU* mmu);
        Register AF, BC, DE, HL;

        void Initialise();
        void Cycle();
        void Execute(uint8_t instruction);
        
        void DebugRegisters();
        void DebugInstruction(uint8_t inst);

        typedef void (CPU::*Opcode)(void);
        Opcode Opcodes[0x100] = {0};
        void PopulateOpcodes();
    
    private:
        bool IME = false;
        bool stopped = false;
        bool halted = false;

        std::bitset<8> interruptEnables;
        std::bitset<8> interruptFlags;

        void HandleInterrupts();
        void SetInterrupt(uint8_t interrupt);
        void ExecuteInterrupt(uint8_t interrupt);

        void SetBit(uint8_t &byte, uint8_t bit);
        void ClearBit(uint8_t &byte, uint8_t bit);
        void ToggleBit(uint8_t &byte, uint8_t bit);
        uint8_t GetBit(uint8_t byte, uint8_t bit);

        void PUSH_STACK(Register &reg);
        void PUSH_STACK16(uint16_t value);
        void POP_STACK(Register &reg);
        void POP_STACK16();
        uint16_t READ_STACK();

        void LD(uint8_t &reg1, uint8_t reg2);
        void LD(uint16_t address, uint8_t reg);
        void LD(uint8_t &reg1, uint16_t address);
        void ADD(uint8_t reg2);
        void ADD_HL(uint16_t reg2);
        void ADD_SP();
        void ADC(uint8_t reg2);
        void SUB(uint8_t reg2);
        void SBC(uint8_t reg2);
        void AND(uint8_t reg2);
        void XOR(uint8_t reg2);
        void OR(uint8_t reg2);
        void CP(uint8_t reg);
        void INC(uint8_t &reg);
        void INC(Register reg);
        void INC_SP();
        void DEC(uint8_t &reg);
        void DEC(Register reg);
        void DEC_SP();
        void RET();
        void RST(uint8_t byte);
        void CALL();
        void JR();
        void JP();
        void JP_HL();
        void RL(uint8_t &reg, bool isA);
        void RLC(uint8_t &reg, bool isA);
        void RR(uint8_t &reg, bool isA);
        void RRC(uint8_t &reg, bool isA);
        void SLA(uint8_t &reg);
        void SRA(uint8_t &reg);
        void SRL(uint8_t &reg);
        void SWAP(uint8_t &reg);
        void BIT(uint8_t &reg, uint8_t bit);
        void RES(uint8_t &reg, uint8_t bit);
        void SET(uint8_t &reg, uint8_t bit);
        void DI();
        void EI();
        void STOP();
        void HALT();
        void NOP();
        void SCF();
        void CPL();
        void CCF();
        void DAA();

        void Opcode0x00();
        void Opcode0x01();
        void Opcode0x02();
        void Opcode0x03();
        void Opcode0x04();
        void Opcode0x05();
        void Opcode0x06();
        void Opcode0x07();
        void Opcode0x08();
        void Opcode0x09();
        void Opcode0x0A();
        void Opcode0x0B();
        void Opcode0x0C();
        void Opcode0x0D();
        void Opcode0x0E();
        void Opcode0x0F();
        void Opcode0x10();
        void Opcode0x11();
        void Opcode0x12();
        void Opcode0x13();
        void Opcode0x14();
        void Opcode0x15();
        void Opcode0x16();
        void Opcode0x17();
        void Opcode0x18();
        void Opcode0x19();
        void Opcode0x1A();
        void Opcode0x1B();
        void Opcode0x1C();
        void Opcode0x1D();
        void Opcode0x1E();
        void Opcode0x1F();
        void Opcode0x20();
        void Opcode0x21();
        void Opcode0x22();
        void Opcode0x23();
        void Opcode0x24();
        void Opcode0x25();
        void Opcode0x26();
        void Opcode0x27();
        void Opcode0x28();
        void Opcode0x29();
        void Opcode0x2A();
        void Opcode0x2B();
        void Opcode0x2C();
        void Opcode0x2D();
        void Opcode0x2E();
        void Opcode0x2F();
        void Opcode0x30();
        void Opcode0x31();
        void Opcode0x32();
        void Opcode0x33();
        void Opcode0x34();
        void Opcode0x35();
        void Opcode0x36();
        void Opcode0x37();
        void Opcode0x38();
        void Opcode0x39();
        void Opcode0x3A();
        void Opcode0x3B();
        void Opcode0x3C();
        void Opcode0x3D();
        void Opcode0x3E();
        void Opcode0x3F();
        void Opcode0x40();
        void Opcode0x41();
        void Opcode0x42();
        void Opcode0x43();
        void Opcode0x44();
        void Opcode0x45();
        void Opcode0x46();
        void Opcode0x47();
        void Opcode0x48();
        void Opcode0x49();
        void Opcode0x4A();
        void Opcode0x4B();
        void Opcode0x4C();
        void Opcode0x4D();
        void Opcode0x4E();
        void Opcode0x4F();
        void Opcode0x50();
        void Opcode0x51();
        void Opcode0x52();
        void Opcode0x53();
        void Opcode0x54();
        void Opcode0x55();
        void Opcode0x56();
        void Opcode0x57();
        void Opcode0x58();
        void Opcode0x59();
        void Opcode0x5A();
        void Opcode0x5B();
        void Opcode0x5C();
        void Opcode0x5D();
        void Opcode0x5E();
        void Opcode0x5F();
        void Opcode0x60();
        void Opcode0x61();
        void Opcode0x62();
        void Opcode0x63();
        void Opcode0x64();
        void Opcode0x65();
        void Opcode0x66();
        void Opcode0x67();
        void Opcode0x68();
        void Opcode0x69();
        void Opcode0x6A();
        void Opcode0x6B();
        void Opcode0x6C();
        void Opcode0x6D();
        void Opcode0x6E();
        void Opcode0x6F();
        void Opcode0x70();
        void Opcode0x71();
        void Opcode0x72();
        void Opcode0x73();
        void Opcode0x74();
        void Opcode0x75();
        void Opcode0x76();
        void Opcode0x77();
        void Opcode0x78();
        void Opcode0x79();
        void Opcode0x7A();
        void Opcode0x7B();
        void Opcode0x7C();
        void Opcode0x7D();
        void Opcode0x7E();
        void Opcode0x7F();
        void Opcode0x80();
        void Opcode0x81();
        void Opcode0x82();
        void Opcode0x83();
        void Opcode0x84();
        void Opcode0x85();
        void Opcode0x86();
        void Opcode0x87();
        void Opcode0x88();
        void Opcode0x89();
        void Opcode0x8A();
        void Opcode0x8B();
        void Opcode0x8C();
        void Opcode0x8D();
        void Opcode0x8E();
        void Opcode0x8F();
        void Opcode0x90();
        void Opcode0x91();
        void Opcode0x92();
        void Opcode0x93();
        void Opcode0x94();
        void Opcode0x95();
        void Opcode0x96();
        void Opcode0x97();
        void Opcode0x98();
        void Opcode0x99();
        void Opcode0x9A();
        void Opcode0x9B();
        void Opcode0x9C();
        void Opcode0x9D();
        void Opcode0x9E();
        void Opcode0x9F();
        void Opcode0xA0();
        void Opcode0xA1();
        void Opcode0xA2();
        void Opcode0xA3();
        void Opcode0xA4();
        void Opcode0xA5();
        void Opcode0xA6();
        void Opcode0xA7();
        void Opcode0xA8();
        void Opcode0xA9();
        void Opcode0xAA();
        void Opcode0xAB();
        void Opcode0xAC();
        void Opcode0xAD();
        void Opcode0xAE();
        void Opcode0xAF();
        void Opcode0xB0();
        void Opcode0xB1();
        void Opcode0xB2();
        void Opcode0xB3();
        void Opcode0xB4();
        void Opcode0xB5();
        void Opcode0xB6();
        void Opcode0xB7();
        void Opcode0xB8();
        void Opcode0xB9();
        void Opcode0xBA();
        void Opcode0xBB();
        void Opcode0xBC();
        void Opcode0xBD();
        void Opcode0xBE();
        void Opcode0xBF();
        void Opcode0xC0();
        void Opcode0xC1();
        void Opcode0xC2();
        void Opcode0xC3();
        void Opcode0xC4();
        void Opcode0xC5();
        void Opcode0xC6();
        void Opcode0xC7();
        void Opcode0xC8();
        void Opcode0xC9();
        void Opcode0xCA();
        void Opcode0xCB();
        void Opcode0xCC();
        void Opcode0xCD();
        void Opcode0xCE();
        void Opcode0xCF();
        void Opcode0xD0();
        void Opcode0xD1();
        void Opcode0xD2();
        void Opcode0xD3();
        void Opcode0xD4();
        void Opcode0xD5();
        void Opcode0xD6();
        void Opcode0xD7();
        void Opcode0xD8();
        void Opcode0xD9();
        void Opcode0xDA();
        void Opcode0xDB();
        void Opcode0xDC();
        void Opcode0xDD();
        void Opcode0xDE();
        void Opcode0xDF();
        void Opcode0xE0();
        void Opcode0xE1();
        void Opcode0xE2();
        void Opcode0xE3();
        void Opcode0xE4();
        void Opcode0xE5();
        void Opcode0xE6();
        void Opcode0xE7();
        void Opcode0xE8();
        void Opcode0xE9();
        void Opcode0xEA();
        void Opcode0xEB();
        void Opcode0xEC();
        void Opcode0xED();
        void Opcode0xEE();
        void Opcode0xEF();
        void Opcode0xF0();
        void Opcode0xF1();
        void Opcode0xF2();
        void Opcode0xF3();
        void Opcode0xF4();
        void Opcode0xF5();
        void Opcode0xF6();
        void Opcode0xF7();
        void Opcode0xF8();
        void Opcode0xF9();
        void Opcode0xFA();
        void Opcode0xFB();
        void Opcode0xFC();
        void Opcode0xFD();
        void Opcode0xFE();
        void Opcode0xFF();

};

