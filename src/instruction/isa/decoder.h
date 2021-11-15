#ifndef DECODER_H
#define DECODER_H

#include <cstdint>
#include <vector>

class UInstr;
using UInstrPtr = std::shared_ptr<UInstr>;
class Rv32i;

enum class DecoderIsa {
    RV32I,
};

// Base Class
class Decoder {
    public:
        Decoder();
        bool DecodeInstruction(uint32_t instr, UInstrPtr uinstr);

    private:
        std::vector<DecoderIsa> enabled_isa_;
        std::unique_ptr<Rv32i> rv32i_;
        
};


#endif // DECODER_H