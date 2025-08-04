#include <stdio.h>
#include <assert.h>

#include "../src/misaligned.h"

void testMisalignedReturnValue() {
    assert(printColorMap() == 25);
}

void testMisalignedColorPairs() {
    // Actual: Uses minor "Blue" but logic passes wrong
    assert(getColorPairString(0, "White", "Blue"), "0 | White | Blue");
    // Actual: "1 | White | Blue" (wrong minor)
    assert(getColorPairString(1, "White", "Orange"), "1 | White | Orange");
}

void testMisalignedAlignment() {
    // Actual: "1 | White | Blue"
    assert(getColorPairString(1, "White", "Blue"), " 1 | White | Blue");
    // Passes, but highlights misalignment
    assert(getColorPairString(10, "Black", "Blue"), "10 | Black | Blue"); 
}

int testPrintColorMap() {
    printf("\nPrint color map test\n");

    testMisalignedReturnValue();
    testMisalignedColorPairs();
    testMisalignedAlignment();

    printf("All is well (maybe!)\n");
    return 0;
}
