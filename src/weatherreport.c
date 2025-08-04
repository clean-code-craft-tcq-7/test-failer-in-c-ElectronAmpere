#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "./weatherreport.h"

const char* getWeatherString(struct SensorReadings readings) {
    const char* weatherStr = "Sunny Day";
    if (readings.temperatureInC > 25) {
        if (readings.precipitation >= 20 && readings.precipitation < 60) {
            weatherStr = "Partly Cloudy";
        } else if (readings.windSpeedKMPH > 50) {
            weatherStr = "Alert, Stormy with heavy rain";
        }
    }
    return weatherStr;
}


char* report(struct SensorReadings (*sensorReader)()) {
    size_t bufsize = 50;
    char* weather = (char*)malloc(bufsize);
    if (!weather) return NULL;
    struct SensorReadings readings = sensorReader();
    const char* weatherStr = getWeatherString(readings);
    snprintf(weather, bufsize, "%s", weatherStr);
    return weather;
}
