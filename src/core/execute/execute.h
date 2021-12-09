#ifndef EXECUTE_H
#define EXECUTE_H

#include <utility>
#include <map>
#include <common.h>
#include <delay.h>

// Forward Class Declaration
class UInstr;
using UInstrPtr = std::shared_ptr<UInstr>;
class Scheduler;
using SchedulerPtr = std::shared_ptr<Scheduler>;
enum class SchedulerUnits;
class Func;


/*
    Class: Execute
    Description: The class centers around a vector of "schedulers"s.  When uinstr is allocated, it will enter the assigned
                 "scheduler" (Int/Float/Mem) and go through the enabled pipestages until it is ready to go back to the ROB.

                 Process - Main function that is called every cycle and calls all other supporting functions
    Main Functions:
        StartExecute  - Receives UINSTR from Allocate Class and pushes into correct queue
        Schedule      - Calls each "scheduler" to process UINSTR
        Reg
        MemQueue      - Calls each memory queue to process load/store
        FinishExec    - Send UINSTR to Retire Class

    To Add Scheduler:
        1 - Modify "portbind.h", SchedulerUnits to add new name
        2 - Modify the "scheduler" with new name/information
        3 - Modify "Execute::Execute", 
        4 - "portbind.h", res_table_
        5 - If Scheduler needs big change, need to create new child class
*/
enum class ExecutePipeStage {
    StartExec,          // Receive UINSTR from Allocate Class
    InsertRS,           // Scheduler Pipe
    InsertMemQueue,     // Ld/St Pipe
    FinishExec,         // Send UINSTR to Retire Class
    count       // Used for size of enum class
};


class Execute {
    public:
        Execute();

        // Main Function - This calls everything that is needed in a "cycle"
        void Process(int cycle, bool reset);

        // Cycle Functions - These try to model specific cyles of the "Execution Stage"
        void StartExec();
        void InsertRS();
        void Issue();
        void ExecuteUInstr();

        // Helper Functions - These are not tied to a cycle but do a specific "job"
        void IssuedUInstr();            // Once instruction is issued, determine where it needs to go
        void Squash();                  // UInstr needs to be squashed
        void RemoveFromScheduler();     // Remove UInstr from scheduler.

    private:
        int cycle_;
        DelayPtr<UInstrPtr> alloc_to_exec_rp;

        DelayPtr<UInstrPtr> issue_uinstr_wp;
        DelayPtr<UInstrPtr> issue_uinstr_rp;

        std::vector<int> source_ready_cycle_;
        std::map<SchedulerUnits,SchedulerPtr> scheduler_;

        std::unique_ptr<Func> func_;

};

#endif // EXECUTE_H