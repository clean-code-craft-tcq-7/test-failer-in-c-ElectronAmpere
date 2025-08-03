#include <stdio.h>
#include <assert.h>
#include <limits.h>
#include "../src/tshirts.h"

#define SHIRTS_RANGE_SWEEP(start, stop, checker) \
    for (int sweep = start; sweep <= stop; sweep++) \
    {\
        assert(size(sweep) == checker);\
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
    printf("\nTshirt size test\n");
    testTshirtSizeSmall();
    testTshirtSizeMedium();
    testTshirtSizeLarge();
    printf("All is well (maybe!)\n");
    return 0;
}

