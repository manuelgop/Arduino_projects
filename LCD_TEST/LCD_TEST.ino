/*
  LiquidCrystal Library - Hello World

 Demonstrates the use a 16x2 LCD display.  The LiquidCrystal
 library works with all LCD displays that are compatible with the
 Hitachi HD44780 driver. There are many of them out there, and you
 can usually tell them by the 16-pin interface.

 This sketch prints "Hello World!" to the LCD
 and shows the time.

  The circuit:
 * LCD RS pin to digital pin 12
 * LCD Enable pin to digital pin 11
 * LCD D4 pin to digital pin 5
 * LCD D5 pin to digital pin 4
 * LCD D6 pin to digital pin 3
 * LCD D7 pin to digital pin 2
 * LCD R/W pin to ground
 * 10K resistor:
 * ends to +5V and ground
 * wiper to LCD VO pin (pin 3)

 Library originally added 18 Apr 2008
 by David A. Mellis
 library modified 5 Jul 2009
 by Limor Fried (http://www.ladyada.net)
 example added 9 Jul 2009
 by Tom Igoe
 modified 22 Nov 2010
 by Tom Igoe

 This example code is in the public domain.

 http://www.arduino.cc/en/Tutorial/LiquidCrystal
 */

// include the library code:
#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
int b1 = 8;
int b2 = 9;
int estadob1 = 0;
int estadob2 = 0;

void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(20, 2);
  // Print a message to the LCD.
  pinMode(b1, INPUT_PULLUP);
  pinMode(b2, INPUT_PULLUP);
 

}

void loop() {
  lcd.setCursor(0, 0);
  lcd.print("----SDI OPCIONES----");
  estadob1 = digitalRead(b1);
  delay(5);
  estadob2 = digitalRead(b2);
  delay(5);
  if (estadob1 == HIGH && estadob2 == HIGH) {
    lcd.clear();
    lcd.setCursor(0, 1);
    lcd.print("NINGUNO");
    //delay(500);
  } else if (estadob1 == LOW && estadob2 == HIGH) {
    //  lcd.clear();
    //   lcd.setCursor(0, 1);
    //  lcd.print("Boton UNO");
    estadob1=LOW;
    estadob2=HIGH;
    funcionuno();
    delay(5);

  } else if (estadob1 == HIGH && estadob2 == LOW) {
    //  lcd.clear();
    //  lcd.setCursor(0, 1);
    //  lcd.print("Boton DOS");
    funciondos();
  } else if (estadob1 == LOW && estadob2 == LOW) {
    lcd.clear();
    lcd.setCursor(0, 3);
    lcd.print("LOS DOS");
    //delay(500);
  }






}

void funcionuno() {
  lcd.clear();
  lcd.setCursor(0, 3);
  lcd.print("Boton UNO");

}


void funciondos() {
  lcd.clear();
  lcd.setCursor(0, 3);
  lcd.print("Boton DOS");

}

int leerbotones(){
  
    if (estadob1 == HIGH && estadob2 == HIGH) {
    return 1;
    //
  } else if (estadob1 == LOW && estadob2 == HIGH) {
    delay(5);
    return 2;

  } else if (estadob1 == HIGH && estadob2 == LOW) {
    return 3;
  } else if (estadob1 == LOW && estadob2 == LOW) {
    return 4;
  }
  
}
