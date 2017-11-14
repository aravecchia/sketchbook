#include <Arduino.h>

#include <LiquidCrystal_I2C.h>

#include <Wire.h>
//#include <LiquidCrystal_SI2C.h>

LiquidCrystal_I2C	lcd(0x38, 20, 2);
//LiquidCrystal_SI2C  lcd(0x38,0,1,2,3, 6,5,4);
//                   ADDRESS RS E D4 D5 D6 D7 BACKLIGHT
//                   ADDRESS BL RS RW E D4 D5 D6 D7
/*
  // Creat a set of new characters
  const uint8_t charBitmap[][8] = {
   { 0xc, 0x12, 0x12, 0xc, 0, 0, 0, 0 },
   { 0x6, 0x9, 0x9, 0x6, 0, 0, 0, 0 },
   { 0x0, 0x6, 0x9, 0x9, 0x6, 0, 0, 0x0 },
   { 0x0, 0xc, 0x12, 0x12, 0xc, 0, 0, 0x0 },
   { 0x0, 0x0, 0xc, 0x12, 0x12, 0xc, 0, 0x0 },
   { 0x0, 0x0, 0x6, 0x9, 0x9, 0x6, 0, 0x0 },
   { 0x0, 0x0, 0x0, 0x6, 0x9, 0x9, 0x6, 0x0 },
   { 0x0, 0x0, 0x0, 0xc, 0x12, 0x12, 0xc, 0x0 }
*/

int t = 200;
void setup()
{
  lcd.begin (20, 4);
//  lcd.setBacklightPin(3, POSITIVE);
//  lcd.setBacklight(HIGH);
  Serial.begin(9600);
}

void loop()
{
  // Do a little animation by writing to the same location
  lcd.home ();                   // go home
  lcd.print("Hello, Arduino ");
  delay ( t );
  lcd.setCursor ( 1, 1 );        // go to the next line
  for (int x = 0; x <= 255; x++)
  {
    lcd.print(x);
    lcd.clear();
    Serial.println(x);
    delay ( t );
  }
}

