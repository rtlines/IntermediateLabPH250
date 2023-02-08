/////////////////////////////////////////////////////////
// Extended Voltmeter
// This voltmeter with the values given below
// is designed to measure a 0 to 20V range with 1024 
// discrete values of with an uncertainty of about 0.02V
/////////////////////////////////////////////////////////
 //set up a variable to represent Analog Input 0
int AI0 = 0;         
// Resistance of R1(put in your actual value here)
float R1 = 98000.0; 
// Resistance of R2(put in your actual value here)  
float R2 = 15000.0;  
 
int ADC_value = 0;    // Place to put the A2D values
float voltage = 0.0;  // calculated signal voltage
//mV Arduino's minimum detectable voltage
float delta_v_min = 0.0049 
 
/////////////////////////////////////////////////////////
void setup() {
  //Initiate Serial Communication
  Serial.begin(9600);    //9600 baud rate
}
 
/////////////////////////////////////////////////////////
void loop() {
  // read the serial data from AI0
  ADC_value = analogRead(AI0);
  // if you want to, print out the channel A2D values. 
  // Uncomment if you want them.
  //Serial.print("analog channel value ");
  //Serial.print(ADC_value);
  // calculate the signal voltage 
  voltage=ADC_value*(delta_v_min)*(R1+R2)/R2;
  // print out the signal voltage
  Serial.print(" voltage ");
  Serial.println(voltage, 4);  
}
/////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////