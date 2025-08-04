#ifndef __MISALIGNED_H__
#define __MISALIGNED_H__

#define COLOR_MAP_LENGTH_MAX (50)
struct ColorPairString {
    int pairNumber;
    char pairColor[COLOR_MAP_LENGTH_MAX];
};

struct ColorPairString printColorMap();
char* generateColorPairString(int pairNumber, const char* majorColor, const char* minorColor);

#endif /* __MISALIGNED_H__ */
