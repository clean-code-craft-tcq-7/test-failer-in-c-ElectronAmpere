#include "gtest/gtest.h"
#include "./test_misaligned.h"
#include "./test_tshirts.h"
#include "./test_weatherreport.h"

extern "C" {
    void testTshirtSize();
    void testPrintColorMap();
    void testWeatherReport();
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
