#include "./misaligned.h"
#include <stdio.h>

static const char *majorColors[] = {"White", "Red", "Black", "Yellow",
                                    "Violet"};
static const char *minorColors[] = {"Blue", "Orange", "Green", "Brown",
                                    "Slate"};

const char *getMajorColor(int index) {
  if (index < MAJOR_INDEX_MIN || index >= MAJOR_INDEX_MAX) {
    return "Invalid";
  }
  return majorColors[index];
}

const char *getMinorColor(int index) {
  if (index < MINOR_INDEX_MIN || index >= MINOR_INDEX_MAX) {
    return "Invalid";
  }
  return minorColors[index];
}

int getPairNumber(int majorIndex, int minorIndex) {
  return ((majorIndex * COLOR_INDEX_OFFSET) + minorIndex + COLOR_INDEX_DEFAULT);
}

void mapColorPair(char *buffer, size_t bufferSize, int pairNumber,
                  const char *majorColor, const char *minorColor) {
  snprintf(buffer, bufferSize, "%8d | %11s | %s", pairNumber, majorColor,
           minorColor);
}

void mapColorHeader(char *buffer, size_t bufferSize) {
  snprintf(buffer, bufferSize, "%-8s | %-11s | %-11s", "Pair No.",
           "Major Color", "Minor Color");
}

int printColorMap() {
  int majorIndex = 0;
  int minorIndex = 0;
  char buffer[COLOR_MAP_LENGTH_MAX];
  char bufferHeader[COLOR_HEADER_LENGTH_MAX];

  mapColorHeader(bufferHeader, sizeof(bufferHeader));
  printf("%s\n", bufferHeader);
  for (majorIndex = 0; majorIndex < MAJOR_INDEX_MAX; majorIndex++) {
    for (minorIndex = 0; minorIndex < MINOR_INDEX_MAX; minorIndex++) {
      mapColorPair(buffer, sizeof(buffer),
                   getPairNumber(majorIndex, minorIndex),
                   getMajorColor(majorIndex), getMinorColor(minorIndex));
      printf("%s\n", buffer);
    }
  }
  return majorIndex * minorIndex;
}
