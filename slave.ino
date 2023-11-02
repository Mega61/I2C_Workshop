#include <Wire.h>

#define TMP36_PIN A0
#define SLAVE_ADDRESS 0x04

void setup() {
  Wire.begin(SLAVE_ADDRESS);
  Wire.onRequest(sendTemperature);
  analogReference(INTERNAL);
}

void loop() {
  delay(1000); // Espera 1 segundo
}

void sendTemperature() {
  int reading = analogRead(TMP36_PIN);
  float voltage = reading * (1.1 / 1024.0);
  float temperature = (voltage - 0.5) * 100;
  Wire.println(temperature);
  Wire.write((int)temperature);
}
