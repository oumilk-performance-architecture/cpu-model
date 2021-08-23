#ifndef REGISTER_H
#define REGISTER_H

#include <cstdint>
#include <array>
#include <vector>

#include <parameter.h>

// Right now I do not want marbles but want to have the option for the future, setting trash can size to same as number of registers 
//  accomplishes that

enum class Cpsr {
    n,
    z,
    c,
    v,
    q
};

extern parameter<int> num_phys_reg ("num_phys_reg", 12);

class Register {
    public:
        Register();
        uint32_t GetRegisterValue(int phys_reg);
        void SetRegisterValue(int phys_reg, uint32_t value);
        
    private:
        std::array<int, 12> rat;
        std::array<int, 12> srat;
        std::vector<int>    trash;
};

#endif // REGISTER_H