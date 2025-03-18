#include "config.h"

#define RXD2 16
#define TXD2 17  

HardwareSerial sensorSerial(2); // UART para comunicación con sensores

float ValorTemperatura = 0;
float ValorHumedad = 0;
float ValorNivel = 0;

#define IO_LOOP_DELAY 10000
#define SERIAL_LOOP_DELAY 400

unsigned long lastUpdate = 0;

// Feeds de Adafruit IO
AdafruitIO_Feed *feedTemperatura = io.feed("temperatura");
AdafruitIO_Feed *feedHumedad = io.feed("humedad");
AdafruitIO_Feed *feedNivel = io.feed("nivel");
AdafruitIO_Feed *feedRegar = io.feed("regar");
AdafruitIO_Feed *feedVentilar = io.feed("ventilar");

void setup() {
  Serial.begin(9600);
  while (!Serial);
  Serial.println("Iniciando conexión con Adafruit IO...");

  // Inicializamos el UART para la comunicación con los sensores
  sensorSerial.begin(9600, SERIAL_8N1, RXD2, TXD2);

  io.connect();

  // Espera hasta que se conecte a Adafruit IO
  while (io.status() < AIO_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  Serial.println();
  Serial.println(io.statusText());
}

void loop() {
  io.run();
    
  // Lectura de datos de los sensores vía UART
  if (sensorSerial.available()) {
    String data = sensorSerial.readStringUntil('\n');  // Leer hasta nueva línea

    if (data.length() > 0) {  
      // Se espera que los datos vengan en el formato "T:xx.x H:xx.x N:xx.x"
      sscanf(data.c_str(), "T:%f H:%f N:%f", &ValorTemperatura, &ValorHumedad, &ValorNivel);

      Serial.print("Temperatura: "); Serial.println(ValorTemperatura);
      Serial.print("Humedad: "); Serial.println(ValorHumedad);
      Serial.print("Nivel de agua: "); Serial.println(ValorNivel);
    }
  }

  // Enviar los datos a Adafruit IO cada IO_LOOP_DELAY
  if (millis() > (IO_LOOP_DELAY + lastUpdate)) {
    lastUpdate = millis();
    feedTemperatura->save(ValorTemperatura);
    feedHumedad->save(ValorHumedad);
    feedNivel->save(ValorNivel);
  }

  // Condiciones para el riego y ventilación
  bool regarEstado = feedRegar->get();  // Leer estado del feed de riego
  bool ventilarEstado = feedVentilar->get();  // Leer estado del feed de ventilación

  // Si el feed de riego está activado, enviar "riegoon" por UART
  if (regarEstado) {
    sensorSerial.println("riegoON");
    Serial.println("Enviando señal de riego: riegoON");
  }

  // Si el feed de ventilación está activado, enviar "ventilaron" por UART
  if (ventilarEstado) {
    sensorSerial.println("ventilarON");
    Serial.println("Enviando señal de ventilación: ventilarON");
  }

  delay(SERIAL_LOOP_DELAY);  // Esperar un poco antes de la próxima iteración
}