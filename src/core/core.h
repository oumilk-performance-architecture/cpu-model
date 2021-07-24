#ifndef CORE_H
#define CORE_H

#include <fetch.h>

class Core {
    public:
        Core(int number);
        ~Core();
        unsigned int call_fetch();
        int call_me();
        
    private:
        int k;
        Fetch *fetch;
};

#endif // CORE_H