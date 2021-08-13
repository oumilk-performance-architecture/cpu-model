#ifndef UOP_H
#define UOP_H

enum class Uop {
    /* */
    LSL_imm, LSL_reg, 
    /* Move */
    MOVS_imm, MOVS_reg, MOV_imm, MOV_reg
};

#endif // UOP_H