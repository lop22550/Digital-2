#include <Wire.h>

#define I2CSlaveAddress1 0x55
#define I2CSlaveAddress2 0x46


#define I2C_SDA 21
#define I2C_SCL 22

byte datoToSend = 0x42;

uint8_t error;
uint8_t bytesReceived;

typedef enum {
  I2C_ERROR_OK=0,
  I2C_ERROR_DEV,
  I2C_ERROR_ACK,
  I2C_ERROR_TIMEOUT,
  I2C_ERROR_BUS,
  I2C_ERROR_BUSY,
  I2C_ERROR_MEMORY,
  I2C_ERROR_CONTINUE,
  I2C_ERROR_NO_BEGIN
} i2c_err_t;

void setup() {
  Serial.begin(115200);
  Wire.begin(I2C_SDA, I2C_SCL);

}

void loop() {
 
  delay(2000);

  uint8_t sensor = random(99);
  Wire.beginTransmission(I2CSlaveAddress1);
  Wire.printf("S>%u", sensor);
  //uint8_t error = Wire.endTransmission(true);
  error = Wire.endTransmission(true);
  Serial.printf("endTransmission: %u\n", error);

  //uint8_t bytesReceived = Wire.requestFrom(I2CSlaveAddress1, 4);
  bytesReceived = Wire.requestFrom(I2CSlaveAddress1, 4);

  Serial.printf("requestFrom: %u\n", bytesReceived);
  if (bytesReceived > 0) {
    uint8_t temp[10];
    for (int i = 0; i < bytesReceived; i++) {
      temp[i] = Wire.read();
      Serial.printf("Byte %d: %u", i, temp[i]);
    }
  } else {
    Serial.println("No data received");
}

//****************************Comunicación con dispositivo 2 (la del 7seg) ******************************
/*
delay(2000);

  //uint8_t sensor = random(99);
  Wire.beginTransmission(I2CSlaveAddress2);
  Wire.printf("S>%u");
  error = Wire.endTransmission(true);
  Serial.printf("endTransmission: %u\n", error);

  bytesReceived = Wire.requestFrom(I2CSlaveAddress2, 4);

  Serial.printf("requestFrom: %u\n", bytesReceived);
  if (bytesReceived > 0) {
    uint8_t temp[10];
    for (int i = 0; i < bytesReceived; i++) {
      temp[i] = Wire.read();
      Serial.printf("Byte %d: %u", i, temp[i]);
    }
  } else {
    Serial.println("No data received");
}

*/
}