#include "scheduler.h"
#include <uinstr.h>

/*
    Class: CycleTracker
*/
CycleTracker::CycleTracker(int num_ports, int window) {
    in_use_cycle_.resize(num_ports, std::vector<int>(1<<window, std::numeric_limits<uint8_t>::max()));
    cycle_mask_ = (1 << window) - 1;
};

bool CycleTracker::IsAvailable(int port, int cycle) {
    int masked = cycle_mask_ & cycle;
    if (in_use_cycle_[port][masked] == std::numeric_limits<uint8_t>::max()) {
        return true;
    }
    return false;
};

void CycleTracker::Reserve(int port, int cycle, UInstrPtr uinstr) {
    int masked = cycle_mask_ & cycle;
    if (IsAvailable(port, cycle)) {
        in_use_cycle_[port][masked] = uinstr->GetRobID();
    } else {
        throw std::runtime_error("Unable to reserve cycle\n");
    }
};

void CycleTracker::Release(int port, int cycle) {
    int masked = cycle_mask_ & cycle;
    in_use_cycle_[port][masked] = std::numeric_limits<int>::max();
};

/*
    Scheduler
*/
Scheduler::Scheduler(SchedulerUnits sched, int num_entries, int num_ports, std::vector<int>& source_ready_cycle):
    source_ready_cycle_(source_ready_cycle) { 
    num_entries_ = num_entries;
    num_ports_   = num_ports;
    sched_       = sched;

    res_station_.reserve(num_entries);

    writeback_usage_ = std::make_unique<CycleTracker>(num_ports, 5);
    exec_usage_      = std::make_unique<CycleTracker>(num_ports, 5);
};
int
Scheduler::NumFreeEntries() {
    return num_entries_ - res_station_.size();
};
void
Scheduler::Insert(UInstrPtr uinstr) {
    if (NumFreeEntries() <= 0) {
        std::cout << "Reservation Full, cannot insert\n";
        throw std::logic_error("Reservation Full, cannot insert");
    } 
    res_station_.push_back(uinstr);
};
void 
Scheduler::Deallocate(UInstrPtr uinstr) {
    auto entry = std::find(res_station_.begin(), res_station_.end(), uinstr);
    if (entry != res_station_.end()) {
        res_station_.erase(entry);
    }
};
bool
Scheduler::AreSourcesReady(UInstrPtr uinstr, int cycle) {
    bool rs1_ready = uinstr->ValidRs1() ? (source_ready_cycle_[uinstr->GetPhysRs1()] <= cycle) : true;
    bool rs2_ready = uinstr->ValidRs2() ? (source_ready_cycle_[uinstr->GetPhysRs2()] <= cycle) : true;
    return rs1_ready && rs2_ready;
};
UInstrPtr
Scheduler::PickOldest(int port, int cycle) {
    // Check the following:
    //   - Sources Ready
    //   - Not Issued Already
    //   - WB Slot Available  
    //   - Exec Slot Available
    for (UInstrPtr uinstr : res_station_) {
        // Ready? - add port check
        if ((uinstr->GetPort() != port) || uinstr->GetIssued() || !AreSourcesReady(uinstr, cycle) ) {
            continue;
        }
        // WB and Exec slot available
        int wb_cycle = cycle + uinstr->GetLatency(); // + writeback cycles
        int exec_cycle = cycle;
        if (exec_usage_->IsAvailable(port, exec_cycle) &&
            writeback_usage_->IsAvailable(port, wb_cycle)
           ) {
            writeback_usage_->Reserve(port, wb_cycle, uinstr);
            exec_usage_->Reserve(port, exec_cycle, uinstr);
            uinstr->SetIssued(true);
            return uinstr;
        }
    }
    return nullptr;
};