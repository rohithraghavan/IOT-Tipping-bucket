#include <LiquidCrystal.h>
const int rs = 8, en = 13, d4 =12, d5 = 11, d6 = 10, d7 = 9; // lcd pins by default
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
float BktCounter = 0.00; // Tipping counter
unsigned long int lastDebounceTime = 0;  // the last time the counter was incremented
long int mintimegap = 10;    // the  min time gap between two values
unsigned long int time = 0; //var for storing millis()
const byte interruptPin = 2; // interrupt pin in uno is 2 and 3
float RainCnt = 0.00; 

void setup()
{
  Serial.begin(9600);
  lcd.begin(16,2); //width and height of the lcd screen
  pinMode(interruptPin,INPUT); //output of interruptPin
 attachInterrupt(digitalPinToInterrupt(interruptPin),raincnt,FALLING); //interrupt pin on changing from 1 to 0 will trigger the func
}

void loop()
{
  delay(100); //delay of 100ms for updating tips
  lcd.clear(); //clears  the lcd display
  lcd.print("Tip count :");
  lcd.print(BktCounter);
  lcd.setCursor(0,2);
  RainCnt = BktCounter * 0.0088;
  lcd.print("Rain mm:");
  lcd.print(RainCnt);
  }

void raincnt()
{
  time = millis(); //records time when control enters function
  if ( (time - lastDebounceTime) > mintimegap) {  // interrupt entering time and last debounce time diff should be greater than 100
       BktCounter++;
       lastDebounceTime = millis(); //set current time as last debounce time
       }
}
