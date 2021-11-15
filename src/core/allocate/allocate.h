#ifndef ALLOCATE_H
#define ALLOCATE_H

#include <utility>
#include <deque>

#include <portbind.h>
#include <delay.h>
#include <common.h>

class UInstr;
using UInstrPtr = std::shared_ptr<UInstr>;
class FreeTable;
class RegisterAliasTable;
class Rob;

/*
    Class: Allocate
    Description: The class centers around the deque "allocate_queue".  When uinstr is fetched, it will enter the "allocate_queue" and
                 go through the enabled pipestages until it is ready to go into the reservation stations

                 Process - Main function that is called every cycle and calls all other supporting functions
                 PortBind - Handles port binding logic
                 Rename   - Handles renaming logic 
    To Add Pipestage:
        1 - Modify "AllocPipeStage" to add the new pipestage name and where it should be located at.
        2 - Modify "AllocateInfo" to add cycle_"pipestage"
        3 - Add function that will handle the pipestage details
*/

enum class AllocPipeStage {
    Allocation,
    PortBind,
    Rename,
    Dispatch,
    count       // Used for size of enum class
};

static const enum_array<AllocPipeStage, std::string, 4> AllocPipeStage_str = {
    "Allocation",
    "PortBind",
    "Rename",
    "Dispatch",
};

struct AllocateInfo {
    public:
        UInstrPtr      uinstr_;

        // Stage Information
        AllocPipeStage pipestage_;
        enum_array<AllocPipeStage, int, (int)AllocPipeStage::count> cycle_ = {std::numeric_limits<int>::max()};
        enum_array<AllocPipeStage, int, (int)AllocPipeStage::count> done_ = {false};

        AllocateInfo(int cycle, UInstrPtr uinstr) {
            pipestage_ = AllocPipeStage::Allocation;
            cycle_[AllocPipeStage::Allocation] = cycle;
            uinstr_           = uinstr;
            //PortBind_cycle_   = std::numeric_limits<int>::max();
        }
};
using AllocateInfoPtr = std::shared_ptr<AllocateInfo>;

class Allocate {
    public:
        Allocate(std::shared_ptr<Rob> rob,
                 std::shared_ptr<RegisterAliasTable> rat,
                 std::shared_ptr<RegisterAliasTable> srat,
                 std::shared_ptr<FreeTable> free_table);
        void Process(int cycle, bool reset);


    private:
        // Pipestage Functions
        void Allocation();
        void PortBind();
        void Rename();
        void Dispatch();

        // Support Functions
        void CreatePipeMap();
        void StartStage();
        void FinishStage(AllocateInfoPtr alloc_ptr, int latency);
        void PrintAllocateUops();

        std::deque<AllocateInfoPtr> allocate_queue_;
        std::vector<AllocPipeStage> allocate_stage_;
        std::map<AllocPipeStage, AllocPipeStage> allocate_stage_map_;

        DelayPtr<UInstrPtr> decode_to_alloc_rp;
        DelayPtr<UInstrPtr> alloc_to_exec_wp;
        std::unique_ptr<Portbind> portbind;
        int cycle_;
        std::shared_ptr<Rob>                rob_;
        std::shared_ptr<RegisterAliasTable> rat_;
        std::shared_ptr<RegisterAliasTable> srat_;
        std::shared_ptr<FreeTable>          free_table_;
};

#endif // ALLOCATE_H