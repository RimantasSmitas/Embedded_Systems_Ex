/***************************************************************************
//YWROBOT
//Compatible with the Arduino IDE 1.0
//Library version:1.1


/***************************************************************************
  Example for BME280 Weather Station using two Sensors with I2C Communication
  written by Thiago Barros for BlueDot UG (haftungsbeschränkt)
  BSD License

  This sketch was written for the Bosch Sensor BME280.
  The BME280 is a MEMS device for measuring temperature, humidity and atmospheric pressure.
  For more technical information on the BME280, please go to ------> http://www.bluedot.space

 ***************************************************************************/

//Used a LiquidCrystal I2C & BlueDotBME280 Libraries as a base
//and made some small modificatios to make it work for me. 

/////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////Wirring///////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////Common wirring//////////////////////////////////////////
///////////////Breadboard used to break out the connection to all devices////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
///////SCL to SCL// Used a breadboard to breakout this pin to all the devices /////////////// 
///////SDA to SDA// Used a breadboard to breakout this pin to all the devices /////////////// 
/////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////GND to GND/////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////Displays////////////////////////////////////////////////
/////////////////////////////////////5V to VCC///////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////BME280/////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////VCC to 3.3V/////////////////////////////////////////////
///////////////////////CSB TO 3.3V to put the device in I2C mode/////////////////////////////
/////////////////////////////SDO TO 3.3V on the first sensor/////////////////////////////////
/////////////////////////////SDO TO GND on the second sensor/////////////////////////////////
//Even if you're using only one sensor you need to plug SDO to VCC or GND as it is used to
//determine the I2C address. If you don't the sensors operation will be unstable.////////////
/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////


#include <Wire.h> 

#include "BlueDot_BME280.h"
#include <LiquidCrystal_I2C.h>

BlueDot_BME280 bme1;                                     //Object for Sensor 1
BlueDot_BME280 bme2;                                     //Object for Sensor 2

int bme1Detected = 0;                                    //Checks if Sensor 1 is available
int bme2Detected = 0;                                    //Checks if Sensor 2 is available

LiquidCrystal_I2C lcd0(0x23,20,4);  // set the LCD address to 0x23 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd1(0x25,20,4);  // set the LCD address to 0x25 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd2(0x26,20,4);  // set the LCD address to 0x26 for a 16 chars and 2 line display

//Simple easy setup 
//Setup LCDs then sensors and display the static mesage.
void setup()
{
  Serial.begin(9600);
  LCDSetup();
  BmeSetup();
  StaticMessages();  
}

//This function is used to write the static messages to the display so we do not need to rewrite them every loop
void StaticMessages(){
  WriteLCD0(3,0,"First sensor"); 
  WriteLCD1(3,0,"Second sensor"); 
  WriteLCD2(3,0,"Do the results"); 
  WriteLCD2(7,1,"match?"); 
  WriteLCD2(1,2,"Based on DataSheet");
  WriteLCD2(3,3,"It can be +-1"); 
}

//Humidity sensor setup placed here, so our setup function looks simple
void BmeSetup(){
 
  Serial.println(F("Basic Weather Station"));

  //*********************************************************************
  //*************BASIC SETUP - SAFE TO IGNORE**************************** 
  
  //This program is set for the I2C mode

    bme1.parameter.communication = 0;                    //I2C communication for Sensor 1 (bme1)
    bme2.parameter.communication = 0;                    //I2C communication for Sensor 2 (bme2)

  //*********************************************************************
  //*************BASIC SETUP - SAFE TO IGNORE****************************
    
  //Set the I2C address of your breakout board  

    bme1.parameter.I2CAddress = 0x77;                    //I2C Address for Sensor 1 (bme1)
    bme2.parameter.I2CAddress = 0x76;                    //I2C Address for Sensor 2 (bme2)
      
  //*********************************************************************
  //*************ADVANCED SETUP - SAFE TO IGNORE*************************
    
  //Now choose on which mode your device will run
  //On doubt, just leave on normal mode, that's the default value

  //0b00:     In sleep mode no measurements are performed, but power consumption is at a minimum
  //0b01:     In forced mode a single measured is performed and the device returns automatically to sleep mode
  //0b11:     In normal mode the sensor measures continually (default value)
  
    bme1.parameter.sensorMode = 0b11;                    //Setup Sensor mode for Sensor 1
    bme2.parameter.sensorMode = 0b11;                    //Setup Sensor mode for Sensor 2 
                  
  //*********************************************************************
  //*************ADVANCED SETUP - SAFE TO IGNORE*************************
  
  //Great! Now set up the internal IIR Filter
  //The IIR (Infinite Impulse Response) filter suppresses high frequency fluctuations
  //In short, a high factor value means less noise, but measurements are also less responsive
  //You can play with these values and check the results!
  //In doubt just leave on default

  //0b000:      factor 0 (filter off)
  //0b001:      factor 2
  //0b010:      factor 4
  //0b011:      factor 8
  //0b100:      factor 16 (default value)

    bme1.parameter.IIRfilter = 0b100;                   //IIR Filter for Sensor 1
    bme2.parameter.IIRfilter = 0b100;                   //IIR Filter for Sensor 2

  //*********************************************************************
  //*************ADVANCED SETUP - SAFE TO IGNORE*************************

    //Next you'll define the oversampling factor for the humidity measurements
  //Again, higher values mean less noise, but slower responses
  //If you don't want to measure humidity, set the oversampling to zero

  //0b000:      factor 0 (Disable humidity measurement)
  //0b001:      factor 1
  //0b010:      factor 2
  //0b011:      factor 4
  //0b100:      factor 8
  //0b101:      factor 16 (default value)

    bme1.parameter.humidOversampling = 0b101;            //Humidity Oversampling for Sensor 1
    bme2.parameter.humidOversampling = 0b101;            //Humidity Oversampling for Sensor 2

  //*********************************************************************
  //*************ADVANCED SETUP - SAFE TO IGNORE*************************
  
  //Now define the oversampling factor for the temperature measurements
  //You know now, higher values lead to less noise but slower measurements
  
  //0b000:      factor 0 (Disable temperature measurement)
  //0b001:      factor 1
  //0b010:      factor 2
  //0b011:      factor 4
  //0b100:      factor 8
  //0b101:      factor 16 (default value)

    bme1.parameter.tempOversampling = 0b101;              //Temperature Oversampling for Sensor 1
    bme2.parameter.tempOversampling = 0b101;              //Temperature Oversampling for Sensor 2

  //*********************************************************************
  //*************ADVANCED SETUP - SAFE TO IGNORE*************************
  
  //Finally, define the oversampling factor for the pressure measurements
  //For altitude measurements a higher factor provides more stable values
  //On doubt, just leave it on default
  
  //0b000:      factor 0 (Disable pressure measurement)
  //0b001:      factor 1
  //0b010:      factor 2
  //0b011:      factor 4
  //0b100:      factor 8
  //0b101:      factor 16 (default value)  

    bme1.parameter.pressOversampling = 0b101;             //Pressure Oversampling for Sensor 1
    bme2.parameter.pressOversampling = 0b101;             //Pressure Oversampling for Sensor 2 

  //*********************************************************************
  //*************ADVANCED SETUP - SAFE TO IGNORE*************************
  
  //For precise altitude measurements please put in the current pressure corrected for the sea level
  //On doubt, just leave the standard pressure as default (1013.25 hPa);
  
    bme1.parameter.pressureSeaLevel = 1013.25;            //default value of 1013.25 hPa (Sensor 1)
    bme2.parameter.pressureSeaLevel = 1013.25;            //default value of 1013.25 hPa (Sensor 2)

  //Also put in the current average temperature outside (yes, really outside!)
  //For slightly less precise altitude measurements, just leave the standard temperature as default (15°C and 59°F);
  
    bme1.parameter.tempOutsideCelsius = 15;               //default value of 15°C
    bme2.parameter.tempOutsideCelsius = 15;               //default value of 15°C
  
    bme1.parameter.tempOutsideFahrenheit = 59;            //default value of 59°F
    bme2.parameter.tempOutsideFahrenheit = 59;            //default value of 59°F

  //*********************************************************************
  //*************ADVANCED SETUP IS OVER - LET'S CHECK THE CHIP ID!*******

  if (bme1.init() != 0x60)
  {    
    Serial.println(F("Ops! First BME280 Sensor not found!"));
    bme1Detected = 0;
  }

  else
  {
    Serial.println(F("First BME280 Sensor detected!"));
    bme1Detected = 1;
  }

  if (bme2.init() != 0x60)
  {    
    Serial.println(F("Ops! Second BME280 Sensor not found!"));
    bme2Detected = 0;
  }

  else
  {
    Serial.println(F("Second BME280 Sensor detected!"));
    bme2Detected = 1;
  }

  if ((bme1Detected == 0)&(bme2Detected == 0))
  {
    Serial.println();
    Serial.println();
    Serial.println(F("Troubleshooting Guide"));
    Serial.println(F("*************************************************************"));
    Serial.println(F("1. Let's check the basics: Are the VCC and GND pins connected correctly? If the BME280 is getting really hot, then the wires are crossed."));
    Serial.println();
    Serial.println(F("2. Did you connect the SDI pin from your BME280 to the SDA line from the Arduino?"));
    Serial.println();
    Serial.println(F("3. And did you connect the SCK pin from the BME280 to the SCL line from your Arduino?"));
    Serial.println();
    Serial.println(F("4. One of your sensors should be using the alternative I2C Address(0x76). Did you remember to connect the SDO pin to GND?"));
    Serial.println();
    Serial.println(F("5. The other sensor should be using the default I2C Address (0x77. Did you remember to leave the SDO pin unconnected?"));

    Serial.println();
    
    while(1);
  }
    
  Serial.println();
  Serial.println();

}

//All LCD setup is hiddent here so our setup function looks simple
void LCDSetup(){
  // initialize the lcds 
  lcd0.init();                      
  lcd1.init();
  lcd2.init();
 
 //Turn the back light on
 lcd0.backlight();
 lcd1.backlight();
 lcd2.backlight();
  
}

//Writting functions, writting the message and placing the cursor is sent here and forwarded to the display. 
//There is a way to make this into a a one function, but that just complicates the code. 
void WriteLCD0(int column, int row,char message[]){
  lcd0.setCursor(column,row);
  lcd0.print(message);
  }

void WriteLCD1(int column, int row,char message[]){
  lcd1.setCursor(column,row);
  lcd1.print(message);
  }

void WriteLCD2(int column, int row,char message[]){
  lcd2.setCursor(column,row);
  lcd2.print(message);
  }
///////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////

//Functions to read the temperature and humidity from the sensors
//They're quite simple and might seem unecessary, but if we were to change the sensors, we would only have change the code here
//Theres a way to combine the functions to make a unified temperature and humidity reading funcitons. But thats for the second iteration of this code.     
float ReadTemp1(){
  return bme1.readTempC();
}

float ReadTemp2(){
  return bme2.readTempC();
}

float ReadHumid1(){
  return bme1.readHumidity();
}

float ReadHumid2(){
  return bme2.readHumidity();
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void loop()
{
  //Create a buffer variable where data could be stored 
  char result[5]; 

  //dtostrf converts the float in to string(char[])
  //first variable is the one you want to convert 
  //Scond is the lenght of the variable
  //Third is precision or how many numbers after the decimal point
  //Fourth is the char array that you're copying to.
  // Its needed because I2C library required an char[] to print on display
  
  dtostrf(ReadTemp1(),5,2,result);
  WriteLCD0(7,1,result);
  WriteLCD0(12,1,"C");

  Serial.println("The first sensor is reading");
  Serial.print(result);
  Serial.println(" Degrees Celcius");
  
  
  dtostrf(ReadHumid1(),5,2,result);
  WriteLCD0(7,2,result);
  WriteLCD0(12,2,"%");

  Serial.print("And ");
  Serial.print(result);
  Serial.println("% in Relative humidity");
  Serial.println();
  dtostrf(ReadTemp2(),5,2,result);
  WriteLCD1(7,1,result);
  WriteLCD1(12,1,"C");

  Serial.println("The second sensor is reading");
  Serial.print(result);
  Serial.println(" Degrees Celcius");
  
  
  dtostrf(ReadHumid2(),5,2,result);
  WriteLCD1(7,2,result);
  WriteLCD1(12,2,"%");

  Serial.print("And ");
  Serial.print(result);
  Serial.println("% in Relative humidity");
  Serial.println();

//A reasonable delay to no go crazy :) 
  delay(500);
}
