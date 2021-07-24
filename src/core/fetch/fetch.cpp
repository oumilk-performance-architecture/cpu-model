#include "fetch.h"

Fetch::Fetch(int number) {
    k = number;
};

int Fetch::what_am_i() {
    return k;
};

Fetch::~Fetch() {

};
