#ifndef BUS_H
#define BUS_H

#include <cstdint>
#include <vector>
#include <delay.h>


/*
  Loads 1 byte per index
*/
class Bus {
    
    public:
        Bus(unsigned int sram_size, unsigned int srom_size);
        ~Bus(); 

        void Process(int cycle);

        uint32_t Read32(uint32_t addr);
        void Write32(uint32_t addr, uint32_t data);

        uint16_t Read16(uint32_t addr);
        void Write16(uint32_t addr, uint16_t data);
        
        uint8_t Read8(uint32_t addr);
        void Write8(uint32_t addr, uint8_t data);

        void Output_contents(std::string filename);
        void Load_program(std::string filename);
    private:
        int cycle_;
        std::vector<uint8_t> sram;
        std::vector<uint8_t> code;
};

#endif // BUS_H