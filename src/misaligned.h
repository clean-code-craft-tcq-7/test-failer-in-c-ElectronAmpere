#ifndef __MISALIGNED_H__
#define __MISALIGNED_H__

#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#define MAJOR_INDEX_MIN (0)
#define MAJOR_INDEX_MAX (5)
#define MINOR_INDEX_MIN (0)
#define MINOR_INDEX_MAX (5)

#define COLOR_INDEX_OFFSET (5)
#define COLOR_INDEX_DEFAULT (1)
#define COLOR_MAP_LENGTH_MIN (10)
#define COLOR_MAP_LENGTH_MAX (50)
#define COLOR_HEADER_LENGTH_MAX (50)

const char *getMajorColor(int index);
const char *getMinorColor(int index);
int getPairNumber(int majorIndex, int minorIndex);
void mapColorPair(char *buffer, size_t bufferSize, int pairNumber,
                  const char *majorColor, const char *minorColor);
void mapColorHeader(char *buffer, size_t bufferSize);
int printColorMap();

#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /* __MISALIGNED_H__ */
