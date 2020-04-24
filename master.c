#include <LiquidCrystal.h> //include Library LiquidCrystal.h
#include <Servo.h> //include Library LiquidCrystal.h
#define pirPin 10 //define pirPin 10

Servo servo1; // Define servo to servo1
int calibrationTime = 30; //Assign value 30 to variable calibrationTime
int pos = 0; // assign value 0 to variable pos
int PIRValue = 0; // assign value 0 to variable PIRValue
int i =0; // assign value 0 to variable i
int rest =1000; //assign value 1000 to variable rest
long unsigned int lowIn; //initialize variable pause
long unsigned int pause = 500; //assign value 500 to variable pause
boolean lockLow = true; // assign value true to variable lockLow
boolean takeLowTime; // initialize variable takeLowTime
LiquidCrystal lcd(12, 11, 5, 4, 3, 2); // define LiquidCrystal lcd pins
int button = 8; //assign value 8 to variable 8
void rest_d() // class rest_d
{
  lcd.setCursor(0, 1); //set cursor on lcd to position 0,1
  lcd.print("Left: "); // print string to lcd
  lcd.setCursor(7, 1); //set cursor on lcd to position 7,1
  lcd.print(rest); // print variable rest to lcd
   lcd.setCursor(11, 1); // set cursor on lcd to position 11,1
  lcd.print("/1000"); // print string to lcd
}
void setup() // Class setup
{
  servo1.attach(7); // attach servo to pin 8
  Serial.begin(9600); // open 9600 Serial port
  pinMode(pirPin, INPUT); // Set pin (pirPin) to receive signals
  pinMode(button, INPUT); // Set pin (button) to receive signals
  lcd.begin(16, 2); //intialize lcd rows and columns
  lcd.print("Initializing..."); // write string to lcd
  
  while(i<=100) // while i lower or same as 100 repeat
  {
  	lcd.setCursor(0,1); //set cursor on lcd on position 0,1
	lcd.print(i); // print variable i to lcd
    lcd.setCursor(3,1); // set  cursor on lcd on position 3,1
    lcd.print("%"); // print string on lcd
    i++; // increment i
    delay(20);    	// delay code by 20 milliseconds
  }
    delay(500); // delay code by 500 milliseconds
  	lcd.setCursor(0,0); // set cursor on lcd to position 0,0
  	lcd.print("Initialization "); // print string to lcd
  	lcd.setCursor(0,1); // set cursor on lcd to position 0,1
  	lcd.print("Complete !"); // print string to lcd
  	delay(1000); // delay code by 1000 milliseconds
  	lcd.clear(); // clear lcd
    rest_d(); // call class rest_d
    lcd.setCursor(0,0); // set cursor on lcd to position 0,0
  	lcd.print("AutoSanitizer"); // print string on lcd
}
void servo() // class servo
{
  for (pos = 0; pos <= 90; pos += 1) // for as long as pos is 0 but smaller/equal than 90 repeat
  { 
    servo1.write(pos);  // set servo to value of variable pos            
    delay(30);          // delay code by 30 milliseconds             
  }
  for (pos = 90; pos >= 0; pos -= 1) // for as long as pos is 0 but greater/equal than 90 repeat
  { 
    servo1.write(pos);  // set servo to value of variable pos
    delay(30);          // delay code by 30 milliseconds
  }
   for (pos = 0; pos <= 90; pos += 1) // for as long as pos is 0 but smaller/equal to 90 repeat
  { 
    servo1.write(pos);  // set servo to value of variable pos
    delay(15);          //delay code by 15 milliseconds             
  }
  rest--; // decrement variable rest
    
}

void PIRSensor() // class PIRSensor
{
  if(digitalRead(pirPin) == HIGH) // if pirPin is HIGH then
  {
    if(lockLow) // if lockLow is true then
    {
      PIRValue = 1; // assign value 1 to variable PIRValue
      lockLow = false; // assign value false to variable lockLow
      lcd.clear(); // clear lcd
	  lcd.setCursor(0,0); // set cursor on lcd to position 0,0
      lcd.print("Motion detected."); // print string to lcd
      rest_d(); // call class rest_d
      delay(1000); // delay code by 1000 
      lcd.clear(); // clear lcd
      servo(); // call class servo
      delay(50); // delay code by 50 milliseconds
     }
      takeLowTime = true; // assign value true to variable takeLowTime
    
   }
  if(digitalRead(pirPin) == LOW) // if pirPin is LOW then
  {
    if(takeLowTime) // if takeLowTime is true then
    {
      lowIn = millis(); // assign variable millis as a value to variable lowIn
      takeLowTime = false; // assign value false to variable takeLowTime
    }
      if(!lockLow && millis() - lowIn > pause) // if lockLow and millis minus LowIn is NOT bigger than pause then
      {
         PIRValue = 0; // assign value 0 to variable PIRValue
         lockLow = true; // assign value true to variable lockLow
         lcd.clear(); // clear lcd
         lcd.setCursor(0,0); // set cursor on lcd to position 0,0
         lcd.print("Motion ended."); // print string to lcd
         rest_d(); // call class rest_d
         delay(50); // delay code by 50 milliseconds
         lcd.setCursor(0,0); // set cursor on lcd to position 0,0
         lcd.print("AutoSanitizer"); // print string to lcd
      }
   }
}

void loop() // class loop 
{
  PIRSensor(); // call class PIRSensor
   if(digitalRead(button) == LOW) // if button is LOW then
   {
     rest = 1000; // assign value 1000 to variable rest
   }
}