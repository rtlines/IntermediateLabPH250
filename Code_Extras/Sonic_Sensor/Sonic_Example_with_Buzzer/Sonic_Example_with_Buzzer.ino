//www.elegoo.com
//2016.12.08
#include "pitches.h"
#include "SR04.h"
#define TRIG_PIN 12
#define ECHO_PIN 11
SR04 sr04 = SR04(ECHO_PIN,TRIG_PIN);
long a;
int ledPin = 7;

// notes in the melody:
//int melody[] = {
//  NOTE_C5, NOTE_D5, NOTE_E5, NOTE_F5, NOTE_G5, NOTE_A5, NOTE_B5, NOTE_C6};
int melody[] = {NOTE_C5};
int duration = 500;  // 500 miliseconds

void setup() {
   Serial.begin(9600);
   delay(1000);
   pinMode(ledPin, OUTPUT);
} 

void loop() {
   a=sr04.Distance();
   Serial.print(a);
     if (a<10) {
        Serial.println("cm Too Close");
        for (int thisNote = 0; thisNote < 8; thisNote++) {
             // pin8 output the voice, every scale is 0.5 sencond
             tone(8, melody[thisNote], duration);
             }
        digitalWrite(ledPin, HIGH);
        }
     else { 
        Serial.println("cm");
        digitalWrite(ledPin, LOW);
        }
   delay(1000);
}
