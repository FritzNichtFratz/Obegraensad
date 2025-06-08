#define _STASSID "EIGENE_SSD"
#define _STAPSK  "EIGENES_PW"

// ESP32 bzw. ESP8266 wird über die IDE-Boardauswahl gesetzt
#ifdef ESP32
  // Pinbelegung ESP32
  #define _P_EN  16  // grau (Pinbezeichnung OE/)
  #define _P_DI  17  // blau (Pinbezeichnung SDI)
  #define _P_CLK 18  // weiss (Pinbezeichnung CLK)
  #define _P_CLA 19  // braun (Pinbezeichnung LA/)
  #define _P_BTN 23  // grün (Taster)
//  #define _P_IKEA D2  // gelb
//  #define _P_BTN_IKEA RX  // 
#else
  // Pinbelegung Wemos D1 mini (clone)
  #define _P_EN  D5  // grau (Pinbezeichnung OE/)
  #define _P_DI  D6  // blau (Pinbezeichnung SDI)
  #define _P_CLK D7  // weiss (Pinbezeichnung CLK)
  #define _P_CLA D1  // braun (Pinbezeichnung LA/)
  #define _P_BTN D4  // grün (Taster)
  #define _P_IKEA D2  // gelb
  #define _P_BTN_IKEA RX  // 
#endif
//#define ESP32C3   // Pinbelegung ESP32-C3 SuperMini
#ifdef ESP32C3
  #undef _P_EN
  #undef _P_DI
  #undef _P_CLK
  #undef _P_CLA
  #undef _P_BTN
  #undef _P_IKEA
  #undef _P_BTN_IKEA
  // Pinbelegung ESP32-C3 SuperMini
  #define _P_EN  1    // grau (Pinbezeichnung OE/)
  #define _P_DI  2    // blau (Pinbezeichnung SDI)
  #define _P_CLK 3    // weiss (Pinbezeichnung CLK)
  #define _P_CLA 4    // braun (Pinbezeichnung LA/)
  #define _P_BTN 10   // grün (Taster)
  #define _P_IKEA 0
  #define _P_BTN_IKEA 0
#endif

#define _MY_NTP_SERVER "pool.ntp.org"

#define MQTT_BROKER_IP  "192.168.1.31"
#define MQTTUSERNAME  ""
#define MQTTPASSWORD ""
#ifdef ESP32
  #define MQTTCLIENT "Obegraensad32"
#else
  #define MQTTCLIENT "Obegraensad"
#endif
#define MQTTPORT 1883
