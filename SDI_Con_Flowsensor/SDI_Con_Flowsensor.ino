#include <LiquidCrystal.h>                //Incluimos la libreria que contiene las funciones del display LCD
 
int m, mu=0,md=0;                          //Declaramos las variables que vamos a usar
int s, su=0,sd=0;
int l, lu=0,ld=0,lc=0;
int pulsador,antes,despues;
long int tiempo,inicio;
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);  
int boton1inicio=6;
int boton1final=1;
int reset=0;
int boton2inicio=7;
int boton2final=0;
long int tiempo2,inicio2;
int pulsador2,antes2,despues2;
int m2, mu2=0,md2=0;                          //Declaramos las variables que vamos a usar
int s2, su2=0,sd2=0;
int l2, lu2=0,ld2=0,lc2=0;
int botonoperacion = 8;
float valor=0.0;
int iniciaCta =0;
////////////3 TIMER
long int tiempo3,inicio3;
int pulsador3,antes3,despues3;
int m3, mu3=0,md3=0;                          //Declaramos las variables que vamos a usar
int s3, su3=0,sd3=0;
int l3, lu3=0,ld3=0,lc3=0;
int boton3inicio=1;
int boton3final=0;
int bandera=0;
/////////////////////
//Nuevo para el flowsensor
/////////////////////
// which pin to use for reading the sensor? can use any pin!
#define FLOWSENSORPIN 8

// count how many pulses!
volatile uint16_t pulses = 0;
// track the state of the pulse pin
volatile uint8_t lastflowpinstate;
// you can try to keep time of how long it is between pulses
volatile uint32_t lastflowratetimer = 0;
// and use that to calculate a flow rate
volatile float flowrate;
// Interrupt is called once a millisecond, looks for any pulses from the sensor!
SIGNAL(TIMER0_COMPA_vect) {
  uint8_t x = digitalRead(FLOWSENSORPIN);
  
  if (x == lastflowpinstate) {
    lastflowratetimer++;
    return; // nothing changed!
  }
  
  if (x == HIGH) {
    //low to high transition!
    pulses++;
  }
  lastflowpinstate = x;
  flowrate = 1000.0;
  flowrate /= lastflowratetimer;  // in hertz
  lastflowratetimer = 0;
}

void useInterrupt(boolean v) {
  if (v) {
    // Timer0 is already used for millis() - we'll just interrupt somewhere
    // in the middle and call the "Compare A" function above
    OCR0A = 0xAF;
    TIMSK0 |= _BV(OCIE0A);
  } else {
    // do not call the interrupt function COMPA anymore
    TIMSK0 &= ~_BV(OCIE0A);
  }
}

//////////////////////////////////////////////
void setup() {
  // put your setup code here, to run once:
lcd.begin(20, 4);                       //Establecemos el tamaño del display (16 caracteres de largo y 2 lineas de alto)
  lcd.print("Pulos: ");                    //Imprimimos a continuacion el resto "metro___"
  lcd.setCursor(4, 1);                    //Situamos el comienzo de la siguiente impresion de datos en el caracter 5
                                          //(comienza a contar en el 0)
  lcd.print("000:000");                 //y en la segunda linea empezando por arriba(comienza a contar en 0)
  lcd.setCursor(4, 2);  //Imprimimos "00:00:000"
  lcd.print("000:000");
  pinMode(boton1inicio, INPUT_PULLUP);                      //Ponemos el pin 6 como entrada para el Sensor START/STOP
  pinMode(boton1final, INPUT_PULLUP);   //Ponemos el pin 7 como entrada para el Pulsador RESET
  pinMode(reset, INPUT_PULLUP);
  antes=HIGH;                             //Ponemos la variable antes a HIGH
  despues=HIGH;
   antes2=HIGH;                             //Ponemos la variable antes a HIGH
  despues2=HIGH; 
  antes3=HIGH;                             //Ponemos la variable antes a HIGH
  despues3=HIGH; 
  bandera=HIGH;
   pinMode(boton2inicio, INPUT_PULLUP);                      //Ponemos el pin 6 como entrada para el Sensor START/STOP
  pinMode(boton2final, INPUT_PULLUP); 
  pinMode(botonoperacion, INPUT_PULLUP);
  /////////////////////////////////
  ///---Para el CountdownTimer---/////
   pinMode(boton3inicio, INPUT_PULLUP);                      //Ponemos el pin 6 como entrada para el Sensor START/STOP
  pinMode(boton3final, INPUT_PULLUP); 
//Para el Flowsensor////
/////////////////
   pinMode(FLOWSENSORPIN, INPUT);
   digitalWrite(FLOWSENSORPIN, HIGH);
   lastflowpinstate = digitalRead(FLOWSENSORPIN);
/////////////////
}

void loop() {
  // put your main code here, to run repeatedly:
  if(digitalRead(reset)==LOW){                //Si el pin 7 esta LOW
    lcd.setCursor(4, 1);                  //Nos ponemos en el LCD en la segunda linea caracter 5
    lcd.print("000:000");               //Escribimos 00:00:000 (Ponemos el cronometro a 0)
    delay(200);      //Establecemos un retardo de 200ms
    lcd.setCursor(4, 2);                  //Nos ponemos en el LCD en la segunda linea caracter 5
    lcd.print("000:000");               //Escribimos 00:00:000 (Ponemos el cronometro a 0)
    delay(200);
    lcd.setCursor(0,3);
    lcd.print("                   ");
    s=0;
   s2=0; 
   pulsador3=1;
   
  }
  despues=digitalRead(boton1inicio);
  if(despues==LOW&&antes==HIGH){    //Si el valor que tenia era HIGH y ahora tiene LOW sera porque lo hemos activado
    inicio=millis();    //Guardamos en inicio el tiempo que se lleva ejecutando el programa hasta que
    useInterrupt(true);                                     //se activa el sensor start/stop
    antes=despues;                        //cambiamos el valor de la variable antes al que tiene la variable despues
    pulsador=0;                           //Ponemos la variable pulsador a 0
    delay(200);                           //Establecemos un retardo de 200ms
     
    while(pulsador==0){                   //Cuando la variable pulsador sea 0
      tiempo=millis()-inicio;            //Calculamos el tiempo que paso desde que se activo el sensor start/stop
       
      m=(tiempo/1000)/60;                 //Calculamos los minutos
      mu=m%10;                            //Descomponemos los minutos y sacamos el valor de las unidades
      md=(m-mu)/10;                       //Descomponemos los minutos y sacamos el valor de las decenas
       
      s=(tiempo/1000);                 //Calculamos los segundos
      su=s%10;                            //Descomponemos los segundos y sacamos el valor de las unidades
      sd=(s-su)/10;                       //Descomponemos los segundos y sacamos el valor de las decenas
       
      l=(tiempo%1000);                    //Calculamos las milesimas de segundo
      lu=l%10;                            //Descomponemos las milesimas y sacamos el valor de las unidades
      ld=((l-lu)/10)%10;                  //Descomponemos las milesimas y sacamos el valor de las decenas
      lc=(l-(ld*10)-lu)/100;              //Descomponemos las milesimas y sacamos el valor de las centenas
       
      lcd.setCursor(4, 1);                //Ponemos el cursor en la linea 2 y el caracter 5
      //lcd.print(md);                      //Imprimimos los valores en el display
      //lcd.print(mu);             
      //lcd.print(":");
      //lcd.print(sd);
      lcd.print(s);
      lcd.print(":");
      lcd.print(lc);
      lcd.print(ld);
      lcd.print(lu);
      lcd.setCursor(0, 0);
      lcd.print("Pulses:"); 
      lcd.print(pulses, DEC);
 
      //despues=digitalRead(boton1inicio);             //Guardamos en la variable despues el valor del pin6 (sensor start/stop)
      if(pulses>255){      //Si el valor que tenia era HIGH y ahora tiene LOW sera porque hemos activado
                                          //el sensor
        antes=despues;                    //cambiamos el valor de la variable antes al que tiene la variable después
        pulsador=1;         //Ponemos la variable pulsador a 1
        delay(200);        //Establecemos un retardo de 200ms
        despues3=HIGH;
        antes3=LOW;
      }
      antes=despues;                      //cambiamos el valor de la variable antes al que tiene la variable despues
    }
  }
   antes=despues; 
   ///////////////CODIGO PARA EL TERCER TIEMPO EN ARDUINO//////////
   despues3=digitalRead(boton2inicio);
   if(pulses>255){          //Si el valor que tenia era HIGH y ahora tiene LOW sera porque lo hemos activado
    inicio3=millis();                      //Guardamos en inicio el tiempo que se lleva ejecutando el programa hasta que
                                          //se activa el sensor start/stop
    antes3=despues3;                        //cambiamos el valor de la variable antes al que tiene la variable despues
    pulsador3=0;                           //Ponemos la variable pulsador a 0
    delay(200);                           //Establecemos un retardo de 200ms
     
    while(pulsador3==0 && bandera==HIGH){                   //Cuando la variable pulsador sea 0
     tiempo3=millis()-inicio3;            //Calculamos el tiempo que paso desde que se activo el sensor start/stop
      //m2=(tiempo2/1000)/60;  
      m3=(tiempo3/1000)/60;                 //Calculamos los minutos
      mu3=m3%10;                            //Descomponemos los minutos y sacamos el valor de las unidades
      md3=(m3-mu3)/10;                       //Descomponemos los minutos y sacamos el valor de las decenas
       
      s3=(tiempo3/1000)%60;                 //Calculamos los segundos
      su3=s3%10;                            //Descomponemos los segundos y sacamos el valor de las unidades
      sd3=(s3-su3)/10;                       //Descomponemos los segundos y sacamos el valor de las decenas
       
      l3=(tiempo3%1000);                    //Calculamos las milesimas de segundo
      lu3=l%10;                            //Descomponemos las milesimas y sacamos el valor de las unidades
      ld3=((l3-lu3)/10)%10;                  //Descomponemos las milesimas y sacamos el valor de las decenas
      lc3=(l3-(ld3*10)-lu3)/100;              //Descomponemos las milesimas y sacamos el valor de las centenas
      
      lcd.setCursor(4, 3);                //Ponemos el cursor en la linea 2 y el caracter 5
      lcd.print(md3);                      //Imprimimos los valores en el display
      lcd.print(mu3);             
      lcd.print(":");
      lcd.print(sd3);
      lcd.print(s3);
      lcd.print(":");
      lcd.print(lc3);
      lcd.print(ld3);
      lcd.print(lu3);
      ////////////////
      lcd.setCursor(0, 0);
      lcd.print("Pulses:"); 
      lcd.print(pulses, DEC);
 
      
      despues2=digitalRead(boton2inicio);      //Guardamos en la variable despues el valor del pin6 (sensor start/stop)
      
      if(despues2==LOW&&antes2==HIGH){      //Si el valor que tenia era HIGH y ahora tiene LOW sera porque hemos activado
       bandera=LOW;                                   //el sensor
       antes2=despues2;                   //cambiamos el valor de la variable antes al que tiene la variable después
        pulsador3=1;         //Ponemos la variable pulsador a 1
        delay(200);                       //Establecemos un retardo de 200ms
      }
      antes3=despues3;                      //cambiamos el valor de la variable antes al que tiene la variable despues
    }
  }
antes3=despues3; 
   
   ///////////////////////////////////////
   //segundo boton
   ///////////////////////////////////////
   despues2=digitalRead(boton2inicio);
  if(despues2==LOW&&antes2==HIGH){          //Si el valor que tenia era HIGH y ahora tiene LOW sera porque lo hemos activado
    inicio2=millis();                      //Guardamos en inicio el tiempo que se lleva ejecutando el programa hasta que
                                          //se activa el sensor start/stop
    antes2=despues2;                        //cambiamos el valor de la variable antes al que tiene la variable despues
    pulsador2=0;                           //Ponemos la variable pulsador a 0
    delay(200);                           //Establecemos un retardo de 200ms
     
    while(pulsador2==0){                   //Cuando la variable pulsador sea 0
      tiempo2=millis()-inicio2;            //Calculamos el tiempo que paso desde que se activo el sensor start/stop
       
      m2=(tiempo2/1000)/60;                 //Calculamos los minutos
      mu2=m2%10;                            //Descomponemos los minutos y sacamos el valor de las unidades
      md2=(m2-mu2)/10;                       //Descomponemos los minutos y sacamos el valor de las decenas
       
      s2=(tiempo2/1000);                 //Calculamos los segundos
      su2=s2%10;                            //Descomponemos los segundos y sacamos el valor de las unidades
      sd2=(s2-su2)/10;                       //Descomponemos los segundos y sacamos el valor de las decenas
       
      l2=(tiempo2%1000);                    //Calculamos las milesimas de segundo
      lu2=l%10;                            //Descomponemos las milesimas y sacamos el valor de las unidades
      ld2=((l2-lu2)/10)%10;                  //Descomponemos las milesimas y sacamos el valor de las decenas
      lc2=(l2-(ld2*10)-lu2)/100;              //Descomponemos las milesimas y sacamos el valor de las centenas
       
      lcd.setCursor(4, 2);                //Ponemos el cursor en la linea 2 y el caracter 5
      //lcd.print(md2);                      //Imprimimos los valores en el display
      //lcd.print(mu2);             
      //lcd.print(":");
      //lcd.print(sd2);
      lcd.print(s2);
      lcd.print(":");
      lcd.print(lc2);
      lcd.print(ld2);
      lcd.print(lu2);
 
      despues2=digitalRead(boton2inicio);             //Guardamos en la variable despues el valor del pin6 (sensor start/stop)
      if(despues2==LOW&&antes2==HIGH){      //Si el valor que tenia era HIGH y ahora tiene LOW sera porque hemos activado
                                          //el sensor
        antes2=despues2;                    //cambiamos el valor de la variable antes al que tiene la variable después
        pulsador2=1;                       //Ponemos la variable pulsador a 1
        delay(200);                       //Establecemos un retardo de 200ms
      }
      antes2=despues2;                      //cambiamos el valor de la variable antes al que tiene la variable despues
    }
  }
   antes2=despues2; 
 if((digitalRead(botonoperacion)==LOW)&&(pulsador2==1)){
    lcd.clear();
    lcd.setCursor(0,3);
    //valor = s+s2+s3;
    //valor=((1-(s/s2))*100)/m3;
    //valor=float(m3)/0.0;
    valor=((1-(float(s)/float(s2)))*100)/float(m3);
    lcd.print("El SDI es: ");
    lcd.setCursor(13,3);
    lcd.print(valor);
   
 }  
}

