
//Configure onboard LED to light up when the LDR is mainly/fully covered.
//Set threshold limit and show ADC values (at a reasonable rate) on serial monitor and when threshold limit is crossed 

// The LDR that I picked out of the pile was 12k and a resistor is 2.3k 
//Depending how you on your resistors and wiring the code will have to be diffrent
//This is how I wirred it  
//         5V----LDR---R---GND
//                   | 
//                   |
//                   A0
void setup() {
  pinMode(A0,INPUT);
  pinMode(LED_BUILTIN,OUTPUT);
  Serial.begin(9600);
}

//Read the value print a message and light up an LED if needed  
void ReadTheRoom(){
  int Reading = analogRead(A0); 
 if (Reading>100){
  Serial.println("I'm walking on sunshine");}
  else{
  Serial.println("Hello darkness my old friend");
  }
  if(Reading<50) {
  Serial.print("It's too dark ");
  Serial.print(Reading);
  Serial.println(" We need a light");
  digitalWrite(LED_BUILTIN,HIGH);
  }
  else {
   digitalWrite(LED_BUILTIN,LOW);
  }
}

void loop() {
  delay(500);
  ReadTheRoom();
  
  
}
