#include "BluetoothSerial.h"

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

//#define LED 2
# define RXuart2 16 
# define TXuart2 17

BluetoothSerial BT; // Objeto Bluetooth

void setup() {
  Serial.begin(115200); // Inicialización de la conexión en serie para la depuración
  
  Serial2.begin(9600, SERIAL_8N1, RXuart2, TXuart2);
  Serial.println("Serial 2 started at 9600 baud rate");

  BT.begin("ESP32-1"); // Nombre de su dispositivo Bluetooth y en modo esclavo
  Serial.println("El dispositivo Bluetooth está listo para emparejarse");
  //pinMode (LED, OUTPUT); // Cambie el pin LED a OUTPUT

}

void loop() {
  if (BT.available()) // Compruebe si recibimos algo de Bluetooth
  {
    int incoming = BT.read(); // Lee lo que recibimos
    Serial.print("Recibido: ");
    Serial.println(incoming);

    Serial2.print(incoming);

    
    /*if (incoming == 49){ // 1 en ASCII
      //digitalWrite(LED, HIGH); // LED Encendido
      BT.println("LED encendido"); // Envía el mensaje de texto a través de BT Serial
    }
    if (incoming == 48){ // 0 en ASCII
      //digitalWrite(LED, LOW); // LED Apagado
      BT.println("LED apagado"); // Envía el mensaje de texto a través de BT Serial
    }*/
  }
  delay(1000);
  Serial.println("-------------------------------");
}
