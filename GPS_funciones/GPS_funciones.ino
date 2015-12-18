/*
  6-12-12
  Aaron Weiss
  SparkFun Electronics, Beerware
  
  Example GPS Parser based off of arduiniana.org TinyGPS examples.
  
  Parses NMEA sentences from an EM406 running at 4800bps into readable 
  values for latitude, longitude, elevation, date, time, course, and 
  speed. Use 115200 baud for your serial port baud rate 
  
  For the SparkFun GPS Shield. Make sure the switch is set to DLINE.
  
  Once you get your longitude and latitude you can paste your 
  coordinates from the terminal window into Google Maps. Here is the 
  link for SparkFun's location.  
  http://maps.google.com/maps?q=40.06477,+-105.20997
  
  Uses the NewSoftSerial library for serial communication with your GPS, 
  so connect your GPS TX and RX pin to any digital pin on the Arduino, 
  just be sure to define which pins you are using on the Arduino to 
  communicate with the GPS module. 
  
  REVISIONS:
  1-17-11 
    changed values to RXPIN = 2 and TXPIN = to correspond with
    hardware v14+. Hardware v13 used RXPIN = 3 and TXPIN = 2.
  
*/ 

// In order for this sketch to work, you will need to download 
// TinyGPS and NewSoftSerial library from arduiniana.org and put them 
// into the libraries folder in your ardiuno directory.
#include <SoftwareSerial.h>
#include <TinyGPS.h>
#include <SFE_BMP180.h>
#include <Wire.h>
#include <Adafruit_BMP085.h>

// Define which pins you will use on the Arduino to communicate with your 
// GPS. In this case, the GPS module's TX pin will connect to the 
// Arduino's RXPIN which is pin 3.
#define RXPIN 2
#define TXPIN 3
//#define RXPIN 5
//#define TXPIN 4

// This is the serial rate for your terminal program. It must be this 
// fast because we need to print everything before a new sentence 
// comes in. If you slow it down, the messages might not be valid and 
// you will likely get checksum errors.
// Set this value equal to the baud rate of your terminal program
#define TERMBAUD  115200

// Set this value equal to the baud rate of your GPS
#define GPSBAUD  9600

// Create an instance of the TinyGPS object
TinyGPS gps;
// Initialize the NewSoftSerial library to the pins you defined above
SoftwareSerial uart_gps(RXPIN, TXPIN);

// This is where you declare prototypes for the functions that will be 
// using the TinyGPS library.
void getgps(TinyGPS &gps);

// In the setup function, you need to initialize two serial ports; the 
// standard hardware serial port (Serial()) to communicate with your 
// terminal program an another serial port (NewSoftSerial()) for your 
// GPS.

///LM35 CONFIGURACIÓN
int analog_pin = 0;
float temperatura;
//MP180 Configuracion
Adafruit_BMP085 bmp;
//Photoresistor CONFIGURACIÓN
int photocellPin = A1;     // the cell and 10K pulldown are connected to a0
int photocellReading;     // the analog reading from the sensor divider
int LEDpin = 11;          // connect Red LED to pin 11 (PWM pin)
int LEDbrightness;        // 




void setup()
{
 
  // Sets baud rate of your terminal program
  Serial.begin(TERMBAUD);
  // Sets baud rate of your GPS
  uart_gps.begin(GPSBAUD);
  bmp.begin();
  pinMode(12, OUTPUT);    
//  
//  Serial.println("");
//  Serial.println("Esperando respuesta de GPS");
//  Serial.println("Waiting");
//  Serial.println("");
}

// This is the main loop of the code. All it does is check for data on 
// the RX pin of the ardiuno, makes sure the data is valid NMEA sentences, 
// then jumps to the getgps() function.
void loop()
{
  while(uart_gps.available())     // While there is data on the RX pin...
  {
      int c = uart_gps.read();    // load the data into a variable...
      if(gps.encode(c))      // if there is a new valid sentence...
      {   
        digitalWrite(12, HIGH);
        getgps(gps);       // then grab the data.
        Serial.print("+");
        temp();
        Serial.print("+");
        presion();
        Serial.print("+");
        lux();
        delay(1000);
      }
  }
}

// The getgps function will get and print the values we want.
void getgps(TinyGPS &gps)
{
  // To get all of the data into varialbes that you can use in your code, 
  // all you need to do is define variables and query the object for the 
  // data. To see the complete list of functions see keywords.txt file in 
  // the TinyGPS and NewSoftSerial libs.
  
  // Define the variables that will be used
  float latitude, longitude;
  // Then call this function
  gps.f_get_position(&latitude, &longitude);
  // You can now print variables latitude and longitude
  Serial.print(latitude,5); 
  Serial.print("+"); 
  Serial.print(longitude,5);


}

void temp(){
temperatura = analogRead(analog_pin);
 temperatura = 5.0*temperatura*100.0/1024.0;
Serial.print(temperatura);

}

void presion(){
//   Serial.print("Temperature del 180 = ");
//    Serial.print(bmp.readTemperature());
//    Serial.println(" *C");
    
    //Serial.print("Pressure = ");
    Serial.print(bmp.readPressure());
  //  Serial.println(" Pa");
    
    // Calculate altitude assuming 'standard' barometric
    // pressure of 1013.25 millibar = 101325 Pascal
    //Serial.print("Altitude del 180= ");
    //Serial.print(bmp.readAltitude());
   // Serial.println(" meters");

   // Serial.print("Pressure at sealevel (calculated) = ");
   //Serial.print("+");
    //Serial.print(bmp.readSealevelPressure());
    //Serial.println(" Pa");
    //delay(1000);


}


void lux(){
  photocellReading = analogRead(photocellPin);  
 
  //Serial.print("Analog reading = ");
  Serial.println(photocellReading);     // the raw analog reading
 
  // LED gets brighter the darker it is at the sensor
  // that means we have to -invert- the reading from 0-1023 back to 1023-0
  photocellReading = 1023 - photocellReading;
  //now we have to map 0-1023 to 0-255 since thats the range analogWrite uses
  LEDbrightness = map(photocellReading, 0, 1023, 0, 255);
  analogWrite(LEDpin, LEDbrightness);
 // delay(1000);

}
