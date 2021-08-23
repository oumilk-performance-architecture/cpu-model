#ifndef FUNC_H
#define FUNC_H

#include <uinstr.h>

class Func {
    public:
        Func();
        bool ExecuteUop(UInstrPtr uop);


        typedef void (Func::*exec)(UInstrPtr instr);
        struct ExecuteTable {
            Uop uop;
            exec exec;
        };
    private:
        uint32_t ConvertToU32(uint64_t result);
        bool CalcCarry(uint64_t result);
        bool CalcOverflow(uint64_t result);

        UInstr Lsli(UInstr uop);
        UInstr Lslr(UInstr uop);
        void ExecMov(UInstrPtr uinstr);
        void ExecAdd(UInstrPtr uinstr);
        void SetFlags(UInstrPtr uinstr, uint64_t result);

        std::vector<ExecuteTable> exec_table = {
            {Uop::MOVS_imm,      &Func::ExecMov},
            {Uop::MOV_reg,       &Func::ExecMov},
            {Uop::MOVS_reg,      &Func::ExecMov},
            {Uop::ADDS_imm,      &Func::ExecAdd},
            {Uop::ADDS_reg,      &Func::ExecAdd},
            {Uop::ADD_reg,       &Func::ExecAdd},
            {Uop::ADD_SP_imm_t1, &Func::ExecAdd},
            {Uop::ADD_SP_imm_t2, &Func::ExecAdd}
        };       

};
#endif //FUNC_H