#ifndef CORE_H
#define CORE_H

#include "fetch/fetch.h"
#include <armv6m.h>

class Core {
    public:
        Core();
        ~Core();
        void Clock();
        
    private:
        int k;
        Fetch *fetch;
        Armv6m *isa;
};

#endif // CORE_H