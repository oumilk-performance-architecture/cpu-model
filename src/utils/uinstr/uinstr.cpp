#include "uinstr.h"
#include <iostream>

UInstr::UInstr() {
    set_apsr_ = false;
    // Max is "unasigned"
    rd_ = std::numeric_limits<uint8_t>::max();
    rn_ = std::numeric_limits<uint8_t>::max();
    rm_ = std::numeric_limits<uint8_t>::max();
    ra_ = std::numeric_limits<uint8_t>::max();
    rt_ = std::numeric_limits<uint8_t>::max();
    srca_phys_ = -1;
    srcb_phys_ = -1;
};

// Logical
void UInstr::SetOpcode(Uop opcode) {
    opcode_ = opcode;
};
Uop UInstr::GetOpcode() {
    return opcode_;
};

// Architectural Registers
void UInstr::SetRd(uint8_t rd) {
    rd_ = rd;
};
void UInstr::SetRn(uint8_t rn) {
    rn_ = rn;
};
void UInstr::SetRm(uint8_t rm) {
    rm_ = rm;
};
void UInstr::SetRa(uint8_t ra) {
    ra_ = ra;
};
void UInstr::SetRt(uint8_t rt) {
    rt_ = rt;
};
void UInstr::SetAPSRUpdate(bool set_apsr) {
    set_apsr_ = set_apsr;
};


// 
void UInstr::SetRegList(uint8_t reg_list) {
    reg_list_ = reg_list;
};
void UInstr::SetImmed(uint32_t immed) {
    immed_ = immed;
};
uint32_t UInstr::GetImmed() {
    return immed_;
};
void UInstr::SetCond(uint8_t cond) {
    cond_ = static_cast<Cond>(cond);
}
void UInstr::SetCond(Cond cond) {
    cond_ = cond;//static_cast<Cond>(cond);
}

// Physical
void UInstr::SetPhysSrcA(int srca_phys) {
    srca_phys_ = srca_phys;
};
void UInstr::SetPhysSrcB(int srcb_data) {
    srcb_data_ = srcb_data;
};
void UInstr::SetPhysDest(int dest_phys) {
    dest_phys_ = dest_phys;
};
void UInstr::SetPhysAPSR(int apsr_phys) {
    apsr_phys_ = apsr_phys;
};

// Data
void UInstr::SetDataSrcA(uint32_t srca_data) {
    srca_data_ = srca_data;
};
void UInstr::SetDataSrcB(uint32_t srcb_data) {
    srcb_data_ = srcb_data;
};
void UInstr::SetDataDest(uint32_t dest_data) {
    dest_data_ = dest_data;
};
void UInstr::SetDataFlagN(bool value) {
    apsr_data_.set((int)Apsr::n, value);
};
void UInstr::SetDataFlagZ(bool value) {
    apsr_data_.set((int)Apsr::z, value);
};
void UInstr::SetDataFlagC(bool value) {
    apsr_data_.set((int)Apsr::c, value);
};
void UInstr::SetDataFlagV(bool value) {
    apsr_data_.set((int)Apsr::v, value);
};


// Simulation
void UInstr::SetExecUnit(std::vector<ExecUnits> unit) {
    exec_units_ = unit;
};
void UInstr::SetLatency(int latency) {
    latency_ = latency;
};
void UInstr::SetResUnit(std::vector<ResUnits> unit) {
    res_units_ = unit;
};

// Support
void UInstr::PrintDetails() {
    std::cout << "Uop Detail: \n";
    std::cout << " Opcode: " << uop_str[(int)opcode_] << "\n";
    std::cout << " Latency: " << latency_ << "\n";
    std::cout << " Arch - Rd: " << (int) rd_ << "  ";
    std::cout << " Rn: " << (int) rn_ << "  ";
    std::cout << " Immed: " << (int) immed_ << "\n";
    std::cout << " Phys - SrcA: " << (int) srca_phys_ << " ";
    std::cout << " SrcB: " << (int) srcb_phys_ << "\n";
    PrintExec();
    std::cout << "\n";
};

void UInstr::PrintExec() {
    std::cout << "  Exec Units: ";
    for (auto it = exec_units_.begin(); it != exec_units_.end(); it++) {
        //std::cout << execunits_str[(int)(*it)] << " ";
        std::cout << (int)(*it) << " ";
    }
    std::cout << "\n";
    std::cout << "  Res Units: ";
    for (auto it = res_units_.begin(); it != res_units_.end(); it++) {
        //std::cout << execunits_str[(int)(*it)] << " ";
        std::cout << (int)(*it) << " ";
    }
    std::cout << "\n";
};

void UInstr::PrintResults() {
    std::cout << "Opcode: " << uop_str[(int)opcode_] << "\n";
    std::cout << "  Source A: " << (int) srca_data_ << "  ";
    std::cout << "  Source B: " << (int) srcb_data_ << "\n";
    std::cout << "  Dest: " << (int) dest_data_ << "\n";
    std::cout << " Flag:  ";
    std::cout << "   n: " << (int) apsr_data_[(int)Apsr::n];
    std::cout << "   z: " << (int) apsr_data_[(int)Apsr::z];
    std::cout << "   c: " << (int) apsr_data_[(int)Apsr::c];
    std::cout << "   v: " << (int) apsr_data_[(int)Apsr::v];
    std::cout << "\n";
}

std::ostream & operator << (std::ostream &out, UInstr &c)
{
    out << "UInstr Opcode: " << uop_str[(int)c.GetOpcode()] << "\n";
    out << "  Rd: " << (int)c.GetRd();
    out << "  Rb: " << (int)c.GetRn();
    out << "  Immed: " << (int)c.GetImmed() << "\n";
    return out;
}

std::ostream & operator << (std::ostream &out, UInstrPtr &c)
{
    out << "UInstrPtr Opcode: " << uop_str[(int)c->GetOpcode()] << "\n";
    out << "  Rd: " << (int)c->GetRd();
    out << "  Rb: " << (int)c->GetRn();
    out << "  Immed: " << (int)c->GetImmed() << "\n";
    return out;
}