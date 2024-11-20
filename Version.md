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
  - MQTT
  - OTA
- Beispielflow für Node-RED hinzugefügt
