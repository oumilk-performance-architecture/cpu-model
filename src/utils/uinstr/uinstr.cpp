#include "uinstr.h"
#include <iostream>

/*enum class source_reg {
    RN,
    RM,
    RA,
    RT
};*/

UInstr::UInstr() {
    // Max is "unassigned"
    rd_  = std::numeric_limits<uint8_t>::max();
    rs1_ = std::numeric_limits<uint8_t>::max();
    rs2_ = std::numeric_limits<uint8_t>::max();
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
void UInstr::SetRs1(uint8_t rs1) {
    rs1_ = rs1;
};
void UInstr::SetRs2(uint8_t rs2) {
    rs2_ = rs2;
};


// 
void UInstr::SetImmed(uint32_t immed) {
    immed_ = immed;
};

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
std::string UInstr::GetOpcodeString() {
    return uop_str[(int)opcode_];
}
void UInstr::PrintDetails() {
    std::cout << "Uop Detail: \n";
    std::cout << " Opcode: " << uop_str[(int)opcode_] << "\n";
    std::cout << " Latency: " << latency_ << "\n";
    std::cout << " Arch - Rd: " << (int) rd_ << "  ";
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
    std::cout << "\n";
}

std::ostream & operator << (std::ostream &out, UInstr &c)
{
    out << "UInstr Opcode: " << uop_str[(int)c.GetOpcode()] << "\n";
    out << "  Rd: " << (int)c.GetRd();
    out << "  Immed: " << (int)c.GetImmed() << "\n";
    return out;
}