#include <stdio.h>
#include <assert.h>
#include <string.h>

#include "../src/misaligned.h"

void testMisalignedReturnValue() {
    struct ColorPairString expectedPair = {0};
    expectedPair = printColorMap();
    assert(expectedPair.pairNumber == 25);
}

void testMisalignedColorPairs() {
    // Actual: Uses minor "Blue" but logic passes wrong
    assert(strcmp(generateColorPairString(0, "White", "Blue"), "0 | White | Blue") == 0);
    // Actual: "1 | White | Blue" (wrong minor)
    assert(strcmp(generateColorPairString(1, "White", "Orange"), "1 | White | Orange") == 0);
}

void testMisalignedAlignment() {
    // Actual: "1 | White | Blue"
    assert(strcmp(generateColorPairString(1, "White", "Blue"), " 1 | White | Blue") == 0);
    // Passes, but highlights misalignment
    assert(strcmp(generateColorPairString(10, "Black", "Blue"), "10 | Black | Blue") == 0); 
}

int testPrintColorMap() {
    printf("\nPrint color map test\n");

    testMisalignedReturnValue();
    testMisalignedColorPairs();
    testMisalignedAlignment();

    printf("All is well (maybe!)\n");
    return 0;
}
