#include <Servo.h> //Die Servobibliothek wird aufgerufen. Sie wird benötigt, damit die Ansteuerung des Servos vereinfacht wird.
 

unsigned long MinutenTaster_zeit;
int MinutenTaster_gedrueckt;
unsigned long StartTaster_zeit;
int StartTaster_gedrueckt;

int ModusEingabe;

#include <Arduino.h>
#include <U8g2lib.h>
#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif
#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif
U8G2_SH1106_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, U8X8_PIN_NONE, D1, D2 );



Servo teehalter; //Erstellt für das Programm ein Servo mit dem Namen „servoblau“
 int MinutenTaster = D5;
 int StartTaster = D6;
 int MinutenTasterstatus = 0;
 int EndMinutenTasterstatus = 0;
 int TeeZiehzeit = 0;
 int Wartezeit = 0;
 int Pieper = D8;
 int Abkuehler = 0;
 int Abkuehlzeit = 0;
 int AbgekuehlteZeit = 0;

 
 void setup()
 {
   teehalter.attach(D7); //Das Setup enthält die Information, dass das Servo an der Steuerleitung (gelb) mit Pin 8 verbunden wird. Hier ist natürlich auch ein anderer Pin möglich.
   pinMode(MinutenTaster, INPUT);
   pinMode(StartTaster, INPUT);
   pinMode(Pieper,OUTPUT);
   Serial.begin(115200);
   teehalter.write(180);

   MinutenTaster_gedrueckt=0;
   MinutenTaster_zeit=0;
   StartTaster_gedrueckt=0;
   StartTaster_zeit=0;   

   teehalter.write(160);
   
   u8g2.begin();
   ModusEingabe=0;
 }

void statusausgeben () {
Serial.println("--------");
Serial.print(TeeZiehzeit);
Serial.println("");
}

void oled_TeezeitAuswahl() {
  u8g2.firstPage();
  do {
    u8g2.setFontDirection(1);
    
    u8g2.setFont(u8g2_font_fur14_tf);
    u8g2.drawStr(100,1, "Teezeit");
    u8g2.setFont(u8g2_font_fur11_tf);
    u8g2.drawStr(80,4, "waehlen:");
    u8g2.setFont(u8g2_font_fur25_tf);

    //TeeZiehzeit
    //u8g2.drawStr(42,22, "1");
    char buffer[10];
    sprintf( buffer, "%d", TeeZiehzeit );
    u8g2.drawStr(42,22, buffer);
   
    u8g2.setFont(u8g2_font_fur14_tf);
    u8g2.drawStr(20,1, "Minute");
 
  } while ( u8g2.nextPage() );
}


void oled_ZiehzeitAusgeben(int minuten, int sekunden) {
  u8g2.firstPage();
  do {
    u8g2.setFontDirection(1);
    u8g2.setFont(u8g2_font_fur11_tf);
    u8g2.drawStr(80,8, "Ziehzeit");
    u8g2.setFont(u8g2_font_fur25_tf);
    char buffer[10];
    sprintf( buffer, "%d", minuten );
    u8g2.drawStr(42,1, buffer);
    u8g2.drawStr(42,19, ":");
    sprintf( buffer, "%02d", sekunden );
    u8g2.drawStr(42,26, buffer);
  } while ( u8g2.nextPage() );
}

void oled_AbkuehlzeitAusgeben(int minuten, int sekunden) {
  u8g2.firstPage();
  do {
    u8g2.setFontDirection(1);
    u8g2.setFont(u8g2_font_fur11_tf);
    u8g2.drawStr(80,8, "Abkuehl");
    u8g2.setFont(u8g2_font_fur25_tf);
    char buffer[10];
    sprintf( buffer, "%01d", minuten );
    u8g2.drawStr(42,1, buffer);
    u8g2.drawStr(42,19, ":");
    sprintf( buffer, "%02d", sekunden );
    u8g2.drawStr(42,26, buffer);
  } while ( u8g2.nextPage() );
}



void oled_TeeFertigAusgeben() {
  u8g2.firstPage();
  do {
    u8g2.setFontDirection(1);
    u8g2.setFont(u8g2_font_fur11_tf);
    u8g2.drawStr(80,8, "Tee");
    u8g2.drawStr(60,8, "ist");
    u8g2.drawStr(40,8, "fertig");

  } while ( u8g2.nextPage() );
}

void beepen() {
    digitalWrite(Pieper,HIGH);
    delay(100);
    digitalWrite(Pieper,LOW);
    delay(100);
    digitalWrite(Pieper,HIGH);
    delay(100);
    digitalWrite(Pieper,LOW);
}

void loop()
{ 

   if (ModusEingabe==0){
      oled_TeezeitAuswahl();
   }

  
  if (digitalRead(MinutenTaster) == HIGH) {
    MinutenTaster_gedrueckt=1;
    if (MinutenTaster_zeit==0){
      MinutenTaster_zeit=millis();
    }
  } else {
     if (MinutenTaster_gedrueckt==1
      &&millis()>MinutenTaster_zeit+400){
       ModusEingabe=0;
       MinutenTaster_gedrueckt=0;
       MinutenTaster_zeit=0;
       TeeZiehzeit++;
       statusausgeben(); 
       Abkuehler = 0;
     }    
  }

  if (digitalRead(StartTaster) == HIGH) {
    StartTaster_gedrueckt=1;
    if (StartTaster_zeit==0){
      StartTaster_zeit=millis();
    }
  } else {
     if (StartTaster_gedrueckt==1
      &&millis()>StartTaster_zeit+400){
       ModusEingabe=1;
       StartTaster_gedrueckt=0;
       StartTaster_zeit=0;
       Serial.println("---Servostart---");
       //Wartezeit = TeeZiehzeit*60000;
       teehalter.write(90);
       //delay(Wartezeit); 
       
       for (TeeZiehzeit = TeeZiehzeit - 1;TeeZiehzeit >= 0; TeeZiehzeit-- ) {
        
        for (int i = 59; i >= 0; i--) {
          Serial.print(TeeZiehzeit);
          Serial.print(":");
          Serial.println(i);
          oled_ZiehzeitAusgeben(TeeZiehzeit,i);
          delay(1000);
        }
       }
       
        for (int i = 90; i <= 160; i++) {
       teehalter.write(i);
       delay(10);        
       }
       beepen();
       TeeZiehzeit = 0;
       Abkuehler = 1;
       Abkuehlzeit =millis() + 7*60*1000 ;
     }    
  }
  
if (Abkuehler == 1) {
  int sekunden=(Abkuehlzeit-millis())/1000;
  int minuten=(int)sekunden/60;
  sekunden=sekunden-(minuten*60);
  oled_AbkuehlzeitAusgeben( minuten, sekunden );
  if (Abkuehlzeit <= millis() ){
    oled_TeeFertigAusgeben();
    for (int i = 0; i <= 5; i++) {
       beepen();
       delay(1000);
    }
    Abkuehler = 0;
    ModusEingabe=0;
  }

}


}
