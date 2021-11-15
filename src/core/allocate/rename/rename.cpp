#include "rename.h"
#include <utility>
#include <iostream>
#include <iomanip>
#include <parameter.h>
#include <uinstr.h>
#include <rob.h>
/*
    Rename
    Details: Architectural restrictions on renaming u-instructions (# allocations, types, etc)
*/

namespace param {
    parameter<bool>       enable_renaming ("enable_renaming", false);
    parameter<int>        num_arch_reg ("num_arch_reg", 32);
    extern parameter<int> num_phys_reg;
};

Rename::Rename(std::shared_ptr<Rob> rob,
               std::shared_ptr<RegisterAliasTable> rat,
               std::shared_ptr<RegisterAliasTable> srat,
               std::shared_ptr<FreeTable> free_table) {
    // Ports
    pb_to_rename_rp          = std::make_unique<Delay<UInstrPtr>>("pb_to_rename");
    rename_to_reservation_wp = std::make_unique<Delay<UInstrPtr>>("rename_to_reservation");
    allocate_rob_wp          = std::make_unique<Delay<UInstrPtr>>("allocate_rob");

    // Connect to structures
    rob_ = rob;
    rat_ = rat;
    srat_ = srat;
    free_table_ = free_table;
};

void Rename::Process(int cycle, bool reset) {
    cycle_ = cycle;
    ClaimRob();
    RenameRegisters();
};

void Rename::ClaimRob() {
    rob_->Dispatch();
}

void Rename::RenameRegisters() {

    while (pb_to_rename_rp->IsReady(cycle_)) {
        UInstrPtr uinstr;

        // Check for stall scenarios

        // Good to Rename
        pb_to_rename_rp->Receive(uinstr, cycle_);
        std::cout << "Rename: " << std::dec << cycle_ << "\n";

        // Sources - Check to see what sources are there    
        if (uinstr->GetRs1() <= param::num_arch_reg) {
            uinstr->SetPhysSrcA(srat_->Get(uinstr->GetRs1()));
        }
        if (uinstr->GetRs2() <= param::num_arch_reg) {
            uinstr->SetPhysSrcB(srat_->Get(uinstr->GetRs2()));
        }
        // Destination
        if (uinstr->GetRd() <= param::num_arch_reg) {
            int phys_dest = ClaimPhysicalRegister(uinstr->GetRd());
            srat_->Set(uinstr->GetRd(), phys_dest);
        }
        
        rename_to_reservation_wp->Send(uinstr, cycle_);
    };
};

int Rename::MapSpeculativeRegister(int reg) {
    if (!param::enable_renaming)
        return reg;
    return srat_->Get(reg);
}

int Rename::ClaimPhysicalRegister(int arch_reg) {
    if (!param::enable_renaming)
        return arch_reg;
    
    if (free_table_->Available()) {
        int phys_reg = free_table_->Claim();
        rat_->Set(arch_reg, phys_reg);
        return phys_reg;
    }
    return -1;
};

void Rename::PrintState() {
    std::cout << std::right;
    std::cout << std::setw(3) << "Reg";
    std::cout << std::setw(6) << "SRAT";
    std::cout << std::setw(6) << "RAT";
    std::cout << "\n";
    for (auto i = 0; i < param::num_phys_reg; i++) {
        std::cout << std::setw(3) << i;
        std::cout << std::setw(6) << srat_->Get(i);
        std::cout << std::setw(6) << rat_->Get(i);
        std::cout << "\n";
    }
    std::cout << "\n";
};

void Rename::PrintFreeList() {
    std::cout << "Number of physical registers: " << param::num_phys_reg << "\n";
    std::cout << "List of free physical registers: \n";
    //for (auto it = free_list_.cbegin(); it != free_list_.cend(); ++it) {
    //    std::cout << *it << ", ";
    //}
    std::cout << "\n";
};