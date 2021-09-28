#include "fetch.h"
#include <iostream>
#include <idata.h>
#include <delay.h>


Delay<uint32_t>*      bus_return_info_rp    = new Delay<uint32_t>("bus_return_info");
Delay<uint32_t>*      raw_inst_to_decode_wp = new Delay<uint32_t>("raw_inst_to_decode");
Delay<bool>*          fetch_reset_done_wp   = new Delay<bool>("fetch_reset_done");

// Notes:
//  ARM's PC register [15] is the current instruction plus 8 bytes.  That's confusing to figure out if we are in a deep pipeline
//  so for now just keep track of PC locally and try our best to update the [15] register
Fetch::Fetch() {
    pc_ = 0x4;
    reset_ = false;
    nip_fetch_mem_wp   = new Delay<uint32_t>("nip_fetch_mem");
};

Fetch::~Fetch() {
    delete nip_fetch_mem_wp;
}

void Fetch::Process(int cycle, bool reset) {
    cycle_ = cycle;

    // Reset Process - should be a better way of doing this
    //  ARM Cortex-M Reset Process 
    //    Read 0x04 and set the PC to whatever is stored there.
    //    It checks for the lsbit to see if it is a valid thumb address, strips it off then begins fetch
    if (reset) {
        // First reset cycle, send out request for start address
        if (reset_ == false) {
            nip_fetch_mem_wp->Send(0x04, cycle);
            reset_ = reset;
        }
        while (bus_return_info_rp->Receive(pc_, cycle)) {
            if ((pc_ & 0x1) == 0) {
                // This isn't supported THUMB ARM dode
            };
            pc_&=~1;
            fetch_reset_done_wp->Send(false, cycle);
        }
        return;
    }
    std::shared_ptr<Idata> idata = CalculateNextPc();
    // Next PC - make into class later on with branch prediction
    pc_ = idata->GetIp(); 
    // ICache

    // Temp - Memory Access (Need to move this to memory unit/cache)
    nip_fetch_mem_wp->Send(pc_-2, cycle_);
    uint32_t raw_inst;
    while (bus_return_info_rp->Receive(raw_inst, cycle_)) {
        idata->SetData(raw_inst);
        //std::cout << "Raw Instruction: " << (int)idata->GetData() << "\n";
        
        raw_inst_to_decode_wp->Send(raw_inst, cycle_);   
    }

    // Send to Decoder
    

};

std::unique_ptr<Idata> Fetch::CalculateNextPc() {
    std::unique_ptr<Idata> idata = std::make_unique<Idata>(cycle_);
    idata->SetIp(pc_ + 2);
    
    return idata;
}
