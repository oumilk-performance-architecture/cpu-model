#include "idata.h"

int Idata::id_ = 0;

Idata::Idata(int cycle) {
    static int ID = 0;
    cycle_ = cycle;
    data_valid_ = false;
    ++id_;
}

void Idata::SetIp(uint32_t ip) {
    ip_ = ip;
}

uint32_t Idata::GetIp() {
    return ip_;
}

void Idata::SetData(uint32_t data) {
    data_ = data;
}

uint32_t Idata::GetData() {
    return data_;
}

int Idata::GetId() {
    return id_;
}