/////////////////////////////////////////////////////////
//Arduino Sketch to blink one LED light
//   Written by Brother Lines
//	(place your name here in your code)
//   Feb 6, 2017
//
//   Define our Arduino Variables
//      We will call pin 13 "ledPin"
/////////////////////////////////////////////////////////
int ledPin=13;
 
/////////////////////////////////////////////////////////
// Arduino setup function comes next
//    Every Arduino sketch needs a setup function
//    We will set up our ledPin (pin 13) as an output pin
void setup() {
 // put your setup code here, to run once to set up:
 pinMode(ledPin, OUTPUT);
 }
 
/////////////////////////////////////////////////////////
// Arduino loop function
//    Every Arduino sketch has a loop function
//    This is where we put what we want the Arduino to do
//    The Arduino will do whatever is in the loop function 
//    until the Arduino is unplugged.
 
void loop() {
 // put your main code here, to run repeatedly:
 // turn on the LED
 digitalWrite(ledPin,HIGH);
 
 // leave in on for 100ms
 delay(100);
 
 // turn off the LED
 digitalWrite(ledPin,LOW);
 
 // leave in off for 100ms
 delay(100);
 }
/////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////