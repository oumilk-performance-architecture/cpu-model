#include "allocate.h"
#include <uinstr.h>

Allocate::Allocate() {
    decode_to_alloc_rp      = std::make_unique<Delay<UInstrPtr>>("decode_to_alloc");
    allocate_to_portbind_wp = std::make_unique<Delay<UInstrPtr>>("allocate_to_portbind");
    allocate_to_portbind_rp = std::make_unique<Delay<UInstrPtr>>("allocate_to_portbind");
    pb_to_rename_wp         = std::make_unique<Delay<UInstrPtr>>("pb_to_rename");
    decode_to_alloc_rp->SetLatency(1);

    portbind = std::make_unique<Portbind>();
};

void Allocate::PortBind() {
    // Any instructions decoded and ready?
    while (decode_to_alloc_rp->IsReady(cycle_)) {
        UInstrPtr uinstr;
        // Check for Stalls

        // Port Bind Preference from Port Bind File
        decode_to_alloc_rp->Receive(uinstr, cycle_);
        //std::cout << "Allocate: " << std::dec << cycle_ << "\n";
        portbind->PortBindInstructions(uinstr);
        //uinstr->PrintDetails();

        // Port Bind Logic

        // Send to Next Stage
        pb_to_rename_wp->Send(uinstr, cycle_);
    }
};

void Allocate::Process(int cycle, bool reset) {
    cycle_ = cycle;

    if (reset) {
        return;
    }
    PortBind();
}