#include <iostream>
#include <string>
#include "gtest/gtest.h"

#include "../src/weatherreport.h"

//! Note: humidity not used in code

// This is a stub for a weather sensor. For the sake of testing 
// we create a stub that generates weather data and allows us to
// test the other parts of this application in isolation
// without needing the actual Sensor during development
struct SensorReadings safeSensorStub() {
    struct SensorReadings readings = {
        .temperatureInC = 20,
        .precipitation = 0,
        .humidity = 26, //! Not used in code
        .windSpeedKMPH = 0,
    };
    return readings;
}

struct SensorReadings unsafeSensorStub() {
    struct SensorReadings readings = {
        .temperatureInC = 32,
        .precipitation = 10,
        .humidity = 26, //! Not used in code
        .windSpeedKMPH = 40,
    };
    return readings;
}

struct SensorReadings randomSensorStub() {
    struct SensorReadings readings = {
        .temperatureInC = 50,
        .precipitation = 70,
        .humidity = 26, //! Not used in code
        .windSpeedKMPH = 52,
    };
    return readings;
}

void testSafeSensorStub() {
    char* result = report(safeSensorStub);

    EXPECT_STREQ(getWeatherString(safeSensorStub()), "Sunny Day");
    EXPECT_STREQ(result, "Sunny Day");
    free(result);
}

void testUnsafeSensorStub() {
    EXPECT_STREQ(getWeatherString(unsafeSensorStub()), "Hot Day");
}

void testReport() {
    char* result = report(safeSensorStub);
    EXPECT_STREQ(result, "Sunny Day");
    result = report(unsafeSensorStub);
    EXPECT_STREQ(result, "Sunny Day");
    free(result);
}

void testBoundaryConditions() {
    struct SensorReadings boundary = {
        .temperatureInC = 26,
        .precipitation = 60,
        .windSpeedKMPH = 40,
    };
    EXPECT_STREQ(getWeatherString(boundary), "Rainy Day");
}

int testWeatherReport() {
    std::cout <<"\nWeather report test\n";
    testSafeSensorStub();
    testUnsafeSensorStub();
    testReport();
    testBoundaryConditions();
    std::cout <<"All is well (maybe!)\n";
    return 0;
}
