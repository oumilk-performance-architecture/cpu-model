#ifndef PORTBIND_H
#define PORTBIND_H

#include <vector>
#include <map>
#include <uop.h>
#include <common.h>
#include <string>

class UInstr;
using UInstrPtr = std::shared_ptr<UInstr>;

/*
    Class: Portbind
    Description: The class contains information on the schedulers, ports, and execution units.  Child classes 
                 should be created for different "projects"

    ReservationUnits - All possible schedulers
    ExecUnits        - All possible exec units
    res_table_       - Ties the exec units to the scheduler/ports
    latency_table_   - UINSTRS are tied to exec units allowed and reservation stations.
*/

enum class SchedulerUnits {
    AGU0,
    INT0,
    INT1
};

static const enum_array<SchedulerUnits, std::string, 3> schedulerUnits_str = {
    "AGU0",
    "INT0",
    "INT1"
};

enum class ExecUnits {
    AGU0,
    ALU0,
    MUL1
};

static const enum_array<ExecUnits, std::string, 3> execunits_str = {
    "AGU0",
    "ALU0",
    "MUL1"
};

class Portbind {
    public:
        Portbind();

        void GetPortInformation(UInstrPtr uinstr);
        //virtual SchedulerUnits GetScheduler(UInstrPtr uinstr);

        struct LatencyTable {
            Uop uop;
            int latency;
            std::vector<ExecUnits> exec_units;
            std::vector<SchedulerUnits>  res_units;
        };

    private:
        std::map<ExecUnits, SchedulerUnits> sched_table_ = {
            {ExecUnits::AGU0, SchedulerUnits::AGU0},
        };

        std::vector<LatencyTable> latency_table_ = {
            {Uop::LUI,  1,   {ExecUnits::AGU0}, {}},
        };

        std::vector<SchedulerUnits> GetResUnits(std::vector<ExecUnits>);
};

#endif // PORTBIND_H