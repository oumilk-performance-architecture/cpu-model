#ifndef ISA_H
#define ISA_H

#include <cstdint>
#include <vector>

class UInstr;
using UInstrPtr = std::shared_ptr<UInstr>;

// Base Class
class Isa {
    public:
        virtual bool DecodeInstructions(uint32_t instr, UInstrPtr uinstr) = 0;


    // 32 Bit
    constexpr uint32_t Mask32(int hi, int lo) {
        if (hi - lo >= 31)
            return -1;
        return (1 << (hi - lo + 1)) - 1;
    };
    constexpr uint32_t BitMask32(int hi, int lo) {
        return Mask32(hi, lo) << lo;
    }
    constexpr uint32_t BitMask32(int h1, int l1, int h2, int l2) {
        return (Mask32(h1, l1) << l1) | (Mask32(h2, l2) << l2);
    }
    constexpr uint32_t BitMask32(int h1, int l1, int h2, int l2, int h3, int l3) {
        return (Mask32(h1, l1) << l1) | (Mask32(h2, l2) << l2) | (Mask32(h3, l3) << l3);
    }

    // 16 Bit
    constexpr int Mask(int hi, int lo) {
        return (1 << (hi - lo + 1)) - 1;
    };
    constexpr uint16_t BitMask(int hi, int lo) {
        return Mask(hi, lo) << lo;
    }
    constexpr uint16_t Opcode(uint16_t opcode, int lo) {
        return opcode << lo;
    };
    constexpr uint32_t Opcode32(uint32_t opcode, int lo) {
        return opcode << lo;
    };
    constexpr uint32_t Opcode32(uint32_t opcode1, int lo1, uint32_t opcode2, int lo2) {
        return opcode1 << lo1 | opcode2 << lo2;
    };
    constexpr uint32_t Opcode32(uint32_t opcode1, int lo1, uint32_t opcode2, int lo2, uint32_t opcode3, int lo3) {
        return opcode1 << lo1 | opcode2 << lo2 | opcode3 << lo3;
    };

    // Data Mask
    template <class T>
    constexpr T DataMask (T instr_data, int hi, int lo) {
        return (instr_data & (T) Mask(hi,lo)) >> lo;
    };
    template <class T>
    constexpr T Mask11to7 (T instr_data) {
        return DataMask(instr_data, 11, 7);
    };
    template <class T>
    constexpr T Mask31to12(T instr_data) {
        return DataMask(instr_data, 31, 12);
    };
    template <class T>
    constexpr T Mask31to20(T instr_data) {
        return DataMask(instr_data, 31, 20);
    };
    template <class T>
    constexpr T Mask24to20(T instr_data) {
        return DataMask(instr_data, 24, 20);
    };
    template <class T>
    constexpr T Mask19to15(T instr_data) {
        return DataMask(instr_data, 19, 15);
    };
    template <class T>
    constexpr T Mask32BImmed(T instr_data) {
        return DataMask(instr_data, 31, 25) << 5 | DataMask(instr_data, 11, 7);
    };

    private:
};
using IsaBase = Isa;

#endif // ISA_H