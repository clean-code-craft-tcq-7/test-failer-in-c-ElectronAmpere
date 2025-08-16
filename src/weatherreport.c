#include "weatherreport.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int validateSensorReadings(const struct SensorReadings *readings) {
  if (readings == NULL) {
    return -1;
  }
  if (readings->temperatureInC < TEMPERATURE_COLD ||
      readings->temperatureInC > TEMPERATURE_HOT ||
      readings->precipitation < PRECIPITATION_MIN ||
      readings->humidity < HUMIDITY_MIN || readings->humidity > HUMIDITY_MAX ||
      readings->windSpeedKMPH < WIND_SPEED_MIN_KMPH) {
    return -1;
  }
  return 0;
}

const char *getWeatherString(struct SensorReadings readings) {
  if (validateSensorReadings(&readings) != 0) {
    return "Invalid Readings";
  }

  // Stormy: high precipitation AND high wind speed
  if (readings.precipitation >= PRECIPITATION_PARTLY_CLOUDY_MAX &&
      readings.windSpeedKMPH >= STORMY_RAIN_WIND_SPEED_KMPH) {
    return "Alert, Stormy with heavy rain";
  }

  // Partly cloudy: moderate precipitation
  if (readings.precipitation >= PRECIPITATION_PARTLY_CLOUDY_MIN &&
      readings.precipitation < PRECIPITATION_PARTLY_CLOUDY_MAX) {
    return "Partly Cloudy";
  }

  // Windy: high wind speed (but not stormy)
  if (readings.windSpeedKMPH > HIGH_WIND_SPEED) {
    return "Windy Day";
  }

  // Temperature-based conditions
  if (readings.temperatureInC > NORMAL_ROOM_TEMPERATURE) {
    if (readings.humidity > HIGH_HUMIDITY) {
      return "Humid Hot Day";
    }
    if (readings.humidity < LOW_HUMIDITY) {
      return "Dry Hot Day";
    }
    return "Hot Day";
  }

  if (readings.temperatureInC < LOW_TEMPERATURE) {
    if (readings.humidity > HIGH_HUMIDITY) {
      return "Humid Cold Day";
    }
    return "Cold Day";
  }

  // Sunny: low precipitation, low wind, moderate humidity
  if (readings.precipitation < PRECIPITATION_PARTLY_CLOUDY_MIN &&
      readings.windSpeedKMPH <= SUNNY_WIND_SPEED_MAX &&
      readings.humidity >= LOW_HUMIDITY && readings.humidity <= HIGH_HUMIDITY) {
    return "Sunny Day";
  }

  // Normal: moderate humidity
  if (readings.humidity > HIGH_HUMIDITY) {
    return "Humid Day";
  }
  if (readings.humidity < LOW_HUMIDITY) {
    return "Dry Day";
  }
  return "Normal Day";
}

char *report(struct SensorReadings (*sensorReader)()) {
  if (sensorReader == NULL) {
    return NULL;
  }
  struct SensorReadings readings = sensorReader();
  const char *weatherStr = getWeatherString(readings);
  size_t bufsize = strlen(weatherStr) + 1;
  char *weather = (char *)malloc(bufsize);
  if (weather == NULL) {
    return NULL;
  }
  snprintf(weather, bufsize, "%s", weatherStr);
  return weather;
}
