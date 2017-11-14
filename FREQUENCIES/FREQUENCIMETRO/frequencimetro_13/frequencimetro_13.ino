#include <Arduino.h>
/*
Desenvolvido por Alexandre Aravecchia
aravecchia@gmail.com
www.aravecchia.weebly.com
*/
#include <LiquidCrystal.h>
#include <Wire.h>
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);
//Estes valores quando trabalhar na protoboard
//LiquidCrystal lcd(13, 12, 11, 10, 9, 8);
//Estes valores quando trabalhar no proteus
const int entrada = 2;
//const int timeout = 2000000;   // um segundo

void setup()
{  
  Serial.begin(9600);
  pinMode(entrada, INPUT);
  lcd.begin(20, 2);
}

void loop()
{
  int t=500;
  unsigned long pico  = 0;
  unsigned long vale = 0;
float periodo = 0;
float frequencia = 0;

  pico    = (pulseIn(entrada, HIGH));
  vale   = (pulseIn(entrada, LOW));
  periodo = (pico + vale);
  frequencia = (1000000/periodo);

  if(periodo)
  {
    Serial.print("T: ");
    Serial.print(periodo);
    Serial.print(" us - ");

    Serial.print("Freq: ");
    Serial.print(frequencia,2);
    Serial.println(" Hz");

    lcd.setCursor(0,0);
    lcd.print("T=");
    lcd.print(periodo);
    lcd.print("us");
    lcd.setCursor(0,1);
    lcd.print("f=");
    lcd.print(frequencia,2);
    lcd.print("Hz");
    delay(t);
  }
}
