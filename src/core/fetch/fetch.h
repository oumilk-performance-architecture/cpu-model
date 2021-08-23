#ifndef FETCH_H
#define FETCH_H

#include <utility>
#include <cstdint>
#include <iostream>
#include <idata.h>

class Fetch {
    public:
        Fetch();

        void Clock(int cycle);
        std::unique_ptr<Idata> CalculateNextPc();
        uint32_t FetchMemory();

    private:
        int cycle_;
        uint32_t pc_;
        uint32_t npc_;

};

#endif // FETCH_H