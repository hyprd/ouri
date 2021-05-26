#include "cpu.h"
#include "opcodes.h"

Register::Register(){}

Register::Register(uint8_t *hi, uint8_t *lo){ 
    high = hi; 
    low = lo;
}

uint16_t Register::GetRegister() { 
    return *high << 8 | (*low & 0x00FF);    
}

void Register::SetRegister(uint16_t value) {
    *low = value & 0x00FF;
    *high = value >> 8;
}

CPU::CPU(MMU* _mmu) {
    mmu = _mmu;
    A = B = C = D = E = F = H = L = 0x00;
    SP = PC = 0x0000;
    AF = Register(&A, &F);
    BC = Register(&B, &C);
    DE = Register(&D, &E);
    HL = Register(&H, &L);

    Initialise();
    PopulateOpcodes();
    PopulateExtendedOpcodes();
} 

void CPU::Initialise() {
    std::cout << "\n[INFO] Initialising CPU..." << std::endl;
    cycles = 0;
    PC = 0x0100;
    AF.SetRegister(0x01B0);
    BC.SetRegister(0x0013);
    DE.SetRegister(0x00D8);
    HL.SetRegister(0x014D);
    mmu->SetMemory(0xFF05, 0x00);
    mmu->SetMemory(0xFF06, 0x00);
    mmu->SetMemory(0xFF07, 0x00);
    mmu->SetMemory(0xFF10, 0x80);
    mmu->SetMemory(0xFF11, 0xBF);
    mmu->SetMemory(0xFF12, 0xF3);
    mmu->SetMemory(0xFF14, 0xBF);
    mmu->SetMemory(0xFF16, 0x3F);
    mmu->SetMemory(0xFF17, 0x00);
    mmu->SetMemory(0xFF19, 0xBF);
    mmu->SetMemory(0xFF1A, 0x7F);
    mmu->SetMemory(0xFF1B, 0xFF);
    mmu->SetMemory(0xFF1C, 0x9F);
    mmu->SetMemory(0xFF1E, 0xBF);
    mmu->SetMemory(0xFF20, 0xFF);
    mmu->SetMemory(0xFF21, 0x00);
    mmu->SetMemory(0xFF22, 0x00);
    mmu->SetMemory(0xFF23, 0xBF);
    mmu->SetMemory(0xFF24, 0x77);
    mmu->SetMemory(0xFF25, 0xF3);
    mmu->SetMemory(0xFF26, 0xF1);
    mmu->SetMemory(0xFF40, 0x91);
    mmu->SetMemory(0xFF42, 0x00);
    mmu->SetMemory(0xFF43, 0x00);
    mmu->SetMemory(0xFF45, 0x00);
    mmu->SetMemory(0xFF47, 0xFC);
    mmu->SetMemory(0xFF48, 0xFF);
    mmu->SetMemory(0xFF49, 0xFF);
    mmu->SetMemory(0xFF4A, 0x00);
    mmu->SetMemory(0xFF4B, 0x00);
    mmu->SetMemory(0xFFFF, 0x00);
    SP = 0xFFFE;
    std::cout << "[INFO] Done." << std::endl;
}

void CPU::Cycle() {
    Execute(mmu->ReadMemory(PC));
}

void CPU::Execute(uint8_t instruction) {
    DebugInstruction(instruction);
    std::cout << "\nPC: " << PC << "\t";
    std::cout << "\nCycles: " << std::dec << cycles << std::endl;
    if(!extended) {
        (this->*Opcodes[instruction])();
        cycles += opcodeTimings[instruction];
    } else {
        (this->*ExtendedOpcodes[instruction])();
        cycles += opcodeExtendedTimings[instruction];
        extended = false;
    }
    if(!halted) PC++;
    HandleInterrupts();
}
