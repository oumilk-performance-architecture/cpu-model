#include "core.h"

Core::Core(int number) {
  k = number;
};

int Core::call_me() {
    return k;
};

Core::~Core() {

};

