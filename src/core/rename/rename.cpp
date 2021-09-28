#include "rename.h"
#include <utility>
#include <iostream>
#include <iomanip>
#include <parameter.h>

parameter<bool>       enable_renaming ("enable_renaming", false);
parameter<int>        num_arch_reg ("num_arch_reg", 15);
extern parameter<int> num_phys_reg;

Rename::Rename():
    srat(num_arch_reg),
    rat(num_arch_reg),
    free_list(num_phys_reg) {
    // Initialize Free List
    for (int n = 0; n < num_phys_reg; n++) {
        free_list.push_back(n);
    }
};

int Rename::ClaimPhysicalRegister(int arch_reg) {
    if (!enable_renaming)
        return arch_reg;
    
    if (!free_list.empty()) {
        int chosen = free_list.front();
        srat[arch_reg] = std::make_pair(chosen, true);
        free_list.pop_front();
        return chosen;
    }
    return -1;
};

void Rename::PrintState() {
    std::cout << std::right;
    std::cout << std::setw(3) << "Reg";
    std::cout << std::setw(6) << "SRAT";
    std::cout << std::setw(6) << "RAT";
    std::cout << "\n";
    for (auto i = 0; i < srat.size(); i++) {
        std::cout << std::setw(3) << i;
        std::cout << std::setw(6) << srat[i].first;
        std::cout << std::setw(6) << rat[i].first;
        std::cout << "\n";
    }
    std::cout << "\n";
}

void Rename::PrintFreeList() {
    std::cout << "Number of physical registers: " << num_phys_reg << "\n";
    std::cout << "List of free physical registers: \n";
    for (auto it = free_list.cbegin(); it != free_list.cend(); ++it) {
        std::cout << *it << ", ";
    }
    std::cout << "\n";
}
