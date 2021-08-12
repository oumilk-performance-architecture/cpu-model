#include <bus.h>
#include "gtest/gtest.h"


#define VUI std::vector<unsigned int>
#define VU8 std::vector<uint8_t>

class BusTest: public ::testing::Test {
    protected:
        VUI address = { };
        VU8 data    = { };
    
};