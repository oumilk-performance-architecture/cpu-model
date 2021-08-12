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
  bus->load_program(argv[1]);
  bus->output_contents("./ou");

  // Testme
  cout << "Version " << arm_cpu_VERSION_MAJOR << "." << arm_cpu_VERSION_MINOR << "\n\n";
  //cout << "Core Value: " << co->call_me() << "\n";
  //cout << "Core Value: " << co->call_fetch() << "\n";

  while (true) {
    core->Clock();
    break;
  }
  return 0;
}
