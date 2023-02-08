/////////////////////////////////////////////////////////
// Extended Voltmeter for plus and minus five volts
// This voltmeter with the values given below
// is designed to measure a-5V0 to +5V range with 1014 
// discrete values of with an uncertainty of about 98mV. 
// A voltage divider is use with equal resistances. 
// +5V is given to one side and our +-5V signal to the 
// other side. The output voltage is taken in between the 
// two resistors. I think we need to wire all the voltage 
// devices to the GND pin to keep common ground. 
/////////////////////////////////////////////////////////
//set up a variable to represent Analog Input 0
int AI0 = 0;          
int value = 0;        // Place to put the A2D values
float voltage = 0.0;  // calculated signal voltage
 
/////////////////////////////////////////////////////////
 void setup() {
  //Initiate Serial Communication
  Serial.begin(9600);    //9600 baud rate
}
 
/////////////////////////////////////////////////////////
 void loop() {
  // read the serial data from AI0
  value = analogRead(AI0);
  // if you want to, print out the channel A2D values. 
  // Uncomment if you want them.
  //Serial.print("analog channel value ");
  //Serial.print(value);
  // calculate the signal voltage 
  voltage=(2*value*(5.0/1024.0))-5;
  // print out the signal voltage
  Serial.print(" voltage ");
  Serial.println(voltage, 4);  
}
/////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////