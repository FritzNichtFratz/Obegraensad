// Zeitanzeige auf IKEA OBEGRÄNSAD mit ESP8266/ESP32
// basierend auf Sketch zum Artikel aus MAKE: 06/2023 S. 64 
// https://github.com/MakeMagazinDE/Obegraensad
// (c)2024 FritzNichtFratz
// Original FAT Font (C)2023 DR. ARMIN ZINK
// 
// OTA und MQTT unter Verwendung von
// https://github.com/plapointe6/EspMQTTClient

#include <Arduino.h>
#include <pgmspace.h>
#include <NTPClient.h>
#include <EspMQTTClient.h>
#include "Parameter.h"

#define PROJECT "OBEGRÄNSAD"
#define VERSION "V1.20"
#ifdef ESP32
  #define BOARD "ESP32"
#else
  #define BOARD "ESP8266"
#endif

#define DISPLAYON 0
#define DISPLAYOFF 255

#define QUADRANT_I 0
#define QUADRANT_II 1
#define QUADRANT_III 2
#define QUADRANT_IV 3

// Parameter aus Datei Parameter.h
//// WLAN
#define STASSID _STASSID
#define STAPSK  _STAPSK
//// Pinbelegung
#define P_EN  _P_EN
#define P_DI  _P_DI
#define P_CLK _P_CLK
#define P_CLA _P_CLA
#define P_BTN _P_BTN
#define P_IKEA _P_IKEA
#define P_BTN_IKEA _P_BTN_IKEA

// SET YOUR TIMEZONE HERE
#define MY_NTP_SERVER _MY_NTP_SERVER // set the best fitting NTP server (pool) for your location
#define MY_TZ "CET-1CEST,M3.5.0,M10.5.0/3" // https://github.com/nayarsystems/posix_tz_db/blob/master/zones.csv

uint8_t brightness_steps[] = {254, 245, 215, 100};  // Helligkeitsstufen (254..0 => Min. Helligkeit bis Max. (255=Anzeige aus))
uint8_t steps = sizeof(brightness_steps) / sizeof(brightness_steps[0]);
uint8_t brightnessStep = 1;
uint8_t brightness = brightness_steps[brightnessStep];

String modes[] = {"Clock", "Counter", "Message", "Debug"};
uint8_t mode = 0;

bool updateDone = false;
const uint32_t TastenDauer = 2000;
const uint32_t TastenDauerDimmer = 3000;
uint32_t TastenStart, TastenEnde;

bool dispOn = true;
bool dispBlinking = false;
uint8_t blinkLow = brightness_steps[1] - 5;
uint8_t blinkHigh = brightness_steps[2] + 50;
bool lowBlinking = false;
uint32_t blinkDauer = 1000;
uint32_t akt_blinkDauer = 0;
bool debug = false;
bool dispDimmer = false;
bool dispIkea = false;
bool btnPressed = false;

uint8_t second;
uint8_t minute;
uint8_t hour;
time_t  now;     // this is the epoch
tm      tm;

EspMQTTClient client(
  STASSID, 
  STAPSK,
  MQTT_BROKER_IP, // MQTT Broker server ip
  MQTTUSERNAME,   // Can be omitted if not needed
  MQTTPASSWORD,   // Can be omitted if not needed
  MQTTCLIENT,     // Client name that uniquely identify your device
  MQTTPORT        // The MQTT port, default to 1883. this line can be omitted
);

#include "Font_System7x7.h"

// --------------------------------------------------------------------------
// THIS IS CLASS p_panel, for freqenz and OBERGRÄNSAD IKEA Panels 
//
int lut[16][16] = {
  {23, 22, 21, 20, 19, 18, 17, 16, 7, 6, 5, 4, 3, 2, 1, 0},
  {24, 25, 26, 27, 28, 29, 30, 31, 8, 9, 10, 11, 12, 13, 14, 15},
  {39, 38, 37, 36, 35, 34, 33, 32, 55, 54, 53, 52, 51, 50, 49, 48},
  {40, 41, 42, 43, 44, 45, 46, 47, 56, 57, 58, 59, 60, 61, 62, 63},
  {87, 86, 85, 84, 83, 82, 81, 80, 71, 70, 69, 68, 67, 66, 65, 64},
  {88, 89, 90, 91, 92, 93, 94, 95, 72, 73, 74, 75, 76, 77, 78, 79},
  {103, 102, 101, 100, 99, 98, 97, 96, 119, 118, 117, 116, 115, 114, 113, 112},
  {104, 105, 106, 107, 108, 109, 110, 111, 120, 121, 122, 123, 124, 125, 126, 127},
  {151, 150, 149, 148, 147, 146, 145, 144, 135, 134, 133, 132, 131, 130, 129, 128},
  {152, 153, 154, 155, 156, 157, 158, 159, 136, 137, 138, 139, 140, 141, 142, 143},
  {167, 166, 165, 164, 163, 162, 161, 160, 183, 182, 181, 180, 179, 178, 177, 176},
  {168, 169, 170, 171, 172, 173, 174, 175, 184, 185, 186, 187, 188, 189, 190, 191},
  {215, 214, 213, 212, 211, 210, 209, 208, 199, 198, 197, 196, 195, 194, 193, 192},
  {216, 217, 218, 219, 220, 221, 222, 223, 200, 201, 202, 203, 204, 205, 206, 207},
  {231, 230, 229, 228, 227, 226, 225, 224, 247, 246, 245, 244, 243, 242, 241, 240},
  {232, 233, 234, 235, 236, 237, 238, 239, 248, 249, 250, 251, 252, 253, 254, 255}
};
uint8_t p_buf[16*16];

// Clear the Panel Buffer
void clearDisplay() {
  for (int i = 0; i < 256; i++) {
      p_buf[i] = 0;
  }

}

void clearDisplayArea(int x, int y, int b, int h) {
  for (int i = 0; i < b; i++) { 
    for (int j = 0; j < h; j++) 
      p_buf[lut[x + i][y + j]] = 0;
  }
}

void showDisplay(bool dispStateOn) {
  if (dispStateOn) {
    analogWrite(P_EN, brightness_steps[brightnessStep]);
  } else {
    #ifdef ESP32
      analogWrite(P_EN, DISPLAYOFF);
    #else
      digitalWrite(P_EN, HIGH);
    #endif
  }
}

void updateDisplay(bool dispState) {
  showDisplay(false);
  digitalWrite(P_CLA, HIGH);
  digitalWrite(P_CLK, LOW);
  for (int i = 0; i < 256 ; i++) {
    digitalWrite(P_DI, p_buf[i]);
    digitalWrite(P_CLK, HIGH);
    digitalWrite(P_CLK, LOW);
  }  
  digitalWrite(P_CLA, LOW);
  showDisplay(dispState);
}

void printChar(uint8_t x, uint8_t y, char ch) {   // Draw a Char Glyph into Panel Buffer
  uint8_t d;

  for (uint8_t x_Font = 0; x_Font < 7; x_Font++) { 
    d = pgm_read_byte_near((ch - 32) * 7 + x_Font + System7x7);  // get Data from Memory
    for (uint8_t y_Font = 0; y_Font < 7; y_Font++) 
      p_buf[lut[y + y_Font][x + x_Font]] = (d & bit(y_Font));
  }
}  

void printChar(uint8_t quadrant, char ch) {
  uint8_t x; uint8_t y;

  switch (quadrant) {
    case QUADRANT_I:   x = 0; y = 0; break;
    case QUADRANT_II:  x = 8; y = 0; break;
    case QUADRANT_III: x = 0; y = 8; break;
    case QUADRANT_IV:  x = 8; y = 8; break;
    default:           x = 0; y = 0; 
  }
  printChar(x, y, ch);
}  

void printClockChar(uint8_t quadrant, char ch) {
  uint8_t x; uint8_t y;

  switch (quadrant) {
    case QUADRANT_I:   x = 0; y = 0; break;
    case QUADRANT_II:  x = 7; y = 0; break;
    case QUADRANT_III: x = 0; y = 8; break;
    case QUADRANT_IV:  x = 7; y = 8; break;
    default:           x = 0; y = 0; 
  }
  printChar(x, y, ch);
}  

void printStringChar(String s) {
  for (uint8_t quadrant = 0; quadrant < 4; quadrant++) {
    printChar(quadrant, (char)s[quadrant]);
  }
}  

void setDisplay(String Mode) {
  if (Mode == modes[0]) {                // Clock
    clearDisplay();
    printClockChar(QUADRANT_I, (hour / 10) + 48);
    printClockChar(QUADRANT_II, (hour % 10) + 48);
    printClockChar(QUADRANT_III, (minute / 10) + 48);
    printClockChar(QUADRANT_IV, (minute % 10) + 48);
  } else if (Mode == modes[1]) {                // Counter

  }
}
// ------------------------ NTP ---------------------------------------------
const char* getTimeString(void) {
  static char acTimeString[32];
  time_t now = time(nullptr);
  ctime_r(&now, acTimeString);
  size_t stLength;
  while (((stLength = strlen(acTimeString))) && ('\n' == acTimeString[stLength - 1])) {
    acTimeString[stLength - 1] = 0; // Remove trailing line break...
  }
  return acTimeString;
}
 
void set_clock(void) {
  #ifdef ESP32
    configTzTime(MY_TZ, MY_NTP_SERVER); // --> Here is the IMPORTANT ONE LINER needed in your sketch!
  #else
    configTime(MY_TZ, MY_NTP_SERVER); // --> Here is the IMPORTANT ONE LINER needed in your sketch!
  #endif

  Serial.print("Waiting for NTP time sync: ");
  time_t now = time(nullptr);   // Secs since 01.01.1970 (when uninitialized starts with (8 * 3600 = 28800)
  while (now < 8 * 3600 * 2) {  // Wait for realistic value
    Serial.print(".");
    now = time(nullptr);
  }
  Serial.println("");
  Serial.printf("Set Current time: %s\n", getTimeString());
}

void set_clock_from_tm() {
  time(&now);                       // read the current time
  localtime_r(&now, &tm);           // update the structure tm with the current time  
  // update time from struct
  hour = tm.tm_hour;
  minute = tm.tm_min;
  second = tm.tm_sec;
}

String Version(void) {
  String Project = String(PROJECT);
  String Version = String(VERSION);
  String Board = String(BOARD);

  return Project + " " + Version + " " + Board;
}

// ----------------------SETUP ----------------------------------------------
void setup() {
  Serial.begin(115200);

  pinMode(P_EN, OUTPUT);
  pinMode(P_CLK, OUTPUT);
  pinMode(P_CLA, OUTPUT);
  pinMode(P_DI, OUTPUT);
  pinMode(P_BTN, INPUT_PULLUP);
  pinMode(P_IKEA, OUTPUT);
  digitalWrite(P_IKEA, LOW);
  pinMode(P_BTN_IKEA, OUTPUT);
  digitalWrite(P_BTN_IKEA, HIGH);

  clearDisplay();
  printStringChar((String)VERSION[0]+(String)VERSION[1]+(String)VERSION[3]+(String)VERSION[4]); 
  updateDisplay(dispOn); delay(1000);

  printStringChar("WLAN"); updateDisplay(dispOn); delay(1000);
  WiFi.mode(WIFI_STA);
  WiFi.begin(STASSID, STAPSK);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("Wifi connected!");
  Serial.println(WiFi.localIP());
  
  printStringChar("Time"); updateDisplay(dispOn); delay(1000);
  set_clock();
  set_clock_from_tm();

  printStringChar("MQTT"); updateDisplay(dispOn); delay(1000);
  client.enableDebuggingMessages(); // Allow to display useful debugging messages. Can be set to false to disable them during program execution
  client.enableHTTPWebUpdater(); // Enable the web updater. User and password default to values of MQTTUsername and MQTTPassword. These can be overridded with enableHTTPWebUpdater("user", "password").
  client.enableOTA(); // Enable OTA (Over The Air) updates. Password defaults to MQTTPassword. Port is the default OTA port. Can be overridden with enableOTA("password", port).

  setDisplay(modes[mode]); updateDisplay(dispOn);
}

// This function is called once everything is connected (Wifi and MQTT)
// WARNING : YOU MUST IMPLEMENT IT IF YOU USE EspMQTTClient
void onConnectionEstablished()
{
  client.subscribe("obegraensad/askVersion", [](const String & payload) {
    client.publish("obegraensad/version", Version()); 
  });

  client.subscribe("obegraensad/Taster", [](const String & payload) {
    if (dispIkea) {
      digitalWrite(P_BTN_IKEA, LOW);
      delay(100);
      digitalWrite(P_BTN_IKEA, HIGH);
    } else btnPressed = true;
  });

  client.subscribe("obegraensad/setDisplay", [](const String & payload) {
    if (payload == "ON") dispOn = true; else dispOn = false;
    showDisplay(dispOn);
  });

  client.subscribe("obegraensad/setBlinking", [](const String & payload) {
    if (payload == "ON") {
      dispBlinking = true;
      lowBlinking = false;
      akt_blinkDauer = millis();
    } else {
      dispBlinking = false;
      setDisplay(modes[mode]);
      updateDisplay(dispOn);
    }
  });

  client.subscribe("obegraensad/setDebug", [](const String & payload) {
    if (payload == "ON") debug = true; else debug = false;
  });

  client.subscribe("obegraensad/setIkea", [](const String & payload) {
    if (payload == "ON") dispIkea = true; else dispIkea = false;
    if (dispIkea) {
      digitalWrite(P_IKEA, HIGH);
    } else {
      digitalWrite(P_IKEA, LOW);
      delay(500);
      setDisplay(modes[mode]);
      updateDisplay(dispOn);
    }
  });

  client.subscribe("obegraensad/display-state", [](const String & payload) {
    String state;

    if (dispOn) state = "ON"; else state = "OFF";
    client.publish("obegraensad/display", state);
  });

  client.subscribe("obegraensad/setBrightness", [](const String & payload) {
    brightness = payload.toInt();
    if (debug && dispOn) analogWrite(P_EN, brightness);
  });

  client.subscribe("obegraensad/setBrightnessStep", [](const String & payload) {
    brightnessStep = payload.toInt();
    if (dispOn) analogWrite(P_EN, brightness_steps[brightnessStep]);
  });
}

// ---------------------- LOOP ----------------------------------------------
void loop() {
  client.loop();  // MQTT

  set_clock_from_tm();
  if ((second == 0) && (!updateDone)) {
    setDisplay(modes[mode]);
    updateDisplay(dispOn);
    if (minute == 0) set_clock();
    updateDone = true;
  } else if (second != 0) updateDone = false;
  delay(100);

  if (dispBlinking && !dispIkea) {
    if (lowBlinking) analogWrite(P_EN, blinkLow); else analogWrite(P_EN, blinkHigh);
    if ((millis() - akt_blinkDauer) > blinkDauer) {
      lowBlinking = !lowBlinking;
      akt_blinkDauer = millis();
    }
  }
  
  // TASTE
  if (((digitalRead(P_BTN) == 0) || btnPressed) && !dispIkea){                // Taste wurde gedrückt
    btnPressed = false;
    TastenStart = millis();
    TastenEnde = 0;
    while (((digitalRead(P_BTN) == 0) && (TastenEnde < TastenDauer)) || btnPressed) {   // Auf Loslassen der Taste oder
      delay(50);                                                        // langen Tastendruck warten
      TastenEnde = millis() - TastenStart;
    }
    if (TastenEnde >= TastenDauer) {            // Wurde Taste lange gedrückt?
      showDisplay(dispOn = false);
      while (digitalRead(P_BTN) == 0);          // Auf Loslassen der Taste warten
    } else {                                    // Taste wurde kurz gedrückt
      if (!dispOn) {                                // War Display ausgeschaltet?
        //dispOn = true;
        setDisplay(modes[mode]);
        showDisplay(dispOn = true);
      } else {                                  // ansonsten Helligkeit ändern
        if (brightnessStep >= (steps - 1)) {        // brightness schon auf Maximum?
          brightnessStep = 0;                       // Dann von Vorne anfangen
        } else brightnessStep++;                    // Ansonsten nächste Stufe wählen
      }
      analogWrite(P_EN, brightness_steps[brightnessStep]);  // Gewählte bzw. vorherige Helligkeit einstellen
    }
  }
}
