#include <Arduino.h>


#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x38, 20, 4);
// set the LCD address to 0x20 for a 16 chars and 2 line display
int led = 13;
int t = 500;

void setup()
{
  lcd.init();
  // set up the LCD's number of columns and rows and:
  pinMode(led, OUTPUT);
}
void loop()
{

  // Print a message to the LCD.
  lcd.print("HELLO FUCKIN WORLD!");

  digitalWrite(led, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(t);              // wait for a second
  digitalWrite(led, LOW);    // turn the LED off by making the voltage LOW
  delay(t);              // wait for a second
}
