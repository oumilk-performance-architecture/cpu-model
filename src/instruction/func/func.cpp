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

void Func::ExecAddi(UInstrPtr uinstr) {
    uint32_t immed = sign_11.x = uinstr->GetImmed();
    uinstr->SetDataRd(uinstr->GetDataRs1() + immed);
};
void Func::ExecSlti(UInstrPtr uinstr) {
    int32_t immed = sign_11.x = uinstr->GetImmed();
    uint32_t value = ((int32_t) uinstr->GetDataRs1()) < immed;
    uinstr->SetDataRd(value);
};
void Func::ExecSltiu(UInstrPtr uinstr) {
    uint32_t immed = sign_11.x = uinstr->GetImmed();
    uint32_t value = uinstr->GetDataRs1() < immed;
    uinstr->SetDataRd(value);
};
uint32_t Func::ExecSlt(uint32_t rs1_data, uint32_t rs2_data) {
    return (uint32_t)((int32_t) rs1_data < (int32_t) rs2_data);
};
void Func::ExecLui(UInstrPtr uinstr) {
    // Sign extend if 64 bit mode so not doing it now.
    uint32_t temp = sign_31.x = uinstr->GetImmed() << 12;
    uinstr->SetDataRd(temp);
}
// TODO - need to figure out how we implement the PC part
void Func::ExecAuipc(UInstrPtr uinstr) {
    uint32_t temp = sign_31.x = uinstr->GetImmed() << 12;
    uinstr->SetDataRd(temp);
}
