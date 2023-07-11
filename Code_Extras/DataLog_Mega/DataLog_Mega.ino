// ===================================================
// DataLogger with instructions for use on the 
// Areduino MEGA board based on the 
// RobotDyn SD/RTC Arduino shield example 
//
// Todd Lines 
// Last revised: 2023-06-29
//
// The datalogger code is quite minimal.  Because the
//   Mega has so much more memory it could be made
//   much fancier.  But this code gives the idea.
//
// Using a BME680 sensor as an example
//   Saves temperature, humidity, pressure, altitude, 
//   relative humidity and gas air quality measurements
//   from a BME680 to a SD card with time stamp as an 
//   example of data logging where the sensor library
//   and data take up a lot of the Arduino memory.
//   Symptoms of the memory being currupted are 
//   weird characthers being printed to the serial 
//   monitor or SD card, or nothing printing at all,
//   or the program hanging and not producing any
//   output.  If these things happen, try printing
//   just the time stamp. If that works, then try 
//   printing the time stamp and one piece of data.
//   Then add another piece until the problem recurs.  
//   Then, adjust what you are printing until you can
//   get your data to all be printed and saved.  This
//   may mean you need to keep better notes on what 
//   date is in which column and with what units because
//   this may not be in your saved data file.
//
// Collects data at a given rate, that is set by the
//   delay at the end of the loop with the delay time in 
//   milliseconds.  
//
// This code uses the stratgy of opening the file, 
//   writing data, and closing the file for each data 
//   point so if the sensor fails the file will fail 
//   having just been closed and only the last data 
//   point will be lost. It does not warn you if the 
//   data file won't open so be sure to check that data 
//   is actually being written to your SD card.
//
//   The code uses a RTC for it's time stamp.  
//  
//   The Ardunio Mega is wired differently than the Uno
//      To make the data logger shield work you need
//      to make two big adjustments.
//
//      1.  Bend the data logger pins (gently) so pin
//          A4 and A5 stick out and don't connect
//          then wire shield A4 to Mega pin 20 and 
//          wire sheld A5 to Mega pin 21.
//          This will allow the SCL and SDA of the shield
//          to connect where the SCL and SDA are on the Mega
//
//      2.  For the SPI bus you don't have to bend the pins but
//          Wire pin 10 to 53
//          Wire pin 11 to 51
//          Wire pin 12 to 50
//          Wire pin 13 to 52
//          And change code so const int SD_PIN = 53;
//          This will allow the SD card reader to work on the
//          Mega.
//   
// ===================================================

// ==== include statements
   #include <SD.h>

// RTC libary by Adafruit. Must be manually installed
   #include "RTClib.h" 

// BME680 libaries by Adafruit and the SPI library
//   I will use I2C so I don't think I need the SPI 
//   library
//  #include <SPI.h>
  #include <Adafruit_Sensor.h>
  #include "Adafruit_BME680.h"

// These next define statements would be for SPI bus, 
//     but I will use the i2C
//  #define BME_SCK 13
//  #define BME_MISO 12
//  #define BME_MOSI 11
//  #define BME_CS 10
  #define SEALEVELPRESSURE_HPA (1013.25)

  Adafruit_BME680 bme; // I2C
  //Adafruit_BME680 bme(BME_CS); // hardware SPI
  //Adafruit_BME680 bme(BME_CS, BME_MOSI, BME_MISO,  BME_SCK);

// SD card pin to use
   const int SD_PIN = 53;

// Real time clock type and variable
   RTC_DS1307 rtc;
   
/*
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
*/
/*
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
*/

// ====================================================
// SETUP
// ====================================================

void setup() {
   // Open serial communications for the serial monitor
      Serial.begin(9600);

   // Start the real time clock. This is from the 
   //     Adafruit RTC example code since our data
   //     loggers use Adafruit RTS's

      //init_RTC();
         // (note 24-hour time: 3pm -> 15)	
         // This line sets the RTC with an 
         // explicit date & time, for example: 
         // to set January 21, 2014 at 3:18pm 
         // you would use the following line: 
         // rtc.adjust(DateTime(2023, 4, 27, 17, 05, 0));
           Serial.print("Initializing RTC...");
      //
      if (!rtc.begin()) {
         Serial.println(" failed!");
         while (1);
         }
/*         
      Serial.println(" done!");
      if (!rtc.isrunning())
            Serial.println(
           "WARNING: RTC has not been previously set");
*/      
   // Initialize the SD card so we can write to it in
   //   the loop.  The commented out line calls a function
   //   to do this, but I want to do as little as possible
   //   so I am not using the function.
   //   init_SD();
      Serial.print("Initializing SD card...");
      //
      if (!SD.begin(SD_PIN)) {
          Serial.println(" failed!");
          while (1);
          }
      //
      //Serial.println(" done!");
    
  // Now set up your sensor here.  I will use the Adafruit 
  //    BME680 for this example  
  //
  //    setup BME680 - These next lines are from the Adafruit
  //       BME680 test code 
           //Serial.println(F("BME680 test"));
           if (!bme.begin()) {
              Serial.println("Could not start BME680 sensor, check wiring!");
              while (1);
              }
           // Set up oversampling and filter initialization
           bme.setTemperatureOversampling(BME680_OS_8X);
           bme.setHumidityOversampling(BME680_OS_2X);
           bme.setPressureOversampling(BME680_OS_4X);
           bme.setIIRFilterSize(BME680_FILTER_SIZE_3);
           bme.setGasHeater(320, 150); // 320*C for 150 ms
           Serial.println("BME680 Started");

    // Tell the User that we started a new collection
    //  Be careful here. Printing things in the setup can be
    //  tricky. Don't print something that is very long
    File dataFile = SD.open("datalog.txt", FILE_WRITE);
       dataFile.println("START OF NEW COLLECT");
       Serial.println("START OF NEW COLLECT");
       dataFile.close();
 
  }  // End of setup


// ====================================================
// LOOP
// ====================================================
  
void loop( ) {
  // make a place to put our time stamp and data
  String dataString="";
  //
  // get the time stamp information from the RTC
  DateTime now = rtc.now();
  //
  // make an output string that has the time and date
  //    We need to be careful while doing this.
  //    Arduino Unos have only a tiny bit of memory
  //    It is really easy to use it all up and when
  //    we do, the microcontroller can become 
  //    unstable. We have three devices connected
  //    to our Arduino, the SD card reader, the RTC
  //    and the sensor, in this case an Adafruit
  //    BME280. That is a lot!  So we will output 
  //    the data with as few extra characters as 
  //    possible. This includes spaces! We will 
  //    separate using commas, because python
  //    makes it easy to use csv files.  I left 
  //    in units, but you could put them in the 
  //    headder and reduce the dataString further.
  dataString = dataString + String(now.year());
  dataString = dataString + '-' ;
  dataString = dataString + String(now.month());
  dataString = dataString + '-';
  dataString = dataString  + String(now.day());
  dataString = dataString + ' ';
  dataString = dataString  + String(now.hour());
  dataString = dataString + ":";
  dataString = dataString  + String(now.minute());
  dataString = dataString + ":";
  dataString = dataString  + String(now.second());
  dataString = dataString + ",";
  bme.performReading();
  dataString = dataString + String(bme.temperature);
  dataString = dataString + "C,";
  dataString = dataString + String(bme.pressure / 100.0);
  dataString = dataString + "hPa,";
  dataString = dataString + String(bme.readAltitude(SEALEVELPRESSURE_HPA));
  dataString = dataString + "m,";
  dataString = dataString + String(bme.readHumidity());
  dataString = dataString + "%,";
  dataString = dataString + String(bme.gas_resistance / 1000.0);
  dataString = dataString + "KO";
  // print out the time stamp and the sensor data
  Serial.println(dataString);
  File dataFile = SD.open("datalog.txt", FILE_WRITE);
     dataFile.println(dataString);
     dataFile.close();
  //
  delay(1000); // time between data points
  //
  // Now turn the light on or off for this itteration
  //  of the loop.  Set up n for the next loop.  If
  //  n=0 this time the light turns off so set n=1 for 
  //  next time to turn it off.

  // End of Loop
  }
