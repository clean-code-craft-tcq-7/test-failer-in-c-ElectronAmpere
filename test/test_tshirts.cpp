#include <iostream>
#include <climits>
#include "../src/tshirts.h"
#include "gtest/gtest.h"

#define SHIRTS_RANGE_SWEEP(start, stop, checker) \
    for (int sweep = start; sweep <= stop; sweep++) { \
        EXPECT_EQ(size(sweep), checker); \
    }

void testTshirtSizeSmall() {
    SHIRTS_RANGE_SWEEP(0, 38, 'S');
}

void testTshirtSizeMedium() {
    SHIRTS_RANGE_SWEEP(39, 42, 'M');
}

void testTshirtSizeLarge() {
    SHIRTS_RANGE_SWEEP(43, INT_MAX, 'L');
}

int testTshirtSize() {
    std::cout <<"\nTshirt size test\n";
    testTshirtSizeSmall();
    testTshirtSizeMedium();
    testTshirtSizeLarge();
    std::cout <<"All is well (maybe!)\n";
    return 0;
}

