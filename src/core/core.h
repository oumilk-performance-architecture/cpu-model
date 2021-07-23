#ifndef CORE_H
#define CORE_H

class Core {
    public:
        Core(int number);
        ~Core();
        int call_me();
    private:
        int k;
};

#endif // CORE_H