#ifndef ARMV6M_H
#define ARMV6M_H

#include <vector>
#include <uinstr.h>
#include "../isa.h"


class Armv6m : public Isa {
    public:
        Armv6m();
        ~Armv6m();
        UInstr DecodeInstructions(uint16_t instr);

        typedef UInstr (Armv6m::*decode)(uint16_t instr);
        struct Decoder16BTable {
            uint16_t mask;
            uint16_t match;
            decode genUop;
        };
    private:
        UInstr Decode_adcs();
        UInstr DecodeLslsImmed(uint16_t instr);
        UInstr DecodeLslsReg(uint16_t instr);

        std::vector<Decoder16BTable> opcode_table = {
            {BITMASK16(11), OPCODE(0b00000, 11),     &Armv6m::DecodeLslsImmed},
            {BITMASK16(6),  OPCODE(0b0100000010, 6), &Armv6m::DecodeLslsReg}
        };
    
};


#endif // ARMV6M_H