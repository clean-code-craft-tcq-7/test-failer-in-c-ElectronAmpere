#include <stdio.h>
#include <assert.h>

#include "../src/misaligned.h"

int testPrintColorMap() {
    printf("\nPrint color map test\n");
    int result = printColorMap();
    assert(result == 25);  // This still passes (weak test)

    // Strengthened tests: Duplicate arrays for independent verification (avoids changing production)
    const char* majorColor[] = {"White", "Red", "Black", "Yellow", "Violet"};
    const char* minorColor[] = {"Blue", "Orange", "Green", "Brown", "Slate"};
    int i = 0, j = 0;
    for (i = 0; i < 5; i++) {
        for (j = 0; j < 5; j++) {
            int pairNumber = i * 5 + j;
            char expected[50];
            // Expected correct format: Padded for alignment if pairNumber < 10, correct minorColor[j]
            const char* padding = (pairNumber < 10) ? " " : "";
            snprintf(expected, sizeof(expected), "%s%d | %s | %s", padding, pairNumber, majorColor[i], minorColor[j]);

            // Actual uses production logic (passes minorColor[i] as in buggy code)
            char* actual = generateColorPairString(pairNumber, majorColor[i], minorColor[i]);
            assert(strcmp(actual, expected) == 0);  // This will fail due to bugs
        }
    }
    printf("All is well (maybe!)\n");
    return 0;
}
