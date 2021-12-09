#ifndef UOP_H
#define UOP_H

enum class Uop {
    /*
        RV32I
    */
    /* U Type - Long immediates */
    LUI, AUIPC,
    /* I Type - Short immediates and loads */
    LB, LH, LW, LBU, LHU, JALR, ECALL, 
    ADDI, SLTI, SLTIU, XORI, ORI, ANDI,
    SLLI, SRLI, SRAI,
    /* B Type - Branches */
    BEQ, BNE, BLT, BGE, BLTU, BGEU,
    /* J Type - Unconditional Jumps */
    JAL,
    /* R Type - Register to Register Operation */
    ADD, SUB, SLL, SLT, SLTU, XOR, SRL, SRA, OR, AND,
    /* S Type - Stores */
    SB, SH, SW
};

//static const enum_array<Uop, std::string, 38> uop_str = {
//    /*
//        RV32I
//    */
//    /* U Type - Long immediates */
//    "LUI", "AUIPC",
//    /* I Type - Short immediates and loads */
//    "LB", "LH", "LW", "LBU", "LHU", "JALR", "ECALL",
//    "ADDI", "SLTI", "SLTIU", "XORI", "ORI", "ANDI",
//    "SLLI", "SRLI", "SRAI",
//    /* B Type - Branches */
//    "BEQ", "BNE", "BLT", "BGE", "BLTU", "BGEU",
//    /* J Type - Unconditional Jumps */
//    "JAL",
//    /* R Type - Register to Register Operation */
//    "ADD", "SUB", "SLL", "SLT", "SLTU", "XOR", "SRL", "SRA", "OR", "AND",
//    /* S Type - Stores */
//    "SB", "SH", "SW"
//};

static const char *uop_str[] = {
    /*
        RV32I
    */
    /* U Type - Long immediates */
    "LUI", "AUIPC",
    /* I Type - Short immediates and loads */
    "LB", "LH", "LW", "LBU", "LHU", "JALR", "ECALL",
    "ADDI", "SLTI", "SLTIU", "XORI", "ORI", "ANDI",
    "SLLI", "SRLI", "SRAI",
    /* B Type - Branches */
    "BEQ", "BNE", "BLT", "BGE", "BLTU", "BGEU",
    /* J Type - Unconditional Jumps */
    "JAL",
    /* R Type - Register to Register Operation */
    "ADD", "SUB", "SLL", "SLT", "SLTU", "XOR", "SRL", "SRA", "OR", "AND",
    /* S Type - Stores */
    "SB", "SH", "SW"
};

#endif // UOP_H