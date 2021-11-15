#include <iostream>
#include "decoder.h"
#include <rv32i.h>

Decoder::Decoder() {
    rv32i_ = std::make_unique<Rv32i>();
};

bool Decoder::DecodeInstruction(uint32_t instr, UInstrPtr uinstr) {
    return rv32i_->DecodeInstructions(instr, uinstr);
};