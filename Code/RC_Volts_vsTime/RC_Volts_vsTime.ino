/////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////
// Voltmeter with a time stamp
// will measure 0 to 5V only!
// Voltages outside 0 to 5V will destroy your Arduino!!!
/////////////////////////////////////////////////////////
// we want to have voltage vs time,
// so make a place to store a time value
unsigned long time;

// make some integer variables that identify the 
// analog input pins we will use:
int AI0 = 0;
int AI1 = 1;

// you also need a place to put the analog to 
// digital converter values 
// from the Arduino
int ADC0 = 0;
int ADC1 = 0;

// Remember we will have to convert from Analog to 
// digital converter(ADC) units to volts.
// We need our delta_V_min just like we did in lab 3 
float delta_v_min=0.0049;   // volts per A2D unit

// We need a place to put the calculated voltage
float voltage = 0.0;
 
/////////////////////////////////////////////////////////
 void setup() {
    // put your setup code here, to run once:
    //Initiate Serial Communication
    Serial.begin(9600);    //9600 baud rate
    }
 
/////////////////////////////////////////////////////////
 void loop() {
    // Read in the voltages in A2D units form the
    // serial port
    ADC0 = analogRead(AI0); 
    ADC1 = analogRead(AI1);
  
    // Convert the voltage across the 
    // test resistor to voltage 
    //   units using delta_v_min
    voltage = (ADC1-ADC0) * delta_v_min;
 
    // output the time since we started and the voltage
    Serial.print(" time in sec, ");
    // this next line uses millis() which gives time in
    // ms since we started
    time = millis();
    // convert to seconds and print.
    Serial.print(time/1000.0, 6);  
    Serial.print(", voltage across C, ");
    Serial.println(voltage,6);
    }
/////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////
