
#include <iostream>
#include <fstream> 
#include <cstdint>

#include "bus.h"

#include <stdio.h> // Temporary
Bus::Bus(unsigned int sram_size, unsigned int srom_size):
    sram(sram_size * 1024, 0),
    code(srom_size * 1024, 0)
{
}

Bus::~Bus() {

}

uint8_t Bus::read8(unsigned int addr) {
    unsigned int mask = (addr & 0xF0000000) >> 7;
    unsigned int base = 0;
    switch (mask) {
        case 0x0 ... 0x1:
            base = 0;
            return code[addr - (base << 7)];
        case 0x2 ... 0x3:
            break;
        case 0x4 ... 0x5:
            base = 4;
            return sram[addr - (base << 7)];
        case 0x6 ... 0x9:
            break;
        case 0xA ... 0xD:
            break;
    }
    return 0;
};

uint8_t Bus::write8(unsigned int addr, uint8_t data) {
    unsigned int mask = (addr & 0xF0000000) >> 7;
    unsigned int base = 0;
    switch (mask) {
        case 0x0 ... 0x1:
            base = 0;
            code[addr - (base << 7)] = data;
            return data;
        case 0x2 ... 0x3:
            break;
        case 0x4 ... 0x5:
            base = 4;
            sram[addr - (base << 7)] = data;
            return data;
        case 0x6 ... 0x9:
            break;
        case 0xA ... 0xD:
            break;
    }
    return 0;
};

// Modifieds: Bus->code;
void Bus::load_program(std::string filename) {
    std::cout << "loading program: " << filename << "\n";

    FILE *fp = fopen(filename.c_str(), "rb");
    unsigned int ra = fread(&code[0], 1, code.size()*sizeof(uint8_t), fp);
    fclose(fp);
    
};

void Bus::output_contents(std::string filename) {
    std::ofstream outfile;
    unsigned int i = 0;
    // CODE
    outfile.open(filename + ".code.mem");
    for_each(code.begin(), code.end(), [&i, &outfile](uint8_t value) {
        outfile << std::dec << i++ << " ";
        outfile << std::dec << int(value) << "\n";
    });
    outfile.close();

};