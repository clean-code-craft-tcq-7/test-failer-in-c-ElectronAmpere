#ifndef __WEATHERREPORT_H__
#define __WEATHERREPORT_H__

#define TEMPERATURE_COLD (-50)
#define TEMPERATURE_NORMAL (25)
#define TEMPERATURE_HOT (60)
#define PRECIPITATION_MIN (0)
#define HUMIDITY_MIN (0)
#define HUMIDITY_MAX (100)
#define WIND_SPEED_MIN_KMPH (0)

// Constants for thresholds (clean, testable)
#define NORMAL_ROOM_TEMPERATURE 25
#define PRECIPITATION_PARTLY_CLOUDY_MIN 20
#define PRECIPITATION_PARTLY_CLOUDY_MAX 60 // Assuming <60 from original <60
#define STORMY_RAIN_WIND_SPEED_KMPH 50
#define HIGH_HUMIDITY 80
#define LOW_HUMIDITY 30
#define HIGH_WIND_SPEED 40 // For "Windy" modifiers
#define LOW_TEMPERATURE 10 // For "Cold" modifiers

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

struct SensorReadings {
  int temperatureInC;
  int precipitation;
  int humidity;
  int windSpeedKMPH;
};

const char *getWeatherString(struct SensorReadings readings);
char *report(struct SensorReadings (*sensorReader)());

#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /* __WEATHERREPORT_H__ */
