/////////////////////////////////////////////////////////
// very simple voltmeter
// will measure 0 to 5V only!
// Voltages outside 0 to 5V will destroy your Arduino!!!
// Don't wire this backwards!
/////////////////////////////////////////////////////////
// define a variable that tells which analog pin we will 
//   use
int AI0 = 1;    //AI0 stands for analog input zero
// define a variable that holds our Delta_v_min
float delta_v_min=0.0049;   // volts per A2D unit
// define a variable for our A2D version of our signal
int ADC_value = 0;
// define a variable for our voltage version of our signal
float voltage = 0.0;
 
/////////////////////////////////////////////////////////
void setup() {
  // put your setup code here, to run once when your
  // Arduino starts up:
  //
  // Initiate Serial Communication, so we can see the
  // voltage on our computer
  Serial.begin(1200);    //9600 baud rate
}
 
/////////////////////////////////////////////////////////
void loop() {
  // Read in the voltage in A2D units form the serial port
  //   remember that AI0 is the pin number to read from
  ADC_value = analogRead(AI0); 
  // Let's print out our A2D version of our signal
  Serial.print(" A2D ");
  Serial.print(ADC_value); 
  // Now convert to voltage units using delta_v_min
  voltage = ADC_value * delta_v_min;
  // And print out our voltage version of our signal
  Serial.print(" voltage ");
  // Print the voltage with 4 significant figures)
  Serial.println(voltage, 4);  
}
/////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////