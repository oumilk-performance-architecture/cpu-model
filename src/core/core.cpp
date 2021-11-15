#include "core.h"
#include <utility>
#include <vector>
#include <iostream>
#include <parameter.h>
#include <allocate.h>
#include <decode.h>
#include <fetch.h>
#include <execute.h>
#include <rob.h>

Delay<bool>*          fetch_reset_done_rp   = new Delay<bool>("fetch_reset_done");

namespace param {
    extern parameter<int> num_phys_reg;
    parameter<int>        num_arch_reg ("num_arch_reg", 32);
}

Core::Core() {
    cycle_ = 0;
    reset_ = false;

    // Global Structures
    rob_  = std::make_shared<Rob>();
    rat_  = std::make_shared<RegisterAliasTable>(param::num_arch_reg);
    srat_ = std::make_shared<RegisterAliasTable>(param::num_arch_reg);
    free_table_ = std::make_shared<FreeTable>(param::num_phys_reg);

    // Processes
    fetch_    = std::make_unique<Fetch>();
    decode_   = std::make_unique<Decode>();
    allocate_ = std::make_unique<Allocate>(rob_, rat_, srat_, free_table_);
    execute_  = std::make_unique<Execute>();
    // Retire

    // Global States  
};


void Core::Process(int cycle) {
    cycle_ = cycle;

    //while (fetch_reset_done_rp->Receive(reset_,cycle)) {
    //}
    
    fetch_->Process(cycle_, reset_);
    decode_->Process(cycle_, reset_);
    allocate_->Process(cycle_, reset_);
    execute_->Process(cycle_, reset_);
}