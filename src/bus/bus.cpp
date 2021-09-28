
#include <iostream>
#include <fstream> 
#include <cstdint>
#include <delay.h>

#include "bus.h"

#include <stdio.h> // Temporary

Delay<uint32_t>* nip_fetch_mem_rp = new Delay<uint32_t>("nip_fetch_mem");
Delay<uint32_t>* bus_return_info_wp = new Delay<uint32_t>("bus_return_info");

Bus::Bus(unsigned int sram_size, unsigned int srom_size):
    sram(sram_size * 1024, 0),
    code(srom_size * 1024, 0)
{
   nip_fetch_mem_rp->SetLatency(3);
}

Bus::~Bus() {

}

void Bus::Process(int cycle) {
    cycle_ = cycle;

    uint32_t pc;
    while (nip_fetch_mem_rp->Receive(pc, cycle_)) {
        bus_return_info_wp->Send(Read16(pc), cycle_);
    }
}

// TODO: Need to check for correct memory access
uint32_t Bus::Read32(uint32_t addr) {
    uint32_t data;
    data =  Read16(addr);
    data |= Read16(addr + 2) << 16;
    return data;
};

void Bus::Write32(uint32_t addr, uint32_t data) {
    uint16_t tdata = (data & 0x0000FFFF);
    Write16(addr, tdata);
    tdata = (data & 0xFFFF0000) >> 16;
    Write16(addr + 2, tdata);
};
 
uint16_t Bus::Read16(uint32_t addr) {
    uint16_t data;
    data =  Read8(addr);
    data |= Read8(addr + 1) << 8;
    return data;
};

void Bus::Write16(uint32_t addr, uint16_t data) {
    uint8_t tdata = (data & 0x00FF); 
    Write8(addr, tdata);
    tdata = (data & 0xFF00) >> 16;
    Write8(addr + 1, tdata);
};

uint8_t Bus::Read8(uint32_t addr) {
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

void Bus::Write8(uint32_t addr, uint8_t data) {
    uint32_t mask = (addr & 0xF0000000) >> 7;
    uint32_t base = 0;
    switch (mask) {
        case 0x0 ... 0x1:
            base = 0;
            code[addr - (base << 7)] = data;
        case 0x2 ... 0x3:
            break;
        case 0x4 ... 0x5:
            base = 4;
            sram[addr - (base << 7)] = data;
        case 0x6 ... 0x9:
            break;
        case 0xA ... 0xD:
            break;
    }
};

// Modifieds: Bus->code;
void Bus::Load_program(std::string filename) {
    std::cout << "loading program: " << filename << "\n";

    FILE *fp = fopen(filename.c_str(), "rb");
    unsigned int ra = fread(&code[0], 1, code.size()*sizeof(uint8_t), fp);
    fclose(fp);
    
};

void Bus::Output_contents(std::string filename) {
    std::ofstream outfile;
    unsigned int i = 0;
    // CODE
    outfile.open(filename + ".code.mem");
    for_each(code.begin(), code.end(), [&i, &outfile](uint8_t value) {
        outfile << std::hex << i++ << " ";
        outfile << std::hex << int(value) << "\n";
    });
    outfile.close();

};