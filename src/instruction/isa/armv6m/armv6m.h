#ifndef ARMV6M_H
#define ARMV6M_H

#include <vector>
#include <uinstr.h>
#include "../isa.h"


class Armv6m : public Isa {
    public:
        Armv6m();
        bool DecodeInstructions(uint16_t instr, UInstrPtr uinstr);//, Uop uop);

        typedef void (Armv6m::*decode)(uint16_t instr, UInstrPtr uop);
        struct Decoder16BTable {
            uint16_t mask;
            uint16_t match;
            decode genUop;
            Uop uop;
        };
    private:
        // SHIFT
        void DecodeLslsImmed(uint16_t instr, UInstrPtr uinstr);
        void DecodeLslsReg(uint16_t instr, UInstrPtr uinstr);
        void DecodeAsrsImmed(uint16_t instr, UInstrPtr uinstr);
        void DecodeAsrsReg(uint16_t instr, UInstrPtr uinstr);
        void DecodeLsrsImmed(uint16_t instr, UInstrPtr uinstr);
        void DecodeLsrsReg(uint16_t instr, UInstrPtr uinstr);
        // ADD
        void DecodeAdcs(uint16_t instr, UInstrPtr uinstr);
        void DecodeAddsImmedT1(uint16_t instr, UInstrPtr uinstr);
        void DecodeAddsImmedT2(uint16_t instr, UInstrPtr uinstr);
        void DecodeAddsRegT1(uint16_t instr, UInstrPtr uinstr);
        void DecodeAddRegT2(uint16_t instr, UInstrPtr uinstr);
        void DecodeAddSpImmedT1(uint16_t instr, UInstrPtr uinstr);
        void DecodeAddSpImmedT2(uint16_t instr, UInstrPtr uinstr);
        void DecodeAddSpRegT1(uint16_t instr, UInstrPtr uinstr);
        void DecodeAddSpRegT2(uint16_t instr, UInstrPtr uinstr);
        void DecodeAdr(uint16_t instr, UInstrPtr uinstr);
        // LOGICAL
        void DecodeAnds(uint16_t instr, UInstrPtr uinstr);
        void DecodeBics(uint16_t instr, UInstrPtr uinstr);
        void DecodeEors(uint16_t instr, UInstrPtr uinstr);
        void DecodeMvns(uint16_t instr, UInstrPtr uinstr);
        void DecodeOrrs(uint16_t instr, UInstrPtr uinstr);
        void DecodeTst(uint16_t instr, UInstrPtr uinstr);
        // Branch
        void DecodeBT1(uint16_t instr, UInstrPtr uinstr);
        void DecodeBT2(uint16_t instr, UInstrPtr uinstr);
        void DecodeBlx(uint16_t instr, UInstrPtr uinstr);
        void DecodeBx(uint16_t instr, UInstrPtr uinstr);
        // State Change
        void DecodeBkpt(uint16_t instr, UInstrPtr uinstr);
        // Compare
        void DecodeCmn(uint16_t instr, UInstrPtr uinstr);
        void DecodeCmpImmed(uint16_t instr, UInstrPtr uinstr);
        void DecodeCmpReg(uint16_t instr, UInstrPtr uinstr);
        // Load
        void DecodeLdm(uint16_t instr, UInstrPtr uinstr);
        void DecodeLdrImmedT1(uint16_t instr, UInstrPtr uinstr);
        void DecodeLdrImmedT2(uint16_t instr, UInstrPtr uinstr);
        void DecodeLdrLit(uint16_t instr, UInstrPtr uinstr);
        void DecodeLdrReg(uint16_t instr, UInstrPtr uinstr);
        void DecodeLdrbImmed(uint16_t instr, UInstrPtr uinstr);
        void DecodeLdrbReg(uint16_t instr, UInstrPtr uinstr);
        void DecodeLdrhImmed(uint16_t instr, UInstrPtr uinstr);
        void DecodeLdrhReg(uint16_t instr, UInstrPtr uinstr);
        void DecodeLdrsb(uint16_t instr, UInstrPtr uinstr);
        void DecodeLdrsh(uint16_t instr, UInstrPtr uinstr);
        // Store
        void DecodeStm(uint16_t instr, UInstrPtr uinstr);
        void DecodeStrImmedT1(uint16_t instr, UInstrPtr uinstr);
        void DecodeStrImmedT2(uint16_t instr, UInstrPtr uinstr);
        void DecodeStrReg(uint16_t instr, UInstrPtr uinstr);
        void DecodeStrbImmed(uint16_t instr, UInstrPtr uinstr);
        void DecodeStrbReg(uint16_t instr, UInstrPtr uinstr);
        void DecodeStrhImmed(uint16_t instr, UInstrPtr uinstr);
        void DecodeStrhReg(uint16_t instr, UInstrPtr uinstr);
        // Move
        void DecodeMovsImmed(uint16_t instr, UInstrPtr uinstr);
        void DecodeMovRegT1(uint16_t instr, UInstrPtr uinstr);
        void DecodeMovsRegT2(uint16_t instr, UInstrPtr uinstr);
        // Multiply
        void DecodeMuls(uint16_t instr, UInstrPtr uinstr);
        // Hint
        void DecodeNop(uint16_t instr, UInstrPtr uinstr);
        void DecodeSev(uint16_t instr, UInstrPtr uinstr);
        void DecodeWfe(uint16_t instr, UInstrPtr uinstr);
        void DecodeWfi(uint16_t instr, UInstrPtr uinstr);
        void DecodeYield(uint16_t instr, UInstrPtr uinstr);
        // Pop
        void DecodePop(uint16_t instr, UInstrPtr uinstr);
        // Push
        void DecodePush(uint16_t instr, UInstrPtr uinstr);
        // Reverse
        void DecodeRev(uint16_t instr, UInstrPtr uinstr);
        void DecodeRev16(uint16_t instr, UInstrPtr uinstr);
        void DecodeRevsh(uint16_t instr, UInstrPtr uinstr);
        // Rotate
        void DecodeRors(uint16_t instr, UInstrPtr uinstr);
        // Subtract
        void DecodeRsbs(uint16_t instr, UInstrPtr uinstr);
        void DecodeSbcs(uint16_t instr, UInstrPtr uinstr);
        void DecodeSubsImmedT1(uint16_t instr, UInstrPtr uinstr);
        void DecodeSubsImmedT2(uint16_t instr, UInstrPtr uinstr);
        void DecodeSubsReg(uint16_t instr, UInstrPtr uinstr);
        void DecodeSub(uint16_t instr, UInstrPtr uinstr);
        // State Change
        void DecodeSvc(uint16_t instr, UInstrPtr uinstr);
        // Extend
        void DecodeSxtb(uint16_t instr, UInstrPtr uinstr);
        void DecodeSxth(uint16_t instr, UInstrPtr uinstr);
        void DecodeUxtb(uint16_t instr, UInstrPtr uinstr);
        void DecodeUxth(uint16_t instr, UInstrPtr uinstr);


        
        
        // TODO: Need to check for multiple match and handle this
        std::vector<Decoder16BTable> opcode_table = {
            // Shift
            //{BitMask(15,11), Opcode(0b00000, 11),          &Armv6m::DecodeLslsImmed,    Uop::LSL_imm},
            //{BitMask(15,6),  Opcode(0b0100000010, 6),      &Armv6m::DecodeLslsReg,      Uop::LSL_reg},
            //{BitMask(15,11), Opcode(0b00010, 11),          &Armv6m::DecodeAsrsImmed,    NULL},
            //{BitMask(15,6),  Opcode(0b0100000100, 6),      &Armv6m::DecodeAsrsReg,      NULL},
            //{BitMask(15,11), Opcode(0b00001, 11),          &Armv6m::DecodeLsrsImmed,    NULL},
            //{BitMask(15,6),  Opcode(0b0100000011, 6),      &Armv6m::DecodeLsrsReg,      NULL},
            // Add
            {BitMask(15,6),  Opcode(0b0100000101, 6),      &Armv6m::DecodeAdcs,         Uop::ADCS},
            {BitMask(15,9),  Opcode(0b0001110, 9),         &Armv6m::DecodeAddsImmedT1,  Uop::ADDS_imm},
            {BitMask(15,11), Opcode(0b00110, 11),          &Armv6m::DecodeAddsImmedT2,  Uop::ADDS_imm},
            {BitMask(15,9),  Opcode(0b0001100, 9),         &Armv6m::DecodeAddsRegT1,    Uop::ADDS_reg},  // or Uop::ADD_PC_reg
            {BitMask(15,8),  Opcode(0b01000100, 8),        &Armv6m::DecodeAddRegT2,     Uop::ADD_reg},
            {BitMask(15,11), Opcode(0b10101, 11),          &Armv6m::DecodeAddSpImmedT1, Uop::ADD_SP_imm_t1},
            {BitMask(15,7),  Opcode(0b101100000, 7),       &Armv6m::DecodeAddSpImmedT2, Uop::ADD_SP_imm_t2},
            //{BitMask(15,7) | BitMask(6,3),  Opcode(0b0100010001101, 3),     &Armv6m::DecodeAddSpRegT1,    Uop::ADD_SP_reg_t1},
            //{BitMask(15,7) | BitMask(2,0),  Opcode(0b0100010010000101, 0),  &Armv6m::DecodeAddSpRegT2,    Uop::ADD_SP_reg_t2},
            //{BitMask(15,11), Opcode(0b10100, 11),          &Armv6m::DecodeAdr,          Uop::ADR_imm},
            // Logical
            //{BitMask(15,6),  Opcode(0b0100000000,6),       &Armv6m::DecodeAnds,         NULL},
            //{BitMask(15,6),  Opcode(0b0100001110,6),       &Armv6m::DecodeBics,         NULL},
            //{BitMask(15,6),  Opcode(0b0100000001,6),       &Armv6m::DecodeEors,         NULL},
            //{BitMask(15,6),  Opcode(0b0100001111,6),       &Armv6m::DecodeMvns,         NULL},
            //{BitMask(15,6),  Opcode(0b0100001100,6),       &Armv6m::DecodeOrrs,         NULL},
            //{BitMask(15,6),  Opcode(0b0100001000,6),       &Armv6m::DecodeTst,          NULL},
            // Branch
            //{BitMask(15,12), Opcode(0b1101,12),            &Armv6m::DecodeBT1,          NULL}, // SVC would match
            //{BitMask(15,11), Opcode(0b11100,11),           &Armv6m::DecodeBT2,          NULL},
            //{BitMask(15,7),  Opcode(0b010001111,7),        &Armv6m::DecodeBlx,          NULL},
            //{BitMask(15,7),  Opcode(0b010001110,7),        &Armv6m::DecodeBx,           NULL},
            //{BitMask(15,8),  Opcode(0b10111110,8),         &Armv6m::DecodeBkpt,         NULL},
            //{BitMask(15,6),  Opcode(0b0100001011,6),       &Armv6m::DecodeCmn,          NULL},
            //{BitMask(15,11), Opcode(0b00101,11),           &Armv6m::DecodeCmpImmed,     NULL},
            //{BitMask(15,6),  Opcode(0b0100001010,6),       &Armv6m::DecodeCmpReg,       NULL},
            // Load
            //{BitMask(15,11), Opcode(0b11001,11),           &Armv6m::DecodeLdm,          NULL},
            //{BitMask(15,11), Opcode(0b01101,11),           &Armv6m::DecodeLdrImmedT1,   NULL},
            //{BitMask(15,11), Opcode(0b10011,11),           &Armv6m::DecodeLdrImmedT2,   NULL},
            {BitMask(15,11), Opcode(0b01001,11),           &Armv6m::DecodeLdrLit,       Uop::ADR_lit},
            //{BitMask(15,9),  Opcode(0b0101100,9),          &Armv6m::DecodeLdrReg,       NULL},
            //{BitMask(15,11), Opcode(0b01111,11),           &Armv6m::DecodeLdrbImmed,    NULL},
            //{BitMask(15,9),  Opcode(0b0101110,9),          &Armv6m::DecodeLdrbReg,      NULL},
            //{BitMask(15,11), Opcode(0b10001,11),           &Armv6m::DecodeLdrhImmed,    NULL},
            //{BitMask(15,9),  Opcode(0b0101101,9),          &Armv6m::DecodeLdrhReg,      NULL},
            //{BitMask(15,9),  Opcode(0b0101011,9),          &Armv6m::DecodeLdrsb,        NULL},
            //{BitMask(15,9),  Opcode(0b0101111,9),          &Armv6m::DecodeLdrsh,        NULL},
            // Store
            //{BitMask(15,11), Opcode(0b11000,9),            &Armv6m::DecodeStm,          NULL},
            //{BitMask(15,11), Opcode(0b01100,9),            &Armv6m::DecodeStrImmedT1,   NULL},
            //{BitMask(15,11), Opcode(0b10010,9),            &Armv6m::DecodeStrImmedT2,   NULL},
            //{BitMask(15,9),  Opcode(0b0101000,9),          &Armv6m::DecodeStrReg,       NULL},
            //{BitMask(15,11), Opcode(0b01110,11),           &Armv6m::DecodeStrbImmed,    NULL},
            //{BitMask(15,9),  Opcode(0b0101010,9),          &Armv6m::DecodeStrbReg,      NULL},
            //{BitMask(15,11), Opcode(0b10000,11),           &Armv6m::DecodeStrhImmed,    NULL},
            //{BitMask(15,9),  Opcode(0b0101001,9),          &Armv6m::DecodeStrhReg,      NULL},
            // Move
            //{BitMask(15,11), Opcode(0b00100,11),           &Armv6m::DecodeMovsImmed,    Uop::MOVS_imm},
            //{BitMask(15,8),  Opcode(0b01000110,8),         &Armv6m::DecodeMovRegT1,     Uop::MOV_reg},
            //{BitMask(15,6),  Opcode(0b0000000000,6),       &Armv6m::DecodeMovsRegT2,    Uop::MOVS_reg},
            // Multiply
            //{BitMask(15,6),  Opcode(0b0100001101,6),       &Armv6m::DecodeMuls,         NULL},
            // Hint
            //{BitMask(15,0),  Opcode(0b1011111100000000,0), &Armv6m::DecodeNop,          NULL},
            //{BitMask(15,0),  Opcode(0b1011111101000000,0), &Armv6m::DecodeSev,          NULL},
            //{BitMask(15,0),  Opcode(0b1011111100100000,0), &Armv6m::DecodeWfe,          NULL},
            //{BitMask(15,0),  Opcode(0b1011111100110000,0), &Armv6m::DecodeWfi,          NULL},
            //{BitMask(15,0),  Opcode(0b1011111100010000,0), &Armv6m::DecodeYield,        NULL},
            // Pop
            //{BitMask(15,9),  Opcode(0b1011110,9),          &Armv6m::DecodePop,          NULL},
            // Push
            //{BitMask(15,9),  Opcode(0b1011010,9),          &Armv6m::DecodePush,         NULL},
            // Reverse
            //{BitMask(15,6),  Opcode(0b1011101000,6),       &Armv6m::DecodeRev,          NULL},
            //{BitMask(15,6),  Opcode(0b1011101001,6),       &Armv6m::DecodeRev16,        NULL},
            //{BitMask(15,6),  Opcode(0b1011101011,6),       &Armv6m::DecodeRevsh,        NULL},
            // Rotate
            //{BitMask(15,6),  Opcode(0b0100000111,6),       &Armv6m::DecodeRors,         NULL},
            // Subtract
            //{BitMask(15,6),  Opcode(0b0100001001,6),       &Armv6m::DecodeRsbs,         NULL},
            //{BitMask(15,6),  Opcode(0b0100000110,6),       &Armv6m::DecodeSbcs,         NULL},
            //{BitMask(15,9),  Opcode(0b0001111,9),          &Armv6m::DecodeSubsImmedT1,  NULL},
            //{BitMask(15,11), Opcode(0b00111,11),           &Armv6m::DecodeSubsImmedT2,  NULL},
            //{BitMask(15,9),  Opcode(0b0001101,9),          &Armv6m::DecodeSubsReg,      NULL},
            //{BitMask(15,7),  Opcode(0b101100001,7),        &Armv6m::DecodeSub,          NULL},
            // State Change
            //{BitMask(15,8),  Opcode(0b11011111,8),         &Armv6m::DecodeSvc,          NULL},
            // Extend
            //{BitMask(15,6),  Opcode(0b1011001001,6),       &Armv6m::DecodeSxtb,         NULL},
            //{BitMask(15,6),  Opcode(0b1011001000,6),       &Armv6m::DecodeSxth,         NULL},
            //{BitMask(15,6),  Opcode(0b1011001011,6),       &Armv6m::DecodeUxtb,         NULL},
            //{BitMask(15,6),  Opcode(0b1011001010,6),       &Armv6m::DecodeUxth,         NULL}*/
        };
    
};


#endif // ARMV6M_H