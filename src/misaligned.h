#ifndef __MISALIGNED_H__
#define __MISALIGNED_H__

#define COLOR_MAP_LENGTH_MAX (50)

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#define MAJOR_INDEX_MIN (0)
#define MAJOR_INDEX_MAX (5)
#define MINOR_INDEX_MIN (0)
#define MINOR_INDEX_MAX (5)

#define COLOR_INDEX_OFFSET (5)
#define COLOR_INDEX_DEFAULT (1)

const char* getMajorColor(int index);
const char* getMinorColor(int index);
int getPairNumber(int majorIndex, int minorIndex);
void mapColorPair(char* buffer, size_t bufferSize, int pairNumber, 
                  const char* majorColor, const char* minorColor);
int printColorMap();

#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /* __MISALIGNED_H__ */
