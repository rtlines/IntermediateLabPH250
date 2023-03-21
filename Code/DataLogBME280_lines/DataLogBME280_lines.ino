
// ===================================================
// DataLogger based on the 
// RobotDyn SD/RTC Arduino shield example by Nolan Chandler
//
// Todd Lines Nolan Chandler
// Last revised: 2023-03-20
//
// Saves temperature and humidity measurements from a 
//   BME280 to a SD card with time stamp as an example 
//   of data logging
//
// Collects data at a given rate, that is set by the
//   variable watetime_ms. This code uses the stratgy
//   of opening the file, writing data, and closing 
//   the file for each data point so if the sensor fails
//   the file will fail closed and only the last data
//   point will be lost.
//   The code uses a RTC for it's time stamp.    
//   
// ===================================================

// ==== include statements
   #include <SD.h>

// RTC libary by Adafruit. Must be manually installed
   #include "RTClib.h" 

// BME280 libaries by Adafruit.
   #include <SPI.h>
   #include <Adafruit_Sensor.h>
   #include <Adafruit_BME280.h>
   // global variables for BME280
   #define BME_SCK 13
   #define BME_MISO 12
   #define BME_MOSI 11
   #define BME_CS 10
   #define SEALEVELPRESSURE_HPA (1013.25)
   // delcair a varibale for the bme data, we are using I2C
   Adafruit_BME280 bme; // I2C
   //Adafruit_BME280 bme(BME_CS); // hardware SPI
   //Adafruit_BME280 bme(BME_CS, BME_MOSI, BME_MISO, BME_SCK); // software SPI

// SD card pin to use
   const int SD_PIN = 9;
   File logfile;

// Real time clock type and variable
   RTC_DS1307 rtc;

// data collection variables to set up how often data are recorded
   int i = 0;
   int N = 50; // Number of samples per file
   int waittime_ms = 30000; // milliseconds between samples


// =========================================
// initializes the RTC, 
// and checks to see if it has been set
// =========================================
void init_RTC() {
  Serial.print("Initializing RTC...");
  //
  if (!rtc.begin()) {
    Serial.println(" failed!");
    while (1);
  }
  //
  Serial.println(" done!");
  //
  if (!rtc.isrunning())
    Serial.println(
    "WARNING: RTC has not been previously set");
  }


// ======================================================
// attempts to initialize the SD card for reading/writing
// ======================================================

void init_SD() {
  Serial.print("Initializing SD card...");
  //
  if (!SD.begin(SD_PIN)) {
    Serial.println(" failed!");
    while (1);
  }
  //
  Serial.println(" done!");
  }


// ======================================================
// prints out BME280 data to the serial monitor.
//   From the Adafruit BME280 test code.
//   Not used, but kept for testing.
// ======================================================
void printValues() {
  Serial.print("Temperature = ");
  Serial.print(bme.readTemperature());
  Serial.println(" C");
  Serial.print("Pressure = ");
  Serial.print(bme.readPressure() / 100.0F);
  Serial.println(" hPa");
  Serial.print("Approx. Altitude = ");
  Serial.print(bme.readAltitude(SEALEVELPRESSURE_HPA));
  Serial.println(" m");
  Serial.print("Humidity = ");
  Serial.print(bme.readHumidity());
  Serial.println(" %");
  Serial.println();
  }

// ====================================================
// SETUP
// ====================================================

void setup() {
   // Open serial communications
      Serial.begin(9600);
   // start the real time clock
      init_RTC();
     // (note 24-hour time: 3pm -> 15)	
     // This line sets the RTC with an 
     // explicit date & time, for example: 
     // to set January 21, 2014 at 3:18pm 
     // you would use the following line: 
     // rtc.adjust(DateTime(2014, 1, 21, 15, 18, 0));
   // initialize the SD card
      init_SD();
    
  // setup BME280 - These next lines are from the Adafruit BME280 test code 
       Serial.println(F("BME280 test"));
       unsigned status;
       // default settings
       status = bme.begin();  
       // You can also pass in a Wire library object like &Wire2
       // status = bme.begin(0x76, &Wire2)
       if (!status) {
          Serial.println("Could not find a valid BME280 sensor, check wiring, address, sensor ID!");
          Serial.print("SensorID was: 0x"); Serial.println(bme.sensorID(),16);
          Serial.print("        ID of 0xFF probably means a bad address, a BMP 180 or BMP 085\n");
          Serial.print("   ID of 0x56-0x58 represents a BMP 280,\n");
          Serial.print("        ID of 0x60 represents a BME 280.\n");
          Serial.print("        ID of 0x61 represents a BME 680.\n");
          while (1) delay(10);
          }    
       Serial.println("-- Default Test --");
       Serial.println("BME280 Started");
  }  // End of setup


// ====================================================
// LOOP
// ====================================================
  
void loop( ) {
   String dataString = ""; 
   //get the time for the data sample
   DateTime now = rtc.now();
   // add to this the temperature, pressure, and humidity from the BME280
     Serial.print(now.year());
     Serial.print("-");
     Serial.print(now.month());
     Serial.print("-");
     Serial.print(now.day());
     Serial.print(" , ");
     Serial.print(now.hour());
     Serial.print(":");
     Serial.print(now.minute());
     Serial.print(":");
     Serial.print(now.second());
     Serial.print(" ");
     Serial.print(", Temp, ");
     Serial.print(bme.readTemperature());
     Serial.print(" C, ");
     Serial.print("Pressure = ");
     Serial.print(bme.readPressure() / 100.0F);
     Serial.print(" hPa, ");
     Serial.print("Approx. Altitude = ");
     Serial.print(bme.readAltitude(SEALEVELPRESSURE_HPA));
     Serial.print(" m, ");
     Serial.print("Humidity = ");
     Serial.print(bme.readHumidity());
     Serial.println(" %");
    
   // open the file. note that only one file can be open at a time,
   // so you have to close this one before opening another.
      File dataFile = SD.open("datalog.txt", FILE_WRITE);
      // If the file is available, write to it, but then close it 
      //   right after. We will only keep the file open while we are 
      //   writing to it. This is safer. It helps prevent getting files 
      //   corrupted, and let's the Arduino keep adding to the file after 
      //   a problem.
      if (dataFile) {
         // print our data point, Start with the RTC time stamp
         dataFile.print(now.year());
         dataFile.print("-");
         dataFile.print(now.month());
         dataFile.print("-");
         dataFile.print(now.day());
         dataFile.print(" , ");
         dataFile.print(now.hour());
         dataFile.print(":");
         dataFile.print(now.minute());
         dataFile.print(":");
         dataFile.print(now.second());
         dataFile.print(" ");
         //
         dataFile.print(bme.readTemperature());
         dataFile.print(" C, ");
         dataFile.print("Pressure = ");
         dataFile.print(bme.readPressure() / 100.0F);
         dataFile.print(" hPa, ");
         dataFile.print("Approx. Altitude = ");
         dataFile.print(bme.readAltitude(SEALEVELPRESSURE_HPA));
         dataFile.print(" m, ");
         dataFile.print("Humidity = ");
         dataFile.print(bme.readHumidity());
         dataFile.println(" %");
         // close the file for safety
         dataFile.close();
         }
      // if the file does't open, pop up an error:
      else {
         Serial.println("error opening datalog.txt");
         }
   delay(waittime_ms); // time between data points
   // End of Loop
   }
