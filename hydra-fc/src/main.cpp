#include <Arduino.h>

void setup() {
  // Initialise built in LED as output
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  // Blink built in LED3
  digitalWrite(LED_BUILTIN, HIGH);  // turn the LED on (HIGH is the voltage level)
  delay(100);                      // wait for a 1000 millisecond
  digitalWrite(LED_BUILTIN, LOW);   // turn the LED off by making the voltage LOW
  delay(100);                      // wait for a 1000 millisecond
}

