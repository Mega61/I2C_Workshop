#include <Wire.h>

#define TMP36_PIN A0
#define SLAVE_ADDRESS 0x04

void setup() {
  // Inicializa la comunicación I2C con la dirección del esclavo definida
  Wire.begin(SLAVE_ADDRESS);
  // Define la función "sendTemperature" como la que se llama cuando se solicita información
  Wire.onRequest(sendTemperature);
  // Establece la referencia de voltaje interno para las lecturas analógicas
  analogReference(INTERNAL);
}

void loop() {
  // Espera 1 segundo antes de continuar
  delay(1000);
}

void sendTemperature() {
  // Lee el valor analógico del sensor conectado a TMP36_PIN
  int reading = analogRead(TMP36_PIN);
  // Convierte el valor en voltaje utilizando una referencia de 1.1V y 1024 pasos de resolución
  float voltage = reading * (1.1 / 1024.0);
  // Calcula la temperatura en grados Celsius a partir del voltaje leído
  float temperature = (voltage - 0.5) * 100;
  // Envía la temperatura a través del bus I2C como texto y como valor entero
  Wire.println(temperature);
  Wire.write((int)temperature);
}
