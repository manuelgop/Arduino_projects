void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

}

void loop() {
  // put your main code here, to run repeatedly:
  //Serial.println("Hola PI+45:45+4554:8484");
  Serial.print("latitud");
  Serial.print("+");
  Serial.print("longitud");
  Serial.print("+");
  Serial.print(35.45);
  Serial.print("+");
  Serial.print("presion");
  Serial.print("+");
  Serial.println("500");
  delay(2000);
}
