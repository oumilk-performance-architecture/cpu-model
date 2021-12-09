#include "allocate.h"
#include <rat.h>
#include <parameter.h>
#include <uinstr.h>
#include <portbind.h>

namespace param {
    parameter<bool>       enable_renaming ("enable_renaming", false);

    parameter<int>        allocation_cycles ("allocation_cycles", 0);
    parameter<int>        portbind_cycles   ("portbind_cycles",   1);
    parameter<int>        rename_cycles     ("rename_cycles",     1);
};


Allocate::Allocate( std::shared_ptr<Rob> rob,
                    std::shared_ptr<RegisterAliasTable> rat,
                    std::shared_ptr<RegisterAliasTable> srat,
                    std::shared_ptr<FreeTable> free_table) {

    rob_        = rob;
    rat_        = rat;
    srat_       = srat;
    free_table_ = free_table;
    decode_to_alloc_rp      = std::make_unique<Delay<UInstrPtr>>("decode_to_alloc");
    alloc_to_exec_wp        = std::make_unique<Delay<UInstrPtr>>("alloc_to_exec");
    decode_to_alloc_rp->SetLatency(1);

    portbind = std::make_shared<Portbind>();

    // Create Pipestages
    allocate_stage_.push_back(AllocPipeStage::Allocation);
    allocate_stage_.push_back(AllocPipeStage::PortBind);
    if (param::enable_renaming) {allocate_stage_.push_back(AllocPipeStage::Allocation);}
    allocate_stage_.push_back(AllocPipeStage::Dispatch);
    // Create Pipestage maps
    //CreatePipeMap();
};

/*  Should we do this instead of having the for loop inside FinishStage?
void Allocate::CreatePipeMap() {
    AllocPipeStage last_stage = AllocPipeStage::Allocation;
    for (auto iter = allocate_stage_.begin(); iter != allocate_stage_.end(); ++iter) {
        AllocPipeStage pipe_stage = (*iter);
        if (pipe_stage != AllocPipeStage::Allocation) {
            allocate_stage_map_[pipe_stage] = last_stage;
        } 
        last_stage = pipe_stage;
    }
}*/

void Allocate::Allocation() {
    // Instructions decoded and ready to allocate
    while (decode_to_alloc_rp->IsReady(cycle_)) {
        UInstrPtr uinstr;
        decode_to_alloc_rp->Receive(uinstr, cycle_);

        std::cout << "Allocation: " << cycle_ << "\n";
        std::cout << "  Uop: " << uinstr->GetOpcodeString() << "\n";

        AllocateInfoPtr allocateInfo = std::make_shared<AllocateInfo>(cycle_, uinstr);
        FinishStage(allocateInfo, 0);
        allocate_queue_.push_back(allocateInfo);
    }
};

void Allocate::PortBind() {
    AllocPipeStage curr_stage = AllocPipeStage::PortBind;
    // Check for Stalls

    // Check for Available
    for (auto iter = allocate_queue_.begin(); iter != allocate_queue_.end(); ++iter) {
        AllocateInfoPtr allocateInfo = (*iter);
        if (allocateInfo->pipestage_==curr_stage &&
            !allocateInfo->done_[curr_stage] &&
            allocateInfo->cycle_[curr_stage] <= cycle_) {
            std::cout << "Port Binding: " << cycle_ << "\n";
            std::cout << "  Uop: " << allocateInfo->uinstr_->GetOpcodeString() << "\n";
            std::cout << "\n";
            UInstrPtr uinstr = allocateInfo->uinstr_;
            portbind->GetPortInformation(uinstr);

            // Assign exec/sched - right now just pick the first...
            uinstr->SetAssignedSched(uinstr->GetSchedUnit()[0]);
            uinstr->SetAssignedExec(uinstr->GetExecUnit()[0]);

            FinishStage(allocateInfo, 1);
        }
    }
};

void Allocate::Rename() {

};

void Allocate::Dispatch() {
    AllocPipeStage curr_stage = AllocPipeStage::Dispatch;
    // Check for Stalls

    // Check for Available
    for (auto iter = allocate_queue_.begin(); iter != allocate_queue_.end(); ++iter) {
        AllocateInfoPtr allocateInfo = (*iter);
        if (allocateInfo->pipestage_==curr_stage &&
            !allocateInfo->done_[curr_stage] &&
            allocateInfo->cycle_[curr_stage] <= cycle_) {
            // Send to Exec and remove from Allocate queue
            UInstrPtr uinstr = allocateInfo->uinstr_;
            alloc_to_exec_wp->Send(uinstr, cycle_);
            allocate_queue_.pop_front();
            //uinstr->PrintDetails();
        } else {
            return;
        }
    }
};

void Allocate::FinishStage(AllocateInfoPtr allocateInfo, int latency) {
    AllocPipeStage pipestage = allocateInfo->pipestage_;

    assert(pipestage != AllocPipeStage::Dispatch);
    // Find Next State
    auto iter = std::find(allocate_stage_.begin(), allocate_stage_.end(), pipestage);
    if (iter != allocate_stage_.end()) {
        iter++;
        allocateInfo->pipestage_ = (*iter);
        allocateInfo->done_[pipestage] = true;
        allocateInfo->cycle_[pipestage] = cycle_;
        allocateInfo->cycle_[(*iter)] = cycle_ + latency;
    }

};

void Allocate::PrintAllocateUops() {
    std::cout << "Allocating Uops, Cycle: " << cycle_ << "\n";
    for (auto iter = allocate_queue_.begin(); iter != allocate_queue_.end(); ++iter) {
        AllocateInfoPtr alloc_ptr = (*iter);
        AllocPipeStage stage = alloc_ptr->pipestage_;
        UInstrPtr uinstr = alloc_ptr->uinstr_;
        std::cout << "  " << uinstr->GetOpcodeString();
        std::cout << ", Stage: " << AllocPipeStage_str[stage];
        std::cout << ", Done: " << alloc_ptr->done_[stage];
        std::cout << ", Cycle: " << alloc_ptr->cycle_[stage];
        std::cout << "\n";
    }
}

void Allocate::Process(int cycle, bool reset) {
    cycle_ = cycle;

    if (reset) {
        return;
    }
    // Always called first
    Allocation();

    // Order shouldn't matter, should be handled by cycle/state logic
    PortBind();
    Rename();

    // Always called last
    Dispatch();

    // Debug
    //PrintAllocateUops();
}