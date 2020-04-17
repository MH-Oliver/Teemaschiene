# Meine Teemaschiene

Mit der Teemaschine kann man bequem Tee zubereiten.
Ein Teebeutel wird dazu an einem Arm über einer Tasse befestigt.
Nach einstellen der individuellen Ziehzeit wird der Teebeuten in die Tasse gelassen.
Nach der Ziehzeit piept die Maschine und zieht den Beutel aus der Tasse. Es beginnt jetzt die Abkühlzeit. Danach piept die Maschine etwas länger und man kann den Tee sofort trinken.


Hier gibt es Video dazu:
https://youtu.be/Xvad99uWc6Y
 

Bauteile:
-Nodemcu mit ESP8266
-OLED Display SH1106 mit 128x64 Pixel
-Tower Pro Micro Servo 9g Sg90
-Beeper HSD

Steckplatine siehe:
Teemaschiene_Steckplatiene.jpg

 

Das Projekt wurde mit der Arduino IDE verwendet und folgende Libs:
-Servo by Michael Margolis
-U8g2  by Oliver
(Wichtig für das OLED Display diesen Konstruktor verwenden!
U8G2_SH1106_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, U8X8_PIN_NONE, D1, D2 ))

Code:
Teemaschiene.ino
