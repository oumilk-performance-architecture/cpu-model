#ifndef RENAME_H
#define RENAME_H

#include <utility>
#include <deque>
#include <vector>
#include <delay.h>
#include <parameter.h>
#include "rat.h"

// Forward Class Declaration
class UInstr;
using UInstrPtr = std::shared_ptr<UInstr>;
class Rob;

extern parameter<int> num_arch_reg;

class Rename {

    public:
        Rename(std::shared_ptr<Rob> rob,
               std::shared_ptr<RegisterAliasTable> rat,
               std::shared_ptr<RegisterAliasTable> srat,
               std::shared_ptr<FreeTable> free_table);

        void Process(int cycle, bool reset);
        void ClaimRob();
        void RenameRegisters();
        int MapSpeculativeRegister(int reg);

        // Temp
        void PrintState();
        void PrintFreeList();

    private:
        DelayPtr<UInstrPtr> pb_to_rename_rp;
        DelayPtr<UInstrPtr> rename_to_reservation_wp;
        DelayPtr<UInstrPtr> allocate_rob_wp;

        std::shared_ptr<RegisterAliasTable> rat_;
        std::shared_ptr<RegisterAliasTable> srat_;
        std::shared_ptr<FreeTable> free_table_;
        std::shared_ptr<Rob> rob_;
        int cycle_;

        int ClaimPhysicalRegister(int arch_reg);
        int GetPhysicalRegister();
        bool SetPhysicalRegister(uint8_t arch_reg, uint8_t phys_reg);

};

#endif // RENAME_H