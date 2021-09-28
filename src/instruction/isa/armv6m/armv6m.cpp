#include <vector>
#include "armv6m.h"
#include <uinstr.h>
#include <iostream>
#include <tuple>


Armv6m::Armv6m() {
};


bool Armv6m::DecodeInstructions(uint16_t instr, UInstrPtr uinstr) {//, Uop uop) {
    std::vector<Decoder16BTable>::iterator iter;
    auto decodeInstr = [&instr](const Decoder16BTable opcode) {
        return (instr & opcode.mask) == opcode.match; 
    };
    iter = std::find_if(opcode_table.begin(), opcode_table.end(), decodeInstr);
    if (iter != opcode_table.end()) {
        uinstr->SetOpcode(iter->uop);  // uop
        (this->*(iter->genUop))(instr, uinstr);
        return true;
    } 
    return false;
};

void Armv6m::DecodeLslsImmed(uint16_t instr, UInstrPtr uinstr) {
    uinstr->SetRd(DataMask(instr, 2, 0));
    uinstr->SetRm(DataMask(instr, 5, 3));
    uinstr->SetImmed(DataMask(instr, 10, 6));
    uinstr->SetAPSRUpdate(true);
}

void Armv6m::DecodeLslsReg(uint16_t instr, UInstrPtr uinstr) {
    uinstr->SetRd(DataMask(instr, 2, 0));
    uinstr->SetRm(DataMask(instr, 5, 3));
    uinstr->SetAPSRUpdate(true);
}

void Armv6m::DecodeAsrsImmed(uint16_t instr, UInstrPtr uinstr) {
    uinstr->SetRd(DataMask(instr, 2, 0));
    uinstr->SetRm(DataMask(instr, 5, 3));
    uinstr->SetImmed(DataMask(instr, 10, 6));
    uinstr->SetAPSRUpdate(true);
}

void Armv6m::DecodeAsrsReg(uint16_t instr, UInstrPtr uinstr) {
    uinstr->SetRd(DataMask(instr, 2, 0));
    uinstr->SetRm(DataMask(instr, 5, 3));
    uinstr->SetAPSRUpdate(true);
}
void Armv6m::DecodeLsrsImmed(uint16_t instr, UInstrPtr uinstr) {
    uinstr->SetRd(DataMask(instr, 2, 0));
    uinstr->SetRm(DataMask(instr, 5, 3));
    uinstr->SetImmed(DataMask(instr, 10, 6));
    uinstr->SetAPSRUpdate(true);
}

void Armv6m::DecodeLsrsReg(uint16_t instr, UInstrPtr uinstr) {
    uinstr->SetRm(DataMask(instr, 5, 3));
    uinstr->SetRd(DataMask(instr, 2, 0));
    uinstr->SetAPSRUpdate(true);
}

void Armv6m::DecodeAdcs(uint16_t instr, UInstrPtr uinstr) {
    uinstr->SetRn(DataMask(instr, 5, 3));
    uinstr->SetRn(DataMask(instr, 2, 0));
    uinstr->SetRd(DataMask(instr, 2, 0));
    uinstr->SetAPSRUpdate(true);
}

void Armv6m::DecodeAddsImmedT1(uint16_t instr, UInstrPtr uinstr) {
    uinstr->SetImmed(DataMask(instr, 8, 6));
    uinstr->SetRn(DataMask(instr, 5, 3));
    uinstr->SetRd(DataMask(instr, 2, 0));
    uinstr->SetAPSRUpdate(true);
}

void Armv6m::DecodeAddsImmedT2(uint16_t instr, UInstrPtr uinstr) {
    uinstr->SetRd(DataMask(instr, 10, 8));
    uinstr->SetRn(DataMask(instr, 10, 8));
    uinstr->SetImmed(DataMask(instr, 7, 0));
    uinstr->SetAPSRUpdate(true);
}

void Armv6m::DecodeAddsRegT1(uint16_t instr, UInstrPtr uinstr) {
    uinstr->SetRd(DataMask(instr, 2, 0));
    uinstr->SetRn(DataMask(instr, 5, 3));
    uinstr->SetRm(DataMask(instr, 8, 6));
    uinstr->SetAPSRUpdate(true);
    if (uinstr->GetRd() == 15) {
        uinstr->SetOpcode(Uop::ADD_PC_reg);
    }
}

void Armv6m::DecodeAddRegT2(uint16_t instr, UInstrPtr uinstr) {
    uint8_t rd = DataMask(instr, 7, 7) << 3 | DataMask(instr, 2, 0);
    uinstr->SetRd(rd);
    uinstr->SetRn(rd);
    uinstr->SetRm(DataMask(instr, 6, 3));
    uinstr->SetAPSRUpdate(false);
    if (rd == 13)
        uinstr->SetOpcode(Uop::ADD_SP_reg_t2);
    if (rd == 15)
        uinstr->SetOpcode(Uop::ADD_PC_reg);
}

void Armv6m::DecodeAddSpImmedT1(uint16_t instr, UInstrPtr uinstr) {
    uinstr->SetRd(DataMask(instr, 10, 8));
    uinstr->SetRn(13);
    uinstr->SetImmed(DataMask(instr, 7, 0)<<2);
    uinstr->SetAPSRUpdate(false);
}

void Armv6m::DecodeAddSpImmedT2(uint16_t instr, UInstrPtr uinstr) {
    uinstr->SetRd(13);
    uinstr->SetRn(13);
    uinstr->SetImmed(DataMask(instr, 6, 0)<<2);
    uinstr->SetAPSRUpdate(false);
}

void Armv6m::DecodeAddSpRegT1(uint16_t instr, UInstrPtr uinstr) {
    uint8_t rd = DataMask(instr, 7, 7) << 3 | DataMask(instr, 2, 0);
    uinstr->SetRd(rd);
    uinstr->SetRm(rd);
    uinstr->SetRn(13);
}

void Armv6m::DecodeAddSpRegT2(uint16_t instr, UInstrPtr uinstr) {
    uinstr->SetRm(DataMask(instr, 6, 3));
    uinstr->SetRn(13);
    uinstr->SetRd(13);
}

void Armv6m::DecodeAdr(uint16_t instr, UInstrPtr uinstr) {
    uinstr->SetRd(DataMask(instr, 10, 8));
    uinstr->SetRn(13);
    uinstr->SetImmed(DataMask(instr, 7, 0)<<2);
}

void Armv6m::DecodeAnds(uint16_t instr, UInstrPtr uinstr) {
    uinstr->SetRm(DataMask(instr, 5, 3));
    uinstr->SetRd(DataMask(instr, 2, 0));
    uinstr->SetRn(DataMask(instr, 2, 0));
    uinstr->SetAPSRUpdate(true);
}

void Armv6m::DecodeBics(uint16_t instr, UInstrPtr uinstr) {
    uinstr->SetRm(DataMask(instr, 5, 3));
    uinstr->SetRd(DataMask(instr, 2, 0));
    uinstr->SetRn(DataMask(instr, 2, 0));
    uinstr->SetAPSRUpdate(true);
}

void Armv6m::DecodeEors(uint16_t instr, UInstrPtr uinstr) {
    uinstr->SetRm(DataMask(instr, 5, 3));
    uinstr->SetRd(DataMask(instr, 2, 0));
    uinstr->SetRn(DataMask(instr, 2, 0));
    uinstr->SetAPSRUpdate(true);
}

void Armv6m::DecodeMvns(uint16_t instr, UInstrPtr uinstr) {
    uinstr->SetRm(DataMask(instr, 5, 3));
    uinstr->SetRd(DataMask(instr, 2, 0));
    uinstr->SetAPSRUpdate(true);
}

void Armv6m::DecodeOrrs(uint16_t instr, UInstrPtr uinstr) {
    uinstr->SetRm(DataMask(instr, 5, 3));
    uinstr->SetRd(DataMask(instr, 2, 0));
    uinstr->SetRn(DataMask(instr, 2, 0));
    uinstr->SetAPSRUpdate(true);
}

void Armv6m::DecodeTst(uint16_t instr, UInstrPtr uinstr) {
    uinstr->SetRm(DataMask(instr, 5, 3));
    uinstr->SetRn(DataMask(instr, 2, 0));
    uinstr->SetAPSRUpdate(true);
}

void Armv6m::DecodeBT1(uint16_t instr, UInstrPtr uinstr) {
    uinstr->SetImmed(DataMask(instr, 7, 0)<<1);
    uinstr->SetCond(DataMask(instr,11,8));
}

void Armv6m::DecodeBT2(uint16_t instr, UInstrPtr uinstr) {
    uinstr->SetImmed(DataMask(instr, 10, 0)<<1);
    uinstr->SetCond(Cond::AL);
}

void Armv6m::DecodeBlx(uint16_t instr, UInstrPtr uinstr) {
    uinstr->SetRm(DataMask(instr, 6, 3));
}

void Armv6m::DecodeBx(uint16_t instr, UInstrPtr uinstr) {
    uinstr->SetRm(DataMask(instr, 6, 3));
}

void Armv6m::DecodeBkpt(uint16_t instr, UInstrPtr uinstr) {
    uinstr->SetImmed(DataMask(instr, 7, 0));
}

void Armv6m::DecodeCmn(uint16_t instr, UInstrPtr uinstr) {
    uinstr->SetRm(DataMask(instr, 5, 3));
    uinstr->SetRn(DataMask(instr, 2, 0));
    uinstr->SetAPSRUpdate(true);
}

void Armv6m::DecodeCmpImmed(uint16_t instr, UInstrPtr uinstr) {
    uinstr->SetRn(DataMask(instr, 10, 8));
    uinstr->SetImmed(DataMask(instr, 7, 0));
    uinstr->SetAPSRUpdate(true);
}

void Armv6m::DecodeCmpReg(uint16_t instr, UInstrPtr uinstr) {
    uinstr->SetRm(DataMask(instr, 5, 3));
    uinstr->SetRn(DataMask(instr, 2, 0));
    uinstr->SetAPSRUpdate(true);
}

void Armv6m::DecodeLdm(uint16_t instr, UInstrPtr uinstr) {
    uinstr->SetRn(DataMask(instr, 10, 8));
    uinstr->SetRegList(DataMask(instr, 7, 0));
}

void Armv6m::DecodeLdrImmedT1(uint16_t instr, UInstrPtr uinstr) {
    uinstr->SetImmed(DataMask(instr, 10, 6));
    uinstr->SetRn(DataMask(instr, 5, 3));
    uinstr->SetRt(DataMask(instr, 2, 0));
}

void Armv6m::DecodeLdrImmedT2(uint16_t instr, UInstrPtr uinstr) {
    uinstr->SetRt(DataMask(instr, 10, 8));
    uinstr->SetImmed(DataMask(instr, 7, 0));
}

void Armv6m::DecodeLdrLit(uint16_t instr, UInstrPtr uinstr) {
    uinstr->SetRt(DataMask(instr, 10, 8));
    uinstr->SetImmed(DataMask(instr, 7, 0));
}

void Armv6m::DecodeLdrReg(uint16_t instr, UInstrPtr uinstr) {
    uinstr->SetRm(DataMask(instr, 8, 6));
    uinstr->SetRn(DataMask(instr, 5, 3));
    uinstr->SetRt(DataMask(instr, 2, 0));
}

void Armv6m::DecodeLdrbImmed(uint16_t instr, UInstrPtr uinstr) {
    uinstr->SetImmed(DataMask(instr, 10, 6));
    uinstr->SetRn(DataMask(instr, 5, 3));
    uinstr->SetRt(DataMask(instr, 2, 0));
}

void Armv6m::DecodeLdrbReg(uint16_t instr, UInstrPtr uinstr) {
    uinstr->SetRm(DataMask(instr, 8, 6));
    uinstr->SetRn(DataMask(instr, 5, 3));
    uinstr->SetRt(DataMask(instr, 2, 0));
}

void Armv6m::DecodeLdrhImmed(uint16_t instr, UInstrPtr uinstr) {
    uinstr->SetImmed(DataMask(instr, 10, 6)<<1);
    uinstr->SetRn(DataMask(instr, 5, 3));
    uinstr->SetRt(DataMask(instr, 2, 0));
}

void Armv6m::DecodeLdrhReg(uint16_t instr, UInstrPtr uinstr) {
    uinstr->SetRm(DataMask(instr, 8, 6));
    uinstr->SetRn(DataMask(instr, 5, 3));
    uinstr->SetRt(DataMask(instr, 2, 0));
}

void Armv6m::DecodeLdrsb(uint16_t instr, UInstrPtr uinstr) {
    uinstr->SetRm(DataMask(instr, 8, 6));
    uinstr->SetRn(DataMask(instr, 5, 3));
    uinstr->SetRt(DataMask(instr, 2, 0));
}

void Armv6m::DecodeLdrsh(uint16_t instr, UInstrPtr uinstr) {
    uinstr->SetRm(DataMask(instr, 8, 6));
    uinstr->SetRn(DataMask(instr, 5, 3));
    uinstr->SetRt(DataMask(instr, 2, 0));
}

void Armv6m::DecodeStm(uint16_t instr, UInstrPtr uinstr) {
    uinstr->SetRn(DataMask(instr, 10, 8));
    uinstr->SetRegList(DataMask(instr, 7, 0));
}

void Armv6m::DecodeStrImmedT1(uint16_t instr, UInstrPtr uinstr) {
    uinstr->SetImmed(DataMask(instr, 10, 6)<<2);
    uinstr->SetRn(DataMask(instr, 5, 3));
    uinstr->SetRt(DataMask(instr, 2, 0));
}

void Armv6m::DecodeStrImmedT2(uint16_t instr, UInstrPtr uinstr) {
    uinstr->SetRt(DataMask(instr, 10, 8));
    uinstr->SetImmed(DataMask(instr, 7, 0)<<2);
}

void Armv6m::DecodeStrReg(uint16_t instr, UInstrPtr uinstr) {
    uinstr->SetRm(DataMask(instr, 8, 6));
    uinstr->SetRn(DataMask(instr, 5, 3));
    uinstr->SetRt(DataMask(instr, 2, 0));
}

void Armv6m::DecodeStrbImmed(uint16_t instr, UInstrPtr uinstr) {
    uinstr->SetImmed(DataMask(instr, 10, 6));
    uinstr->SetRn(DataMask(instr, 5, 3));
    uinstr->SetRt(DataMask(instr, 2, 0));
}

void Armv6m::DecodeStrbReg(uint16_t instr, UInstrPtr uinstr) {
    uinstr->SetRm(DataMask(instr, 8, 6));
    uinstr->SetRn(DataMask(instr, 5, 3));
    uinstr->SetRt(DataMask(instr, 2, 0));
}

void Armv6m::DecodeStrhImmed(uint16_t instr, UInstrPtr uinstr) {
    uinstr->SetImmed(DataMask(instr, 10, 6)<<1);
    uinstr->SetRn(DataMask(instr, 5, 3));
    uinstr->SetRt(DataMask(instr, 2, 0));
}

void Armv6m::DecodeStrhReg(uint16_t instr, UInstrPtr uinstr) {
    uinstr->SetRm(DataMask(instr, 8, 6));
    uinstr->SetRn(DataMask(instr, 5, 3));
    uinstr->SetRt(DataMask(instr, 2, 0));
}

void Armv6m::DecodeMovsImmed(uint16_t instr, UInstrPtr uinstr) {
    uinstr->SetRd(DataMask(instr, 10, 8));
    uinstr->SetImmed(DataMask(instr, 7, 0));
    uinstr->SetAPSRUpdate(true);
}

void Armv6m::DecodeMovRegT1(uint16_t instr, UInstrPtr uinstr) {
    uint8_t rd = DataMask(instr, 7, 7) << 3 | DataMask(instr, 2, 0);
    uinstr->SetRm(DataMask(instr, 6, 3));
    uinstr->SetRd(rd);
}

void Armv6m::DecodeMovsRegT2(uint16_t instr, UInstrPtr uinstr) {
    uinstr->SetRm(DataMask(instr, 5, 3));
    uinstr->SetRd(DataMask(instr, 2, 0));
    uinstr->SetAPSRUpdate(true);
}

void Armv6m::DecodeMuls(uint16_t instr, UInstrPtr uinstr) {
    uinstr->SetRn(DataMask(instr, 5, 3));
    uinstr->SetRm(DataMask(instr, 2, 0));
    uinstr->SetRd(DataMask(instr, 2, 0));
    uinstr->SetAPSRUpdate(true);
}

void Armv6m::DecodeNop(uint16_t instr, UInstrPtr uinstr) {
}

void Armv6m::DecodeSev(uint16_t instr, UInstrPtr uinstr) {
}

void Armv6m::DecodeWfe(uint16_t instr, UInstrPtr uinstr) {
}

void Armv6m::DecodeWfi(uint16_t instr, UInstrPtr uinstr) {
}

void Armv6m::DecodeYield(uint16_t instr, UInstrPtr uinstr) {
}

void Armv6m::DecodePop(uint16_t instr, UInstrPtr uinstr) {
    uinstr->SetRegList(DataMask(instr, 7, 0));
}

void Armv6m::DecodePush(uint16_t instr, UInstrPtr uinstr) {
    uinstr->SetRegList(DataMask(instr, 7, 0));
}

void Armv6m::DecodeRev(uint16_t instr, UInstrPtr uinstr) {
    uinstr->SetRm(DataMask(instr, 5, 3));
    uinstr->SetRd(DataMask(instr, 2, 0));
}

void Armv6m::DecodeRev16(uint16_t instr, UInstrPtr uinstr) {
    uinstr->SetRm(DataMask(instr, 5, 3));
    uinstr->SetRd(DataMask(instr, 2, 0));
}

void Armv6m::DecodeRevsh(uint16_t instr, UInstrPtr uinstr) {
    uinstr->SetRm(DataMask(instr, 5, 3));
    uinstr->SetRd(DataMask(instr, 2, 0));
}

void Armv6m::DecodeRors(uint16_t instr, UInstrPtr uinstr) {
    uinstr->SetRm(DataMask(instr, 5, 3));
    uinstr->SetRd(DataMask(instr, 2, 0));
    uinstr->SetRn(DataMask(instr, 2, 0));
    uinstr->SetAPSRUpdate(true);
}

void Armv6m::DecodeRsbs(uint16_t instr, UInstrPtr uinstr) {
    uinstr->SetRd(DataMask(instr, 5, 3));
    uinstr->SetRn(DataMask(instr, 2, 0));
    uinstr->SetAPSRUpdate(true);
}

void Armv6m::DecodeSbcs(uint16_t instr, UInstrPtr uinstr) {
    uinstr->SetRm(DataMask(instr, 5, 3));
    uinstr->SetRd(DataMask(instr, 2, 0));
    uinstr->SetRn(DataMask(instr, 2, 0));
    uinstr->SetAPSRUpdate(true);
}

void Armv6m::DecodeSubsImmedT1(uint16_t instr, UInstrPtr uinstr) {
    uinstr->SetImmed(DataMask(instr, 8, 6));
    uinstr->SetRn(DataMask(instr, 5, 3));
    uinstr->SetRd(DataMask(instr, 2, 0));
    uinstr->SetAPSRUpdate(true);
}

void Armv6m::DecodeSubsImmedT2(uint16_t instr, UInstrPtr uinstr) {
    uinstr->SetRd(DataMask(instr, 10, 8));
    uinstr->SetRn(DataMask(instr, 10, 8));
    uinstr->SetImmed(DataMask(instr, 7, 0));
    uinstr->SetAPSRUpdate(true);
}

void Armv6m::DecodeSubsReg(uint16_t instr, UInstrPtr uinstr) {
    uinstr->SetRm(DataMask(instr, 8, 6));
    uinstr->SetRn(DataMask(instr, 5, 3));
    uinstr->SetRd(DataMask(instr, 2, 0));
    uinstr->SetAPSRUpdate(true);
}

void Armv6m::DecodeSub(uint16_t instr, UInstrPtr uinstr) {
    uinstr->SetImmed(DataMask(instr, 6, 0) << 2);
}

void Armv6m::DecodeSvc(uint16_t instr, UInstrPtr uinstr) {
    uinstr->SetImmed(DataMask(instr, 7, 0));
}

void Armv6m::DecodeSxtb(uint16_t instr, UInstrPtr uinstr) {
    uinstr->SetRm(DataMask(instr, 5, 3));
    uinstr->SetRd(DataMask(instr, 2, 0));
}

void Armv6m::DecodeSxth(uint16_t instr, UInstrPtr uinstr) {
    uinstr->SetRm(DataMask(instr, 5, 3));
    uinstr->SetRd(DataMask(instr, 2, 0));
}

void Armv6m::DecodeUxtb(uint16_t instr, UInstrPtr uinstr) {
    uinstr->SetRm(DataMask(instr, 5, 3));
    uinstr->SetRd(DataMask(instr, 2, 0));
}

void Armv6m::DecodeUxth(uint16_t instr, UInstrPtr uinstr) {
    uinstr->SetRm(DataMask(instr, 5, 3));
    uinstr->SetRd(DataMask(instr, 2, 0));
}