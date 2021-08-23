#ifndef IDATA_H
#define IDATA_H

#include <cstdint>

class Idata {
    public:
        Idata(int cycle);
        void SetIp(uint32_t ip);
        uint32_t GetIp();

        void SetData(uint32_t data);
        uint32_t GetData();

        int GetId();
    private:
        static int id_;
        int cycle_;
        uint32_t ip_;
        uint32_t data_;
        bool data_valid_;
};

#endif // IDATA_H