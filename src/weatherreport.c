#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "./weatherreport.h"

const char *getWeatherString(struct SensorReadings readings) {
  // Guard against invalid inputs (defensive, testable)
  if ((readings.temperatureInC < TEMPERATURE_COLD ||
       readings.temperatureInC > TEMPERATURE_HOT) ||
      (readings.precipitation < PRECIPITATION_MIN) ||
      (readings.humidity < HUMIDITY_MIN || readings.humidity > HUMIDITY_MAX) ||
      (readings.windSpeedKMPH < WIND_SPEED_MIN_KMPH)) {
    return "Invalid Readings";
  }

  const char *weatherStr = "Sunny Day";
  if (readings.temperatureInC > NORMAL_ROOM_TEMPERATURE) {
    if (readings.precipitation >= PRECIPITATION_PARTLY_CLOUDY_MIN &&
        readings.precipitation < PRECIPITATION_PARTLY_CLOUDY_MAX) {
      weatherStr = "Partly Cloudy";
    } else if (readings.windSpeedKMPH > STORMY_RAIN_WIND_SPEED_KMPH) {
      weatherStr = "Alert, Stormy with heavy rain";
    } else {
      // New: Integrate humidity for hot days
      if (readings.humidity > HIGH_HUMIDITY) {
        weatherStr = "Humid Hot Day";
      } else if (readings.humidity < LOW_HUMIDITY) {
        weatherStr = "Dry Hot Day";
      } else {
        weatherStr = "Hot Day";
      }
    }
  } else {
    // New: Conditions for non-hot temps, incorporating humidity
    if (readings.temperatureInC < LOW_TEMPERATURE) {
      if (readings.humidity > HIGH_HUMIDITY) {
        weatherStr = "Humid Cold Day";
      } else {
        weatherStr = "Cold Day";
      }
    } else {
      // Mild temps
      if (readings.humidity > HIGH_HUMIDITY) {
        weatherStr = "Humid Day";
      } else if (readings.humidity < LOW_HUMIDITY) {
        weatherStr = "Dry Day";
      }
      // Overlay precipitation/wind if applicable (e.g., rainy mild day)
      if (readings.precipitation >= PRECIPITATION_PARTLY_CLOUDY_MIN) {
        weatherStr = "Rainy Day";
      } else if (readings.windSpeedKMPH > HIGH_WIND_SPEED) {
        weatherStr = "Windy Day";
      }
    }
  }

  return weatherStr;
}

char *report(struct SensorReadings (*sensorReader)()) {
  size_t bufsize = 50;
  char *weather = (char *)malloc(bufsize);
  if (!weather)
    return NULL;
  struct SensorReadings readings = sensorReader();
  const char *weatherStr = getWeatherString(readings);
  snprintf(weather, bufsize, "%s", weatherStr);
  return weather;
}
