#ifndef DECODE_H
#define DECODE_H

#include <armv6m.h>
#include <deque>

class DecodeInfo {
    public:
        UInstrPtr uinstr_;
        int ready_for_alloc_cycle_;

        DecodeInfo() {
            ready_for_alloc_cycle_ = std::numeric_limits<int>::max();
        }

        bool ReadyForAlloc(int cycle) {return ready_for_alloc_cycle_ <= cycle;};
};
using DecodeInfoPtr = std::shared_ptr<DecodeInfo>;

/*
    Class: Decode
    Structure:
        StartDecode  - Begin decoding instruction
        FinishDecode - Send to Allocation
*/
class Decode {
    public:
        Decode();
        void Process(int cycle, bool reset);
        void StartDecode();
        void FinishDecode();
    
    private:
        std::deque<DecodeInfoPtr> decoding_instr;
        int cycle_;
        Armv6m *isa;

};


#endif // DECODE_H