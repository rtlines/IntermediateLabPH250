/////////////////////////////////////////////////////////
// very simple voltmeter that also returns the time since 
// the data collection started with the voltage.
// will measure 0 to 5V only!
// Voltages outside 0 to 5V will destroy your Arduino!!!
/////////////////////////////////////////////////////////
  int AI0 = 0;
  float delta_v_min=0.0049;   // volts per A2D unit
  int value = 0;
  float voltage = 0.0;
 
/////////////////////////////////////////////////////////
   void setup() {
      // put your setup code here, to run once:
      //Initiate Serial Communication
      Serial.begin(9600);    //9600 baud rate
    }
    
/////////////////////////////////////////////////////////
   void loop() {
      // read in the voltage 
      // in A2D units form the serial port
      value = analogRead(AI0); 
      Serial.print(" time in milliseconds ");
      // the millis() function gives the time 
      // in milliseconds since the sketch started
      Serial.print(millis()); 
      // convert to voltage units using delta_v_min
      voltage = value * delta_v_min;
      Serial.print(" voltage ");
      Serial.println(voltage, 4);  
  }
/////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////