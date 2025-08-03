#include "gtest/gtest.h"

extern "C" {
    int testPrintColorMap();
    int testTshirtSize();
    void testRainy();
    void testHighPrecipitation();
    int testWeatherReport();
}


TEST(TShirt, Size) {
    testTshirtSize();
}

TEST(ColorMap, Print) {
    testPrintColorMap();
}

TEST(WeatherReport, Report) {
    testWeatherReport();
}
