#include "allocate.h"

#include <delay.h>

Delay<UInstrPtr>*     decode_to_alloc_rp = new Delay<UInstrPtr>("decode_to_alloc");

Allocate::Allocate() {
    decode_to_alloc_rp->SetLatency(1);
};

void Allocate::StartAllocate() {
    UInstrPtr uinstr = std::make_shared<UInstr>();
    while (decode_to_alloc_rp->Receive(uinstr, cycle_)) {
        std::cout << "Allocate: " << std::dec << cycle_ << "\n";
        AllocateInfoPtr alloc_ptr = std::make_shared<AllocateInfo>(cycle_);
        alloc_ptr->uinstr_ = uinstr;
        alloc_ptr->uinstr_->PrintDetails();
        alloc_ptr->ready_for_portbind_cycle_ = cycle_ + 1;
        allocate_instr.push_back(alloc_ptr);
    }
}

void Allocate::PortBind() {
    UInstrPtr uinstr;
    for (auto it = allocate_instr.cbegin(); it != allocate_instr.cend();) {
        if ((*it)->ReadyForPortBind(cycle_)) {
            std::cout << "Port Bind: " << std::dec << cycle_ << "\n";
            uinstr = (*it)->uinstr_;
            portbind.PortBindInstructions(uinstr);
            (*it)->portbind_done_ = true;
            (*it)->uinstr_->PrintDetails();
        }
        it++;
    }
}
/*
    Should have:
        cracked
        port_bound
        memory_renamed
*/
void Allocate::FinishAllocate() {

}

void Allocate::Process(int cycle, bool reset) {
    cycle_ = cycle;

    if (reset) {
        return;
    }
    StartAllocate();
    PortBind();
    FinishAllocate();
}