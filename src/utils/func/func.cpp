#include "func.h"
#include <uinstr.h>
#include <uop.h>

Func::Func() {

};

Func::~Func() {

};

UInstr Func::ExecuteUop(UInstr uop) {
    //switch (uop.get)
    Uop temp = Uop::LSLI;
    return uop;
};

UInstr Func::Lsli(UInstr uop) {
    return uop;
};

UInstr Func::Lslr(UInstr uop) {
    return uop;
};