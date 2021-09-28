#ifndef ICACHE_H
#define ICACHE_H

#include <cstdint>

class Icache {
    public:
        Icache();

        void Process(int cycle); 

        void SetData()

    private:
        int GetSet(uint32_t addr);
        int GetTag(uint32_t addr);

        int cycle_;
};

#endif // ICACHE_H