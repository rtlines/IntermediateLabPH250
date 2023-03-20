
// ===================================================
// DataLogger based on the 
// RobotDyn SD/RTC Arduino shield example by Nolan Chandler
//
// Todd Lines Nolan Chandler
// Last revised: 2023-02-22
//
// Saves temperature and humidity measurements from a 
//   DHT11 to a SD card with time stamp as an example 
//   of data logging
//
// Collects data at a given rate, that is set by the 
//   DHT11 sensor and saves them with a timestamp on 
//   the SD card to files called // "LOG000.TXT", 
//   "LOG001.TXT", etc. A new file is opened every N 
//   samples to collect another N samples.
// ===================================================

// ==== include statements
#include <SPI.h>
#include <SD.h>

// RTC libary by Adafruit. Must be manually installed
#include "RTClib.h" 

//#include <Wire.h>
//#include <SPI.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

#define BME_SCK 13
#define BME_MISO 12
#define BME_MOSI 11
#define BME_CS 10

#define SEALEVELPRESSURE_HPA (1013.25)

Adafruit_BME280 bme; // I2C
//Adafruit_BME280 bme(BME_CS); // hardware SPI
//Adafruit_BME280 bme(BME_CS, BME_MOSI, BME_MISO, BME_SCK); // software SPI

unsigned long delayTime;

//SD card pin to use
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
void init_RTC()
{
  Serial.print("Initializing RTC...");

  if (!rtc.begin()) {
    Serial.println(" failed!");
    while (1);
  }

  Serial.println(" done!");

  if (!rtc.isrunning())
    Serial.println(
     "WARNING: RTC has not been previously set");

}

// ======================================================
// attempts to initialize the SD card for reading/writing
// ======================================================

void init_SD()
{
  Serial.print("Initializing SD card...");

  if (!SD.begin(SD_PIN)) {
    Serial.println(" failed!");
    while (1);
  }

  Serial.println(" done!");
}

// =======================================================
// Opens the next available log file in SD:/LOGS/
// Write to the file using logfile.print() or println(), 
// just like Serial
// =======================================================

File open_next_logfile()
{
  char filename[24];

  // Create folder for logs if it doesn't already exist
  if (!SD.exists("/LOGS/"))
    SD.mkdir("/LOGS/");

  // find the first file LOGxxx.TXT that doesn't exist,
  // then create, open and use that file
  for (int logn = 0; logn < 1000; logn++) {
    sprintf(filename, "/LOGS/LOG%03d.TXT", logn);

    if (!SD.exists(filename)) {
      Serial.print("Opened \'SD:");
      Serial.print(filename);
      Serial.println("\' for logging.");
      break;
    }
  }

  return SD.open(filename, FILE_WRITE);
}

void printValues() {
    Serial.print("Temperature = ");
    Serial.print(bme.readTemperature());
    Serial.println(" °C");

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

   init_RTC();
  
   // (note 24-hour time: 3pm -> 15)	
   // This line sets the RTC with an 
   // explicit date & time, for example: 
   // to set January 21, 2014 at 3:18pm 
   // you would use the following line: 
   // rtc.adjust(DateTime(2014, 1, 21, 15, 18, 0));
  
   init_SD();

   logfile = open_next_logfile();
   
   //setup BME280 
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
      delayTime = 1000;

      Serial.println();
   }


// ====================================================
// LOOP
// ====================================================
  
void loop( )
{
  float temperature;
  float humidity;
  
  //get the time for the data sample
  DateTime now = rtc.now();
  //BME print value function
  printValues();
/*  
  //Measure temperature and humidity.  If the functions returns
  //   true, then a measurement is available. 
if (i < N) {
    if( measure_environment( &temperature, &humidity ) == true ) {
        // write same data to serial
        Serial.print(now.year());
        Serial.print('-');
        Serial.print(now.month());
        Serial.print('-');
        Serial.print(now.day());
        Serial.print(' ');
        Serial.print(now.hour());
        Serial.print(':');
        Serial.print(now.minute());
        Serial.print(':');
        Serial.print(now.second());
        Serial.print(',');
        Serial.print( "T = " );
        Serial.print(temperature);
        Serial.print( " deg. C, H = " );
        Serial.print(humidity);
        Serial.println( "%" );
        Serial.println();
        // Write the date, time and data to log file
        // Same as printing to Serial!
        logfile.print(now.year());
        logfile.print('-');
        logfile.print(now.month());
        logfile.print('-');
        logfile.print(now.day());
        logfile.print(' ');
        logfile.print(now.hour());
        logfile.print(':');
        logfile.print(now.minute());
        logfile.print(':');
        logfile.print(now.second());
        logfile.print(',');
        logfile.print( "T = " );
        logfile.print(temperature);
        logfile.print( " deg. C, H = " );
        logfile.print(humidity);
        logfile.println();
        i++;
        }

  //   delay(waittime_ms); //ms

  }
    // Reached N samples, open the next log 
    // file to record N more
  else {
    logfile.close();
    // comment out the next two lines to stop 
    // recording after the first file
    i = 0;
    logfile = open_next_logfile();
    }
*/    
  logfile.close();
  } 
