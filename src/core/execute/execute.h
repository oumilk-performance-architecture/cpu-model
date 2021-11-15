#ifndef EXECUTE_H
#define EXECUTE_H

#include <utility>
#include <common.h>
#include <delay.h>

// Forward Class Declaration
class UInstr;
using UInstrPtr = std::shared_ptr<UInstr>;


/*
    Class: Execute
    Description: The class centers around the deque "execute_queue".  When uinstr is allocated, it will enter the "execute_queue" and
                 go through the enabled pipestages until it is ready to go back to the ROB

                 Process - Main function that is called every cycle and calls all other supporting functions

    To Add Pipestage:
        1 - Modify "ExecutePipeStage" to add the new pipestage name and where it should be located at.
        2 - Modify "ExecuteInfo" to add cycle_"pipestage"
        3 - Add function that will handle the pipestage details
*/
enum class ExecutePipeStage {
    StartExec,
    RS,
    Exec,
    FinishExec,
    count       // Used for size of enum class
};

static const enum_array<ExecutePipeStage, std::string, 4> ExecutePipeStage_str = {
    "StartExec",
    "RS",
    "Exec",
    "FinishExec",
};

class Execute {
    public:
        Execute();

        void Process(int cycle, bool reset);
        void InsertRS();

    private:
        int cycle_;
        DelayPtr<UInstrPtr> alloc_to_exec_rp;

};

#endif // EXECUTE_H