#ifndef ISA_H
#define ISA_H

#include <cstdint>
#include <vector>
#include <uinstr.h>

// Base Class
class Isa {
    public:
      virtual UInstr DecodeInstructions(uint16_t instr) = 0;
    private:
};

constexpr uint16_t MASK16(int hi, int lo) {
  return (1 << (hi - lo + 1)) - 1;
};

constexpr uint16_t BITMASK16(int lo) {
  return MASK16(15, lo) << lo;
};

constexpr uint16_t OPCODE(uint16_t opcode, int lo) {
  return opcode << lo;
};

constexpr uint16_t DATAMASK16(uint16_t instruction, int hi, int lo) {
  return (instruction & MASK16(hi, lo)) >> lo;
}


#endif // ISA_H