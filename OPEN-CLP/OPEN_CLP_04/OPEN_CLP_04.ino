#include <Arduino.h>

/*
   Projeto OPEN CLP CyberOhm v. 2.0
   Alexandre Aravécchia, Rui Viana et Laboratório de Garagem (labdegaragem.com.br)
   CyberOhm Robotics: cyberohm.com
   abril de 2016
*/
// include the library code:
#include <LiquidCrystal.h>
#include <Wire.h>
// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(2,3,4,5,6,7); // RS - E - DB4 - DB5 - DB6 - DB7

#include <VirtualWire.h>

int t = 1000;
int led13 = 13;
int red_led = 12;
int bps=5000;
int rf=8;

void setup()
{
  Serial.begin(9600);

  // set up the LCD's number of columns and rows and:
  lcd.begin(20, 4);
  // Print a message to the LCD.
  lcd.print("OpenCLP CyberOhm 2.0");
  lcd.blink();
  //  displayBlink(2, t / 2); // blink twice
  lcd.noBlink();
  delay(t / 2);
  lcd.clear();
  pinMode(led13, OUTPUT);
  pinMode(red_led, OUTPUT);


  vw_set_rx_pin(rf);
  vw_setup(5000); // Bits per sec
  vw_rx_start(); // Start the receiver PLL running
}



void displayBlink(int blinks, int duration)
{
  while (blinks--)
  {
    lcd.noDisplay();
    delay(duration);
    lcd.display();
    delay(duration);
  }
}

void loop()
{
  digitalWrite(led13, LOW);
  digitalWrite(red_led, LOW);

  uint8_t buf[1];
  uint8_t buflen = 1;

  lcd.setCursor(0, 0);
  lcd.print("CyberOhm Robotics");

  if (vw_get_message(buf, &buflen)) // Non-blocking
  {
    {
      digitalWrite(led13, HIGH);
      digitalWrite(red_led, LOW); // Flash a light to show received good message
      // Message with a good checksum received, dump it.
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("CyberOhm Robotics");

      for (int i = 0; i < buflen; i++)
      {
        lcd.setCursor(0, 2);
        lcd.print((buf[i]));
        Serial.println(buf[i]);
        //lcd.print(char(buf));// Esse é para receber o valor em si?
        delay(t);
      }
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("CyberOhm Robotics");

      digitalWrite(led13, LOW);
    }
  }
  else
  {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("CyberOhm Robotics");
    digitalWrite(red_led, HIGH);
    lcd.setCursor(0, 2);
    lcd.print("Sem sinal :[");
    delay(2 * t);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("CyberOhm Robotics");
    lcd.setCursor(0, 2);
    lcd.print("Ainda nao :[");
    delay(2 * t);
  }
}

/*
  lcd.setCursor(0, 1);
  lcd.print("Cursor blink");
  lcd.blink();
  lcd.noBlink();
  lcd.clear();
  lcd.noDisplay();
  lcd.display();
  displayBlink(2, t / 4); // blink twice
  displayBlink(2, t / 2); // and again for twice as long

  void displayBlink(int blinks, int duration)
  {
  while (blinks--)
  {
    lcd.noDisplay();
    delay(duration);
    lcd.display();
    delay(duration);
  }
  }
*/
