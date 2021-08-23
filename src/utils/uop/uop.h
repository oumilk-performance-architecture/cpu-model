#ifndef UOP_H
#define UOP_H

enum class Uop {
    /* */
    LSL_imm, LSL_reg, 
    /* Move */
    MOVS_imm, MOV_reg, MOVS_reg,
    /* Add */
    ADDS_imm, ADDS_reg, ADD_reg,
    ADD_SP_imm_t1, ADD_SP_imm_t2,
};

static const char *uop_str[] = {
    "LSL_imm", "LSL_reg",
    "MOVS_imm", "MOV_reg", "MOVS_reg",
    /* Add */
    "ADDS_imm", "ADDS_reg", "ADD_reg",
    "ADD_SP_imm_t1", "ADD_SP_imm_t2",
};

#endif // UOP_H