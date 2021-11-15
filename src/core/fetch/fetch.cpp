#include "fetch.h"
#include <iostream>
#include <idata.h>
#include <delay.h>
#include <parameter.h>


Delay<uint32_t>*      bus_return_info_rp    = new Delay<uint32_t>("bus_return_info");
Delay<uint32_t>*      raw_inst_to_decode_wp = new Delay<uint32_t>("raw_inst_to_decode");
Delay<bool>*          fetch_reset_done_wp   = new Delay<bool>("fetch_reset_done");

namespace param {
    parameter<int>    pc_increment("pc_increment", 4);
}

// Notes:
//  ARM's PC register [15] is the current instruction plus 8 bytes.  That's confusing to figure out if we are in a deep pipeline
//  so for now just keep track of PC locally and try our best to update the [15] register
Fetch::Fetch() {
    pc_ = -4; //0x4;
    reset_ = false;
    nip_fetch_mem_wp   = new Delay<uint32_t>("nip_fetch_mem");
};

//Fetch::~Fetch() {
//    delete nip_fetch_mem_wp;
//}

void Fetch::Process(int cycle, bool reset) {
    cycle_ = cycle;

    // Reset Process - should be a better way of doing this
    //  RiscV Process
    //    Just start at 0x00 and go from there
    /*if (reset) {
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
        
    }*/
    std::shared_ptr<Idata> idata = CalculateNextPc();
    // Next PC - make into class later on with branch prediction
    pc_ = idata->GetIp(); 
    // ICache

    // Temp - Memory Access (Need to move this to memory unit/cache)
    nip_fetch_mem_wp->Send(pc_, cycle_);
    uint32_t raw_inst;
    while (bus_return_info_rp->Receive(raw_inst, cycle_)) {
        idata->SetData(raw_inst);
        //std::cout << "Raw Instruction: " << std::hex << (int)idata->GetData() << "\n";
        //std::cout << "  PC: " << std::dec << (int) pc_ << "\n";
        //std::cout << "  Cycle: " << std::dec << (int) cycle_ << "\n";
        
        raw_inst_to_decode_wp->Send(raw_inst, cycle_);   
    }

    // Send to Decoder
    

};

std::unique_ptr<Idata> Fetch::CalculateNextPc() {
    std::unique_ptr<Idata> idata = std::make_unique<Idata>(cycle_);
    idata->SetIp(pc_ + (int)param::pc_increment);
    
    return idata;
}
