#include <stdio.h>
#include "./misaligned.h"

char* generateColorPairString(int pairNumber, const char* majorColor, const char* minorColor) {
    // Static buffer to avoid memory management
    static char result[50];
    // No padding added to check for alignment
    snprintf(result, sizeof(result), "%d | %s | %s", pairNumber, majorColor, minorColor);
    return result;
}

struct ColorPairString printColorMap() {
    char* majorColor[] = {"White", "Red", "Black", "Yellow", "Violet"};
    char* minorColor[] = {"Blue", "Orange", "Green", "Brown", "Slate"};
    struct ColorPairString colorMap = {0};

    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            colorMap.pairNumber = i * 5 +j;
            snprintf(colorMap.pairColor, sizeof(colorMap.pairColor), "%d | %s | %s", colorMap.pairNumber, majorColor[i], minorColor[i]);
            printf("%s", colorMap.pairColor);
        }
    }

    return colorMap;
}

