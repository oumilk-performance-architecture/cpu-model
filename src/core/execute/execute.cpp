#include "execute.h"

Execute::Execute() {
    rename_to_reservation_wp = std::make_unique<Delay<UInstrPtr>>("rename_to_reservation");
};

void Execute::InsertRS() {

};

void Execute::Process(int cycle, bool reset) {
    cycle_ = cycle;
    InsertRS();
};
