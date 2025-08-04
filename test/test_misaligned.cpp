#include <iostream>
#include <string>
#include "gtest/gtest.h"
#include "../src/misaligned.h"

void testGetMajorColor() {
    EXPECT_STREQ(getMajorColor(0), "White");
    EXPECT_STREQ(getMajorColor(1), "Red");
    EXPECT_STREQ(getMajorColor(2), "Black");
    EXPECT_STREQ(getMajorColor(3), "Yellow");
    EXPECT_STREQ(getMajorColor(4), "Violet");
    EXPECT_STREQ(getMajorColor(5), "Invalid");
}

void testGetMinorColor() {
    EXPECT_STREQ(getMinorColor(0), "Blue");
    EXPECT_STREQ(getMinorColor(1), "Orange");
    EXPECT_STREQ(getMinorColor(2), "Green");
    EXPECT_STREQ(getMinorColor(3), "Brown");
    EXPECT_STREQ(getMinorColor(4), "Slate");
    EXPECT_STREQ(getMinorColor(5), "Invalid");
}

void testGetPairNumber() {
    int expectedPairNumber = 0;
    for (int majorIndex = 0; majorIndex < 5; majorIndex++) {
        for (int minorIndex = 0; minorIndex < 5; minorIndex++) {
            expectedPairNumber = 1 + (majorIndex * 5) + minorIndex; 
            EXPECT_EQ(getPairNumber(majorIndex, minorIndex), expectedPairNumber);
        }
    }
}

void testMapColorPair() {
    char buffer[50];
    
    mapColorPair(buffer, sizeof(buffer), 1, "White", "Blue");
    EXPECT_STREQ(buffer, " 1 | White | Blue");

    mapColorPair(buffer, sizeof(buffer), 10, "Red", "Slate");
    EXPECT_STREQ(buffer, "10 | Red | Slate");

}

void testPrintColorMap() {
    EXPECT_EQ(printColorMap(), 25);
}

int testMisaligned() {
    std::cout <<"\nPrint color map test\n";
    
    testGetMajorColor();
    testGetMinorColor();
    testGetPairNumber();
    testMapColorPair();
    testPrintColorMap();

    std::cout <<"All is well (maybe!)\n";
    return 0;
}
