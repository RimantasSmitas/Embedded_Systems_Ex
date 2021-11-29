//ADC exercise
//Setup the Wemos D1 with an LM35 sensor.
//Display live temperatures on serial monitor (at a reasonable rate)


void setup() {
  pinMode(A0,INPUT);
  Serial.begin(9600);
}

//This function reads the analog value of the temperature and converts it to centigrage
//Arduino has a 10bit ADC which means 1024 bit from 0 to 5V
//By dividing 5 by 1024 we get 0.00488 or 4.88mV per step 
//LM35 output voltage changes by 10mV every degree so we devide 4,88 by 10 to get 0,488 
//Thats the multiplier we need to use to convert reading to centigrade
float ReadTemperature(){
  int reading = analogRead(A0); 

//Puting that lenghty formula in numbers.   
//When doing a single application its fine buttttt
//If you're doing a complex piece of code that does many things
//Try to avoid floats because their non native elements of the language that take a lot 
//Of time to process. The reason i did it as a formula is so that I can reuse the code later
//On other Arduinos even the ones with difrent ADCs or Voltage levels 
//Just change the 5 and 1024 to whatever is needed. 
  float multi = (((5.0/1024.0)*1000.0)/10.0);
  Serial.println(multi);
  float temperature = reading*multi;
  return(temperature);
}


void loop() {
 delay(500);
 Serial.println(ReadTemperature());
}
