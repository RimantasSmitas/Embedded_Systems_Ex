//Application that outputs a string and variables to (serial) monitor

//Create variables that we're going to outpot to Serial monitor
int a = 8;
char Question [] = "How you doing ?";

//Initialize serial monitor
void setup() {
  Serial.begin(9600);
}

//Print our variables and a string in beetween them :) 
void loop() {
  Serial.println(Question);
  Serial.print("I'm Gr");
  Serial.println(a);

}
