//simple button GET server code to control servo and arduino pin 5
//for use with IDE 1.0
//open serial monitor to see what the arduino receives
//use the \ slash to escape the " in the html
//for use with W5100 based ethernet shields
//Powering a servo from the arduino usually DOES NOT WORK.
//note that the below bug fix may be required
// http://code.google.com/p/arduino/issues/detail?id=605
 
#include <SPI.h>
#include <Ethernet.h>
 
#include <Servo.h>
Servo myservo;  // create servo object to control a servo
 
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED }; //physical mac address
byte ip[] = { 192, 168, 1, 120 }; // ip in lan
byte gateway[] = { 192, 168, 1, 1 }; // internet access via router
byte subnet[] = { 255, 255, 255, 0 }; //subnet mask
EthernetServer server(80); //server port
 
String readString;
 
//////////////////////
 
void setup(){
  int colores = 51;
  int blancas = 53;
 
  pinMode(colores, OUTPUT); //pin selected to control
  pinMode(blancas, OUTPUT); //pin selected to control
  //start Ethernet
  Ethernet.begin(mac, ip, gateway, subnet);
  server.begin();
  //the pin for the servo co
  //enable serial data print
  Serial.begin(9600);
  Serial.println("server LED test 1.0"); // so I can keep track of what is loaded
}
 
void loop(){
  // Create a client connection
  EthernetClient client = server.available();
  if (client) {
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
 
        //read char by char HTTP request
        if (readString.length() < 100) {
 
          //store characters to string
          readString += c;
          //Serial.print(c);
        }
 
        //if HTTP request has ended
        if (c == '\n') {
 
          ///////////////
          Serial.println(readString); //print to serial monitor for debuging
 
          client.println("HTTP/1.1 200 OK"); //send new page
          client.println("Content-Type: text/html");
          client.println();
 
          client.println("<HTML>");
          client.println("<HEAD>");
          //client.println("<meta name='apple-mobile-web-app-capable' content='yes' />");
          //client.println("<meta name='apple-mobile-web-app-status-bar-style' content='black-translucent' />");
          //client.println("<link rel='stylesheet' type='text/css' href='http://homeautocss.net84.net/a.css' />");
          client.println("<TITLE>Luces del arbolito</TITLE>");
          client.println("</HEAD>");
          client.println("<BODY>");
          client.println("<H1>ARBOLITO</H1>");
          client.println("<hr />");
          client.println("<br />");
         
          client.println("<a href=\"/?blancas\"\">Prender luces blancas</a>");
          client.println("<br />");
          client.println("<a href=\"/?colores\"\">Prender luces de colores</a><br />"); 
          client.println("<br />");
          client.println("<a href=\"/?todas\"\">Prender todas las luces</a><br />");
          client.println("<br />");
          client.println("<a href=\"/?offtodas\"\">Apagar todas las luces</a><br />");          
 
          client.println("</BODY>");
          client.println("</HTML>");
 
          delay(1);
          //stopping client
          client.stop();
          client.flush();
 
          ///////////////////// control arduino pin
          if(readString.indexOf("?blancas") >0)//revisa para blancas
          {
            digitalWrite(51, HIGH);    // Prende las luces blancas
            digitalWrite(53, LOW);
            Serial.println("Luces blancas PRENDIDAS");
          }
          else if(readString.indexOf("?colores") >0)
          {
            digitalWrite(51, LOW);    // PRENDE LUCES COLORES
            digitalWrite(53, HIGH);
            Serial.println("Luces COLORES PRENDIDAS");
            
          }else if(readString.indexOf("?todas") >0)
          {
            digitalWrite(51, HIGH);    // PRENDE LUCES COLORES
            digitalWrite(53, HIGH);
            Serial.println("Luces TODAS PRENDIDAS");
            
          }else if(readString.indexOf("?offtodas") >0)
          {
            digitalWrite(51, LOW);    // Apaga todas las luces.
            digitalWrite(53, LOW);
            Serial.println("Luces TODAS APAGADAS");
          }
          else
          {
          digitalWrite(51, LOW);    // Apaga todas las luces.
          digitalWrite(53, LOW);
          Serial.println("Luces TODAS APAGADAS");
          }
          
          //clearing string for next read
          readString="";
 
        }
      }
    }
  }
}
