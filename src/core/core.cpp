#include "core.h"
#include <utility>
#include <vector>
#include <iostream>
#include <parameter.h>
#include <allocate.h>
#include <decode.h>
#include <fetch.h>
#include <rename.h>
#include <execute.h>
#include <rob.h>

Delay<bool>*          fetch_reset_done_rp   = new Delay<bool>("fetch_reset_done");

Core::Core() {
    cycle_ = 0;
    reset_ = true;

    // Structures
    rob_      = std::make_shared<Rob>();

    // Processes
    fetch_    = std::make_unique<Fetch>();
    decode_   = std::make_unique<Decode>();
    allocate_ = std::make_unique<Allocate>();
    rename_   = std::make_unique<Rename>(rob_);
    execute_  = std::make_unique<Execute>();
};


void Core::Process(int cycle) {
    cycle_ = cycle;

    while (fetch_reset_done_rp->Receive(reset_,cycle)) {
    }
    
    fetch_->Process(cycle_, reset_);
    decode_->Process(cycle_, reset_);
    allocate_->Process(cycle_, reset_);
    rename_->Process(cycle_, reset_);
    execute_->Process(cycle_, reset_);
}



//bool Core::Clock() {

    // Check for machine done or stalled too long

    /*uint16_t instr = 0b0000000010101010;
    UInstr temp;
    UInstrPtr tempptr1;
    UInstrPtr tempptr2;
    UInstrPtr tempptr3;
    // LsL Imm
    if (isa->DecodeInstructions(instr, &temp)) {
        tempptr1 = state.NewInstruction(temp);
    }
    // Movs Imm
    //  RD = 1, Imm = FF
    instr = 0b0010000111111111;
    if (isa->DecodeInstructions(instr, &temp)) {
        tempptr2 = state.NewInstruction(temp);
    }
    if (func->ExecuteUop(tempptr2)) {
        std::cout << "Execute successful\n";
    };

    int val;
    bool cin, cout;
    std::tie(val, cin, cout) = func->AddWithCary(1,2,true);
    return false;*/

    //Delay<int> fetch_to_itlb;
    //int value;
    //fetch_to_itlb.Send(2, 100);
    //fetch_to_itlb.Send(3, 120);
    //fetch_to_itlb.Send(4, 143);
    //if (fetch_to_itlb.Receive(value, 120)) {
    //    std::cout << "Found matching: " << (int)value << "\n";
   // }
    //fetch_to_itlb.displayAll();


//    return false;
    // Test Msg
    /*Delay<UInstrPtr> fetch_to_itlb;
    UInstrPtr value = 10;
    fetch_to_itlb.Send(1, 100);
    fetch_to_itlb.Send(4, 120);
    fetch_to_itlb.Send(12, 143);
    fetch_to_itlb.displayAll();
    if (fetch_to_itlb.Receive(value, 120)) {
        std::cout << "Found matching: " << value << "\n";
    }
    if (fetch_to_itlb.Receive(value, 100)) {
        std::cout << "Found matching: " << value << "\n";
    }
    fetch_to_itlb.displayAll();*/  
//}

