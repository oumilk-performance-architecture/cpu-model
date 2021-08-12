#ifndef UINSTR_H
#define UINSTR_H

#include <cstdint>
#include <vector>
#include <bitset>
#include <uop.h>

enum class Apsr{
    n,
    z,
    c,
    v
};

class UInstr {
    public:
        UInstr();
        ~UInstr();
        void SetExecUnit(uint8_t unit);
        //void SetUop();
        void SetFlagN(bool value);
        void SetFlagZ(bool value);
        void SetFlagC(bool value);
        void SetRd(uint8_t rd);
        void SetRn(uint8_t rn);
        void SetRm(uint8_t rm);
        void SetRa(uint8_t ra);
        void SetLatency(uint8_t latency);
        void SetImmed(uint8_t immed);

        uint8_t GetRd();
        uint8_t GetRn();
        uint8_t GetRm();
        uint8_t GetRa();


        void PrintDetails();

    private:
        Uop opcode_;
        uint8_t rd_;
        uint8_t rn_;
        uint8_t rm_;
        uint8_t ra_;
        uint8_t immed_;
        uint8_t latency_;
        std::vector<uint8_t> exec_units_;
        std::bitset<sizeof(Apsr)> apsr_;
};

#endif // UINSTR_H