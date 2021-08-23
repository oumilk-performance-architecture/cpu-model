#ifndef UINSTR_H
#define UINSTR_H

#include <cstdint>
#include <vector>
#include <bitset>
#include <uop.h>
#include <iostream>

/*
    Class: UInstr
    Responsible for storing information related to an instruction
*/

enum class Apsr {
    n,
    z,
    c,
    v
};

// TODO: Order matters here
// NZCV
enum class Cond{
    EQ = 0b0000, // Z = 1 (Equal)
    NE = 0b0001, // Z = 0 (Not equal)
    CS = 0b0010, // C = 1 (Higher or same, unsigned)
    CC = 0b0011, // C = 0 (Lower, unsigned)
    MI = 0b0100, // N = 1 (Negative)
    PL = 0b0101, // N = 0 (Positive or zero)
    VS = 0b0110, // V = 1 (overflow)
    VC = 0b0111, // V = 0 (No overflow)
    HI = 0b1000, // C = 1, Z = 0 (Higher, unsigned)
    LS = 0b1001, // C = 0, Z = 1 (Lower or same, unsigned)
    GE = 0b1010, // N = V (Greater than or equal, signed)
    LT = 0b1011, // N != V (Less than, signed)
    GT = 0b1100, // Z = 0, N = V (Greater than, signed)
    LE = 0b1101, // Z = 1, N != V (Less than or equal, signed)
    AL = 0b1110, // * (Always)
};

class UInstr {
    public:
        UInstr();

        // Logical
        void SetOpcode(Uop opcode);
        Uop GetOpcode();

        void SetFlagNZ(bool value);
        void SetFlagNZC(bool value);
        void SetFlagNZCV(bool value);
        void SetFlagN(bool value);
        bool GetUpdateFlagN();
        void SetFlagZ(bool value);
        bool GetUpdateFlagZ();
        void SetFlagC(bool value);
        bool GetUpdateFlagC();
        void SetFlagV(bool value);
        bool GetUpdateFlagV();

        void SetRd(uint8_t rd);
        uint8_t GetRd();
        void SetRn(uint8_t rn);
        uint8_t GetRn();
        void SetRm(uint8_t rm);
        uint8_t GetRm();
        void SetRa(uint8_t ra);
        uint8_t GetRa();
        void SetRt(uint8_t ra);
        uint8_t GetRt();

        void SetRegList(uint8_t reg_list);
        void SetImmed(uint32_t immed);
        uint32_t GetImmed();
        void SetCond(uint8_t cond);
        void SetCond(Cond cond);

        // Physical
        void SetPhysSrcA(int srca_phys);
        int GetPhysSrcA();
        void SetPhysSrcB(int srcb_phys);
        int GetPhysSrcB();
        void SetPhysDest(int dest_phys);
        int GetPhysDest();

        // Data
        void      SetDataSrcA(uint32_t srca_data);
        uint32_t  GetDataSrcA();
        void      SetDataSrcB(uint32_t srcb_data);
        uint32_t  GetDataSrcB();
        void      SetDataDest(uint32_t dest_data);
        uint32_t  GetDataDest();
        void SetDataFlagN(bool value);
        bool GetDataFlagN();
        void SetDataFlagZ(bool value);
        bool GetDataFlagZ();
        void SetDataFlagC(bool value);
        bool GetDataFlagC();
        void SetDataFlagV(bool value);
        bool GetDataFlagV();

        // Simulation
        void SetExecUnit(uint8_t unit);
        void SetLatency(uint8_t latency);

        // Support
        void PrintDetails();
        void PrintResults();

    private:
        // Logical
        Uop opcode_;
        uint8_t rd_;
        uint8_t rn_;
        uint8_t rm_;
        uint8_t ra_;
        uint8_t rt_;
        uint32_t immed_;
        std::bitset<8> reg_list_;
        std::bitset<sizeof(Apsr)> set_apsr_;
        Cond cond_;
        // Physical
        int srca_phys_;
        int srcb_phys_;
        int dest_phys_;
        int apsr_phys_;
        // Data
        uint32_t srca_data_;
        uint32_t srcb_data_;
        uint32_t dest_data_;
        std::bitset<sizeof(Apsr)> apsr_data_;
        // Simulation
        uint8_t latency_;
        std::vector<uint8_t> exec_units_;
};

using UInstrPtr = UInstr*;

std::ostream & operator << (std::ostream &out, UInstr &c);
std::ostream & operator << (std::ostream &out, UInstrPtr &c);

#endif // UINSTR_H