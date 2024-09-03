#include <Arduino.h>
#include <unity.h>

#include <BMI160.h>

void test_imu() {
  TEST_ASSERT_TRUE(BMI160.begin(BMI160GenClass::I2C_MODE, 0x69));     // Connect to imu
}

void setup() {
  UNITY_BEGIN();
  RUN_TEST(test_imu);
  UNITY_END();
}

void loop() {}