#include "uinstr.h"
#include <iostream>

UInstr::UInstr() {
    SetFlagNZCV(false);
};

// Logical
void UInstr::SetOpcode(Uop opcode) {
    opcode_ = opcode;
};
Uop UInstr::GetOpcode() {
    return opcode_;
};

void UInstr::SetFlagNZ(bool value) {
    SetFlagN(value);
    SetFlagZ(value);
};

void UInstr::SetFlagNZC(bool value) {
    SetFlagN(value);
    SetFlagZ(value);
    SetFlagC(value);
};

void UInstr::SetFlagNZCV(bool value) {
    SetFlagN(value);
    SetFlagZ(value);
    SetFlagC(value);
    SetFlagV(value);
};
// Flag - N
void UInstr::SetFlagN(bool value) {
    set_apsr_.set((int)Apsr::n, value);
};
bool UInstr::GetUpdateFlagN() {
    return set_apsr_.test((int)Apsr::n);
};
// Flag - Z
void UInstr::SetFlagZ(bool value) {
    set_apsr_.set((int)Apsr::z, value);
};
bool UInstr::GetUpdateFlagZ() {
    return set_apsr_.test((int)Apsr::z);
};
// Flag - C
void UInstr::SetFlagC(bool value) {
    set_apsr_.set((int)Apsr::c, value);
};
bool UInstr::GetUpdateFlagC() {
    return set_apsr_.test((int)Apsr::c);
};
// Flag - V
void UInstr::SetFlagV(bool value) {
    set_apsr_.set((int)Apsr::v, value);
};
bool UInstr::GetUpdateFlagV() {
    return set_apsr_.test((int)Apsr::v);
};
// Architectural Registers
void UInstr::SetRd(uint8_t rd) {
    rd_ = rd;
};
uint8_t UInstr::GetRd() {
    return rd_;
};
void UInstr::SetRn(uint8_t rn) {
    rn_ = rn;
};
uint8_t UInstr::GetRn() {
    return rn_;
};
void UInstr::SetRm(uint8_t rm) {
    rm_ = rm;
};
uint8_t UInstr::GetRm() {
    return rm_;
};
void UInstr::SetRa(uint8_t ra) {
    ra_ = ra;
};
uint8_t UInstr::GetRa() {
    return ra_;
};
void UInstr::SetRt(uint8_t rt) {
    rt_ = rt;
};
uint8_t UInstr::GetRt() {
    return rt_;
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
    cond_ = static_cast<Cond>(cond);
}

// Physical
void UInstr::SetPhysSrcA(int srca_phys) {
    srca_phys_ = srca_phys;
};
int UInstr::GetPhysSrcA() {
    return srca_data_;
};
void UInstr::SetPhysSrcB(int srcb_data) {
    srcb_data_ = srcb_data;
};
int UInstr::GetPhysSrcB() {
    return srcb_data_;
};
void UInstr::SetPhysDest(int dest_phys) {
    dest_phys_ = dest_phys;
};
int UInstr::GetPhysDest() {
    return dest_phys_;
};


// Data
void UInstr::SetDataSrcA(uint32_t srca_data) {
    srca_data_ = srca_data;
};
uint32_t UInstr::GetDataSrcA() {
    return srca_data_;
};
void UInstr::SetDataSrcB(uint32_t srcb_data) {
    srcb_data_ = srcb_data;
};
uint32_t UInstr::GetDataSrcB() {
    return srcb_data_;
};
void UInstr::SetDataDest(uint32_t dest_data) {
    dest_data_ = dest_data;
};
uint32_t UInstr::GetDataDest() {
    return dest_data_;
};
void UInstr::SetDataFlagN(bool value) {
    apsr_data_.set((int)Apsr::n, value);
};
bool UInstr::GetDataFlagN() {
    return apsr_data_.test((int)Apsr::n);
};
void UInstr::SetDataFlagZ(bool value) {
    apsr_data_.set((int)Apsr::z, value);
};
bool UInstr::GetDataFlagZ() {
    return apsr_data_.test((int)Apsr::z);
};
void UInstr::SetDataFlagC(bool value) {
    apsr_data_.set((int)Apsr::c, value);
};
bool UInstr::GetDataFlagC() {
    return apsr_data_.test((int)Apsr::c);
};
void UInstr::SetDataFlagV(bool value) {
    apsr_data_.set((int)Apsr::v, value);
};
bool UInstr::GetDataFlagV() {
    return apsr_data_.test((int)Apsr::v);
};

// Simulation
void UInstr::SetExecUnit(uint8_t unit) {

};
void UInstr::SetLatency(uint8_t latency) {
    latency_ = latency;
};

// Support
void UInstr::PrintDetails() {
    std::cout << "Uop Detail: \n";
    std::cout << " Opcode: " << uop_str[(int)opcode_] << "\n";
    std::cout << " Rd: " << (int) rd_ << "  ";
    std::cout << " Rn: " << (int) rn_ << "  ";
    std::cout << " Immed: " << (int) immed_ << "\n";
    std::cout << " Flag:  ";
    std::cout << "   n: " << (int) set_apsr_[(int)Apsr::n];
    std::cout << "   z: " << (int) set_apsr_[(int)Apsr::z];
    std::cout << "   c: " << (int) set_apsr_[(int)Apsr::c];
    std::cout << "   v: " << (int) set_apsr_[(int)Apsr::v];
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