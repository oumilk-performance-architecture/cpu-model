#include "execute.h"
#include <parameter.h>
#include <scheduler.h>
#include <uinstr.h>
#include <func.h>
#include <portbind.h>

namespace param {
    parameter<int>        num_entries_agu0 ("num_entries_agu0", 15);
    parameter<int>        num_entries_int0 ("num_entries_int0", 15);
};

Execute::Execute() {
    source_ready_cycle_.resize(100); // This should be replaced by all the registers in the physical register

    alloc_to_exec_rp        = std::make_unique<Delay<UInstrPtr>>("alloc_to_exec");

    // Enabled Scheduler
    scheduler_[SchedulerUnits::AGU0] = std::make_unique<Scheduler>(SchedulerUnits::AGU0, param::num_entries_agu0, 1, source_ready_cycle_);

    // Functional Units
    func_ = std::make_unique<Func>();

    // WP/RP
    issue_uinstr_wp      = std::make_unique<Delay<UInstrPtr>>("issue_uinstr");
    issue_uinstr_rp      = std::make_unique<Delay<UInstrPtr>>("issue_uinstr");
};

/*
    Sends UINSTR to assigned "scheduler"
*/
void Execute::InsertRS() {
    UInstrPtr uinstr;
    SchedulerUnits sched;
    while (alloc_to_exec_rp->Receive(uinstr, cycle_)) {
        sched = uinstr->GetAssignedSched();

        std::cout << "Insert RS (" << cycle_ << "): ";
        std::cout << "  Sched: " << schedulerUnits_str[sched] << "\n";
        scheduler_[sched]->Insert(uinstr);
    }
};
void Execute::Issue() {
    UInstrPtr uinstr;
    for (auto const& [sched, schedPtr] : scheduler_) {
        for (auto port = 0; port < schedPtr->NumPorts(); port++) {
            uinstr = schedPtr->PickOldest(port, cycle_ + 1);
            if (uinstr != nullptr) {
                std::cout << "Issuing - " << uinstr->GetOpcodeString() << "\n";
                issue_uinstr_wp->Send(uinstr, cycle_);
            }
        }
    }
}
/*
    Execute the instruction and add to queue
*/
void Execute::ExecuteUInstr() {
    UInstrPtr uinstr;
    while (issue_uinstr_rp->Receive(uinstr, cycle_)) {
        if (uinstr->GetIssued()) {
            std::cout << "Executing\n";
            // Execute the Uop
            if (!func_->ExecuteUop(uinstr)) {
                // Execution didn't happen, something is wrong
            } else {
                std::cout << "Executing for real\n";
            }
        }
    }
}

void Execute::Process(int cycle, bool reset) {
    cycle_ = cycle;

    // Goal here is that these don't have to be in order and they should all be "cycle" dependent instead
    InsertRS();
    Issue();
    ExecuteUInstr();

    // Helper functions should be called here so they do the work after everything else is done
    // RemoveFromScheduler();
    // Writeback
};
