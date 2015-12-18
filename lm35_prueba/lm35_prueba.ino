int analog_pin = 0;
float temperatura;
void setup () {
  Serial.begin(9600);
}
void loop() {
  temperatura = analogRead(analog_pin);
  temperatura = 5.0*temperatura*100.0/1024.0;
  Serial.print("T: ");
  Serial.print(temperatura);
  Serial.print("\n");
  
  delay(2000);
}
