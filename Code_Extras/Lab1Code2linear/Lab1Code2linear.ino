

int LedPin1 = 4;
int LedPin2 = 5;
int LedPin3 = 6;
int LedPin4 = 7;
int n = 0;
float x = 0.0;

void setup() {
  // put your setup code here, to run once:
  pinMode(LedPin1,OUTPUT);
  pinMode(LedPin2,OUTPUT);
  pinMode(LedPin3,OUTPUT);
  pinMode(LedPin4,OUTPUT);
  Serial.begin(9600);
  }

void loop() {
  // put your main code here, to run repeatedly:
  //x = random(0,4);
  //n=int(x);
  if (n == 0) {
    digitalWrite(LedPin1, HIGH);
    digitalWrite(LedPin2, LOW);
    digitalWrite(LedPin3, LOW);
    digitalWrite(LedPin4, LOW);
    }
  if (n == 1) {
    digitalWrite(LedPin1, LOW);
    digitalWrite(LedPin2, HIGH);
    digitalWrite(LedPin3, LOW);
    digitalWrite(LedPin4, LOW);
    }
  if (n == 2) {
    digitalWrite(LedPin1, LOW);
    digitalWrite(LedPin2, LOW);
    digitalWrite(LedPin3, HIGH);
    digitalWrite(LedPin4, LOW);
    }
  if (n == 3) {
    digitalWrite(LedPin1, LOW);
    digitalWrite(LedPin2, LOW);
    digitalWrite(LedPin3, LOW);
    digitalWrite(LedPin4, HIGH);
    }
  n++;
  if (n>3){ n=0;}  
  delay(200);
  /* 
  Serial.print(x);
  Serial.print("\t");
  Serial.print(n);
  Serial.println();
  */
}
