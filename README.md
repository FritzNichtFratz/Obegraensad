#### Zeitanzeige auf IKEA OBEGRÄNSAD mit ESP8266/ESP32/ESP32-C3 SuperMini

#### (mit Zusatzboard Umschaltung auf Originalchip möglich)

<img title="" src="https://github.com/FritzNichtFratz/Obegraensad/blob/main/Pics/Zeitanzeige.jpg" alt="Picture" width="249">     <img title="" src="https://github.com/FritzNichtFratz/Obegraensad/blob/main/Pics/Zeitanzeige_wideFont.jpg" alt="Picture" width="249">

***

basierend auf dem [**Sketch**](https://github.com/MakeMagazinDE/Obegraensad) zum Artikel aus [**Make-Ausgabe 6/23**](https://www.heise.de/select/make/2023/6)   
OTA und MQTT unter Verwendung der Library von **[plapointe6](https://github.com/plapointe6/EspMQTTClient)** (Für ESP32 ist eine Anpassung nach [Arduino Forum](https://forum.arduino.cc/t/broken-dependencies/1266624/8) nötig)

***

##### Bedienung:

- Ein Drücken der Taste bewirkt beim Loslassen eine Erhöhung der Helligkeit in vier Stufen.
  
  - Nach Erreichen der höchsten Stufe fängt die Helligkeit wieder bei der niedrigsten Stufe an.

- Ein Drücken der Taste länger als 2s schaltet das Display sofort aus.

- Ein Drücken der Taste bei ausgeschaltetem Display schaltet das Display mit der zuletzt gewählten Helligkeit wieder ein.

- Im Ikea-Modus wird der Tastendruck zum Ikea-Chip durchgereicht

***

#### Datei *Parameter.h*:

Die Datei muss vor dem Kompilieren angepasst werden:

- _STASSID und _STAPSK auf eigene SSID des Netzwerks und das eigene Passwort setzen
- Pins an eigene Verdrahtung anpassen
- _MY_NTP_SERVER eventuell ändern (z.B. _fritz.box_, wenn die Fritz!Box den NTP-Server bereitstellt)
- MQTT_BROKER_IP auf die Adresse des eigenen MQTT-(Node-Red)Servers ändern
- MQTTUSERNAME und MQTTPASSWORD können leer bleiben (oder zur Sicherheit eigene Werte eintragen)
- MQTTCLIENT: unter diesem Namen erscheint der ESP im Netzwerk 
- MQTTPORT: 1883 ist der Standardport

***

#### Webupdater:

(mit Zusatzplatine z.Zt. nicht möglich))

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

- subscribe *obegraensad/askVersion*
  - Payload: Timestamp
- publish *obegraensad/version*
  - Payload: String
    - Gibt Name/Version/Board des Sketches zurück
- subscribe *obegraensad/Taster*
  - Payload: Timestamp
    - Simuliert Tastendruck am Panel
- subscribe *obegraensad/setDisplay*
  - Payload: String ("ON"/"OFF")
    - Schaltet das Display ein/aus
- subscribe *obegraensad/setBlinking*
  - Payload: String ("ON"/"OFF")
    - Schaltet blinkende Anzeige ein/aus
- subscribe *obegraensad/setDebug*
  - Payload: String ("ON"/"OFF")
    - Schaltet Debugmodus ein/aus
- subscribe *obegraensad/setIkea*
  - Payload: String ("ON"/"OFF")
    - Schaltet Ikea-Modus ein/aus
- subscribe *obegraensad/display-state*
  - Payload: Timestamp
- publish *obegraensad/display*
  - Payload: String
    - Gibt den Zustand des Displays zurück
- subscribe *obegraensad/setBrightness*
  - Payload: String (254..0)
    - Setzt im Debug-Modus die Helligkeit
- subscribe *obegraensad/setBrightnessStep*
  - Payload: String ("0".."3")
    - Setzt die Helligkeit auf eine der Helligkeitsstufen

***

#### Hardware:

Zusatzplatine mit Step-Down-Regler und Originalchip

<img title="" src="https://github.com/FritzNichtFratz/Obegraensad/blob/main/Hardware/Zusatzplatine.jpg" alt="Picture" width="350">

- Ansteuerung der Datenleitungen über zwei IC 74HCT4053
- Step-Down-Regler versorgt die Schieberegler mit Minimalspg. lt. Datenblatt (3 Volt)
  - Verringerung der Stromaufnahme
  - Sichtbare Minderung der Helligkeit bei niedrigen Helligkeitsstufen
