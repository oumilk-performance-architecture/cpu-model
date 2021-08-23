#ifndef CORE_H
#define CORE_H

#include "fetch/fetch.h"
#include <armv6m.h>
#include <state.h>
#include <func.h> // REMOVE

class Core {
    public:
        Core();
        ~Core();
        void Clock();
        
    private:
        int k;
        Fetch *fetch;
        Armv6m *isa;
        State state;
        Func *func;
};

#endif // CORE_H