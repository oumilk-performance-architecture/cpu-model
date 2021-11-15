#include "func.h"
#include <uinstr.h>

#define REGISTER_MASK 0xFFFF

Func::Func() {

};

bool Func::ExecuteUop(UInstrPtr uinstr) {
    std::vector<ExecuteTable>::iterator iter;
    auto execUop = [&uinstr](const ExecuteTable exec) {
        return uinstr->GetOpcode() == exec.uop; 
    };
    iter = std::find_if(exec_table.begin(), exec_table.end(), execUop);
    
    if (iter != exec_table.end()) {
        (this->*(iter->exec))(uinstr);
        return true;
    } 
    return false;
};

void Func::ExecAdd(UInstrPtr uinstr) {
    uinstr->SetDataDest(uinstr->GetDataSrcA() + uinstr->GetDataSrcB());
};

uint32_t Func::ExecSlt(uint32_t rs1_data, uint32_t rs2_data) {
    return (uint32_t)((int32_t) rs1_data < (int32_t) rs2_data);
};