//Application that uses the code from previous exercises to detect input, 
//which executes a summing function, 
//then outputs result to (serial) monitor and turns on an LED for a set amount of time.

//I chose to detect ground on pin 7 with the use of a internal pullup resistor.
//The reason to use pull ups/downs is to eliminate the environmental noise from interfering.

//defining an input pin
int InputPin = 7;
//Our two variables
int firstValue;
int secondValue;

//Variable for holding last change time
unsigned long lastChange = 0;
//Variable for defining the delay time in miliseconds
unsigned long delayTime = 1000;
//State of the Built in LED 0 is off 1 is on
bool state = 0;

//Initialize Serial monitor
//Set up pins and two values that we are going to work with 
void setup() {
  Serial.begin(9600);
  pinMode(InputPin,INPUT_PULLUP);  
  pinMode(LED_BUILTIN,OUTPUT);
  firstValue = 42;
  secondValue = 69;
}

//A function that adds two numbers together and returns a result
int AdditionFunction(int first,int second){
  int result = first + second;
  return result;
}

//A function that prints a number to serial monitor
void PrintResultsFunction(int result){
  Serial.print("The result is ");
  Serial.println(result);
}


//Check time function 
//Just like in the previous example we use this function to check wether a predifined amount of time has passed. 
//Only in this case we canot flip the state because want to turn it of after a certain period of time, not make it blink
void checkTime(){
  if((millis()-lastChange)>delayTime){
    state = 0;
    lastChange = millis();
    Serial.println("LED State is off");
  }
}

 
//If we detect an input on our input pin
  //Pass values to the addition function,print the results 
  //Change the LED state to 1, make note of current time so we know when to turn of the LED
//Else do nothing
//Check if the time has elapsed
//And act on LED state
void loop() { 
  if(digitalRead(InputPin)==0){
    int results = AdditionFunction(firstValue,secondValue);
    PrintResultsFunction(results);
    state = 1;
    lastChange = millis();
    Serial.println("I'm Grounded");
    Serial.println("LED State is on");
  }
  else {
    Serial.println("I'm Flying");
  }
  checkTime();
  digitalWrite(LED_BUILTIN,state);
}
