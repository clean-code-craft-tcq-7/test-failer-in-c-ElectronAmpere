#include <iostream>
#include <string>
#include "gtest/gtest.h"
#include "../src/misaligned.h"

void testMisalignedReturnValue() {
    struct ColorPairString expectedPair = {0};
    expectedPair = printColorMap();
    EXPECT_EQ(expectedPair.pairNumber, 25);
}

void testMisalignedColorPairs() {
    // Actual: Uses minor "Blue" but logic passes wrong
    EXPECT_EQ(generateColorPairString(0, "White", "Blue"), "0 | White | Blue");
    // Actual: "1 | White | Blue" (wrong minor)
    EXPECT_EQ(generateColorPairString(1, "White", "Orange"), "1 | White | Orange");
}

void testMisalignedAlignment() {
    // Actual: "1 | White | Blue"
    EXPECT_EQ(generateColorPairString(1, "White", "Blue"), " 1 | White | Blue");
    // Passes, but highlights misalignment
    EXPECT_EQ(generateColorPairString(10, "Black", "Blue"), "10 | Black | Blue"); 
}

int testPrintColorMap() {
    std::cout <<"\nPrint color map test\n";

    testMisalignedReturnValue();
    testMisalignedColorPairs();
    testMisalignedAlignment();

    std::cout <<"All is well (maybe!)\n";
    return 0;
}
