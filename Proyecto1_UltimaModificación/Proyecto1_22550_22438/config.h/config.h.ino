#define IO_USERNAME  "Adriagon_040225"
#define IO_KEY       "aio_ibSa760VIHwanBFOOMkzbOqeFTeg"

#define WIFI_SSID "ADRIANA"
#define WIFI_PASS "PruebaESP"

// Incluir la librería Adafruit IO WiFi
#include <AdafruitIO_WiFi.h>

#if defined(USE_AIRLIFT) || defined(ADAFRUIT_METRO_M4_AIRLIFT_LITE) || \
    defined(ADAFRUIT_PYPORTAL)

// Configurar pines para ESP32 con AirLift
#if !defined(SPIWIFI_SS)
#define SPIWIFI     SPI
#define SPIWIFI_SS  10  // Chip select pin
#define SPIWIFI_ACK 9   // a.k.a BUSY o READY pin
#define ESP32_RESETN 6  // Reset pin
#define ESP32_GPIO0 -1  // No conectado
#endif

// Inicializar conexión WiFi con AirLift
AdafruitIO_WiFi io(IO_USERNAME, IO_KEY, WIFI_SSID, WIFI_PASS, 
                   SPIWIFI_SS, SPIWIFI_ACK, ESP32_RESETN, ESP32_GPIO0, SPIWIFI);

#else
// Inicializar conexión WiFi normal (sin AirLift)
AdafruitIO_WiFi io(IO_USERNAME, IO_KEY, WIFI_SSID, WIFI_PASS);
#endif