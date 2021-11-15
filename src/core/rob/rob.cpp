#include "rob.h"
#include <parameter.h>
/*
    Rob
    Details: Simple ROB structure, all the architectural restrictions should be implemented outside of this
             (i.e. # deallocations, # allocations, etc)
*/

namespace param {
    parameter<int>        num_rob_entries ("num_rob_entries", 40);
};

Rob::Rob():
    table_(param::num_rob_entries) {
    //table_(param::num_rob_entries.value()) {
    // ROB pointers
    rob_head_ = 0;
    rob_tail_ = 0;
    num_dispatched_ = 0;

};
    
int Rob::Dispatch() {
    // Validate that it is possible to dispatch
    if (num_dispatched_ >= param::num_rob_entries) {
        throw std::length_error("ROB is full, cannot dispatch another uop");
    }
    // Increment and allocate
    num_dispatched_++;
    table_[rob_tail_].finished = false;
    
    return IncrementPointer(rob_tail_);
};

int Rob::IncrementPointer(int &rob_ptr) {
    rob_ptr++;
    if (rob_ptr >= param::num_rob_entries) {
        rob_ptr = 0;
        return param::num_rob_entries-1;
    }
    return rob_ptr;
}

void Rob::CommitUInstr(int rob_entry) {
    table_[rob_entry].finished = true;
}

bool Rob::Commit(int num_uops) {
    int temp_head_ptr = rob_head_;
    bool can_dealloc = true;
    auto temp_num_uops = num_uops;
    while (temp_num_uops-- > 0) {
        can_dealloc &= table_[temp_head_ptr].finished;
        IncrementPointer(temp_head_ptr);
    }
    if (can_dealloc) {
        rob_head_ = temp_head_ptr;
        num_dispatched_ = num_dispatched_ - num_uops;
    }
    return can_dealloc;
};

int Rob::EntriesAvailable() {
    return param::num_rob_entries-num_dispatched_;
}