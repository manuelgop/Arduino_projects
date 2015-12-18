/*
 Cronómetro, creado por Javier Sirgo Blanco http://zygzax.com/webpcronometro/
  
 Imprime por pantalla el tiempo desde que se pulsa/activa el sensor START/STOP
 hasta que se vuelve a pulsar/activar por segunda vez. El boton RESET(No el de
 la placa arduino, sino el conectado al pin 7) resetea el cronometro a 0.
 El tiempo se imprime de la forma Minutos:Segundos:Milisegundos.
 Cuando se activa o pulsa un sensor/boton suena un pitido de confirmación.
  
 PATILLAGE LCD:
 LCD VSS     a gnd
 LCD VDD     a 5v
 LCD RS      al pin 12
 LCD ENABLE  al pin 11
 LCD D4      al pin 5
 LCD D5      al pin 4
 LCD D6      al pin 3
 LCD D7      al pin 2
  
 POTENCIOMETRO 1 10K (Contraste):
 Conectado a 5v y a gnd. Conectado a LCD V0
  
 SENSORES/PULSADORES:
 Sensor START/STOP    al pin 6 (Se activa con señal LOW)
 Pulsador RESET       al pin 7 (Se activa con señal LOW)
  
 ZUMBADOR:
 Conectado al pin 10 y a gnd
  
 RETROILUMINACION:
 POTENCIOMETRO 2 10K conectado a 5v y a gnd. Conectado a LCD BLA
 LCD BLK conectado a gnd
  
 */
  
#include <LiquidCrystal.h>                //Incluimos la libreria que contiene las funciones del display LCD
 
int m, mu=0,md=0;                          //Declaramos las variables que vamos a usar
int s, su=0,sd=0;
int l, lu=0,ld=0,lc=0;
int pulsador,antes,despues;
long int tiempo,inicio;
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);    //Configuramos las Entradas/Salidas a las que esta conectado el LCD
byte accent_o[8] = {                      //Opcional (Creamos un caracter para la o con tilde que no esta
                                          //predefinida en el display)
  B00010,                                 //Creamos un array de 8 elementos (filas del caracter) en cada uno
                                          //de los elementos
  B00100,                                 //establecemos que pixels de la fila se encienden(1) y cuales se apagan(0)
  B00000,
  B01110,
  B10001,
  B10001,
  B01110,
};
 
void setup() {
  lcd.createChar(0, accent_o);            //Guardamos el caracter accent_o creado en el lugar 0 de la memoria del LCD
  lcd.begin(16, 2);                       //Establecemos el tamaño del display (16 caracteres de largo y 2 lineas de alto)
  lcd.print("-------SDI----------");                  //Imprimimos a continuacion el resto "metro___"
  lcd.setCursor(4, 1);                    //Situamos el comienzo de la siguiente impresion de datos en el caracter 5
                                          //(comienza a contar en el 0)
  lcd.print("00:00:000");                 //y en la segunda linea empezando por arriba(comienza a contar en 0)
                                          //Imprimimos "00:00:000"
  pinMode(8, INPUT);                      //Ponemos el pin 6 como entrada para el Sensor START/STOP
  pinMode(9, INPUT);                      //Ponemos el pin 7 como entrada para el Pulsador RESET
  pinMode(10,OUTPUT);                     //Ponemos el pin 10 como salida para mandar la señal al zumbador
  antes=HIGH;                             //Ponemos la variable antes a HIGH
  despues=HIGH;                           //Ponemos la variable despues a HIGH
}
  
void loop() {
  if(digitalRead(8)==LOW){                //Si el pin 7 esta LOW
    analogWrite(10,100);                  //Mandamos una señal PWM con valor 100 al pin 10 (zumbador)
    lcd.setCursor(4, 1);                  //Nos ponemos en el LCD en la segunda linea caracter 5
    lcd.print("00:00:000");               //Escribimos 00:00:000 (Ponemos el cronometro a 0)
    delay(200);                           //Establecemos un retardo de 200ms
    analogWrite(10,0);                    //Apagamos el zumbador
  }
  despues=digitalRead(9);                 //Guardamos en la variable despues el valor del pin6 (sensor start/stop)
  if(despues==LOW&&antes==HIGH){          //Si el valor que tenia era HIGH y ahora tiene LOW sera porque lo hemos activado
    analogWrite(10,100);                  //Mandamos una señal PWM con valor 100 al pin 10 (zumbador)
    inicio=millis();                      //Guardamos en inicio el tiempo que se lleva ejecutando el programa hasta que
                                          //se activa el sensor start/stop
    antes=despues;                        //cambiamos el valor de la variable antes al que tiene la variable despues
    pulsador=0;                           //Ponemos la variable pulsador a 0
    delay(200);                           //Establecemos un retardo de 200ms
     
    while(pulsador==0){                   //Cuando la variable pulsador sea 0
      tiempo=millis()-inicio;            //Calculamos el tiempo que paso desde que se activo el sensor start/stop
       
      m=(tiempo/1000)/60;                 //Calculamos los minutos
      mu=m%10;                            //Descomponemos los minutos y sacamos el valor de las unidades
      md=(m-mu)/10;                       //Descomponemos los minutos y sacamos el valor de las decenas
       
      s=(tiempo/1000)%60;                 //Calculamos los segundos
      su=s%10;                            //Descomponemos los segundos y sacamos el valor de las unidades
      sd=(s-su)/10;                       //Descomponemos los segundos y sacamos el valor de las decenas
       
      l=(tiempo%1000);                    //Calculamos las milesimas de segundo
      lu=l%10;                            //Descomponemos las milesimas y sacamos el valor de las unidades
      ld=((l-lu)/10)%10;                  //Descomponemos las milesimas y sacamos el valor de las decenas
      lc=(l-(ld*10)-lu)/100;              //Descomponemos las milesimas y sacamos el valor de las centenas
       
      lcd.setCursor(4, 1);                //Ponemos el cursor en la linea 2 y el caracter 5
      lcd.print(md);                      //Imprimimos los valores en el display
      lcd.print(mu);             
      lcd.print(":");
      lcd.print(sd);
      lcd.print(su);
      lcd.print(":");
      lcd.print(lc);
      lcd.print(ld);
      lcd.print(lu);
 
      despues=digitalRead(9);             //Guardamos en la variable despues el valor del pin6 (sensor start/stop)
      analogWrite(10,0);                  //Apagamos el zumbador
      if(despues==LOW&&antes==HIGH){      //Si el valor que tenia era HIGH y ahora tiene LOW sera porque hemos activado
                                          //el sensor
        analogWrite(10,100);              //Mandamos una señal PWM con valor 100 al pin 10 (zumbador)
        antes=despues;                    //cambiamos el valor de la variable antes al que tiene la variable después
        pulsador=1;                       //Ponemos la variable pulsador a 1
        delay(200);                       //Establecemos un retardo de 200ms
        analogWrite(10,0);                //Apagamos el zumbador
      }
      antes=despues;                      //cambiamos el valor de la variable antes al que tiene la variable despues
    }
  }
  antes=despues;                          //cambiamos el valor de la variable antes al que tiene la variable despues
}
