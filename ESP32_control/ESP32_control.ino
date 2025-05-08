//
//#include <esp_wifi.h>
#include "BluetoothSerial.h"

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

BluetoothSerial BT; // Objeto Bluetooth

String clientName = "ESP32-1";
bool connected;

# define RXuart2 16 
# define TXuart2 17

#define LED1 2  // Pin indicador de Conexión con Consola por medio de BT
#define LED2 4  // Pin indicador de Desconexión

char Data;

void setup() {

  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);


  Serial.begin(9600);
  Serial2.begin(9600, SERIAL_8N1, RXuart2, TXuart2);
  Serial.println("Serial 2 started at 9600 baud rate");

  BT.begin("ESP32-2", true); // Nombre de su dispositivo Bluetooth y en modo maestro
  Serial.println("El dispositivo Bluetooth está en modo maestro. Conectando con el anfitrión ...");
  connected = BT.connect(clientName);
  if(connected) {
    Serial.println("¡Conectado exitosamente!");
    digitalWrite(LED1, HIGH);
    digitalWrite(LED2, LOW);
  } else {
    while(!BT.connected(1000)) {
      Serial.println("No se pudo conectar. Asegúrese de que el dispositivo remoto esté disponible y dentro del alcance, luego reinicie la aplicación."); 
      digitalWrite(LED1, LOW);
      digitalWrite(LED2, HIGH);
    }
  }

  

  
}

void loop() {
  // put your main code here, to run repeatedly:
  while (Serial2.available()){
    // get the byte data from the GPS
    Data = Serial2.read();
    Serial.print(Data);
  }

  delay(50);
  BT.write(Data); // Envía los valores del control por Bluetooth

}
