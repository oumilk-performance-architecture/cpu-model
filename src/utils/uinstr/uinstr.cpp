#include "uinstr.h"
#include <portbind.h>
#include <iostream>

/*enum class source_reg {
    RN,
    RM,
    RA,
    RT
};*/

UInstr::UInstr() {
    // Max is "unassigned"
    arch_rd_  = std::numeric_limits<uint8_t>::max();
    arch_rs1_ = std::numeric_limits<uint8_t>::max();
    arch_rs2_ = std::numeric_limits<uint8_t>::max();
    phys_rd_  = std::numeric_limits<uint8_t>::max();
    phys_rs1_ = std::numeric_limits<uint8_t>::max();
    phys_rs2_ = std::numeric_limits<uint8_t>::max();
    port_     = 0;
};

// Logical
void UInstr::SetOpcode(Uop opcode) {
    opcode_ = opcode;
};
Uop UInstr::GetOpcode() {
    return opcode_;
};

// ISA
void UInstr::SetRd(uint8_t rd) {
    SetArchRd(rd);
    SetPhysRd(rd);
};
void UInstr::SetRs1(uint8_t rs1) {
    SetArchRs1(rs1);
    SetPhysRs1(rs1);
};
void UInstr::SetRs2(uint8_t rs2) {
    SetArchRs2(rs2);
    SetPhysRs2(rs2);
};
void UInstr::SetRobID(uint16_t rob_id) {
    rob_id_ = rob_id;
}
// Architectural
void UInstr::SetArchRd(uint8_t arch_rd) {
    arch_rd_ = arch_rd;
};
void UInstr::SetArchRs1(uint8_t arch_rs1) {
    arch_rs1_ = arch_rs1;
};
void UInstr::SetArchRs2(uint8_t arch_rs2) {
    arch_rs2_ = arch_rs2;
};
// Physical
void UInstr::SetPhysRd(uint16_t phys_rd) {
    phys_rd_ = phys_rd;
};
void UInstr::SetPhysRs1(uint16_t phys_rs1) {
    phys_rs1_ = phys_rs1;
};
void UInstr::SetPhysRs2(uint16_t phys_rs2) {
    phys_rs2_ = phys_rs2;
};
// Immediate Information
void UInstr::SetImmed(uint32_t immed) {
    immed_ = immed;
};
// Data
void UInstr::SetDataRd(uint32_t data_rd) {
    data_rd_ = data_rd;
};
void UInstr::SetDataRs1(uint32_t data_rs1) {
    data_rs1_ = data_rs1;
};
void UInstr::SetDataRs2(uint32_t data_rs2) {
    data_rs2_ = data_rs2;
};
// Simulation
void UInstr::SetExecUnit(std::vector<ExecUnits> unit) {
    exec_units_ = unit;
};
void UInstr::SetLatency(int latency) {
    latency_ = latency;
};
void UInstr::SetSchedUnit(std::vector<SchedulerUnits> unit) {
    sched_units_ = unit;
};
void UInstr::SetIssued(bool issued) {
    issued_ = issued;
}
void UInstr::SetPort(int port) {
    port_ = port;
}

// Assigned
void UInstr::SetAssignedSched(SchedulerUnits sched) {
    assigned_sched_ = sched;
}
void UInstr::SetAssignedExec(ExecUnits exec) {
    assigned_exec_ = exec;
}

// Support
std::string UInstr::GetOpcodeString() {
    return uop_str[(int)opcode_];
}
void UInstr::PrintDetails() {
    std::cout << "Uop Detail: \n";
    std::cout << " Opcode: " << uop_str[(int)opcode_] << ", Latency: " << latency_ << "\n";
    std::cout << "        Arch - Rd: " << (int) arch_rd_ << ", RS1: " << (int) arch_rs1_ << ", RS2: " << (int) arch_rs2_;
    std::cout << ", Immed: " << (int) immed_ << "\n";
    std::cout << "        Phys - Rd: " << (int) phys_rd_ << ", RS1: " << (int) phys_rs1_ << ", RS2: " << (int) phys_rs2_ << "\n";
    PrintExec();
    std::cout << "\n";
};

void UInstr::PrintExec() {
    std::cout << "  Exec Units: ";
    for (auto it = exec_units_.begin(); it != exec_units_.end(); it++) {
        std::cout << execunits_str[(*it)] << " ";
        //std::cout << (int)(*it) << " ";
    }
    std::cout << "\n";
    std::cout << "  Scheduler:  ";
    for (auto it = sched_units_.begin(); it != sched_units_.end(); it++) {
        std::cout << schedulerUnits_str[(*it)] << " ";
        //std::cout << (int)(*it) << " ";
    }
    std::cout << "\n";
};

void UInstr::PrintResults() {
    std::cout << "Opcode: " << uop_str[(int)opcode_] << "\n";
    std::cout << "  RS1: " << (int) data_rs1_ << "  ";
    std::cout << "  RS2: " << (int) data_rs2_ << "\n";
    std::cout << "  RD:  " << (int) data_rd_ << "\n";
    std::cout << "\n";
}

std::ostream & operator << (std::ostream &out, UInstr &c)
{
    out << "UInstr Opcode: " << uop_str[(int)c.GetOpcode()] << "\n";
    out << "  Rd: " << (int)c.GetArchRd();
    out << "  Immed: " << (int)c.GetImmed() << "\n";
    return out;
}