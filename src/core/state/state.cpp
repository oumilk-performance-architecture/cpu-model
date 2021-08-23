#include "state.h"
#include <uinstr.h>
#include <idata.h>
#include <iostream>
#include <memory.h>

/*
    Class: State
    Responsible for storing current "state" of the machine, allowing
    everything else to just use pointers to here
        - Fetch Information (Idata)
        - Instructions (UInstr)
*/
State::State() {

}

void State::ListInstructions() {
    auto it = deque_instructions.begin();
    while (it != deque_instructions.end()) {
        it->PrintDetails();
        *it++;
    }
}

UInstrPtr State::NewInstruction(UInstr uop) {
    deque_instructions.push_back(uop);
    UInstrPtr ptr = &deque_instructions.back();

    return ptr;
    //return dynamic_cast<UInstrPtr>(&deque_instructions.back());
}

void State::DeleteOldest() {
    deque_instructions.pop_front();
}