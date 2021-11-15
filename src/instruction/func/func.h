#ifndef FUNC_H
#define FUNC_H

#include <tuple>
#include <memory>
#include <uop.h>
#include <vector>

class UInstr;
using UInstrPtr = std::shared_ptr<UInstr>;


class Func {
    public:
        Func();
        bool ExecuteUop(UInstrPtr uinstr);

        typedef void (Func::*exec)(UInstrPtr uinstr);
        struct ExecuteTable {
            Uop uop;
            exec exec;
        };
    private:
        void ExecAdd(UInstrPtr uinstr);

        template <class T>
        T ExecSub(T rs1_data, T rs2_data) {
            return rs1_data - rs2_data;
        };
        template <class T>
        T ExecSll(T rs1_data, T rs2_data) {
            return rs1_data << rs2_data;
        };
        uint32_t ExecSlt(uint32_t rs1_data, uint32_t rs2_data);
        template <class T>
        T ExecSltu(T rs1_data, T rs2_data) {
            return rs1_data < rs2_data ? 0b1 : 0b0;
        };
        template <class T>
        T ExecXor(T rs1_data, T rs2_data) {
            return rs1_data ^ rs2_data;
        };
        

        std::vector<ExecuteTable> exec_table = {
            {Uop::ADD,    &Func::ExecAdd },
            /*{Uop::MOVS_imm,      &Func::ExecMovImm},
            {Uop::MOV_reg,       &Func::ExecMovReg},
            {Uop::MOVS_reg,      &Func::ExecMovReg},
            {Uop::ADDS_imm,      &Func::ExecAddImm},
            {Uop::ADDS_reg,      &Func::ExecAddReg},
            {Uop::ADD_PC_reg,    &Func::ExecAddPCReg},
            {Uop::ADD_reg,       &Func::ExecAddReg},
            {Uop::ADD_SP_imm_t1, &Func::ExecAddImm},
            {Uop::ADD_SP_imm_t2, &Func::ExecAddImm},
            {Uop::ADD_SP_reg_t1, &Func::ExecAddReg},
            {Uop::ADD_SP_reg_t2, &Func::ExecAddReg},
            {Uop::ADR_imm,       &Func::ExecAddImm},
            {Uop::LSL_imm,       &Func::ExecLslImm},
            {Uop::ADCS,          &Func::ExecAdcs},
            {Uop::LDR_imm,       &Func::ExecAddImm}*/
        };       

};
#endif //FUNC_H