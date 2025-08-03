#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../src/weatherreport.h"

// This is a stub for a weather sensor. For the sake of testing 
// we create a stub that generates weather data and allows us to
// test the other parts of this application in isolation
// without needing the actual Sensor during development

struct SensorReadings sensorStub() {
    struct SensorReadings readings;
    readings.temperatureInC = 50;
    readings.precipitation = 70;
    readings.humidity = 26;
    readings.windSpeedKMPH = 52;
    return readings;
}

void testRainy() {
    char* weather = report(sensorStub);
    printf("%s\n", weather);
    assert(weather && strstr(weather, "rain") != NULL);
    free(weather);
}

void testHighPrecipitation() {
    // This instance of stub needs to be different-
    // to give high precipitation (>60) and low wind-speed (<50)
    char* weather = report(sensorStub);
    // strengthen the assert to expose the bug
    // (function returns Sunny day, it should predict rain)
    assert(weather && strlen(weather) > 0);
    free(weather);
}

int testWeatherReport() {
    printf("\nWeather report test\n");
    testRainy();
    testHighPrecipitation();
    printf("All is well (maybe!)\n");
    return 0;
}
