#include <iostream>
#include <string>
#include "gtest/gtest.h"
#include "../src/misaligned.h"

#define CHECK_STREQ_MAJOR(index, value) EXPECT_STREQ(getMajorColor(index), value)
#define CHECK_STREQ_MINOR(index, value) EXPECT_STREQ(getMinorColor(index), value)
#define MAX_COLORS (5)

static const char* majorColors[MAX_COLORS] = {
        "White", "Red", "Black", "Yellow", "Violet"
    };
static const char* minorColors[MAX_COLORS] = {
        "Blue", "Orange", "Green", "Brown", "Slate"
    };

static const char* expectedColorPair[MAX_COLORS * MAX_COLORS] = {
    " 1 | White  | Blue",
    " 2 | White  | Orange",
    " 3 | White  | Green",
    " 4 | White  | Brown",
    " 5 | White  | Slate",
    " 6 | Red    | Blue",
    " 7 | Red    | Orange",
    " 8 | Red    | Green",
    " 9 | Red    | Brown",
    "10 | Red    | Slate",
    "11 | Black  | Blue",
    "12 | Black  | Orange",
    "13 | Black  | Green",
    "14 | Black  | Brown",
    "15 | Black  | Slate",
    "16 | Yellow | Blue",
    "17 | Yellow | Orange",
    "18 | Yellow | Green",
    "19 | Yellow | Brown",
    "20 | Yellow | Slate",
    "21 | Violet | Blue",
    "22 | Violet | Orange",
    "23 | Violet | Green",
    "24 | Violet | Brown",
    "25 | Violet | Slate",
};

void testGetMajorColor() {
    // Iteration of valid set
    for (int index = 0; index < MAX_COLORS; index++){
        CHECK_STREQ_MAJOR(0, majorColors[index]);
    }
    // Invalid set
    CHECK_STREQ_MAJOR(5, "Invalid");
}

void testGetMinorColor() {

    // Iteration of valid set
    for (int index = 0; index < MAX_COLORS; index++){
        CHECK_STREQ_MINOR(0, minorColors[index]);
    }
    // Invalid set
    CHECK_STREQ_MINOR(5, "Invalid");
}

void testGetPairNumber() {
    int expectedPairNumber = 0;
    for (int majorIndex = 0; majorIndex < MAX_COLORS; majorIndex++) {
        for (int minorIndex = 0; minorIndex < MAX_COLORS; minorIndex++) {
            expectedPairNumber = 1 + (majorIndex * MAX_COLORS) + minorIndex; 
            EXPECT_EQ(getPairNumber(majorIndex, minorIndex), expectedPairNumber);
        }
    }
}

void testMapColorPair() {
    char buffer[50];
    int expectedPairNumber = 0;

    for (int majorIndex = 0; majorIndex < MAX_COLORS; majorIndex++) {
        for (int minorIndex = 0; minorIndex < MAX_COLORS; minorIndex++) {
            expectedPairNumber = 1 + (majorIndex * MAX_COLORS) + minorIndex;
            mapColorPair(buffer, sizeof(buffer), expectedPairNumber, 
                         majorColors[majorIndex], minorColors[minorIndex]);
            EXPECT_STREQ(buffer, expectedColorPair[expectedPairNumber - 1]);
        }
    }
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
