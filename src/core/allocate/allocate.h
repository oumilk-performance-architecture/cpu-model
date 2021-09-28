#ifndef ALLOCATE_H
#define ALLOCATE_H

#include <uinstr.h>
#include <portbind.h>
#include <deque>

class AllocateInfo {
    public:
        UInstrPtr uinstr_;
        int alloc_start_cycle_;
        int ready_for_portbind_cycle_;
        bool portbind_done_;
        bool rename_done_;

        AllocateInfo(int cycle) {
            alloc_start_cycle_ = cycle;
            ready_for_portbind_cycle_ = std::numeric_limits<int>::max();
            portbind_done_ = false;
            rename_done_   = false;
        }
        bool ReadyForPortBind(int cycle) { return !portbind_done_ && (ready_for_portbind_cycle_ <= cycle);};
};
using AllocateInfoPtr = std::shared_ptr<AllocateInfo>;
  
class Allocate {
    public:
        Allocate();
        void Process(int cycle, bool reset);
        void StartAllocate();
        void PortBind();
        void Rename();
        void FinishAllocate();
    private:
        Portbind portbind;
        std::deque<AllocateInfoPtr> allocate_instr;
        int cycle_;
};

#endif // ALLOCATE_H