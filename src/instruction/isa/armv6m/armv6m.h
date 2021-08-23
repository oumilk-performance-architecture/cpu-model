#ifndef ARMV6M_H
#define ARMV6M_H

#include <vector>
#include <uinstr.h>
#include "../isa.h"


class Armv6m : public Isa {
    public:
        Armv6m();
        ~Armv6m();
        bool DecodeInstructions(uint16_t instr, UInstrPtr uop);

        typedef void (Armv6m::*decode)(uint16_t instr, UInstrPtr uop);
        struct Decoder16BTable {
            uint16_t mask;
            uint16_t match;
            decode genUop;
        };
    private:
        // SHIFT
        void DecodeLslsImmed(uint16_t instr, UInstrPtr uop);
        void DecodeLslsReg(uint16_t instr, UInstrPtr uop);
        void DecodeAsrsImmed(uint16_t instr, UInstrPtr uop);
        void DecodeAsrsReg(uint16_t instr, UInstrPtr uop);
        void DecodeLsrsImmed(uint16_t instr, UInstrPtr uop);
        void DecodeLsrsReg(uint16_t instr, UInstrPtr uop);
        // ADD
        void DecodeAdcs(uint16_t instr, UInstrPtr uop);
        void DecodeAddsImmedT1(uint16_t instr, UInstrPtr uop);
        void DecodeAddsImmedT2(uint16_t instr, UInstrPtr uop);
        void DecodeAddsRegT1(uint16_t instr, UInstrPtr uop);
        void DecodeAddRegT2(uint16_t instr, UInstrPtr uop);
        void DecodeAddSpImmedT1(uint16_t instr, UInstrPtr uop);
        void DecodeAddSpImmedT2(uint16_t instr, UInstrPtr uop);
        void DecodeAddSpRegT1(uint16_t instr, UInstrPtr uop);
        void DecodeAddSpRegT2(uint16_t instr, UInstrPtr uop);
        void DecodeAdr(uint16_t instr, UInstrPtr uop);
        // LOGICAL
        void DecodeAnds(uint16_t instr, UInstrPtr uop);
        void DecodeBics(uint16_t instr, UInstrPtr uop);
        void DecodeEors(uint16_t instr, UInstrPtr uop);
        void DecodeMvns(uint16_t instr, UInstrPtr uop);
        void DecodeOrrs(uint16_t instr, UInstrPtr uop);
        void DecodeTst(uint16_t instr, UInstrPtr uop);
        // Branch
        void DecodeBT1(uint16_t instr, UInstrPtr uop);
        void DecodeBT2(uint16_t instr, UInstrPtr uop);
        void DecodeBlx(uint16_t instr, UInstrPtr uop);
        void DecodeBx(uint16_t instr, UInstrPtr uop);
        // State Change
        void DecodeBkpt(uint16_t instr, UInstrPtr uop);
        // Compare
        void DecodeCmn(uint16_t instr, UInstrPtr uop);
        void DecodeCmpImmed(uint16_t instr, UInstrPtr uop);
        void DecodeCmpReg(uint16_t instr, UInstrPtr uop);
        // Load
        void DecodeLdm(uint16_t instr, UInstrPtr uop);
        void DecodeLdrImmedT1(uint16_t instr, UInstrPtr uop);
        void DecodeLdrImmedT2(uint16_t instr, UInstrPtr uop);
        void DecodeLdrLit(uint16_t instr, UInstrPtr uop);
        void DecodeLdrReg(uint16_t instr, UInstrPtr uop);
        void DecodeLdrbImmed(uint16_t instr, UInstrPtr uop);
        void DecodeLdrbReg(uint16_t instr, UInstrPtr uop);
        void DecodeLdrhImmed(uint16_t instr, UInstrPtr uop);
        void DecodeLdrhReg(uint16_t instr, UInstrPtr uop);
        void DecodeLdrsb(uint16_t instr, UInstrPtr uop);
        void DecodeLdrsh(uint16_t instr, UInstrPtr uop);
        // Store
        void DecodeStm(uint16_t instr, UInstrPtr uop);
        void DecodeStrImmedT1(uint16_t instr, UInstrPtr uop);
        void DecodeStrImmedT2(uint16_t instr, UInstrPtr uop);
        void DecodeStrReg(uint16_t instr, UInstrPtr uop);
        void DecodeStrbImmed(uint16_t instr, UInstrPtr uop);
        void DecodeStrbReg(uint16_t instr, UInstrPtr uop);
        void DecodeStrhImmed(uint16_t instr, UInstrPtr uop);
        void DecodeStrhReg(uint16_t instr, UInstrPtr uop);
        // Move
        void DecodeMovsImmed(uint16_t instr, UInstrPtr uop);
        void DecodeMovRegT1(uint16_t instr, UInstrPtr uop);
        void DecodeMovsRegT2(uint16_t instr, UInstrPtr uop);
        // Multiply
        void DecodeMuls(uint16_t instr, UInstrPtr uop);
        // Hint
        void DecodeNop(uint16_t instr, UInstrPtr uop);
        void DecodeSev(uint16_t instr, UInstrPtr uop);
        void DecodeWfe(uint16_t instr, UInstrPtr uop);
        void DecodeWfi(uint16_t instr, UInstrPtr uop);
        void DecodeYield(uint16_t instr, UInstrPtr uop);
        // Pop
        void DecodePop(uint16_t instr, UInstrPtr uop);
        // Push
        void DecodePush(uint16_t instr, UInstrPtr uop);
        // Reverse
        void DecodeRev(uint16_t instr, UInstrPtr uop);
        void DecodeRev16(uint16_t instr, UInstrPtr uop);
        void DecodeRevsh(uint16_t instr, UInstrPtr uop);
        // Rotate
        void DecodeRors(uint16_t instr, UInstrPtr uop);
        // Subtract
        void DecodeRsbs(uint16_t instr, UInstrPtr uop);
        void DecodeSbcs(uint16_t instr, UInstrPtr uop);
        void DecodeSubsImmedT1(uint16_t instr, UInstrPtr uop);
        void DecodeSubsImmedT2(uint16_t instr, UInstrPtr uop);
        void DecodeSubsReg(uint16_t instr, UInstrPtr uop);
        void DecodeSub(uint16_t instr, UInstrPtr uop);
        // State Change
        void DecodeSvc(uint16_t instr, UInstrPtr uop);
        // Extend
        void DecodeSxtb(uint16_t instr, UInstrPtr uop);
        void DecodeSxth(uint16_t instr, UInstrPtr uop);
        void DecodeUxtb(uint16_t instr, UInstrPtr uop);
        void DecodeUxth(uint16_t instr, UInstrPtr uop);


        
        
        // TODO: Need to check for multiple match and handle this
        std::vector<Decoder16BTable> opcode_table = {
            // Shift
            {BitMask(15,11), Opcode(0b00000, 11),          &Armv6m::DecodeLslsImmed},
            {BitMask(15,6),  Opcode(0b0100000010, 6),      &Armv6m::DecodeLslsReg},
            {BitMask(15,11), Opcode(0b00010, 11),          &Armv6m::DecodeAsrsImmed},
            {BitMask(15,6),  Opcode(0b0100000100, 6),      &Armv6m::DecodeAsrsReg},
            {BitMask(15,11), Opcode(0b00001, 11),          &Armv6m::DecodeLsrsImmed},
            {BitMask(15,6),  Opcode(0b0100000011, 6),      &Armv6m::DecodeLsrsReg},
            // Add
            {BitMask(15,6),  Opcode(0b0100000101, 6),      &Armv6m::DecodeAdcs},
            {BitMask(15,9),  Opcode(0b0001110, 9),         &Armv6m::DecodeAddsImmedT1},
            {BitMask(15,11), Opcode(0b00110, 11),          &Armv6m::DecodeAddsImmedT2},
            {BitMask(15,9),  Opcode(0b0001100, 9),         &Armv6m::DecodeAddsRegT1},
            {BitMask(15,8),  Opcode(0b010001, 8),          &Armv6m::DecodeAddRegT2},
            {BitMask(15,11), Opcode(0b10101, 11),          &Armv6m::DecodeAddSpImmedT1},
            {BitMask(15,7),  Opcode(0b101100000, 7),       &Armv6m::DecodeAddSpImmedT2},
            {BitMask(15,7) | BitMask(6,3),  Opcode(0b0100010001101, 3),     &Armv6m::DecodeAddSpRegT1},
            {BitMask(15,7) | BitMask(2,0),  Opcode(0b0100010010000101, 0),  &Armv6m::DecodeAddSpRegT2},
            {BitMask(15,11), Opcode(0b10100, 11),          &Armv6m::DecodeAdr},
            // Logical
            {BitMask(15,6),  Opcode(0b0100000000,6),       &Armv6m::DecodeAnds},
            {BitMask(15,6),  Opcode(0b0100001110,6),       &Armv6m::DecodeBics},
            {BitMask(15,6),  Opcode(0b0100000001,6),       &Armv6m::DecodeEors},
            {BitMask(15,6),  Opcode(0b0100001111,6),       &Armv6m::DecodeMvns},
            {BitMask(15,6),  Opcode(0b0100001100,6),       &Armv6m::DecodeOrrs},
            {BitMask(15,6),  Opcode(0b0100001000,6),       &Armv6m::DecodeTst},
            // Branch
            {BitMask(15,12), Opcode(0b1101,12),            &Armv6m::DecodeBT1}, // SVC would match
            {BitMask(15,11), Opcode(0b11100,11),           &Armv6m::DecodeBT2},
            {BitMask(15,7),  Opcode(0b010001111,7),        &Armv6m::DecodeBlx},
            {BitMask(15,7),  Opcode(0b010001110,7),        &Armv6m::DecodeBx},
            {BitMask(15,8),  Opcode(0b10111110,8),         &Armv6m::DecodeBkpt},
            {BitMask(15,6),  Opcode(0b0100001011,6),       &Armv6m::DecodeCmn},
            {BitMask(15,11), Opcode(0b00101,11),           &Armv6m::DecodeCmpImmed},
            {BitMask(15,6),  Opcode(0b0100001010,6),       &Armv6m::DecodeCmpReg},
            // Load
            {BitMask(15,11), Opcode(0b11001,11),           &Armv6m::DecodeLdm},
            {BitMask(15,11), Opcode(0b01101,11),           &Armv6m::DecodeLdrImmedT1},
            {BitMask(15,11), Opcode(0b10011,11),           &Armv6m::DecodeLdrImmedT2},
            {BitMask(15,11), Opcode(0b01001,11),           &Armv6m::DecodeLdrLit},
            {BitMask(15,9),  Opcode(0b0101100,9),          &Armv6m::DecodeLdrReg},
            {BitMask(15,11), Opcode(0b01111,11),           &Armv6m::DecodeLdrbImmed},
            {BitMask(15,9),  Opcode(0b0101110,9),          &Armv6m::DecodeLdrbReg},
            {BitMask(15,11), Opcode(0b10001,11),           &Armv6m::DecodeLdrhImmed},
            {BitMask(15,9),  Opcode(0b0101101,9),          &Armv6m::DecodeLdrhReg},
            {BitMask(15,9),  Opcode(0b0101011,9),          &Armv6m::DecodeLdrsb},
            {BitMask(15,9),  Opcode(0b0101111,9),          &Armv6m::DecodeLdrsh},
            // Store
            {BitMask(15,11), Opcode(0b11000,9),            &Armv6m::DecodeStm},
            {BitMask(15,11), Opcode(0b01100,9),            &Armv6m::DecodeStrImmedT1},
            {BitMask(15,11), Opcode(0b10010,9),            &Armv6m::DecodeStrImmedT2},
            {BitMask(15,9),  Opcode(0b0101000,9),          &Armv6m::DecodeStrReg},
            {BitMask(15,11), Opcode(0b01110,11),           &Armv6m::DecodeStrbImmed},
            {BitMask(15,9),  Opcode(0b0101010,9),          &Armv6m::DecodeStrbReg},
            {BitMask(15,11), Opcode(0b10000,11),           &Armv6m::DecodeStrhImmed},
            {BitMask(15,9),  Opcode(0b0101001,9),          &Armv6m::DecodeStrhReg},
            // Move
            {BitMask(15,11), Opcode(0b00100,11),           &Armv6m::DecodeMovsImmed},
            {BitMask(15,8),  Opcode(0b01000110,8),         &Armv6m::DecodeMovRegT1},
            {BitMask(15,6),  Opcode(0b0000000000,6),       &Armv6m::DecodeMovsRegT2},
            // Multiply
            {BitMask(15,6),  Opcode(0b0100001101,6),       &Armv6m::DecodeMuls},
            // Hint
            {BitMask(15,0),  Opcode(0b1011111100000000,0), &Armv6m::DecodeNop},
            {BitMask(15,0),  Opcode(0b1011111101000000,0), &Armv6m::DecodeSev},
            {BitMask(15,0),  Opcode(0b1011111100100000,0), &Armv6m::DecodeWfe},
            {BitMask(15,0),  Opcode(0b1011111100110000,0), &Armv6m::DecodeWfi},
            {BitMask(15,0),  Opcode(0b1011111100010000,0), &Armv6m::DecodeYield},
            // Pop
            {BitMask(15,9),  Opcode(0b1011110,9),          &Armv6m::DecodePop},
            // Push
            {BitMask(15,9),  Opcode(0b1011010,9),          &Armv6m::DecodePush},
            // Reverse
            {BitMask(15,6),  Opcode(0b1011101000,6),       &Armv6m::DecodeRev},
            {BitMask(15,6),  Opcode(0b1011101001,6),       &Armv6m::DecodeRev16},
            {BitMask(15,6),  Opcode(0b1011101011,6),       &Armv6m::DecodeRevsh},
            // Rotate
            {BitMask(15,6),  Opcode(0b0100000111,6),       &Armv6m::DecodeRors},
            // Subtract
            {BitMask(15,6),  Opcode(0b0100001001,6),       &Armv6m::DecodeRsbs},
            {BitMask(15,6),  Opcode(0b0100000110,6),       &Armv6m::DecodeSbcs},
            {BitMask(15,9),  Opcode(0b0001111,9),          &Armv6m::DecodeSubsImmedT1},
            {BitMask(15,11), Opcode(0b00111,11),           &Armv6m::DecodeSubsImmedT2},
            {BitMask(15,9),  Opcode(0b0001101,9),          &Armv6m::DecodeSubsReg},
            {BitMask(15,7),  Opcode(0b101100001,7),        &Armv6m::DecodeSub},
            // State Change
            {BitMask(15,8),  Opcode(0b11011111,8),         &Armv6m::DecodeSvc},
            // Extend
            {BitMask(15,6),  Opcode(0b1011001001,6),       &Armv6m::DecodeSxtb},
            {BitMask(15,6),  Opcode(0b1011001000,6),       &Armv6m::DecodeSxth},
            {BitMask(15,6),  Opcode(0b1011001011,6),       &Armv6m::DecodeUxtb},
            {BitMask(15,6),  Opcode(0b1011001010,6),       &Armv6m::DecodeUxth}
        };
    
};


#endif // ARMV6M_H