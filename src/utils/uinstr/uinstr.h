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

class UInstr {
    public:
        UInstr();

        // Logical
        void SetOpcode(Uop opcode);
        Uop GetOpcode();

        /*
          Register Information
        */
        // Architecture
        void SetRd(uint8_t rd);
        void SetRs1(uint8_t rd);
        void SetRs2(uint8_t rd);
        inline uint8_t GetRd()  { return rd_; };
        inline uint8_t GetRs1() { return rs1_; };
        inline uint8_t GetRs2() { return rs2_; };
        // Physical
        void SetPhysSrcA(int srca_phys);
        void SetPhysSrcB(int srcb_phys);
        void SetPhysDest(int dest_phys);
        inline int GetPhysSrcA() { return srca_data_; };
        inline int GetPhysSrcB() { return srcb_data_; };
        inline int GetPhysDest() { return dest_phys_; };
        // Immediate Information
        void SetImmed(uint32_t immed);
        inline uint32_t GetImmed() { return immed_; };

        /*
            Execution Information
        */
        // Data
        void SetDataSrcA(uint32_t srca_data);
        void SetDataSrcB(uint32_t srcb_data);
        void SetDataDest(uint32_t dest_data);
        inline uint32_t GetDataSrcA() { return srca_data_; };
        inline uint32_t GetDataSrcB() { return srcb_data_; };
        inline uint32_t GetDataDest() { return dest_data_; };

        // Simulation
        void SetExecUnit(std::vector<ExecUnits> unit);
        void SetLatency(int latency);
        void SetResUnit(std::vector<ResUnits> unit);
        inline std::vector<ExecUnits> GetExecUnit() { return exec_units_; };
        inline int GetLatency() { return latency_; };
        inline std::vector<ResUnits> GetResUnit() { return res_units_; };

        // Support
        std::string GetOpcodeString();
        void PrintDetails();
        void PrintExec();
        void PrintResults();

    private:
        // Logical
        Uop opcode_;
        uint8_t  rd_;
        uint8_t  rs1_;
        uint8_t  rs2_;
        uint32_t immed_;

        // Physical
        int srca_phys_;
        int srcb_phys_;
        int dest_phys_;
        // Data
        uint32_t srca_data_;
        uint32_t srcb_data_;
        uint32_t dest_data_;
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