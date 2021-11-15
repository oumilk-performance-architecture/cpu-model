#include "execute.h"

Execute::Execute() {
    alloc_to_exec_rp        = std::make_unique<Delay<UInstrPtr>>("alloc_to_exec");
};

void Execute::InsertRS() {
    
};

void Execute::Process(int cycle, bool reset) {
    cycle_ = cycle;
    InsertRS();
};
