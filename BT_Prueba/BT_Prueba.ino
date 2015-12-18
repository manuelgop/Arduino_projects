//Recibir datos con modulo Bluetooth para Arduino http://zygzax.com/
#include <SoftwareSerial.h>
char rec;
SoftwareSerial blue(2,3);
void setup(){
  pinMode(13,OUTPUT);
  blue.begin(9600);
  blue.println("Conectado");
}
void loop() {
  if(blue.available()){
    rec=blue.read();
    switch(rec){
      case '0':
        digitalWrite(10,LOW);
        delay(500);
        blue.println("Led off");
        break;
      case '1':
        digitalWrite(10,HIGH);
        delay(500);
        blue.println("Led on");
        break;
      default:
        delay(500);
        blue.print(rec);
        blue.println(" no es una orden valida. Introduzca 0 o 1");
    }
  }
}
