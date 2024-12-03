#### Zeitanzeige auf IKEA OBEGRÄNSAD mit ESP8266/ESP32
***
basierend auf dem [**Sketch**](https://github.com/MakeMagazinDE/Obegraensad) zum Artikel aus [**Make-Ausgabe 6/23**](https://www.heise.de/select/make/2023/6)   
OTA und MQTT unter Verwendung der Library von **[plapointe6](https://github.com/plapointe6/EspMQTTClient)** (Für ESP32 ist eine Anpassung nach [Arduino Forum](https://forum.arduino.cc/t/broken-dependencies/1266624/8) nötig)
***
##### Bedienung:

- Ein Drücken der Taste bewirkt beim Loslassen eine Erhöhung der Helligkeit in 5 Stufen.
  - Nach Erreichen der höchsten Stufe fängt die Helligkeit wieder bei der niedrigsten Stufe an.
- Ein Drücken der Taste länger als 2s schaltet das Display sofort aus.
- Ein Drücken der Taste bei ausgeschaltetem Display schaltet das Display mit der zuletzt gewählten Helligkeit wieder ein.
***
#### Datei *Parameter.h*:

Die Datei muss vor dem Kompilieren angepasst werden:

- _STASSID und _STAPSK auf eigene SSID des Netzwerks und das eigene Passwort setzen
- _P_EN, _P_DI, _P_CLK, _P_CLA und _P_KEY an eigene Verdrahtung anpassen
- _MY_NTP_SERVER eventuell ändern (z.B. _fritz.box_, wenn die Fritz!Box den NTP-Server bereitstellt)
- MQTT_BROKER_IP auf die Adresse des eigenen MQTT-(Node-Red)Servers ändern
- MQTTUSERNAME und MQTTPASSWORD können leer bleiben (oder zur Sicherheit eigene Werte eintragen)
- MQTTCLIENT: unter diesem Namen erscheint der ESP im Netzwerk 
- MQTTPORT: 1883 ist der Standardport
***
#### Webupdater:

- Kompilieren mit: _Sketch > Kompilierte Binärdatei exportieren_ starten
- Adresse des ESP im Browser öffnen z.B. _http://192.168.1.91_
![Picture](https://github.com/FritzNichtFratz/Obegraensad/blob/main/Pics/OTA1.png)
- Mit dem Button Firmware *Durchsuchen...* die exportierte Datei auswählen     
(Die Datei befindet sich im _Projektordner_ (bei Arduino IDE V1.9x) bzw. im Ordner _Projektordner\build\Projektname_ bei V2.x))
![Picture](https://github.com/FritzNichtFratz/Obegraensad/blob/main/Pics/OTA2.png)
- Mit dem Button *Update Firmware* die Übertragung starten
![Picture](https://github.com/FritzNichtFratz/Obegraensad/blob/main/Pics/OTA3.png)
- Fertig!
***
#### MQTT:

- *obegraensad/setDisplay*
 - Schaltet das Display ein/aus
  - Payload: String ("ON"/"OFF")
- *obegraensad/display-state*
 - Gibt den Zustand des Displays zurück
  - Payload: String ("ON"/"OFF")
- *obegraensad/setBrightness*
 - Setzt die Helligkeit auf eine der Helligkeitsstufen
  - Payload: String ("0".."4")
