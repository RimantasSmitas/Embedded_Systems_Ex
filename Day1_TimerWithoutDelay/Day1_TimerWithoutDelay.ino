//Application that periodically executes an event while other code can still run 
//(timer without using delay(); )
//This example will use milis function you can achieve  
//the same functionality with Direct use of timers 


unsigned long last_millis_count = 0;      /* when program starts, 0 milliseconds passed already (cause it starts now) */
unsigned long timer_without_delay = 1000; /* timer in milliseconds */


void setup() {
  /* initialize serial communication at 9600 bits per second */
  Serial.begin(9600);
}


/* timerWithoutDelayCheck()
 ** Check if timer has passed + other code can still run unlike delay().
 * millis()
 ** Returns the number of milliseconds passed since
 ** the Arduino board began running the current program.
 ** This number will overflow (go back to zero), after ~50 days. */
void timerWithoutDelayCheck() {
  /* if millis() - last_millis_count > timer_without_delay;
   *  e.g. 74361 - 73360 > 1000 */
  if((millis() - last_millis_count) > timer_without_delay) {
    /* Execute function when timer passed */
    timerWithoutDelayExecute();
    
    /* update last_millis_count with current millis() */
    last_millis_count = millis();
  }
}


/* Execute code when timer passed */
void timerWithoutDelayExecute() {
  Serial.print(timer_without_delay);
  Serial.print(" milliseconds passed.\n");
}


void loop() {
  timerWithoutDelayCheck();
}
