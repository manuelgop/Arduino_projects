#include <LiquidCrystal.h>                //Incluimos la libreria que contiene las funciones del display LCD
 
int m, mu=0,md=0;                          //Declaramos las variables que vamos a usar
int s, su=0,sd=0;
int l, lu=0,ld=0,lc=0;
int pulsador,antes,despues;
long int tiempo,inicio;
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);  
int boton1inicio=6;
int boton1final=7;
int reset=0;
int boton2inicio=1;
int boton2final=0;
long int tiempo2,inicio2;
int pulsador2,antes2,despues2;
int m2, mu2=0,md2=0;                          //Declaramos las variables que vamos a usar
int s2, su2=0,sd2=0;
int l2, lu2=0,ld2=0,lc2=0;
int botonoperacion = 8;
int valor=0;
int iniciaCta =0;

//////////////////////////////////////////////
void setup() {
  // put your setup code here, to run once:
lcd.begin(20, 4);                       //Establecemos el tamaño del display (16 caracteres de largo y 2 lineas de alto)
  lcd.print("--------SDI-------");                    //Imprimimos a continuacion el resto "metro___"
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
   pinMode(boton2inicio, INPUT_PULLUP);                      //Ponemos el pin 6 como entrada para el Sensor START/STOP
  pinMode(boton2final, INPUT_PULLUP); 
  pinMode(botonoperacion, INPUT_PULLUP);
  /////////////////////////////////
  ///---Para el CountdownTimer---/////
   

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
  }
  despues=digitalRead(boton1inicio);
  if(despues==LOW&&antes==HIGH){          //Si el valor que tenia era HIGH y ahora tiene LOW sera porque lo hemos activado
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
      //lcd.print(md);                      //Imprimimos los valores en el display
      //lcd.print(mu);             
      //lcd.print(":");
      //lcd.print(sd);
      lcd.print(s);
      lcd.print(":");
      lcd.print(lc);
      lcd.print(ld);
      lcd.print(lu);
 
      despues=digitalRead(boton1inicio);             //Guardamos en la variable despues el valor del pin6 (sensor start/stop)
      if(despues==LOW&&antes==HIGH){      //Si el valor que tenia era HIGH y ahora tiene LOW sera porque hemos activado
                                          //el sensor
        antes=despues;                    //cambiamos el valor de la variable antes al que tiene la variable después
        pulsador=1;         //Ponemos la variable pulsador a 1
        delay(200);                       //Establecemos un retardo de 200ms
      }
      antes=despues;                      //cambiamos el valor de la variable antes al que tiene la variable despues
    }
  }
   antes=despues; 
   

   
   ///////////////////////////////////////
   //segundo boton
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
       
      s2=(tiempo2/1000)%60;                 //Calculamos los segundos
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
    lcd.setCursor(0,3);
    valor = s+s2;
    lcd.print("La suma es:");
    lcd.setCursor(13,3);
    lcd.print(valor);
   
 }  
}

