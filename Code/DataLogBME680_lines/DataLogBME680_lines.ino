
// ===================================================
// DataLogger based on the 
// RobotDyn SD/RTC Arduino shield example by Nolan Chandler
//
// Todd Lines Nolan Chandler
// Last revised: 2023-03-20
//
// Saves temperature and humidity measurements from a 
//   BME680 to a SD card with time stamp as an example 
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

// BME680 libaries by Adafruit.
  #include <SPI.h>
  #include <Adafruit_Sensor.h>
  #include "Adafruit_BME680.h"

  #define BME_SCK 13
  #define BME_MISO 12
  #define BME_MOSI 11
  #define BME_CS 10

  #define SEALEVELPRESSURE_HPA (1013.25)

  Adafruit_BME680 bme; // I2C
  //Adafruit_BME680 bme(BME_CS); // hardware SPI
  //Adafruit_BME680 bme(BME_CS, BME_MOSI, BME_MISO,  BME_SCK);

// SD card pin to use
   const int SD_PIN = 9;
   File logfile;

// Real time clock type and variable
   RTC_DS1307 rtc;

// data collection variables to set up how often data are recorded
   int i = 0;
   int N = 50; // Number of samples per file
   int waittime_ms = 3000; // milliseconds between samples


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


String get_time() {
  String dataString="";
  DateTime now = rtc.now();
   // make an output string that has the time and date
  dataString = dataString +now.year()+'-'+now.month()+'-'+now.day()+', '+now.hour()+":"+now.minute()+":"+now.second();
  return(dataString);
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
    
  // setup BME680 - These next lines are from the Adafruit BME680 test code 
  Serial.println(F("BME680 test"));

  if (!bme.begin()) {
      Serial.println("Could not find a valid BME680 sensor, check wiring!");
      while (1);
      }
      // Set up oversampling and filter initialization
      bme.setTemperatureOversampling(BME680_OS_8X);
      bme.setHumidityOversampling(BME680_OS_2X);
      bme.setPressureOversampling(BME680_OS_4X);
      bme.setIIRFilterSize(BME680_FILTER_SIZE_3);
      bme.setGasHeater(320, 150); // 320*C for 150 ms
      Serial.println("BME680 Started");
  }  // End of setup


// ====================================================
// LOOP
// ====================================================
  
void loop( ) {
   String dataString = ""; 
   //get the time for the data sample
   //DateTime now = rtc.now();
   // make an output string that has the time and date
   // dataString = dataString +now.year()+'-'+now.month()+'-'+now.day()+', '+now.hour()+":"+now.minute()+":"+now.second();
   dataString = get_time();
   Serial.println(dataString);

/*
   // add to this the temperature, pressure, and humidity from the BME
     Serial.print(dataString);
     Serial.print(", Temp, ");
     Serial.print(bme.readTemperature());
     Serial.print(" °C, ");
     Serial.print("Pressure = ");
     Serial.print(bme.readPressure() / 100.0F);
     Serial.print(" hPa, ");
     Serial.print("Approx. Altitude = ");
     Serial.print(bme.readAltitude(SEALEVELPRESSURE_HPA));
     Serial.print(" m, ");
     Serial.print("Humidity = ");
     Serial.print(bme.readHumidity());
     Serial.print(" %, ");
     Serial.print("Gas = ");
     Serial.print(bme.gas_resistance / 1000.0);
     Serial.println(" KOhms");
    
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
         dataFile.print(dataString);
         dataFile.print(", Temp, ");
         dataFile.print(bme.readTemperature());
         dataFile.print(" °C, ");
         dataFile.print("Pressure = ");
         dataFile.print(bme.readPressure() / 100.0F);
         dataFile.print(" hPa, ");
         dataFile.print("Approx. Altitude = ");
         dataFile.print(bme.readAltitude(SEALEVELPRESSURE_HPA));
         dataFile.print(" m, ");
         dataFile.print("Humidity = ");
         dataFile.print(bme.readHumidity());
         dataFile.print(" %, ");
         dataFile.print("Gas = ");
         dataFile.print(bme.gas_resistance / 1000.0);
         dataFile.println(" KOhms");
         // close the file for safety
         dataFile.close();
         }
      // if the file does't open, pop up an error:
      else {
         Serial.println("error opening datalog.txt");
         }
   delay(waittime_ms); // time between data points
   */
   // End of Loop
   }
