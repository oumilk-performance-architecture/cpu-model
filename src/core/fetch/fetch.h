#ifndef FETCH_H
#define FETCH_H

#include <utility>
#include <cstdint>
#include <iostream>
#include <idata.h>
#include <delay.h>


class Fetch {
    public:
        Fetch();
        //~Fetch();

        void Process(int cycle, bool reset);
        uint32_t FetchMemory();

    private:
        std::unique_ptr<Idata> CalculateNextPc();
        int cycle_;
        bool reset_;
        uint32_t pc_;
        uint32_t npc_;

        Delay<uint32_t>* nip_fetch_mem_wp;

};

#endif // FETCH_H