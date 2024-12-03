#define _STASSID "EIGENE_SSD"
#define _STAPSK  "EIGENES_PW"

#ifdef ESP32
//  #define GO32  // wegen time.h/types.h
  // Pinbelegung ESP32
  #define _P_EN  16  // grau (Pinbezeichnung OE/)
  #define _P_DI  17  // blau (Pinbezeichnung SDI)
  #define _P_CLK 18  // gelb (Pinbezeichnung CLK)
  #define _P_CLA 19  // braun (Pinbezeichnung LA/)
  #define _P_KEY 23  // grün
#else
  // Pinbelegung Wemos D1 mini (clone)
  #define _P_EN  D5  // grau (Pinbezeichnung OE/)
  #define _P_DI  D6  // blau (Pinbezeichnung SDI)
  #define _P_CLK D7  // gelb (Pinbezeichnung CLK)
  #define _P_CLA D1  // braun (Pinbezeichnung LA/)
  #define _P_KEY D2  // grün
#endif

#define _MY_NTP_SERVER "pool.ntp.org"

#define MQTT_BROKER_IP  "192.168.1.31"
#define MQTTUSERNAME  ""
#define MQTTPASSWORD ""
#define MQTTCLIENT "Obegraensad"
#define MQTTPORT 1883
