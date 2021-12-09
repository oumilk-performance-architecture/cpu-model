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
enum class SchedulerUnits;
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
        // ISA
        void SetRd(uint8_t rd);
        void SetRs1(uint8_t rs1);
        void SetRs2(uint8_t rs2);
        
        // Architecture
        void SetArchRd(uint8_t arch_rd);
        void SetArchRs1(uint8_t arch_rs1);
        void SetArchRs2(uint8_t arch_rs2);
        inline uint8_t GetArchRd()  { return arch_rd_; };
        inline uint8_t GetArchRs1() { return arch_rs1_; };
        inline uint8_t GetArchRs2() { return arch_rs2_; };
        // Physical
        void SetPhysRd(uint16_t phys_rd);
        void SetPhysRs1(uint16_t phys_rs1);
        void SetPhysRs2(uint16_t phys_rs2);
        void SetRobID(uint16_t rob_id);
        inline int GetPhysRd() { return phys_rd_; };
        inline int GetPhysRs1() { return phys_rs1_; };
        inline int GetPhysRs2() { return phys_rs2_; };
        inline int GetRobID() { return rob_id_; };
        inline bool ValidRs1() { return phys_rs1_ != std::numeric_limits<uint8_t>::max(); };
        inline bool ValidRs2() { return phys_rs2_ != std::numeric_limits<uint8_t>::max(); };
        // Immediate Information
        void SetImmed(uint32_t immed);
        inline uint32_t GetImmed() { return immed_; };

        /*
            Execution Information
        */
        // Data
        void SetDataRd(uint32_t data_rd);
        void SetDataRs1(uint32_t data_rs1);
        void SetDataRs2(uint32_t data_rs2);
        inline uint32_t GetDataRd()  { return data_rd_; };
        inline uint32_t GetDataRs1() { return data_rs1_; };
        inline uint32_t GetDataRs2() { return data_rs2_; };

        // Simulation
        void SetExecUnit(std::vector<ExecUnits> unit);
        void SetLatency(int latency);
        void SetSchedUnit(std::vector<SchedulerUnits> unit);
        void SetIssued(bool issued);
        void SetPort(int port);
        inline std::vector<ExecUnits> GetExecUnit() { return exec_units_; };
        inline int GetLatency() { return latency_; };
        inline std::vector<SchedulerUnits> GetSchedUnit() { return sched_units_; };
        inline bool GetIssued() { return issued_; };
        inline int GetPort() { return port_; };

        // Assigned
        void SetAssignedSched(SchedulerUnits sched);
        void SetAssignedExec(ExecUnits exec);
        inline SchedulerUnits GetAssignedSched() { return assigned_sched_; };
        inline ExecUnits GetAssignedExec() { return assigned_exec_; };

        // Support
        std::string GetOpcodeString();
        void PrintDetails();
        void PrintExec();
        void PrintResults();

    private:
        // Logical
        Uop opcode_;
        uint8_t  arch_rd_;
        uint8_t  arch_rs1_;
        uint8_t  arch_rs2_;
        uint32_t immed_;
        // Physical
        uint16_t phys_rd_;
        uint16_t phys_rs1_;
        uint16_t phys_rs2_;
        uint16_t rob_id_;
        // Data
        uint32_t data_rd_;
        uint32_t data_rs1_;
        uint32_t data_rs2_;
        // Simulation
        int port_;
        bool issued_;
        SchedulerUnits assigned_sched_;
        ExecUnits      assigned_exec_;

        int latency_;
        std::vector<ExecUnits> exec_units_;
        std::vector<SchedulerUnits> sched_units_;
};

//using UInstrPtr = UInstr*;
using UInstrPtr = std::shared_ptr<UInstr>;

std::ostream & operator << (std::ostream &out, UInstr &c);
std::ostream & operator << (std::ostream &out, UInstrPtr &c);

#endif // UINSTR_H