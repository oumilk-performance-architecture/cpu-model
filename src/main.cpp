#include <ProjectConfig.h>
#include <core.h>
#include <bus.h>
#include <iostream>

// Temporary
#include <stdio.h>
#include <stdlib.h>

using namespace std;

static const char *const HEADER = "\nARM CPU Performance Model.\n\n";

int main(int argc, const char *argv[]) {
  Core *core = new Core();
  Bus *bus = new Bus(1024, 1024);

  cout << HEADER;

  // ensure the correct number of parameters are used.
  if (argc < 2) {
    return 1;
  }

  // Load Program into Memory
  bus->Load_program(argv[1]);
  bus->Output_contents("./ou");

  // Version
  cout << "Version " << arm_cpu_VERSION_MAJOR << "." << arm_cpu_VERSION_MINOR << "\n\n";

  // Run CPU until Done
  bool run = true;
  int cycle = 0;
  while (true) {
    core->Process(cycle);
    bus->Process(cycle);
    cycle++;

    if (cycle > 15) {
      break;
    }
  }
  return 0;
}
