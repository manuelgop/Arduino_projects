// include the library code:
#include <LiquidCrystal.h>
#include <OneWire.h>

 
 
OneWire  ds(3);      // Temperature sensor on pin 5
int x = 1;           //Variable to get out of while loop
// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);
float temp_c,temp_f;
int y;
int state = 0;
int right=0,left=0,up=0,down=0;
int sel=0;
unsigned long up_time_1,up_time_2,up_time;
double time_1,time_2,time;
int last_st=0,st=0;
 
 
void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  pinMode( lcdBacklightPin, INPUT );
  digitalWrite(lcdBacklightPin, LOW);
  // Print a message to the LCD.
  lcd.setCursor(0,0);
  lcd.print("Control center");
  lcd.setCursor(0,1);
  lcd.print("Choose an option");
  up_time_1 = millis();
  time_1 = millis();  
}
 
void loop() {
 
  time_2 = millis();
  last_st = state;
  read_state();
  st = state;
  if(st != last_st){
    process_state();
    process_display();
    //delay(45);
    time_1 = millis();
  }
  time = time_2 - time_1;
  time = time/1000;
  if(time >=10){
    pinMode( lcdBacklightPin, OUTPUT);
  }else{
    pinMode( lcdBacklightPin, INPUT );
  }
  delay(90);
 
 
}
 
void process_display(){
 
  switch (right) {
    case 0:
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Control center");
      lcd.setCursor(0,1);
      lcd.print("Choose an option");
      break;
    case 1:
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Get temp 1");
      lcd.setCursor(0,1);
      lcd.print("Press select");
      if(sel == 1){
        get_temp();
        sel = 0;
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Temperature");
        lcd.setCursor(0,1);
        lcd.print(temp_c);
        lcd.print("C//");
        lcd.print(temp_f);
        lcd.print("F");
        delay(3000);
      }
      break;
    case 2:
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Get up time");
      lcd.setCursor(0,1);
      lcd.print("Press select");
      if(sel == 1){
        get_up_time();
        sel = 0;
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Up time");
        lcd.setCursor(0,1);
        lcd.print(up_time);
        lcd.print(" sec");
        delay(3000);
      }
      break;
    case 3:
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("RxBuffer 10");
      lcd.setCursor(0,1);
      lcd.print("Press select");
      if(sel == 1){
        sel = 0;
        lcd.setCursor(0,0);
        lcd.print("VALUE OF 10");
      }
      break;
       
  }
 
}
 
void process_state(){
 
  switch (state) {
    case 1://right
      right = right + 1;
      break;
    case 2://up
      up = up + 1;
      break;
    case 3://down
      up = up - 1;
      break;
    case 4://left
      right = right - 1;
      break;
    case 5:
    break;
   
  }
 
}
 
void read_state(){
 
  state = 0;
  y = analogRead (0);
  //lcd.setCursor(10,1);
  if (y < 100) {
    //lcd.print ("Right ");
    state = 1;
  }
  else if (y < 200) {
    //lcd.print ("Up    ");
    state = 2;
  }
  else if (y < 400){
    //lcd.print ("Down  ");
    state = 3;
  }
  else if (y < 600){
    //lcd.print ("Left  ");
    state = 4;
  }
  else if (y < 800){
    //lcd.print ("Select");
    state = 5;
    sel = 1;
  }
 
}
 
void get_up_time(){
 
  up_time_2 = millis();
  up_time = up_time_2 - up_time_1;
  up_time = up_time/1000;        //time in seconds
 
 
     
}
void get_temp() {
 
  x = 1;
  while(x == 1){
      byte i;
      byte present = 0;
      byte type_s;
      byte data[12];
      byte addr[8];
      float celsius, fahrenheit;
     
      if ( !ds.search(addr)) {
        //Serial.println("No more addresses.");
        //Serial.println();
        ds.reset_search();
        delay(250);
        return;
      }
 
      if (OneWire::crc8(addr, 7) != addr[7]) {
          return;
      }
     
      ds.reset();
      ds.select(addr);
      ds.write(0x44,1);         // start conversion, with parasite power on at the end
     
      present = ds.reset();
      ds.select(addr);    
      ds.write(0xBE);         // Read Scratchpad
   
      for ( i = 0; i < 9; i++) {           // we need 9 bytes
        data[i] = ds.read();
      }
      // convert the data to actual temperature
      unsigned int raw = (data[1] << 8) | data[0];
      if (type_s) {
        raw = raw << 3; // 9 bit resolution default
        if (data[7] == 0x10) {
          // count remain gives full 12 bit resolution
          raw = (raw & 0xFFF0) + 12 - data[6];
        }
      } else {
        byte cfg = (data[4] & 0x60);
        if (cfg == 0x00) raw = raw << 3;  // 9 bit resolution, 93.75 ms
        else if (cfg == 0x20) raw = raw << 2; // 10 bit res, 187.5 ms
        else if (cfg == 0x40) raw = raw << 1; // 11 bit res, 375 ms
        // default is 12 bit resolution, 750 ms conversion time
      }
      celsius = (float)raw / 16.0;
      fahrenheit = celsius * 1.8 + 32.0;
      x = 0;
      temp_c = celsius;
      temp_f = fahrenheit;
     
  }
}
