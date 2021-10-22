#ifndef UINSTR_H
#define UINSTR_H

#include <cstdint>
#include <vector>
#include <bitset>
#include <uop.h>
#include <iostream>

/*
  To Do:
    1 - Parameterize reg name into a vector/array so it can be accessed with RegNames
*/

// Forward Declare
enum class ExecUnits;
enum class ResUnits;
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

enum class RegNames {
    Rd, Rn, Rm, Ra, Rt
};
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

        // Register Information
        void SetRd(uint8_t rd); // Destination
        void SetRn(uint8_t rn); // Operand in arithmetic operation
        void SetRm(uint8_t rm); // Operand in arithmetic operation
        void SetRa(uint8_t ra); // value
        void SetRt(uint8_t ra);
        inline uint8_t GetRd() { return rd_; };
        inline uint8_t GetRn() { return rn_; };
        inline uint8_t GetRm() { return rm_; };
        inline uint8_t GetRa() { return ra_; };
        inline uint8_t GetRt() { return rt_; };

        void SetAPSRUpdate(bool set_apsr);
        inline bool    GetAPSRUpdate() { return set_apsr_; };

        void SetRegList(uint8_t reg_list);
        void SetImmed(uint32_t immed);
        uint32_t GetImmed();
        void SetCond(uint8_t cond);
        void SetCond(Cond cond);

        // Physical
        void SetPhysSrcA(int srca_phys);
        void SetPhysSrcB(int srcb_phys);
        void SetPhysDest(int dest_phys);
        void SetPhysAPSR(int apsr_phys_);
        inline int GetPhysSrcA() { return srca_data_; };
        inline int GetPhysSrcB() { return srcb_data_; };
        inline int GetPhysDest() { return dest_phys_; };
        inline int GetPhysAPSR() { return apsr_phys_; };

        // Data
        void SetDataSrcA(uint32_t srca_data);
        void SetDataSrcB(uint32_t srcb_data);
        void SetDataDest(uint32_t dest_data);
        void SetDataFlagN(bool value);
        void SetDataFlagZ(bool value);
        void SetDataFlagC(bool value);
        void SetDataFlagV(bool value);
        inline uint32_t GetDataSrcA() { return srca_data_; };
        inline uint32_t GetDataSrcB() { return srcb_data_; };
        inline uint32_t GetDataDest() { return dest_data_; };
        inline bool GetDataFlagN() { return apsr_data_.test((int)Apsr::n); };
        inline bool GetDataFlagZ() { return apsr_data_.test((int)Apsr::z); };
        inline bool GetDataFlagC() { return apsr_data_.test((int)Apsr::c); };
        inline bool GetDataFlagV() { return apsr_data_.test((int)Apsr::v); };

        // Simulation
        void SetExecUnit(std::vector<ExecUnits> unit);
        void SetLatency(int latency);
        void SetResUnit(std::vector<ResUnits> unit);
        inline std::vector<ExecUnits> GetExecUnit() { return exec_units_; };
        inline int GetLatency() { return latency_; };
        inline std::vector<ResUnits> GetResUnit() { return res_units_; };

        // Support
        void PrintDetails();
        void PrintExec();
        void PrintResults();

    private:
        // Logical
        Uop opcode_;
        uint8_t rd_;    // Destination
        uint8_t rn_;
        uint8_t rm_;
        uint8_t ra_;
        uint8_t rt_;
        bool    set_apsr_;
        uint32_t immed_;
        std::bitset<8> reg_list_;
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
        int latency_;
        std::vector<ExecUnits> exec_units_;
        std::vector<ResUnits> res_units_;
};

//using UInstrPtr = UInstr*;
using UInstrPtr = std::shared_ptr<UInstr>;

std::ostream & operator << (std::ostream &out, UInstr &c);
std::ostream & operator << (std::ostream &out, UInstrPtr &c);

#endif // UINSTR_H