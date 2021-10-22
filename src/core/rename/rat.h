#ifndef RAT_H
#define RAT_H

#include <vector>

class FreeTable {
    public:
        FreeTable(int size) {
            for (int n = 0; n < size; n++) {
                table.push_back(n);
            }
        };

        bool Available() {
            return !table.empty();
        }

        int Claim() {
            int reg = table.front();
            table.pop_front();
            return reg;
        }

        void Free(int reg) {
            table.push_back(reg);
        }
    private:
        std::deque<int> table;
};

class RegisterAliasTable {
    public:
        RegisterAliasTable(int size):
            table(size) {
            for (int n = 0; n < size; n++) {
                table[n].valid = false;
            }
        };

        struct RatTable {
            int  phys_reg;
            bool valid;
        };

        void Set (int arch_reg, int phys_reg) {
            table[arch_reg].phys_reg = phys_reg;
            table[arch_reg].valid = true;
        };

        int Get (int arch_reg) {
            if (table[arch_reg].valid) {
                return table[arch_reg].phys_reg;
            } else {
                return arch_reg;
            }
        };
        

    private:
        std::vector<RatTable> table;
};

#endif // RAT_H