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

CalcResults Func::AddWithCary(uint32_t a, uint32_t b, bool carry) {
    CalcResults calc;
    uint64_t usum = (uint64_t) a + (uint64_t) b + carry;
    int64_t  ssum = (int64_t)  a + (int64_t)  b + carry;
    
    uint32_t result = (usum & 0xFFFFFFFF);
  
    calc.result = (uint32_t) result;
    calc.carry_out = (((uint64_t) result) == usum);
    calc.overflow = (((int64_t) result) == ssum);
    return calc;
};

CalcResults Func::LSLWithCarry(uint32_t a, uint32_t b) {
    CalcResults calc;
    uint64_t extended_x = ((uint64_t) a) << b;

    calc.result = (uint32_t) extended_x & 0xFFFFFFFF;
    calc.carry_out = (((extended_x & 0x00010000) >> 16) == 1);

    return calc;
};

CalcResults Func::LSRWithCarry(uint32_t a, uint32_t b) {
    CalcResults calc;

    calc.result = (a >> b);
    calc.carry_out = !!(a & (1 << (b-1)));

    return calc;
};

CalcResults Func::ASRWithCarry(uint32_t a, uint32_t b) {
    CalcResults calc;

    int32_t extended_x = a;

    calc.result = (a >> b);
    calc.carry_out = !!(a & (1 << (b-1)));

    return calc;
};

CalcResults Func::RORWithCarry(uint32_t a, uint32_t b) {
    CalcResults calc;

    uint64_t value = ((uint64_t) a << (32-b)) | (a >> b);

    calc.result = value & 0xFFFFFFFF;
    calc.carry_out = !!(value & (1<<31));

    return calc;
};

void Func::ExecMovReg(UInstrPtr uinstr) {
    uint64_t result = uinstr->GetDataSrcB();
    uinstr->SetDataDest(result);
};

void Func::ExecMovImm(UInstrPtr uinstr) {
    uint64_t result = uinstr->GetImmed();
    uinstr->SetDataDest(result);
};

void Func::ExecAddReg(UInstrPtr uinstr) {
    assert(uinstr->GetRd() != 15); // Should not be writing to PC
    CalcResults calc = AddWithCary(uinstr->GetDataSrcA(),
                                   uinstr->GetDataSrcB(),
                                   false);
    uinstr->SetDataDest(calc.result);
    if (uinstr->GetAPSRUpdate()) {
        uinstr->SetDataFlagN(CalculateN(calc.result));
        uinstr->SetDataFlagZ(CalculateZ(calc.result));
        uinstr->SetDataFlagC(calc.carry_out);
        uinstr->SetDataFlagV(calc.overflow);
    }
};

void Func::ExecAddPCReg(UInstrPtr uinstr) {
    CalcResults calc = AddWithCary(uinstr->GetDataSrcA(),
                                   uinstr->GetDataSrcB(),
                                   false);
    uinstr->SetDataDest(calc.result);
};

void Func::ExecAddImm(UInstrPtr uinstr) {
    CalcResults calc = AddWithCary(uinstr->GetDataSrcA(),
                                   uinstr->GetImmed(),
                                   false);
    uinstr->SetDataDest(calc.result);
    if (uinstr->GetAPSRUpdate()) {
        uinstr->SetDataFlagN(CalculateN(calc.result));
        uinstr->SetDataFlagZ(CalculateZ(calc.result));
        uinstr->SetDataFlagC(calc.carry_out);
        uinstr->SetDataFlagV(calc.overflow);
    }
};

void Func::ExecLslImm(UInstrPtr uinstr) {

}

void Func::ExecAdcs(UInstrPtr uinstr) {
    CalcResults calc = AddWithCary(uinstr->GetDataSrcA(),
                                   uinstr->GetDataSrcB(),
                                   uinstr->GetDataFlagC());
    uinstr->SetDataDest(calc.result);
    uinstr->SetDataFlagN(CalculateN(calc.result));
    uinstr->SetDataFlagZ(CalculateZ(calc.result));
    uinstr->SetDataFlagC(calc.carry_out);
    uinstr->SetDataFlagV(calc.overflow);
}

/*void Func::SetFlags(UInstrPtr uinstr, uint32_t value) {
    if (uinstr->GetUpdateFlagN()) {
        uinstr->SetDataFlagN(CalculateN(value));
    }
    if (uinstr->GetUpdateFlagZ()) {
        uinstr->SetDataFlagN(CalculateZ(value));
    }
    if (uinstr->GetUpdateFlagC()) {
        assert("Set flags C not possible, need to use CalcResults.");
    }
    if (uinstr->GetUpdateFlagV()) {
        assert("Set flags V not possible, need to use CalcResults");
    }
};

void Func::SetFlags(UInstrPtr uinstr, CalcResults calc) {
    if (uinstr->GetUpdateFlagN()) {
        uinstr->SetDataFlagN(CalculateN(calc.result));
    }
    if (uinstr->GetUpdateFlagZ()) {
        uinstr->SetDataFlagN(CalculateZ(calc.result));
    }
    if (uinstr->GetUpdateFlagC()) {
        uinstr->SetDataFlagC(calc.carry_out);
    }
    if (uinstr->GetUpdateFlagV()) {
        uinstr->SetDataFlagV(calc.overflow);
    }
};*/