#ifndef ISA_H
#define ISA_H

#include <cstdint>
#include <vector>
#include <uinstr.h>

// Base Class
class Isa {
    public:
      virtual bool DecodeInstructions(uint16_t instr, UInstrPtr uop) = 0;
    private:
};

constexpr int Mask(int hi, int lo) {
  return (1 << (hi - lo + 1)) - 1;
};

constexpr uint16_t BitMask(int hi, int lo) {
  return Mask(hi, lo) << lo;
}

constexpr uint16_t Opcode(uint16_t opcode, int lo) {
  return opcode << lo;
};

template <class T>
constexpr T DataMask (T instr_data, int hi, int lo) {
  return (instr_data & (T) Mask(hi,lo)) >> lo;
}

#endif // ISA_H