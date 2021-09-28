#ifndef REGISTER_H
#define REGISTER_H

#include <cstdint>
#include <array>
#include <vector>

#include <parameter.h>

enum class Cpsr {
    n,
    z,
    c,
    v,
    q
};


class Register {
    public:
        Register();
        uint32_t GetValue(int phys_reg);
        void SetValue(int phys_reg, uint32_t value);
        
    private:
        std::vector<uint32_t> data;
};

#endif // REGISTER_H