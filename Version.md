### Versionshistorie
***
**V0.90**
- Formatierung angepasst
- Pinbelegung und Farbzuordnung geändert
- TIMEZONE angepasst
- Variablen geändert
 - mil entfernt
 - brightness entfernt
 - OE_ eingefügt
 - sec in second geändert
 - TastenStart, TastenEnde, TastenDauer eingefügt
 - Wartezeit TT verringert
 - _pLatch/_pClock/_pData entfernt
- FAT NUMBER "1" modifiziert
- y-Koordinate der Minutenanzeige verschoben
- Funktion p_init entfernt
- Funktion p_scan überarbeitet
- Funktion set_display eingefügt
- Funktion setup angepasst
- Funktion loop angepasst
 - set_clock() wird nur jede Stunde aufgerufen
 - set_display() wird bei Änderung der Minute aufgerufen
 - Tastenroutine überarbeitet und zum Ein-/Ausschalten des Displays geändert

**V0.95**
- Parameter für WiFi und Pinbelegung in Datei Parameter.h ausgelagert
- Variablen geändert
 - Array brightness_steps eingefügt
 - brightness (geändert) wieder eingefügt
- brightness in p_scan eingefügt
- Tastenroutine um die Steuerung des Displays erweitert

**V1.00**
- Array brightness_steps verkleinert
- Funktion p_scan überarbeitet
- Variable TT entfernt
- https://github.com/plapointe6/EspMQTTClient eingebunden
 - MQTT/OTA/Webupdater
- Beispielflow für Node-RED hinzugefügt

**V1.10**
- Diverse Anpassungen für ESP32
  - **#include <WiFi.h>** bei ESP32 in **EspMQTTClient.h** ergänzt 
   (siehe [Arduino Forum](https://forum.arduino.cc/t/broken-dependencies/1266624/8))
  - **digitalWrite(P_EN, HIGH)** durch **analogWrite(P_EN, 255)** ersetzt
  - ESP32 ruft **configTzTime()** statt **configTime()** auf (Parameterübergabe)
  - **OE_** durch **dispOff** ersetzt
- Allgemeine Anpassungen

**V1.15**
- FAT NUMBER "1" modifiziert
- FAT NUMBER "3" modifiziert
- Font "V" und "v" modifiziert
- Font auf 7x7 erweitert
  - Bezeichnungen angepasst
- Helligkeitsstufen verringert und angepasst
- brightness von festen Helligkeitsstufen entkoppelt
- MQTT: Beispiel angepasst
- p_printChar vereinfacht und in printChar umbenannt
- printChar(QUANDRANT_X) eingefügt
- Anzeige des Arbeitsschritts bei Neustart

**V1.16**
- Font in Font_System7x7.h ausgelagert
- P_KEY in P_BTN umbenannt
- Blinken eingefügt
  - Helligkeiten für Blinken eingefügt
- Debug eingefügt
  - Helligkeit über MQTT stufenlos regelbar

**V1.20** (ESP32 und ESP32-C3 ohne Zusatzplatine)
- printClockChar(QUANDRANT_X) eingefügt
- Diverse Überarbeitungen
- Routinen für Zusatzboard mit Ikea-Chip eingefügt
