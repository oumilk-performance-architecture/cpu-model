#ifndef FUNC_H
#define FUNC_H

#include <uinstr.h>

class Func {
    public:
        Func();
        ~Func();
        UInstr ExecuteUop(UInstr uop);

    private:
        UInstr Lsli(UInstr uop);
        UInstr Lslr(UInstr uop);

};
#endif //FUNC_H