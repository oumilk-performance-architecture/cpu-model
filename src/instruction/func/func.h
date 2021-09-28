#ifndef FUNC_H
#define FUNC_H

#include <uinstr.h>
#include <tuple>

struct CalcResults {
    uint32_t result;
    bool carry_out;
    bool overflow;
};

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
        CalcResults AddWithCary(uint32_t a, uint32_t b, bool carry);
        CalcResults LSLWithCarry(uint32_t a, uint32_t b);
        CalcResults LSRWithCarry(uint32_t a, uint32_t b);
        CalcResults ASRWithCarry(uint32_t a, uint32_t b);
        CalcResults RORWithCarry(uint32_t a, uint32_t b); 
        

        void ExecMovImm(UInstrPtr uinstr);
        void ExecMovReg(UInstrPtr uinstr);
        void ExecAddImm(UInstrPtr uinstr);
        void ExecAddReg(UInstrPtr uinstr);
        void ExecAddPCReg(UInstrPtr uinstr);
        void ExecAdrImm(UInstrPtr uinstr);
        void ExecLslImm(UInstrPtr uinstr);
        void ExecAdcs(UInstrPtr uinstr);

        constexpr bool CalculateN(uint32_t value) {
            return value>>31==1;
        };
        constexpr bool CalculateZ(uint32_t value) {
            return value==0;
        };
        //void SetFlags(UInstrPtr uinstr, CalcResults calc);
        //void SetFlags(UInstrPtr uinstr, uint32_t value);

        std::vector<ExecuteTable> exec_table = {
            {Uop::MOVS_imm,      &Func::ExecMovImm},
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
            {Uop::ADCS,          &Func::ExecAdcs}
        };       

};
#endif //FUNC_H