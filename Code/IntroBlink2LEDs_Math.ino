/////////////////////////////////////////////////////////
// code to blink two LED's using a mathematical expression
// to determine when they should light. Note that the
// Arduino code is closer to C++ than python.
/////////////////////////////////////////////////////////
int ledPin1=13;
int ledPin2=12;
int i=0; //loop counter
 
/////////////////////////////////////////////////////////
int fib_count=0; // number of blinks based on Fibonacci
int i_max=10; // maximum Fibonacci number before 
 // starting over
 
/////////////////////////////////////////////////////////
void setup() {
 // put your setup code here, to run once:
 pinMode(ledPin1, OUTPUT);
 pinMode(ledPin2, OUTPUT);
 } 
 
int fib(int x) {
 // calculates the Fibonacci sequence using recursion
 if (x==0) 
    return 0;
 if (x==1)
   return 1;
   return fib(x-1) + fib(x-2);
 } 
 
/////////////////////////////////////////////////////////
void loop() {
 // put your main code here, to run repeatedly:
 // blink the LED's with the number of blinks being 
 // the Fibonacci sequence.
 fib_count=fib(i);
 if (i % 2 == 0 ) {
   // turn off one light
   digitalWrite(ledPin2,LOW);
   // now blink the second light fib_count times 
   for (int n=0; n<fib_count; n++) { 
      digitalWrite(ledPin1,HIGH);
      delay(100);
      digitalWrite(ledPin1,LOW);
      delay(100);
   }
 }
 else {
   // turn off the other light
   digitalWrite(ledPin1,LOW);
   // now blink the first light fib_count times
   for (int n=0; n<fib_count ; n++) { 
      digitalWrite(ledPin2,HIGH);
      delay(100);
      digitalWrite(ledPin2,LOW);
      delay(100);
   }
 }
 // increment i
 i++;
 // limit our blinks to the first i_max Fibonacci numbers
 if (i>i_max) i=0;
 }
}
/////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////