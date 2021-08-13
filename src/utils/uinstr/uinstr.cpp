#include "uinstr.h"
#include <iostream>

UInstr::UInstr() {
};

//UInstr::~UInstr() {
//};

void UInstr::SetExecUnit(uint8_t unit) {

};

void UInstr::SetFlagN(bool value) {
    apsr_.set((int)Apsr::n, value);
};

void UInstr::SetFlagZ(bool value) {
    apsr_.set((int)Apsr::z, value);
};

void UInstr::SetFlagC(bool value) {
    apsr_.set((int)Apsr::c, value);
};

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

void UInstr::SetLatency(uint8_t latency) {
    latency_ = latency;
};

void UInstr::SetImmed(uint8_t immed) {
    immed_ = immed;
};

uint8_t UInstr::GetRd() {
    return rd_;
};

uint8_t UInstr::GetRn() {
    return rn_;
};

uint8_t UInstr::GetRm() {
    return rm_;
};

uint8_t UInstr::GetRa() {
    return ra_;
};

void UInstr::PrintDetails() {
    std::cout << "Uop Detail: \n";
    std::cout << " Rd: " << (int) rd_ << "\n";
    std::cout << " Rn: " << (int) rn_ << "\n";
    std::cout << " Immed: " << (int) immed_ << "\n";
    std::cout << " Flag:\n";
    std::cout << "   n: " << (int) apsr_[(int)Apsr::n];
    std::cout << "   z: " << (int) apsr_[(int)Apsr::z];
    std::cout << "   c: " << (int) apsr_[(int)Apsr::c];
    std::cout << "\n";
};
