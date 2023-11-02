#include <Wire.h>

#define LED_PIN 13
#define SLAVE_ADDRESS 0x04

void setup() {
  pinMode(LED_PIN, OUTPUT);
  Wire.begin();
  Serial.begin(9600);
}

void loop() {
  Wire.requestFrom(SLAVE_ADDRESS, 1);
  if (Wire.available()) {
    int temperature = Wire.read();
    Serial.println(temperature);
    if (temperature > 45) {
      digitalWrite(LED_PIN, HIGH);
    } else {
      digitalWrite(LED_PIN, LOW);
    }
  }
  delay(1000);
}
