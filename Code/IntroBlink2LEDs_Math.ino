/////////////////////////////////////////////////////////
// code to blink two LED's using a mathematical expression
// to determine when they should light. Note that the
// Arduino code is closer to C++ than python.
/////////////////////////////////////////////////////////
int ledPin1=13;
int ledPin2=12;
int i=0; //loop counter
 
/////////////////////////////////////////////////////////
void setup() {
 // put your setup code here, to run once:
 pinMode(ledPin1, OUTPUT);
 pinMode(ledPin2, OUTPUT);
 } 
 
/////////////////////////////////////////////////////////
void loop() {
 // put your main code here, to run repeatedly:
 // blink the LED's with the number of blinks being 
 // the Fibonacci sequence.
 if (i % 2 == 0 ) {
    digitalWrite(ledPin1,HIGH);
    digitalWrite(ledPin2,LOW);
    delay(1000);
    }
  else {
    digitalWrite(ledPin1,LOW);
    digitalWrite(ledPin2,HIGH);
    delay(1000);
    }
    i++;   // increment the loop counter by adding 1 to i
 }

/////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////