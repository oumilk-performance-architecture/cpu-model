#include <vector>
#include "armv6m.h"
#include <uinstr.h>
#include <iostream>


Armv6m::Armv6m() {
};

Armv6m::~Armv6m() {

};

UInstr Armv6m::DecodeInstructions(uint16_t instr) {
    std::vector<Decoder16BTable>::iterator iter;
    auto decodeInstr = [&instr](const Decoder16BTable opcode) {
        return (instr & opcode.mask) == opcode.match; 
    };
    iter = std::find_if(opcode_table.begin(), opcode_table.end(), decodeInstr);
    
    if (iter != opcode_table.end()) {
        return (this->*(iter->genUop))(instr);
    } 
    UInstr uop;
    return uop;
};

UInstr Armv6m::DecodeLslsImmed(uint16_t instr) {
    UInstr uop;
    uop.SetRd(DATAMASK16(instr, 2, 0));
    uop.SetRm(DATAMASK16(instr, 5, 3));
    uop.SetImmed(DATAMASK16(instr, 10, 6));
    return uop;
}

UInstr Armv6m::DecodeLslsReg(uint16_t instr) {
    UInstr uop;
    uop.SetRd(DATAMASK16(instr, 2, 0));
    uop.SetRm(DATAMASK16(instr, 5, 3));
    return uop;
}

UInstr Armv6m::Decode_adcs() {
    UInstr execute;
    return execute;
}