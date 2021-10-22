#include "decode.h"
#include <armv6m.h>

#include <delay.h>


Delay<uint32_t>*      raw_inst_to_decode_rp = new Delay<uint32_t>("raw_inst_to_decode");
Delay<UInstrPtr>*     decode_to_alloc_wp = new Delay<UInstrPtr>("decode_to_alloc");


Decode::Decode() {
    isa = new Armv6m();
    raw_inst_to_decode_rp->SetLatency(1);
};

// Just modeling the delays, might as well decode right now
void Decode::StartDecode() {
    uint32_t raw_inst;

    UInstrPtr uinstr = std::make_shared<UInstr>();
    DecodeInfoPtr decptr = std::make_shared<DecodeInfo>();
    while (raw_inst_to_decode_rp->Receive(raw_inst, cycle_)) {
        std::cout << "Decode: " << std::hex << raw_inst << "\n";

        if (isa->DecodeInstructions(raw_inst, uinstr)) {
            decptr->ready_for_alloc_cycle_ = cycle_+2;
            decptr->uinstr_ = uinstr;
            decoding_instr.push_back(decptr);
        }
    }
};

/*
    Decode is in order, so keep trying to push until
    hitting a non ready uinstr
*/
void Decode::FinishDecode() {
    for (auto it = decoding_instr.cbegin(); it != decoding_instr.cend();) {
        if ((*it)->ReadyForAlloc(cycle_)) {
            UInstrPtr temp = (*it)->uinstr_;
            std::cout << "Decode: " << std::dec << cycle_ << "\n";
            temp->PrintDetails();
            decode_to_alloc_wp->Send(temp, cycle_);
            it = decoding_instr.erase(it);
        } else {
            break;
        }
    }
};

void Decode::Process(int cycle, bool reset) {
    cycle_ = cycle;

    if (reset) {
        return;
    }
    StartDecode();
    FinishDecode();
    
}

//void Decode::Process() {
//
//};