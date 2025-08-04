#ifndef __WEATHERREPORT_H__
#define __WEATHERREPORT_H__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

struct SensorReadings {
    int temperatureInC;
    int precipitation;
    int humidity;
    int windSpeedKMPH;
};

const char* getWeatherString(struct SensorReadings readings);
char* report(struct SensorReadings (*sensorReader)());

#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /* __WEATHERREPORT_H__ */
