#ifndef STATE_H
#define STATE_H

#include <deque>
#include <uinstr.h>
#include <idata.h>

class State {
    public:
        State();
        UInstrPtr NewInstruction(UInstr uop);
        void ListInstructions();
        void DeleteOldest();

    private:
        std::deque<UInstr> deque_instructions;

};

#endif //STATE_H