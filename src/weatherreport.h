#ifndef __WEATHERREPORT_H__
#define __WEATHERREPORT_H__

struct SensorReadings {
    int temperatureInC;
    int precipitation;
    int humidity;
    int windSpeedKMPH;
};

char size(int cms);
char* report(struct SensorReadings (*sensorReader)());

#endif /* __WEATHERREPORT_H__ */
