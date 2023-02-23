
#include <dht_nonblocking.h>

// ===================================================
// RobotDyn SD/RTC Arduino shield example
// Nolan Chandler
// Last revised: 2020-11-18
//
// Meant to serve as a starting point for data logging
// using both a real-time clock (RTC) and a microSD 
// card.
//
// Collects data at a given rate, and saves them with 
// a timestamp on the SD card to files called 
// "LOG000.TXT", "LOG001.TXT", etc. A new file is 
// opened every N samples to collect another N samples.
// ===================================================

// include statements
#include <SPI.h>
#include <SD.h>

// by Adafruit. Must be manually installed
// Real time clock library
#include "RTClib.h" 

// DHT11 sensor library
#include <dht_nonblocking.h>

// global variables and data types
// DHT11 sensor data type
#define DHT_SENSOR_TYPE DHT_TYPE_11
static const int DHT_SENSOR_PIN = 2;
DHT_nonblocking dht_sensor( DHT_SENSOR_PIN, DHT_SENSOR_TYPE );
float temperature, humidity;

//SD card pin
const int SD_PIN = 9;
File logfile;

// Real time clock type
RTC_DS1307 rtc;

// data collection variables to set up how often data are recorded
int i = 0;
int N = 50; // Number of samples per file
int waittime_ms = 3000; // milliseconds between samples

// ====================================================
// special functions
// ====================================================

/*
 * Poll for a measurement, keeping the state machine alive.  Returns
 * true if a measurement is available.
 */
static bool measure_environment( float *temperature, float *humidity ) { 
      //static unsigned long measurement_timestamp = millis( );
      ///* Measure once every four seconds. */
      //if( millis( ) - measurement_timestamp > 3000ul ){
      //   if( dht_sensor.measure( temperature, humidity ) == true ) {
      //      measurement_timestamp = millis( );
      //   return( true );
      //   }
    
    if( dht_sensor.measure( temperature, humidity ) == true ) {
        return( true );
    }
    else return( false );
  }


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
  //delay(waittime_ms); //ms

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
  } 


