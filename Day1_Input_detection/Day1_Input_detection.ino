
//Application that detects input to a pin and sets an output.
//You can do it in a number of difrent ways.

//I chose to detect ground on pin 7 with the use of a internal pullup resistor.
//The reason to use pull ups/downs is to eliminate the environmental noise from interfering.

//defining an input pin
int InputPin = 7;


//Initialize serial and setup the input pin
void setup() {
  Serial.begin(9600);
  pinMode(InputPin,INPUT_PULLUP);  
}

//If the pin read ground print one message else print something else
void loop() {
  if(digitalRead(InputPin)==0){
    Serial.println("I'm Grounded");
  }
  else
    Serial.println("I'm Flying");
 
}
