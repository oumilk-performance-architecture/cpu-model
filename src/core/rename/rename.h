#ifndef RENAME_H
#define RENAME_H

#include <utility>
#include <deque>
#include <vector>
#include <parameter.h>

extern parameter<int> num_arch_reg;

class Rename {

    public:
        Rename();

        int ClaimPhysicalRegister(int arch_reg);
        int GetPhysicalRegister();
        bool SetPhysicalRegister(uint8_t arch_reg, uint8_t phys_reg);

        // Temp
        void PrintState();
        void PrintFreeList();

    private:
        std::vector<std::pair<int, bool>> rat;
        std::vector<std::pair<int, bool>> srat;
        std::deque<int>  free_list;
};

#endif // RENAME_H