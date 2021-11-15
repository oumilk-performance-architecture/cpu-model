#include "reservation.h"
#include <uinstr.h>
/*
    Models simple reservation queue with source ready checks
*/
Reservation::Reservation(int size):
    table_(size) {
    size_  = size;
};

bool Reservation::CanInsert() {
    return NumFreeEntries() > 0;
}

int Reservation::NumFreeEntries() {
    return size_ - table_.size();
}

void Reservation::Insert(UInstrPtr uinstr) {
    if (!CanInsert()) {
        std::cout << "Resevation Full, cannot insert\n";
        throw std::logic_error("Reservation Full, cannot insert");
    }
    table_.push_back(uinstr);
};
  
UInstrPtr Reservation::PickOldest(int port) {
    auto oldest = [](UInstrPtr entry) {
        return;//entry->
    };
    //auto iter = std::find_if(table_.begin(), table_.end(), oldest);

    //if (iter != table_.end()) {

    //}
};