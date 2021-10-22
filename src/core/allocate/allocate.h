#ifndef ALLOCATE_H
#define ALLOCATE_H

#include <utility>
#include <deque>

#include <portbind.h>
#include <delay.h>

class UInstr;
using UInstrPtr = std::shared_ptr<UInstr>;
/*class AllocateInfo {
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
*/
class Allocate {
    public:
        Allocate();
        void Process(int cycle, bool reset);
        void PortBind();
    private:
        DelayPtr<UInstrPtr> decode_to_alloc_rp;
        DelayPtr<UInstrPtr> allocate_to_portbind_wp;
        DelayPtr<UInstrPtr> allocate_to_portbind_rp;
        DelayPtr<UInstrPtr> pb_to_rename_wp;
        std::unique_ptr<Portbind> portbind;
        int cycle_;
};

#endif // ALLOCATE_H