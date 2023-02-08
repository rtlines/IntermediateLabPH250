/////////////////////////////////////////////////////////
//Arduino Sketch to blink two LED light
//   Written by Brother Lines
//   Feb 6, 2017
//
//   Define our Arduino Variables
//      We will call pin 13 "ledPin1"
//      We will call pin 12 "ledPin2"
/////////////////////////////////////////////////////////
int ledPin1=13;
int ledPin2=12;
 
/////////////////////////////////////////////////////////
void setup() {
 // put your setup code here, to run once:
 // set both pins to OUTPUT
 pinMode(ledPin1, OUTPUT);
 pinMode(ledPin2, OUTPUT);
 }
 
/////////////////////////////////////////////////////////
void loop() {
 // put your main code here, to run repeatedly:
 // turn on one LED and turn off the other
 digitalWrite(ledPin1,HIGH);
 digitalWrite(ledPin2,LOW);
 // wait
 delay(100);
 // now switch so the first LED is off
 // and the second is on
 digitalWrite(ledPin1,LOW);
 digitalWrite(ledPin2,HIGH);
 // wait
 delay(100);
 }
/////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////