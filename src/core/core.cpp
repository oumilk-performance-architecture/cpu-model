#include "core.h"
#include <fetch.h>

Core::Core(int number) {
  k = number;
  fetch = new Fetch(number + 20);
};

unsigned int Core::call_fetch() {
  return fetch->what_am_i();
};

int Core::call_me() {
  return k;
};


Core::~Core() {

};

