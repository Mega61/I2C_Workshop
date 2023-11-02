#include <Wire.h>

#define LED_PIN 13
#define SLAVE_ADDRESS 0x04

void setup() {
  // Configura el pin 13 (LED) como salida
  pinMode(LED_PIN, OUTPUT);
  // Inicializa la comunicación I2C
  Wire.begin();
  // Inicializa la comunicación serial a 9600 baudios para mensajes de depuración
  Serial.begin(9600);
}

void loop() {
  // Solicita un byte de datos al esclavo con la dirección especificada (SLAVE_ADDRESS)
  Wire.requestFrom(SLAVE_ADDRESS, 1);
  
  // Verifica si hay datos disponibles para leer
  if (Wire.available()) {
    // Lee el valor de temperatura recibido del esclavo
    int temperature = Wire.read();
    // Imprime el valor de temperatura en el monitor serial
    Serial.println(temperature);
    
    // Comprueba si la temperatura es mayor que 45 grados
    if (temperature > 45) {
      // Enciende el LED conectado al pin 13
      digitalWrite(LED_PIN, HIGH);
    } else {
      // Apaga el LED si la temperatura es menor o igual a 45 grados
      digitalWrite(LED_PIN, LOW);
    }
  }
  
  // Espera 1 segundo antes de continuar con la siguiente lectura
  delay(1000);
}
