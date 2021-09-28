#include "register.h"

parameter<int> num_phys_reg ("num_phys_reg", 15);

Register::Register():
    data(num_phys_reg) {
}; 

uint32_t Register::GetValue(int phys_reg) {
    return data[phys_reg];
};

void Register::SetValue(int phys_reg, uint32_t value) {
    data[phys_reg] = value;
};
