#include "gtest/gtest.h"

// Moved to C++
int testTshirtSize();
int testMisaligned();
void testRainy();
void testHighPrecipitation();
int testWeatherReport();

TEST(TShirt, Size) {
    testTshirtSize();
}

TEST(ColorMap, Print) {
    testMisaligned();
}

TEST(WeatherReport, Report) {
    testWeatherReport();
}
