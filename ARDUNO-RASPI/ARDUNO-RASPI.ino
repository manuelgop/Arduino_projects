int analog_pin = 0;
float temperatura;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  temperatura = analogRead(analog_pin);
  temperatura = 5.0*temperatura*100.0/1024.0;
  Serial.print(temperatura);
  Serial.println(" oC");
  delay(2000);
}
