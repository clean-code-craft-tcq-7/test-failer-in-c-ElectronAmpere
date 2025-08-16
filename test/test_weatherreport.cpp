#include "../src/weatherreport.h"
#include <gtest/gtest.h>
#include <string.h>

// Test fixture
struct WeatherReportTest {
  struct SensorReadings readings;
};

void WeatherReportTest_SetUp(struct WeatherReportTest *fixture) {
  fixture->readings.temperatureInC = 15;
  fixture->readings.precipitation = 0;
  fixture->readings.humidity = 50;
  fixture->readings.windSpeedKMPH = 10;
}

// Sensor stubs
struct SensorReadings safeSensorStub() {
  struct SensorReadings readings = {
      .temperatureInC = 20,
      .precipitation = 0,
      .humidity = 50,
      .windSpeedKMPH = 0,
  };
  return readings;
}

struct SensorReadings unsafeSensorStub() {
  struct SensorReadings readings = {
      .temperatureInC = 32,
      .precipitation = 0,
      .humidity = 40,
      .windSpeedKMPH = 10,
  };
  return readings;
}

struct SensorReadings randomSensorStub() {
  struct SensorReadings readings = {
      .temperatureInC = 50,
      .precipitation = 70,
      .humidity = 20,
      .windSpeedKMPH = 52,
  };
  return readings;
}

struct SensorReadings humidHotStub() {
  struct SensorReadings readings = {
      .temperatureInC = 30,
      .precipitation = 0,
      .humidity = 85,
      .windSpeedKMPH = 10,
  };
  return readings;
}

struct SensorReadings dryHotStub() {
  struct SensorReadings readings = {
      .temperatureInC = 35,
      .precipitation = 0,
      .humidity = 15,
      .windSpeedKMPH = 10,
  };
  return readings;
}

struct SensorReadings humidColdStub() {
  struct SensorReadings readings = {
      .temperatureInC = -10,
      .precipitation = 0,
      .humidity = 90,
      .windSpeedKMPH = 10,
  };
  return readings;
}

struct SensorReadings coldStub() {
  struct SensorReadings readings = {
      .temperatureInC = -5,
      .precipitation = 0,
      .humidity = 50,
      .windSpeedKMPH = 10,
  };
  return readings;
}

struct SensorReadings humidDayStub() {
  struct SensorReadings readings = {
      .temperatureInC = 22,
      .precipitation = 0,
      .humidity = 85,
      .windSpeedKMPH = 10,
  };
  return readings;
}

struct SensorReadings dryDayStub() {
  struct SensorReadings readings = {
      .temperatureInC = 24,
      .precipitation = 0,
      .humidity = 15,
      .windSpeedKMPH = 10,
  };
  return readings;
}

struct SensorReadings rainyDayStub() {
  struct SensorReadings readings = {
      .temperatureInC = 18,
      .precipitation = 25,
      .humidity = 70,
      .windSpeedKMPH = 10,
  };
  return readings;
}

struct SensorReadings windyDayStub() {
  struct SensorReadings readings = {
      .temperatureInC = 20,
      .precipitation = 0,
      .humidity = 55,
      .windSpeedKMPH = 45,
  };
  return readings;
}

struct SensorReadings invalidStub() {
  struct SensorReadings readings = {
      .temperatureInC = -60,
      .precipitation = -10,
      .humidity = 110,
      .windSpeedKMPH = -5,
  };
  return readings;
}

struct SensorReadings sunnyDayStub() {
  struct SensorReadings readings = {
      .temperatureInC = 15,
      .precipitation = 0,
      .humidity = 50,
      .windSpeedKMPH = 20,
  };
  return readings;
}

// Tests for getWeatherString
TEST(WeatherReportTest, GetWeatherString_SafeSensor) {
  EXPECT_STREQ(getWeatherString(safeSensorStub()), "Sunny Day");
}

TEST(WeatherReportTest, GetWeatherString_UnsafeSensor) {
  EXPECT_STREQ(getWeatherString(unsafeSensorStub()), "Hot Day");
}

TEST(WeatherReportTest, GetWeatherString_RandomSensor) {
  EXPECT_STREQ(getWeatherString(randomSensorStub()),
               "Alert, Stormy with heavy rain");
}

TEST(WeatherReportTest, GetWeatherString_HumidHot) {
  EXPECT_STREQ(getWeatherString(humidHotStub()), "Humid Hot Day");
}

TEST(WeatherReportTest, GetWeatherString_DryHot) {
  EXPECT_STREQ(getWeatherString(dryHotStub()), "Dry Hot Day");
}

TEST(WeatherReportTest, GetWeatherString_HumidCold) {
  EXPECT_STREQ(getWeatherString(humidColdStub()), "Humid Cold Day");
}

TEST(WeatherReportTest, GetWeatherString_Cold) {
  EXPECT_STREQ(getWeatherString(coldStub()), "Cold Day");
}

TEST(WeatherReportTest, GetWeatherString_HumidDay) {
  EXPECT_STREQ(getWeatherString(humidDayStub()), "Humid Day");
}

TEST(WeatherReportTest, GetWeatherString_DryDay) {
  EXPECT_STREQ(getWeatherString(dryDayStub()), "Dry Day");
}

TEST(WeatherReportTest, GetWeatherString_RainyDay) {
  EXPECT_STREQ(getWeatherString(rainyDayStub()), "Partly Cloudy");
}

TEST(WeatherReportTest, GetWeatherString_WindyDay) {
  EXPECT_STREQ(getWeatherString(windyDayStub()), "Windy Day");
}

TEST(WeatherReportTest, GetWeatherString_SunnyDay) {
  EXPECT_STREQ(getWeatherString(sunnyDayStub()), "Sunny Day");
}

TEST(WeatherReportTest, GetWeatherString_Invalid) {
  EXPECT_STREQ(getWeatherString(invalidStub()), "Invalid Readings");
}

TEST(WeatherReportTest, GetWeatherString_BoundaryConditions) {
  struct SensorReadings boundaryHumid = {
      .temperatureInC = 26,
      .precipitation = 0,
      .humidity = 81,
      .windSpeedKMPH = 10,
  };
  EXPECT_STREQ(getWeatherString(boundaryHumid), "Humid Hot Day");

  struct SensorReadings boundaryDry = {
      .temperatureInC = 26,
      .precipitation = 0,
      .humidity = 29,
      .windSpeedKMPH = 10,
  };
  EXPECT_STREQ(getWeatherString(boundaryDry), "Dry Hot Day");

  struct SensorReadings boundarySunny = {
      .temperatureInC = 15,
      .precipitation = 19,
      .humidity = 50,
      .windSpeedKMPH = 30,
  };
  EXPECT_STREQ(getWeatherString(boundarySunny), "Sunny Day");

  struct SensorReadings boundaryPartlyCloudy = {
      .temperatureInC = 15,
      .precipitation = 20,
      .humidity = 50,
      .windSpeedKMPH = 10,
  };
  EXPECT_STREQ(getWeatherString(boundaryPartlyCloudy), "Partly Cloudy");

  struct SensorReadings boundaryStormy = {
      .temperatureInC = 15,
      .precipitation = 60,
      .humidity = 50,
      .windSpeedKMPH = 50,
  };
  EXPECT_STREQ(getWeatherString(boundaryStormy),
               "Alert, Stormy with heavy rain");
}

// Tests for report
TEST(WeatherReportTest, Report_SafeSensor) {
  char *result = report(safeSensorStub);
  EXPECT_STREQ(result, "Sunny Day");
  free(result);
}

TEST(WeatherReportTest, Report_UnsafeSensor) {
  char *result = report(unsafeSensorStub);
  EXPECT_STREQ(result, "Hot Day");
  free(result);
}

TEST(WeatherReportTest, Report_RandomSensor) {
  char *result = report(randomSensorStub);
  EXPECT_STREQ(result, "Alert, Stormy with heavy rain");
  free(result);
}

TEST(WeatherReportTest, Report_Invalid) {
  char *result = report(invalidStub);
  EXPECT_STREQ(result, "Invalid Readings");
  free(result);
}

TEST(WeatherReportTest, Report_SunnyDay) {
  char *result = report(sunnyDayStub);
  EXPECT_STREQ(result, "Sunny Day");
  free(result);
}

TEST(WeatherReportTest, Report_NullSensor) {
  char *result = report(NULL);
  EXPECT_TRUE(result == NULL);
  if (result)
    free(result);
}

int testWeatherReport() {
  std::cout << "\nWeather report test\n";

  std::cout << "All is well (maybe!)\n";
  return 0;
}
