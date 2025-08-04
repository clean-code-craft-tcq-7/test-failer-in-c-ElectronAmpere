#include <iostream>
#include <string>
#include "gtest/gtest.h"
#include "../src/misaligned.h"

#define CHECK_STREQ_MAJOR(index, value) EXPECT_STREQ(getMajorColor(index), value)
#define CHECK_STREQ_MINOR(index, value) EXPECT_STREQ(getMinorColor(index), value)

void testGetMajorColor() {
    CHECK_STREQ_MAJOR(0, "White");
    CHECK_STREQ_MAJOR(1, "Red");
    CHECK_STREQ_MAJOR(2, "Black");
    CHECK_STREQ_MAJOR(3, "Yellow");
    CHECK_STREQ_MAJOR(4, "Violet");
    CHECK_STREQ_MAJOR(5, "Invalid");
}

void testGetMinorColor() {
    CHECK_STREQ_MINOR(0, "Blue");
    CHECK_STREQ_MINOR(1, "Orange");
    CHECK_STREQ_MINOR(2, "Green");
    CHECK_STREQ_MINOR(3, "Brown");
    CHECK_STREQ_MINOR(4, "Slate");
    CHECK_STREQ_MINOR(5, "Invalid");
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
