/*Example 37.2 – Super-basic stopwatch using millis();
  http://tronixstuff.com/tutorials > chapter 37
  John Boxall | CC by-sa-nc
*/
 
 #include <LiquidCrystal.h>
 

LiquidCrystal lcd(12, 11, 5, 4, 3, 2); 
unsigned long start, finished, elapsed;

void setup()
{
  lcd.begin(20, 4);
  pinMode(6, INPUT_PULLUP); // start button
  pinMode(7, INPUT_PULLUP); // stop button
  lcd.setCursor(0, 0);
  
  lcd.print("SDI");
}
 
void displayResult()
{
  
  float h,m,s,ms;
  unsigned long over;
  elapsed=finished-start;
  h=int(elapsed/3600000);
  over=elapsed%3600000;
  m=int(over/60000);
  over=over%60000;
  s=int(over/1000);
  ms=over%1000;
  lcd.setCursor(0, 1);
  lcd.clear();
  lcd.print("Elapsed time: ");
  lcd.print(elapsed);
//  lcd.print("Elapsed time: ");
//  lcd.print(h,0);
//  lcd.print("h ");
//  lcd.print(m,0);
//  lcd.print("m ");
//  lcd.print(s,0);
//  lcd.print("s ");
//  lcd.print(ms,0);
//  lcd.print("ms");

}
 
void loop()
{
  if (digitalRead(6)==LOW)
  {
    start=millis();
    delay(200); // for debounce
    lcd.setCursor(0, 1);
    lcd.print("Started...");
  }
  if (digitalRead(7)==LOW)
  {
    finished=millis();
    delay(200); // for debounce
    displayResult();
  }
}
