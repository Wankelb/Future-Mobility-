# Future-Mobility-

First Commit

In diesem Teil der Präsentation werden drei elektronische Projekte realisiert. In den Projekten werden verschiedene elektronische Bauteile verwendet. Das gemeinsame Ziel der Projekte ist es, die Nutzung der Cloud auf internetfähigen Geräten aufzuzeigen.

# Projekt 1: Wetterinformation von der Cloud

 <p align="center">
<img src=".//IMG_6721.jpg"| width=300>
</p> 

In diesem Projekt werden aktuelle Wetterinformationen aus der Cloud empfangen und auf dem Bildschirm angezeigt werden. 
Der ESP32 ist eine kostengünstige und mit geringem Leistungsbedarf ausgeführte 32-Bit-Mikrocontrollerfamilie der chinesischen Firma Espressif, die im Jahr 2016 vorgestellt wurde. Die Mikrocontroller ermöglichen durch ihre offene Bauweise den Aufbau und die Vernetzung von netzwerkbasierten Aktuatoren und Sensoren.

<p align="center">
<img src=".//OpenWeather-Logo.jpg"| width=250>
</p> 

Die Wetterinformationen stammen von OpenWeather. OpenWeather ist ein Team aus IT-Experten und Datenwissenschaftlern, das seit 2014 Deep Weather Data Science praktiziert. OpenWeather stellt für jeden Punkt auf der Welt historische, aktuelle und prognostizierte Wetterdaten über APIs und Cloud-Dienste bereit.
Zuerst verbindet sich das Esp32-Modul mit dem Internet. Nach der Verbindung wird eine Verbindung zur OpenWeather-API angefordert. Das System prüft, ob der KEY von Esp32 korrekt ist. Dieser KEY wird von OPENWeather nach Anfrage erhalten. Nach der KEY-Überprüfung wird der Zugriff auf die Daten bereitgestellt. Diese empfangenen Informationen werden dann auf dem Bildschirm angezeigt.

# Projekt 2: Remote Control durch Arduino IoT Cloud Service

In diesem Projekt wird das Modul Arduino IoT Nano 33 verwendet. Dieses Modul kann sich mit der Arduino Cloud verbinden und die Komponenten auf dem Whiteboard über das Internet steuern. Arduino Cloud: „Die Arduino IoT Cloud ermöglicht es Nutzern, mehrere Sensoren zentral zu verwalten und einzurichten. Die Umgebung macht es auch möglich, Scripts mit anderen Nutzern zu teilen und aus der Ferne zu verteilen. Nicht nur Arduino-Boards, sondern viele andere Linux-Geräte sind damit kompatibel. Elektronik Bauteile auf dem Whiteboard: Arduino Nano IoT 33, DHT 11 Temperatur Sensor, Traffic LED, Blau LED.

<p align="center">
<img src=".//Titel3.jpg"| width=250>
</p> 

Der DHT 11 Sensor am Whiteboard übermittelt die Daten an das NANO 33 Modul. Dieses Modul sendet Daten über das Internet an die Cloud. Auf diese Weise können die vom Sensor empfangenen Daten im Internet und in Apps auf mobilen Geräten eingesehen werden. Die LEDs des Whiteboards können auch über Apps auf mobilen Geräten gesteuert werden. Der Benutzer erstellt eine Anfrage über die Umschalttaste in der App, um die LEDs einzuschalten. Nachdem die Arduino Cloud diese Anfrage genehmigt hat, überträgt sie die Anfrage über das Internet an das NANO 33-Modul. Dann schaltet der Nano 33 die LEDs auf dem Whiteboard ein.

# Projekt 3: Intelligente Home Sicherheit
In diesem Projekt soll ein Home-Sicherheitssystem gemacht werden. Als elektronische Teile werden ein Arduino Uno, ein GSM 808-Modul, ein GPS-Sensor und ein Ultraschallsensor verwendet. Ziel des Projekts ist es, einen Standortlink von Google Maps zu generieren, wenn der Ultraschallsensor eine Bewegung erkennt. Dieser Standortlink wird vom GSM-Modul 808 als SMS an den Benutzer gesendet.
<p align="center">
<img src=".//projekt3.png"| width=300>
</p> 

Wenn der Arduino Uno eine Abweichung in den Sensordaten erkennt, aktiviert der UNO automatisch den Alarm. Danach sendet es eine Nachricht an den Benutzer mit dem GSM 808-Modul.
<p align="center">
<img src=".//IMG_6723.jpg"| width=300>
</p> 
Diese Meldung  beinhaltet die Frage, ob Standortinformationen an die Polizei weitergeleitet werden sollen. Wenn diese Nachricht mit „JA“ beantwortet wird, wird der GPS-Sensor im Gsm808 automatisch aktiviert. Dank der vom GPS-Sensor empfangenen Daten wird ein Google-Maps-Link erstellt. Die erstellten Standortinformationen werden dem Benutzer über GSM 808 mitgeteilt.
<p align="center">
<img src=".//IMG_6724.jpg"| width=300>
</p> 

<p align="center">
<img src=".//IMG_6725.jpg"| width=300>
</p> 
