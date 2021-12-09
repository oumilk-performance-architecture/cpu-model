#ifndef RV32I_H
#define RV32I_H

#include <vector>
#include <uop.h>
#include "../../isa.h"

class UInstr;
using UInstrPtr = std::shared_ptr<UInstr>;

class Rv32i : public IsaBase {
    public:
        Rv32i();
        //bool DecodeInstructions(uint16_t instr, UInstrPtr uinstr);

        typedef void (Rv32i::*decode)(uint32_t instr, UInstrPtr uop);
        struct Decoder32BTable {
            uint32_t mask;
            uint32_t match;
            decode genUop;
            Uop uop;
        };

    private:
        bool doDecodeInstructions(uint32_t instr, UInstrPtr uinstr);
        /* U Type - Long immediates */
        void DecodeU (uint32_t instr, UInstrPtr uinstr);
        /* I Type - Short immediates and loads */
        void DecodeI    (uint32_t instr, UInstrPtr uinstr);
        void DecodeIShift  (uint32_t instr, UInstrPtr uinstr);
        void DecodeEcall (uint32_t instr, UInstrPtr uinster);
        /* B Type - Branches */
        void DecodeB     (uint32_t instr, UInstrPtr uinstr);
        /* J Type - Unconditional Jumps */
        void DecodeJal  (uint32_t instr, UInstrPtr uinstr);
        /* R Type - Register to Register Operation */
        void DecodeR    (uint32_t instr, UInstrPtr uinstr);
        /* S Type - Stores */
        void DecodeS   (uint32_t instr, UInstrPtr uinstr);

        std::vector<Decoder32BTable> opcode_table = {
            /* U Type - Long immediates */
            {BitMask32(6,0),       Opcode32(0b0110111, 0),         &Rv32i::DecodeU, Uop::LUI},
            {BitMask32(6,0),       Opcode32(0b0010111, 0),         &Rv32i::DecodeU, Uop::AUIPC},
            /* I Type - Short immediates and loads */
            {BitMask32(14,12,6,0), Opcode32(0b000,12,0b1100111,0), &Rv32i::DecodeI, Uop::JALR},
            {BitMask32(14,12,6,0), Opcode32(0b000,12,0b0000011,0), &Rv32i::DecodeI, Uop::LB},
            {BitMask32(14,12,6,0), Opcode32(0b001,12,0b0000011,0), &Rv32i::DecodeI, Uop::LH},
            {BitMask32(14,12,6,0), Opcode32(0b010,12,0b0000011,0), &Rv32i::DecodeI, Uop::LW},
            {BitMask32(14,12,6,0), Opcode32(0b100,12,0b0000011,0), &Rv32i::DecodeI, Uop::LBU},
            {BitMask32(14,12,6,0), Opcode32(0b101,12,0b0000011,0), &Rv32i::DecodeI, Uop::LHU},
            {BitMask32(14,12,6,0), Opcode32(0b000,12,0b0010011,0), &Rv32i::DecodeI, Uop::ADDI},
            {BitMask32(14,12,6,0), Opcode32(0b010,12,0b0010011,0), &Rv32i::DecodeI, Uop::SLTI},
            {BitMask32(14,12,6,0), Opcode32(0b011,12,0b0010011,0), &Rv32i::DecodeI, Uop::SLTIU},
            {BitMask32(14,12,6,0), Opcode32(0b100,12,0b0010011,0), &Rv32i::DecodeI, Uop::XORI},
            {BitMask32(14,12,6,0), Opcode32(0b110,12,0b0010011,0), &Rv32i::DecodeI, Uop::ORI},
            {BitMask32(14,12,6,0), Opcode32(0b111,12,0b0010011,0), &Rv32i::DecodeI, Uop::ANDI},
            {BitMask32(31,25,14,12,6,0), Opcode32(0b0000000,25,0b001,12,0b0010011,0), &Rv32i::DecodeIShift,  Uop::SLLI},
            {BitMask32(31,25,14,12,6,0), Opcode32(0b0000000,25,0b101,12,0b0010011,0), &Rv32i::DecodeIShift,  Uop::SRLI},
            {BitMask32(31,25,14,12,6,0), Opcode32(0b0100000,25,0b101,12,0b0010011,0), &Rv32i::DecodeIShift,  Uop::SRAI},
            {BitMask32(31,0),      Opcode32(0, 0),                 &Rv32i::DecodeEcall, Uop::ECALL},
            /* B Type - Branches */
            {BitMask32(14,12,6,0), Opcode32(0b000,12,0b1100011,0), &Rv32i::DecodeB,  Uop::BEQ},
            {BitMask32(14,12,6,0), Opcode32(0b001,12,0b1100011,0), &Rv32i::DecodeB,  Uop::BNE},
            {BitMask32(14,12,6,0), Opcode32(0b100,12,0b1100011,0), &Rv32i::DecodeB,  Uop::BLT},
            {BitMask32(14,12,6,0), Opcode32(0b101,12,0b1100011,0), &Rv32i::DecodeB,  Uop::BGE},
            {BitMask32(14,12,6,0), Opcode32(0b110,12,0b1100011,0), &Rv32i::DecodeB,  Uop::BLTU},
            {BitMask32(14,12,6,0), Opcode32(0b111,12,0b1100011,0), &Rv32i::DecodeB,  Uop::BGEU},
            /* J Type - Unconditional Jumps */
            {BitMask32(6,0),       Opcode32(0b1101111, 0),         &Rv32i::DecodeJal,  Uop::JAL},
            /* R Type - Register to Register Operation */
            {BitMask32(31,25,14,12,6,0), Opcode32(0b0000000,25,0b000,12,0b0110011,0), &Rv32i::DecodeR, Uop::ADD},
            {BitMask32(31,25,14,12,6,0), Opcode32(0b0100000,25,0b000,12,0b0110011,0), &Rv32i::DecodeR, Uop::SUB},
            {BitMask32(31,25,14,12,6,0), Opcode32(0b0000000,25,0b001,12,0b0110011,0), &Rv32i::DecodeR, Uop::SLL},
            {BitMask32(31,25,14,12,6,0), Opcode32(0b0000000,25,0b010,12,0b0110011,0), &Rv32i::DecodeR, Uop::SLT},
            {BitMask32(31,25,14,12,6,0), Opcode32(0b0000000,25,0b011,12,0b0110011,0), &Rv32i::DecodeR, Uop::SLTU},
            {BitMask32(31,25,14,12,6,0), Opcode32(0b0000000,25,0b100,12,0b0110011,0), &Rv32i::DecodeR, Uop::XOR},
            {BitMask32(31,25,14,12,6,0), Opcode32(0b0000000,25,0b101,12,0b0110011,0), &Rv32i::DecodeR, Uop::SRL},
            {BitMask32(31,25,14,12,6,0), Opcode32(0b0100000,25,0b101,12,0b0110011,0), &Rv32i::DecodeR, Uop::SRA},
            {BitMask32(31,25,14,12,6,0), Opcode32(0b0000000,25,0b110,12,0b0110011,0), &Rv32i::DecodeR, Uop::OR},
            {BitMask32(31,25,14,12,6,0), Opcode32(0b0000000,25,0b111,12,0b0110011,0), &Rv32i::DecodeR, Uop::AND},
            /* S Type - Stores */
            {BitMask32(14,12,6,0), Opcode32(0b000,12,0b0100011,0), &Rv32i::DecodeS,   Uop::SB},
            {BitMask32(14,12,6,0), Opcode32(0b001,12,0b0100011,0), &Rv32i::DecodeS,   Uop::SH},
            {BitMask32(14,12,6,0), Opcode32(0b010,12,0b0100011,0), &Rv32i::DecodeS,   Uop::SW},
        };
};

#endif // RV32I_H