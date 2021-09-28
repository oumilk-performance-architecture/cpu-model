#ifndef CORE_H
#define CORE_H

#include <fetch.h>
#include <decode.h>
#include <allocate.h>
//#include <armv6m.h>
#include <state.h>
#include <func.h> // REMOVE
#include <rename.h>

class Core {
    public:
        Core();
        ~Core();
        bool Clock();
        
        void Process(int cycle);
    private:
        int cycle_;
        bool reset_;
        State  state;
        Fetch  fetch;
        Decode decode;
        Allocate allocate;
        //Armv6m *isa;
        
        Func *func;
        Rename *rename;
};

#endif // CORE_H