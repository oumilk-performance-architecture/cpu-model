#include <vector>
#include "rv32i.h"
#include <uinstr.h>

Rv32i::Rv32i() {
};

//bool Rv32i::DecodeInstructions(uint16_t instr, UInstrPtr uinstr) {
//    throw "Invalid instruction size fo RV32I\n";
//}

bool Rv32i::doDecodeInstructions(uint32_t instr, UInstrPtr uinstr) {//, Uop uop) {
    std::vector<Decoder32BTable>::iterator iter;
    auto decodeInstr = [&instr](const Decoder32BTable opcode) {
        return (instr & opcode.mask) == opcode.match; 
    };
    iter = std::find_if(opcode_table.begin(), opcode_table.end(), decodeInstr);
    if (iter != opcode_table.end()) {
        uinstr->SetOpcode(iter->uop);  // uop
        (this->*(iter->genUop))(instr, uinstr);
        return true;
    } 
    return false;
};

/* U Type - Long immediates */
void Rv32i::DecodeU(uint32_t instr, UInstrPtr uinstr) {
    uinstr->SetRd(Mask11to7(instr));
    uinstr->SetImmed(Mask31to12(instr));
};

/* I Type - Short immediates and loads */
void Rv32i::DecodeI(uint32_t instr, UInstrPtr uinstr) {
    uinstr->SetRs1(Mask19to15(instr));
    uinstr->SetRd(Mask11to7(instr));
    uinstr->SetImmed(Mask31to20(instr));
};
void Rv32i::DecodeIShift(uint32_t instr, UInstrPtr uinstr) {
    uinstr->SetRs1(Mask19to15(instr));
    uinstr->SetRd(Mask11to7(instr));
    uinstr->SetImmed(Mask24to20(instr));
};

void Rv32i::DecodeEcall(uint32_t instr, UInstrPtr uinstr) {
};

/* B Type - Branches */
void Rv32i::DecodeB(uint32_t instr, UInstrPtr uinstr) {
    uinstr->SetRs1(Mask19to15(instr));
    uinstr->SetRs2(Mask24to20(instr));
    uinstr->SetImmed(Mask32BImmed(instr));
};

/* J Type - Unconditional Jumps */
void Rv32i::DecodeJal(uint32_t instr, UInstrPtr uinstr) {
    uinstr->SetRd(Mask11to7(instr));
    uinstr->SetImmed(Mask31to12(instr));
};

/* R Type - Register to Register Operation */
void Rv32i::DecodeR(uint32_t instr, UInstrPtr uinstr) {
    uinstr->SetRd(Mask11to7(instr));
    uinstr->SetRs1(Mask19to15(instr));
    uinstr->SetRs2(Mask24to20(instr));
};

/* S Type - Stores */
void Rv32i::DecodeS(uint32_t instr, UInstrPtr uinstr) {
    uinstr->SetRs1(Mask19to15(instr));
    uinstr->SetRs2(Mask24to20(instr));
    uinstr->SetImmed(Mask32BImmed(instr));
};

