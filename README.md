# Workshop de Control de Temperatura y Dashboard en ThingSpeak

Este taller se centra en la implementación de un sistema de control de temperatura de 2 capas que utiliza una configuración maestro-esclavo a través de I2C. El esclavo envía datos de temperatura, capturados por un sensor TMP36, al maestro cada segundo. El maestro activa un LED en caso de que la temperatura supere los 45°C. Además, se publican los datos de temperatura y las alertas en un panel de control alojado en ThingSpeak, que es capaz de mostrar datos históricos de temperatura.

## Internet_script: Control de Temperatura y Publicación en ThingSpeak

Este código es un script de Python que se ejecuta en el computador en el que se encuentran conectados nuestros Aruino UNO y está diseñada para recibir datos de temperatura a través de un puerto serial desde el sensor de temperatura del Arduino. Luego, envía estos datos a ThingSpeak para su visualización en un panel de control. Se recurrió a esto ya que nuestras boards Arduino UNO no cuentan con la capacidad de enviar información a través de WiFi/Bluetooth.

### Configuración y Funcionamiento

- **Configuración de Serial:** Se debe modificar la variable `SERIAL_PORT` para que coincida con el puerto serial al que está conectado el dispositivo que envía los datos de temperatura. Además, se debe proporcionar la API Key de ThingSpeak en `THINGSPEAK_CHANNEL_API_KEY`.

- **Función `send_to_thingspeak`:** Esta función envía la temperatura a ThingSpeak a través de una solicitud HTTP. Los datos se envían como un valor numérico al campo `field1` en ThingSpeak.

- **Función `main`:** La función principal establece la comunicación serial, recibe datos de temperatura, los envía a ThingSpeak y muestra las temperaturas en la consola. Los datos se envían a ThingSpeak cuando se reciben correctamente y se manejan excepciones en caso de datos no válidos.

## Master: Control de Actuador LED

Este código se ejecuta en un dispositivo maestro y controla un actuador LED basado en la temperatura recibida de un dispositivo esclavo a través de la comunicación I2C.

### Configuración y Funcionamiento

- **Configuración del Pin y Comunicación I2C:** El código configura el pin 13 como una salida para el LED y establece la comunicación I2C.

- **Función `loop`:** El bucle principal solicita un byte de datos al dispositivo esclavo con la dirección especificada (SLAVE_ADDRESS). Luego, verifica si hay datos disponibles para leer.

- Si la temperatura recibida es mayor que 45 grados Celsius, el LED se enciende; de lo contrario, se apaga.

- Se agrega un retraso de 1 segundo antes de continuar con la siguiente lectura.

## Slave: Envío de Temperatura a Través de I2C

Este código se ejecuta en un dispositivo esclavo y se encarga de leer un sensor de temperatura (en este caso, el TMP36) y enviar los datos al dispositivo maestro a través de la comunicación I2C.

### Funcionamiento

- El dispositivo esclavo inicia la comunicación I2C con la dirección del esclavo definida.

- Define la función `sendTemperature` como la que se llama cuando se solicita información desde el maestro.

- Configura la referencia de voltaje interno para las lecturas analógicas.

- En el bucle principal, se espera 1 segundo antes de continuar.

- Cuando se solicita información desde el maestro, la función `sendTemperature` lee el valor analógico del sensor TMP36, lo convierte en temperatura en grados Celsius y lo envía al maestro a través del bus I2C tanto como texto como valor entero.
