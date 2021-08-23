#include "fetch.h"
#include <iostream>
#include <idata.h>

Fetch::Fetch() {
};

void Fetch::Clock(int cycle) {
    cycle_ = cycle;
    std::shared_ptr<Idata> idata = CalculateNextPc();
    pc_ = idata->GetIp();
    // TLB/Cache/etc
};

std::unique_ptr<Idata> Fetch::CalculateNextPc() {
    std::unique_ptr<Idata> idata = std::make_unique<Idata>(cycle_);
    idata->SetIp(pc_ + 2);
    return idata;
}

//Fetch::~Fetch() {
//};
