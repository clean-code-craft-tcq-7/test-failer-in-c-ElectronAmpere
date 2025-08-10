#include "../src/weatherreport.h"
#include "gtest/gtest.h"
#include <iostream>
#include <string>

// This is a stub for a weather sensor. For the sake of testing
// we create a stub that generates weather data and allows us to
// test the other parts of this application in isolation
// without needing the actual Sensor during development

// Safe stub: Low temp, moderate humidity → "Sunny Day" (weak, passes)
struct SensorReadings safeSensorStub() {
  struct SensorReadings readings = {
      .temperatureInC = 20,
      .precipitation = 0,
      .humidity = 50, // Now used in code
      .windSpeedKMPH = 0,
  };
  return readings;
}

// Unsafe stub: High temp, low precip/wind, moderate humidity → "Hot Day"
// (strengthened, should pass with update)
struct SensorReadings unsafeSensorStub() {
  struct SensorReadings readings = {
      .temperatureInC = 32,
      .precipitation = 10,
      .humidity = 40, // Now used in code
      .windSpeedKMPH = 40,
  };
  return readings;
}

// Random stub: High temp, high precip/wind, low humidity → "Alert, Stormy with
// heavy rain" (passes if wind>50)
struct SensorReadings randomSensorStub() {
  struct SensorReadings readings = {
      .temperatureInC = 50,
      .precipitation = 70,
      .humidity = 20, // Now used in code
      .windSpeedKMPH = 52,
  };
  return readings;
}

// New stub for Humid Hot Day: High temp, high humidity → "Humid Hot Day"
struct SensorReadings humidHotStub() {
  struct SensorReadings readings = {
      .temperatureInC = 30,
      .precipitation = 0,
      .humidity = 85, // Now used in code
      .windSpeedKMPH = 10,
  };
  return readings;
}

// New stub for Dry Hot Day: High temp, low humidity → "Dry Hot Day"
struct SensorReadings dryHotStub() {
  struct SensorReadings readings = {
      .temperatureInC = 35,
      .precipitation = 0,
      .humidity = 25, // Now used in code
      .windSpeedKMPH = 15,
  };
  return readings;
}

// New stub for Humid Cold Day: Low temp, high humidity → "Humid Cold Day"
struct SensorReadings humidColdStub() {
  struct SensorReadings readings = {
      .temperatureInC = 5,
      .precipitation = 5,
      .humidity = 90, // Now used in code
      .windSpeedKMPH = 20,
  };
  return readings;
}

// New stub for Cold Day: Low temp, moderate humidity → "Cold Day"
struct SensorReadings coldStub() {
  struct SensorReadings readings = {
      .temperatureInC = 8,
      .precipitation = 0,
      .humidity = 60, // Now used in code
      .windSpeedKMPH = 10,
  };
  return readings;
}

// New stub for Humid Day: Mild temp, high humidity → "Humid Day"
struct SensorReadings humidDayStub() {
  struct SensorReadings readings = {
      .temperatureInC = 22,
      .precipitation = 0,
      .humidity = 85, // Now used in code
      .windSpeedKMPH = 5,
  };
  return readings;
}

// New stub for Dry Day: Mild temp, low humidity → "Dry Day"
struct SensorReadings dryDayStub() {
  struct SensorReadings readings = {
      .temperatureInC = 24,
      .precipitation = 0,
      .humidity = 25, // Now used in code
      .windSpeedKMPH = 10,
  };
  return readings;
}

// New stub for Rainy Day: Mild temp, high precip → "Rainy Day"
struct SensorReadings rainyDayStub() {
  struct SensorReadings readings = {
      .temperatureInC = 18,
      .precipitation = 40,
      .humidity = 70, // Now used in code
      .windSpeedKMPH = 15,
  };
  return readings;
}

// New stub for Windy Day: Mild temp, high wind → "Windy Day"
struct SensorReadings windyDayStub() {
  struct SensorReadings readings = {
      .temperatureInC = 20,
      .precipitation = 0,
      .humidity = 55, // Now used in code
      .windSpeedKMPH = 45,
  };
  return readings;
}

// New stub for Invalid Readings: Out-of-range values → "Invalid Readings"
struct SensorReadings invalidStub() {
  struct SensorReadings readings = {
      .temperatureInC = -60,
      .precipitation = -10,
      .humidity = 110, // Now used in code
      .windSpeedKMPH = -5,
  };
  return readings;
}

// Test safe stub: Weak, should pass
void testSafeSensorStub() {
  char *result = report(safeSensorStub);
  EXPECT_STREQ(getWeatherString(safeSensorStub()), "Sunny Day");
  EXPECT_STREQ(result, "Sunny Day");
  free(result);
}

// Test unsafe stub: Strengthened, should pass with "Hot Day"
void testUnsafeSensorStub() {
  EXPECT_STREQ(getWeatherString(unsafeSensorStub()), "Hot Day");
}

// Test report function: Mix weak (pass) and strengthened (pass with updates)
void testReport() {
  char *result = report(safeSensorStub);
  EXPECT_STREQ(result, "Sunny Day");
  free(result);

  result = report(unsafeSensorStub);
  EXPECT_STREQ(result, "Hot Day");
  free(result);

  result = report(randomSensorStub);
  EXPECT_STREQ(result, "Alert, Stormy with heavy rain");
  free(result);

  result = report(humidHotStub);
  EXPECT_STREQ(result, "Humid Hot Day");
  free(result);

  result = report(dryHotStub);
  EXPECT_STREQ(result, "Dry Hot Day");
  free(result);

  result = report(humidColdStub);
  EXPECT_STREQ(result, "Humid Cold Day");
  free(result);

  result = report(coldStub);
  EXPECT_STREQ(result, "Cold Day");
  free(result);

  result = report(humidDayStub);
  EXPECT_STREQ(result, "Humid Day");
  free(result);

  result = report(dryDayStub);
  EXPECT_STREQ(result, "Dry Day");
  free(result);

  result = report(rainyDayStub);
  EXPECT_STREQ(result, "Rainy Day");
  free(result);

  result = report(windyDayStub);
  EXPECT_STREQ(result, "Windy Day");
  free(result);

  result = report(invalidStub);
  EXPECT_STREQ(result, "Invalid Readings");
  free(result);
}

// Test boundary conditions: Strengthened, e.g., edges for humidity/temp
void testBoundaryConditions() {
  struct SensorReadings boundaryHumid = {
      .temperatureInC = 26,
      .precipitation = 60,
      .humidity = 81, // Just above high
      .windSpeedKMPH = 40,
  };
  EXPECT_STREQ(
      getWeatherString(boundaryHumid),
      "Humid Hot Day"); // Assuming precip=60 defaults to hot with humidity

  struct SensorReadings boundaryDry = {
      .temperatureInC = 26,
      .precipitation = 0,
      .humidity = 29, // Just below low
      .windSpeedKMPH = 10,
  };
  EXPECT_STREQ(getWeatherString(boundaryDry), "Dry Hot Day");
}

int testWeatherReport() {
  std::cout << "\nWeather report test\n";
  testSafeSensorStub();
  testUnsafeSensorStub();
  testReport();
  testBoundaryConditions();
  std::cout << "All is well (maybe!)\n";
  return 0;
}
