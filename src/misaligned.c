#include <stdio.h>
#include "./misaligned.h"

static const char* majorColors[] = {
        "White", "Red", "Black", "Yellow", "Violet"
    };
static const char* minorColors[] = {
        "Blue", "Orange", "Green", "Brown", "Slate"
    };

const char* getMajorColor(int index) {
    if (index < MAJOR_INDEX_MIN
     || index >= MAJOR_INDEX_MAX) {
        return "Invalid";
    }
    return majorColors[index];
}

const char* getMinorColor(int index) {
    if (index < MINOR_INDEX_MIN
     || index >= MINOR_INDEX_MAX) {
        return "Invalid";
    }
    return minorColors[index];
}

int getPairNumber(int majorIndex, int minorIndex) {
    return ((majorIndex * COLOR_INDEX_OFFSET) 
            + minorIndex + COLOR_INDEX_DEFAULT);
}

void mapColorPair(char* buffer, size_t bufferSize, int pairNumber, 
                  const char* majorColor, const char* minorColor) {
    snprintf(buffer, bufferSize, "%d | %s | %s", 
             pairNumber, majorColor, minorColor);
}

int printColorMap() {
    int majorIndex = 0;
    int minorIndex = 0;
    char buffer[50];

    for (majorIndex = 0; majorIndex < MAJOR_INDEX_MAX; majorIndex++) {
        for (minorIndex = 0; minorIndex < MINOR_INDEX_MAX; minorIndex++) {
            mapColorPair(buffer, sizeof(buffer), 
                         getPairNumber(majorIndex, minorIndex),
                         getMajorColor(majorIndex),
                         getMinorColor(minorIndex));
            printf("%s\n", buffer);
        }
    }
    return majorIndex * minorIndex;
}

