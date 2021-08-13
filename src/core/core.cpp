#include "core.h"
#include <fetch.h>
#include <armv6m.h>
#include <uinstr.h>
#include <iostream>
#include <uop.h>
#include <parameter.h>

Core::Core() {
  fetch = new Fetch(20);
  isa = new Armv6m();
};

void Core::Clock() {
  uint16_t instr = 0b0100000010101010;
  UInstr uinstr = isa->DecodeInstructions(instr);
  uinstr.PrintDetails();
  std::cout << "LSLI: " << (int)Uop::LSL_imm << "\n";
  std::cout << "LSLR: " << (int)Uop::LSL_reg << "\n";

  parameter<int> num_knobs ("num_knobs", 3);
  parameter<bool> out_of_order ("out_of_order", true);

  if (num_knobs==3) {
    std::cout << "Yay: this seems to be working\n";
  }
  if (out_of_order == true) {
    std::cout << "we are out of order!\n";
  }
  std::cout << "num_knobs: " << num_knobs << "\n";
}


Core::~Core() {
  delete fetch;
};

