// RFID reader for Arduino 
// Wiring version by BARRAGAN <http://people.interaction-ivrea.it/h.barragan> 
// Modified for Arudino by djmatic
// Modified by Xenoepist for added functionality:
//  * Previous version double readed data. This happened because even thou the RFID reader had been deactivated after a data read
//    there was still data in the RFID reader buffer. The solution I implemented was to read this data and flush it.
//  * In this version, an Access list and a Master Key is added. The amount of keys in the access list is defined by the user with one simple modification.
//    At first the access list is empty, but the Master Key code should be manually entered in the program. To add keys to the
//    Access list, scan the master key once [Programming Mode] and then swipe the new key. If the new key is not in the access
//    list, the new key is added to the list. If the new key is alreadyt in the access list, then the key will be deleted from the access list.
//    If you entered programming mode by mistake, swipe the master key again to exit programming mode.
//  * Power it with a 12VDC 2.0Amp, to get enough juice to run VHG05 electronic lock. Also use an NPN transistor, with the base connected to pin 9
//  * Three LED Indicators are used to inform user of what is going on. If you want to modify the pins used, check the beggining of the code
//    under //LED Indicators. If you want to modify the behavior of these LED's, just change the end of the code, the last 5 functions controll
//    the behavior of the LED's.
#include <eeprom.h>
//Constants
#define NumberOfKeys  10  //This defines the amount of keys in the access list
#define WAIT_TIME 2000     //Time door will remain open
#define BLINKS 3               //The amount of times the indicators blink when blinking is required
#define ON_TIME 200         //time in milliseconds the relay stays energized

//External Equipment
#define ENABLE 2               //Pin connected to the Enable pin of RFID
#define LOCK 9                  //Pin that is connected to NPN transistor that energizes lock

//LED Indicators
#define OPEN_LIGHT 4              //LED indicator. Indicates the correct key was entered
#define DENIED_LIGHT 5           //LED indicator. Indicates the wrong key was entered
#define PROGRAMMING_LIGHT 6 //LED indicator. Indicates Programming mode is activated

int     val = 0; 
int     bytesread = 0;
String  Master = "0B082D041A";  //Stores the master key used for programming the other keys
String  empty = "0000000000";
String  keyCode;
String  accessList[NumberOfKeys];
char    code[10];
boolean programmingMode,isInAccessList,KeyFound = false;

void setup() {
pinMode(OPEN_LIGHT,OUTPUT);
pinMode(DENIED_LIGHT,OUTPUT);
pinMode(PROGRAMMING_LIGHT,OUTPUT);
pinMode(ENABLE,OUTPUT);
pinMode(LOCK,OUTPUT);

//Generates an array of size corresponding to the size of the access list
for(int i = 0;i<NumberOfKeys;i++){
 accessList[i] = empty;
}

Serial.begin(2400); // RFID reader SOUT pin connected to Serial RX pin at 2400bps 

digitalWrite(OPEN_LIGHT,LOW);
digitalWrite(DENIED_LIGHT,LOW);
digitalWrite(PROGRAMMING_LIGHT,LOW);
digitalWrite(ENABLE, LOW);                  // LOW Activates the RFID reader, HIGH deactivates it
digitalWrite(LOCK,LOW);

}  


void loop() { 
  /**** EXTRACTION OF DATA FROM CARD ****/
 if(Serial.available() > 0) {            // if data available from reader 
   if((val = Serial.read()) == 10) {   // check for header [Header of data = 10]
     bytesread = 0; 
     
     while(bytesread<10) {              // read 10 digit code 
       if( Serial.available() > 0) { 
         val = Serial.read(); 
         if((val == 10)||(val == 13)) { // if header or stop bytes before the 10 digit reading 
           break;                             // stop reading 
         } 
         code[bytesread] = val;      // add the digit
         bytesread++;                   // ready to read next digit
       } 
     } 
     if(bytesread == 10) {                  // if 10 digit read is complete
     digitalWrite(ENABLE, HIGH);        // deactivate the RFID reader for a moment so it will not flood 
      keyCode = code;
      keyCode = keyCode.substring(0,10);
      /*** INTERPRETATION OF DATA ***/
      //At this point, data was read, and there is a keycode in the keyCode variable      
      if((keyCode == Master) && (programmingMode == false))
      {programmingMode = true;
       digitalWrite(PROGRAMMING_LIGHT,HIGH);
     }
      else
      {if(programmingMode == false)
      {
         for(int i = 0;i<NumberOfKeys;i++)  //check entered key against saved keys
         {
            if(keyCode.equals(accessList[i])){
               KeyFound = true;}                  //if the key is in the access list, KeyFound = true;
         }
         if(KeyFound)
         {
           accessGranted();
           KeyFound = false;
         }
         else{
           accessDenied();
         }
     }
     else if(programmingMode)
     {
       if(keyCode.equals(Master)){  //Master Key swipped during programming mode
       }else
       {
        isInAccessList = false;               //this is an initialization value, if the key is in the access list, this variable will be true later.        
         for(int i = 0;i< NumberOfKeys;i++)   //Scans Access List
           {if(keyCode.equals(accessList[i])) //if the card read is in the Access List
              {
               accessList[i] = empty;         //delete it
               isInAccessList = true;         //isInAccessList set to true, meaning the key was in the access list
               keyDeleted();
              }
           }
          if(isInAccessList == false)             //if the key swipped is not in the access list and...
          {
             for(int i = 0;i< NumberOfKeys;i++){ 
               if(accessList[i].equals(empty))    //...if current Access List Slot is Empty
               {accessList[i] = keyCode;          //Enter Key into Access List Slot
               newKeyEntered();
                break;
                }   
               if(i == (NumberOfKeys - 1))       //if you get to this point at last interation of loop, access List is full
                   listFull();              
             }
          } 
       }
       digitalWrite(PROGRAMMING_LIGHT,LOW);
       programmingMode = false;                   //Programming is done, turn programming mode and indicator off
     }
      }
      resetIndicators();
   }    //end of data reading

 }
}
}

/*** CLEARS DATA FROM BUFFERS TO AVOID DOUBLE READS***/
void flushBuffers(){
  while(Serial.available() > 0)          //if there is still data remaining in the RFID reader buffer
      Serial.read();                         //read it into arduino buffer
  Serial.flush();                             //then flush it
}

/*** RESETTING INDICATORS ***/
void resetIndicators(){
      
     delay(WAIT_TIME);                 //wait a little
     flushBuffers();                       //clear buffers
     
     digitalWrite(LOCK,LOW);              //return everything to starting position
     digitalWrite(OPEN_LIGHT,LOW);
     digitalWrite(DENIED_LIGHT,LOW);
     digitalWrite(ENABLE,LOW);
}

/*** BEHAVIOR OF LED INDICATORS IF A KEY IN THE ACCESS LIST IS SWIPPED ***/
void accessGranted(){
 digitalWrite(OPEN_LIGHT,HIGH);
 digitalWrite(LOCK,HIGH);//Sends 5V to transistor to energize door lock
 delay(ON_TIME);            //Relay stays energized for ON_TIME milliseconds
 digitalWrite(LOCK,LOW); //Immediately after delay, de-energize door.
}
/*** BEHAVIOR OF LED INDICATORS IF A KEY THAT'S NOT IN THE ACCESS LIST IS SWIPPED ***/
void accessDenied(){
 digitalWrite(DENIED_LIGHT,HIGH);
 digitalWrite(LOCK,LOW);
}

/*** BEHAVIOR OF LED INDICATORS IF A NEW KEY IS ENTERED IN THE ACCESS LIST ***/
void newKeyEntered(){
 for(int i = 0; i<BLINKS;i++)
   {
     digitalWrite(PROGRAMMING_LIGHT,LOW);
     delay(250);
     digitalWrite(PROGRAMMING_LIGHT,HIGH);
     delay(250);
   }
   digitalWrite(OPEN_LIGHT,HIGH);
}

/*** BEHAVIOR OF LED INDICATORS IF A KEY IS DELETED FROM ACCESS LIST ***/
void keyDeleted(){
 for(int i = 0; i<BLINKS;i++)
   {
     digitalWrite(PROGRAMMING_LIGHT,LOW);
     delay(250);
     digitalWrite(PROGRAMMING_LIGHT,HIGH);
     delay(250);
   }
   digitalWrite(DENIED_LIGHT,HIGH);
  
}

/*** BEHAVIOR OF LED INDICATORS IF ACCESS LIST IS FULL ***/
void listFull(){
 for(int i = 0; i<BLINKS;i++)
   {
     delay(250);
     digitalWrite(PROGRAMMING_LIGHT,HIGH);
     digitalWrite(DENIED_LIGHT,HIGH);
     digitalWrite(OPEN_LIGHT,HIGH);
     delay(250);
     digitalWrite(PROGRAMMING_LIGHT,LOW);
     digitalWrite(DENIED_LIGHT,LOW);
     digitalWrite(OPEN_LIGHT,LOW);
   }  
     digitalWrite(PROGRAMMING_LIGHT,HIGH);
     digitalWrite(DENIED_LIGHT,HIGH);
     digitalWrite(OPEN_LIGHT,HIGH);
}
