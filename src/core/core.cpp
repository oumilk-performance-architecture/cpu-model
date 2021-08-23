#include "core.h"
#include <utility>
#include <vector>
#include <iostream>
#include <fetch.h>
#include <armv6m.h>
#include <uinstr.h>
#include <uop.h>
#include <parameter.h>
#include <delay.h>

#include <state.h> // Temporary - should be in main.cpp?
#include <func.h> // For sure temporary...remove to exec unit
Core::Core() {
    fetch = new Fetch();
    isa = new Armv6m();
    func = new Func();

};

void Core::Clock() {
    uint16_t instr = 0b0000000010101010;
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
    tempptr2->PrintResults();


    /*Delay<UInstrPtr> fetch_to_itlb;
    UInstrPtr value;
    fetch_to_itlb.Send(tempptr1, 100);
    fetch_to_itlb.Send(tempptr2, 120);
    fetch_to_itlb.Send(tempptr3, 143);
    if (fetch_to_itlb.Receive(value, 120)) {
        std::cout << "Found matching: " << value << "\n";
    }
    fetch_to_itlb.displayAll();

    tempptr1->SetImmed(300);
    
    fetch_to_itlb.displayAll(); */

    /*parameter<int> num_knobs ("num_knobs", 3);
    parameter<bool> out_of_order ("out_of_order", true);

    if (num_knobs==3) {
        std::cout << "Yay: this seems to be working\n";
    }
    if (out_of_order == true) {
        std::cout << "we are out of order!\n";
    }
    std::cout << "num_knobs: " << num_knobs << "\n";*/
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
}


Core::~Core() {
    delete fetch;
};

