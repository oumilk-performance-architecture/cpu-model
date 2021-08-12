#include "core.h"
#include <fetch.h>
#include <armv6m.h>
#include <uinstr.h>
#include <iostream>
#include <uop.h>

Core::Core() {
  fetch = new Fetch(20);
  isa = new Armv6m();
};

void Core::Clock() {
  uint16_t instr = 0b0100000010101010;
  UInstr uinstr = isa->DecodeInstructions(instr);
  uinstr.PrintDetails();
  std::cout << "LSLI: " << (int)Uop::LSLI << "\n";
  std::cout << "LSLR: " << (int)Uop::LSLR << "\n";
}


Core::~Core() {
  delete fetch;
};

