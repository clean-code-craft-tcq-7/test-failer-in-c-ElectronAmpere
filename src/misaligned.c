#include <stdio.h>
#include "./misaligned.h"

char* generateColorPairString(int pairNumber, const char* majorColor, const char* minorColor) {
    // Static buffer to avoid memory management
    static char result[50];
    // No padding added to check for alignment
    snprintf(result, sizeof(result), "%d | %s | %s", pairNumber, majorColor, minorColor);
    return result;
}

int printColorMap() {
    char* majorColor[] = {"White", "Red", "Black", "Yellow", "Violet"};
    char* minorColor[] = {"Blue", "Orange", "Green", "Brown", "Slate"};
    
    int i = 0, j = 0;
    for (i = 0; i < 5; i++) {
        for (j = 0; j < 5; j++) {
            printf("%s\n", 
                   generateColorPairString(i * 5 + j, majorColor[i], minorColor[i]));
        }
    }
    return i * j;
}

