#include "portbind.h"

Portbind::Portbind() {
};

std::vector<ResUnits> Portbind::GetResUnits(std::vector<ExecUnits> exec_units) {
    std::vector<ResUnits> temp;

    for (auto it = exec_units.begin(); it != exec_units.end(); it++) {
        auto search = res_table_.find((*it));
        if (search != res_table_.end()) {
            temp.push_back(search->second);
        }
    }
    // Unique
    std::sort(temp.begin(), temp.end());
    temp.erase(std::unique(temp.begin(), temp.end()), temp.end());
    
    return temp;
};

void Portbind::PortBindInstructions(UInstrPtr uinstr) {
    std::vector<LatencyTable>::iterator iter;
    // Set Latency and Exec
    auto getExecUnit = [&uinstr](const LatencyTable lat_table) {
        return (uinstr->GetOpcode() == lat_table.uop);
    };
    iter = std::find_if(latency_table_.begin(), latency_table_.end(), getExecUnit);
    if (iter != latency_table_.end()) {
        uinstr->SetLatency(iter->latency);
        uinstr->SetExecUnit(iter->exec_units);
        if (iter->res_units.size() < 1) {
            iter->res_units = GetResUnits(uinstr->GetExecUnit());
        }
        uinstr->SetResUnit(iter->res_units);
    };
}
