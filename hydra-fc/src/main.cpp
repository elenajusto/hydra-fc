/* ------------- Libraries ------------- */
#include <Arduino.h>
#include <Wire.h>               // I2C 
#include <SPI.h>                // SPI
#include <Adafruit_BMP280.h>    // Barometer Library
#include <DFRobot_BMI160.h>     // IMU Library
#include <SD.h>                 // SD

/* ------------- Variables ------------- */
Adafruit_BMP280 bmp;
DFRobot_BMI160 bmi160;
const int8_t i2c_addr = 0x69;

const int chipSelect = 10;
File root;

/* ------------- Function Prototypes ------------- */
void i2cscan();
void printBarometer();
void printImu();
void printDirectory(File dir, int numTabs);

/* ------------- Main Program ------------- */
void setup() {

  // Start I2C
  Wire.begin();
  Serial.begin(9600);
  while (!Serial);        

  // Initialise IMU 
  Serial.println("Initialising IMU.");  
  if (bmi160.softReset() != BMI160_OK){
    Serial.println("reset false");
    while(1);
  }
  if (bmi160.I2cInit(i2c_addr) != BMI160_OK){
    Serial.println("init false");
    while(1);
  }
  Serial.println("IMU Initialised.");

  // Initialising Barometer
  Serial.println("Initialising barometer.");
  unsigned status;
  status = bmp.begin(0x76);

  if (!status) {
    Serial.println(F("Could not find a valid BMP280 sensor, check wiring or "
                      "try a different address!"));
    while (1) delay(10);
  }
  bmp.setSampling(Adafruit_BMP280::MODE_NORMAL,     /* Operating Mode. */
                  Adafruit_BMP280::SAMPLING_X2,     /* Temp. oversampling */
                  Adafruit_BMP280::SAMPLING_X16,    /* Pressure oversampling */
                  Adafruit_BMP280::FILTER_X16,      /* Filtering. */
                  Adafruit_BMP280::STANDBY_MS_500); /* Standby time. */
  Serial.println("Barometer intialised.\n");

  // Initilise SD Card
  Serial.print("Initializing SD card...");

  if (!SD.begin(chipSelect)) {
    Serial.println("initialization failed. Things to check:");
    Serial.println("1. is a card inserted?");
    Serial.println("2. is your wiring correct?");
    Serial.println("3. did you change the chipSelect pin to match your shield or module?");
    Serial.println("Note: press reset button on the board and reopen this Serial Monitor after fixing your issue!");
    while (true);
  }

  Serial.println("initialization done.");

  root = SD.open("/");

  printDirectory(root, 0);

  Serial.println("done!");

}

void loop() {
  delay(500);
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
}

void printBarometer(){
  Serial.print(F("Temperature = "));
  Serial.print(bmp.readTemperature());
  Serial.println(" *C");

  Serial.print(F("Pressure = "));
  Serial.print(bmp.readPressure());
  Serial.println(" Pa");

  Serial.print(F("Approx altitude = "));
  Serial.print(bmp.readAltitude(1024)); /* Adjusted to local forecast! */
  Serial.println(" m");

  Serial.println();
}

void printImu(){
  int i = 0;
  int rslt;
  int16_t accelGyro[6]={0}; 
  
  // Get both accel and gyro data from bmi160
  // Parameter accelGyro is the pointer to store the data
  rslt = bmi160.getAccelGyroData(accelGyro);
  if(rslt == 0){
    for(i=0;i<6;i++){
      if (i<3){
        // The first three are gyro data
        Serial.print(accelGyro[i]*3.14/180.0);Serial.print("\t");
      }else{
        // The following three data are accel data
        Serial.print(accelGyro[i]/16384.0);Serial.print("\t");
      }
    }
    Serial.println();
  } else{ 
    Serial.println("err");
  }
}

void printDirectory(File dir, int numTabs) {
  while (true) {

    File entry =  dir.openNextFile();
    if (! entry) {
      // no more files
      break;
    }
    for (uint8_t i = 0; i < numTabs; i++) {
      Serial.print('\t');
    }
    Serial.print(entry.name());
    if (entry.isDirectory()) {
      Serial.println("/");
      printDirectory(entry, numTabs + 1);
    } else {
      // files have sizes, directories do not
      Serial.print("\t\t");
      Serial.println(entry.size(), DEC);
    }
    entry.close();
  }
}
