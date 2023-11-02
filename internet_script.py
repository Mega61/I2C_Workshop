import serial
import requests

# Configuración de Serial
SERIAL_PORT = 'COM3'  # Modifica esto según tu puerto serial
BAUD_RATE = 9600

# Configuración de ThingSpeak
THINGSPEAK_CHANNEL_API_KEY = 'X06COBGOZ9ZZZUQC'  # Reemplaza con tu API Key
THINGSPEAK_URL = 'https://api.thingspeak.com/update'

def send_to_thingspeak(temperature):
    payload = {
        'api_key': THINGSPEAK_CHANNEL_API_KEY,
        'field1': temperature
    }
    try:
        response = requests.post(THINGSPEAK_URL, params=payload)
        print("Respuesta de ThingSpeak:", response.text)
    except:
        print("Error enviando datos a ThingSpeak")

def main():
    with serial.Serial(SERIAL_PORT, BAUD_RATE) as ser:
        while True:
            line = ser.readline().decode('utf-8').strip()
            try:
                temperature = float(line)
                print("Temperatura:", temperature)
                send_to_thingspeak(temperature)
            except ValueError:
                print("Dato no válido:", line)

if __name__ == "__main__":
    main()
