#ifndef PORTBIND_H
#define PORTBIND_H

#include <vector>
#include <map>
#include <uinstr.h>
#include <uop.h>

enum class ResUnits {
    INT1,
    INT2,
};

static const char *resunits_str[] = {
    "INT1",
    "INT2",
};

enum class ExecUnits {
    ALU1,
    ALU2,
    MUL1
};

static const char *execunits_str[] = {
    "ALU1",
    "ALU2",
    "MUL1"
};

class Portbind {
    public:
        Portbind();

        void PortBindInstructions(UInstrPtr uinstr);

        struct LatencyTable {
            Uop uop;
            int latency;
            std::vector<ExecUnits> exec_units;
            std::vector<ResUnits>  res_units;
        };

    private:
        std::map<ExecUnits, ResUnits> res_table_ = {
            {ExecUnits::ALU1, ResUnits::INT1},
            {ExecUnits::ALU2, ResUnits::INT2},
            {ExecUnits::MUL1, ResUnits::INT2},
        };

        std::vector<LatencyTable> latency_table_ = {
            {Uop::LUI,  1,   {ExecUnits::ALU1, ExecUnits::ALU2}, {}},
        };

        std::vector<ResUnits> GetResUnits(std::vector<ExecUnits>);
};

#endif // PORTBIND_H