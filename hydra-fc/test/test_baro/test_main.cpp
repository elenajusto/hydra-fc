#include <Arduino.h>
#include <unity.h>

#include <Wire.h>
#include <SPI.h>
#include <Adafruit_BMP280.h>    

void setUp(void)
{
  // set stuff up here
}

void tearDown(void)
{
  // clean stuff up here
}


void test_barometer() {
  Adafruit_BMP280 barometer = Adafruit_BMP280(&Wire);           // Initialise barometer library object
  TEST_ASSERT_TRUE(barometer.begin(0x76));                      // Connect to barometer
}

void setup() {
  UNITY_BEGIN();
  RUN_TEST(test_barometer);
  UNITY_END();
}

void loop() {}