    int pirPin = 2;
     
    
     
    
     
    void setup()
    {
    pinMode(pirPin, INPUT);
    Serial.begin(9600);
    }
     
    void loop()
    {
    
    if (digitalRead(pirPin) == HIGH)
    {
   
    Serial.println("MOVEMENT");
    }else{
     Serial.println("No hay MOVIMIENTO");
    }
    delay(500);
    }
