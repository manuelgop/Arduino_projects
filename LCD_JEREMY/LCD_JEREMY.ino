//LCD text with incrementing number
//Include the library code:
#include <LiquidCrystal.h>
//Start the time at 0
int time = 0;
//Initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
const int Buno = 8;
const int Bdos = 9;
//Variables for debouncing
boolean lastb1 = LOW;
boolean currentb1 = LOW;
boolean lastb2 = LOW;
boolean currentb2 = LOW;


void setup()
{
  //Set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  //Print a message to the LCD.
  lcd.print("Display opciones SDI");
}
void loop()
{
  //Debounce both buttons
  currentb1 = debounce(lastb1, Buno);
  currentb2 = debounce(lastb2, Bdos);

  if (lastb1 == LOW && currentb1 == HIGH) {
    funcionb1();
  } else if (lastb2 == LOW && currentb2 == HIGH) {
    funcionb1();
  }
  
  lastb1 = currentb1;
  lastb2 = currentb2;
}

//A debouncing function that can be used by both buttons
boolean debounce(boolean last, int pin)
{
  boolean current = digitalRead(pin);
  if (last != current)
  {
    delay(5);
    current = digitalRead(pin);
  }
  return current;
}

void funcionb1(){
  lcd.clear();
   lcd.setCursor(0, 2);
    lcd.print("Boton uno");

}


void funcionb2(){
  lcd.clear();
   lcd.setCursor(0, 2);
    lcd.print("Boton dos");

}
