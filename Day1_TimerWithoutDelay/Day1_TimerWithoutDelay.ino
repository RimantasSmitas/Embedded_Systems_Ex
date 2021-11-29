//Application that periodically executes an event while other code can still run 
//(timer without using delay(); )
//This example will use milis function you can achieve  
//the same functionality with Direct use of timers 


unsigned long lastChange = 0;
unsigned long delayTime = 1000;
bool state = 0;

void setup() {
  pinMode(LED_BUILTIN,OUTPUT);
}

void checkTime(){
  if((millis()-lastChange)>delayTime){
    state =!state;
    lastChange = millis();
  }
}


void loop() {
  checkTime();
  digitalWrite(LED_BUILTIN,state);
}
