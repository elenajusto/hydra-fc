/* ------------- Libraries ------------- */
#include <Arduino.h>
#include <Wire.h>


/* ------------- Function Prototypes ------------- */
void i2cscan();


/* ------------- Main Program ------------- */
void setup() {

  // Start I2C
  Wire.begin();
  Serial.begin(9600);
  while (!Serial);             
  Serial.println("\nI2C Scanner");

  // Initialise built in LED as output
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  // Blink built in LED
  digitalWrite(LED_BUILTIN, HIGH);  // turn the LED on (HIGH is the voltage level)
  delay(100);                       // wait for a 1000 millisecond
  digitalWrite(LED_BUILTIN, LOW);   // turn the LED off by making the voltage LOW
  delay(100);                       // wait for a 1000 millisecond

  // Do I2C scan
  i2cscan();
}

/* ------------- Function Definitions ------------- */
void i2cscan(){
   byte error, address;
  int nDevices;
 
  Serial.println("Scanning...");
 
  nDevices = 0;
  for(address = 1; address < 127; address++ ) {
    Wire.beginTransmission(address);
    error = Wire.endTransmission();
 
    if (error == 0)
    {
      Serial.print("I2C device found at address 0x");
      if (address<16)
        Serial.print("0");
      Serial.print(address,HEX);
      Serial.println("  !");
 
      nDevices++;
    }
    else if (error==4)
    {
      Serial.print("Unknown error at address 0x");
      if (address<16)
        Serial.print("0");
      Serial.println(address,HEX);
    }    
  }
  if (nDevices == 0)
    Serial.println("No I2C devices found\n");
  else
    Serial.println("done\n");
 
  delay(5000);                 // wait 5 seconds for next scan
}
