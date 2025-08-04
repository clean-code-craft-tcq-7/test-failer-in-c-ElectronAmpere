#include "gtest/gtest.h"

// Moved to C++
int testTshirtSize();
int testPrintColorMap();
void testRainy();
void testHighPrecipitation();
int testWeatherReport();

TEST(TShirt, Size) {
    testTshirtSize();
}

TEST(ColorMap, Print) {
    testPrintColorMap();
}

TEST(WeatherReport, Report) {
    testWeatherReport();
}
