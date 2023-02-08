 /////////////////////////////////////////////////////////
// very simple voltmeter and equally simple ammeter
// will measure 0 to 5V only!
// Voltages outside 0 to 5V will destroy your Arduino!!!
// Delta_V_shunt must therefore be much much less than 5V
// The shunt resistor should be much less than the
// resistance of the rest of the circuit.
/////////////////////////////////////////////////////////
// Shunt resistor value goes here:
  float R_shunt= 220;   
  	//ohms  -  remember you have to replace this with your 
  	// actual shunt resistor value
 
// make some integer variables that identify 
//the analog input pins we will use:
   int AI0 = 0;
   int AI1 = 1;
   int AI2 = 2;
 
// you also need a place to put the analog to 
//digital converter values from the Arduino
   int ADC0 = 0;
   int ADC1 = 0;
   int ADC2 = 0;
 
// Remember we will have to convert from Analog to 
// digital converter(ADC) units to volts. We need
// our delta_V_min just like we did in lab 3 
   float delta_v_min=0.0049;   // volts per A2D unit
  
// We need a place to put the 
// calculated voltage and current.
float voltage = 0.0;
float amperage = 0.0;
 
/////////////////////////////////////////////////////////
 void setup() {
  // put your setup code here, to run once:
  //Initiate Serial Communication
  Serial.begin(9600);    //9600 baud rate
}
/////////////////////////////////////////////////////////
 void loop() {
  // Read in the voltages in A2D units form the 
  // Arduino Analog pins
  ADC0 = analogRead(AI0); 
  ADC1 = analogRead(AI1);
  ADC2 = analogRead(AI2);
  
  // Convert the voltage across the 
  // test resistor to voltage 
  //   units using delta_v_min
  voltage = (ADC2-ADC1) * delta_v_min;
 
  // Convert the voltage across R_shunt to voltage units  
  // using delt_v_min, then convert to
  // current using R_shunt
  amperage = (ADC1-ADC0)* delta_v_min / R_shunt;
 
  // output the voltage, amperage, and resistance
  Serial.print(" voltage ");
  Serial.print(voltage, 6);  
  Serial.print(" amperage ");
  Serial.print(amperage,6);
  Serial.print( " resistance " );
  Serial.println(voltage/amperage, 4);
}