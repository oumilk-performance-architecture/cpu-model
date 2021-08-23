#include "func.h"
#include <uinstr.h>
#include <uop.h>

#define REGISTER_MASK 0xFFFF

Func::Func() {

};

bool Func::ExecuteUop(const UInstrPtr uop) {
    std::vector<ExecuteTable>::iterator iter;
    auto execUop = [&uop](const ExecuteTable exec) {
        return uop->GetOpcode() == exec.uop; 
    };
    iter = std::find_if(exec_table.begin(), exec_table.end(), execUop);
    
    if (iter != exec_table.end()) {
        (this->*(iter->exec))(uop);
        return true;
    } 
    return false;
};

UInstr Func::Lsli(UInstr uop) {
    return uop;
};

UInstr Func::Lslr(UInstr uop) {
    return uop;
};

void Func::ExecMov(UInstrPtr uinstr) {
    uint64_t result = uinstr->GetDataSrcB();
    uinstr->SetDataDest(result);
    SetFlags(uinstr, result);
};

void Func::ExecAdd(UInstrPtr uinstr) {
    uint64_t result = (uint64_t) uinstr->GetDataSrcA() + (uint64_t) uinstr->GetDataSrcB();
    uinstr->SetDataDest(ConvertToU32(result));
    SetFlags(uinstr, result);
};

uint32_t Func::ConvertToU32(uint64_t result) {
    return (uint32_t) (result & 0xFFFF);
};

bool Func::CalcCarry(uint64_t result) {
    return (result >> 32) > 0;
};

bool Func::CalcOverflow(uint64_t result) {
    return ((result > INT32_MAX) || (result < INT32_MIN));
};

void Func::SetFlags(UInstrPtr uinstr, uint64_t result) {
    if (uinstr->GetUpdateFlagN()) {
        uinstr->SetDataFlagN(result>>31==1);
    }
    if (uinstr->GetUpdateFlagZ()) {
        uinstr->SetDataFlagN(result==0);
    }
    if (uinstr->GetUpdateFlagC()) {
        uinstr->SetDataFlagC(CalcCarry(result));
    }
    if (uinstr->GetUpdateFlagV()) {
        uinstr->SetDataFlagV(CalcOverflow(result));
    }
};