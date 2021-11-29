//Application that uses a function to add 2 values, passed as arguments,
//and returns the result

//Create variables two variables
int firstValue;
int secondValue;

//Initialise serial comunications
//Give some values to the variables to hold
void setup() {
  Serial.begin(9600);
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

//Pass the variables to the addtion function
//Then pass the result to printing function
void loop() {
  int results = AdditionFunction(firstValue,secondValue);
  PrintResultsFunction(results);
}
