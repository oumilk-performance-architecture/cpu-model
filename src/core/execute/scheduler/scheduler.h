#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <utility>
#include <vector>
#include <deque>
#include <map>

/*
    File: scheduler.h
    Description: Contains implementations of following classes:
        - CycleTracker - base queue used to track which cycles are currently "occupied"
        - Scheduler - base queue used to schedule instructions

*/

// Forward Class Declaration
class UInstr;
using UInstrPtr = std::shared_ptr<UInstr>;
enum class SchedulerUnits;

/*
    Class: CycleTracker
    Description: This class is the base class for tracking cycle usage (WB/EXEC)
      - Use mask to track cycles, considered using std::rotate to track 
        and "decrement" each cycle but seems a bit more complicated that way.
*/
class CycleTracker {
    public:
        CycleTracker(int num_ports, int window);
        void Release(int port, int cycle);
        void Reserve(int port, int cycle, UInstrPtr uinstr);
        bool IsAvailable(int port, int cycle);

    private:
        int cycle_mask_;
        std::vector<std::vector<int>> in_use_cycle_;
};
using CycleTrackerPtr = std::unique_ptr<CycleTracker>;

/*
    Class: Scheduler
    Description: 
*/
class Scheduler {
    public:
        Scheduler(SchedulerUnits sched, int num_entries, int num_ports, std::vector<int>& source_ready_cycle);
        int       NumFreeEntries();
        void      Insert(UInstrPtr uinstr);
        void      Deallocate(UInstrPtr uinstr);
        bool      AreSourcesReady(UInstrPtr uinstr, int cycle);
        UInstrPtr PickOldest(int port, int cycle);
        
        // Helper Functions
        void Squash(UInstrPtr uinstr);
        void Remove(UInstrPtr uinstr);

        inline int NumPorts() { return num_ports_; };

    protected:
        std::vector<int>& source_ready_cycle_;
        std::vector<UInstrPtr> res_station_;
        int num_entries_;
        int num_ports_;
        SchedulerUnits sched_;

        CycleTrackerPtr writeback_usage_;
        CycleTrackerPtr exec_usage_;
};

#endif // SCHEDULER_H