void setup () {
      Serial.begin(9600); //Inicializo el puerto serial a 9600 baudios
      pinMode(12, OUTPUT);
}
void loop () {
      if (Serial.available()) { //Si está disponible
            char c = Serial.read(); //Guardamos la lectura en una variable char
            if (c == 'H') { //Si es una 'H', enciendo el LED
                  Serial.println("'H' pulsada");
                  digitalWrite(12, LOW);
            } else if (c == 'L') { //Si es una 'L', apago el LED
                  Serial.println("'L' pressed");
                  digitalWrite(12, HIGH);
            } else {
                  Serial.println("Caracter no reconocido");
            }
      }
}
