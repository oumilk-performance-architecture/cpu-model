#ifndef BUS_H
#define BUS_H

#include <cstdint>
#include <vector>

#include "bus.h"
/*
  Loads 1 byte per index
*/
class Bus {
    public:
        Bus(unsigned int sram_size, unsigned int srom_size);
        ~Bus(); 
        uint8_t read8(unsigned int addr);
        uint8_t write8(unsigned int addr, uint8_t data);
        void output_contents(std::string filename);
        void load_program(std::string filename);
    private:
        std::vector<uint8_t> sram;
        std::vector<uint8_t> code;
};

#endif // BUS_H