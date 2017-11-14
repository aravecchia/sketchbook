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
LiquidCrystal lcd(5, 6, 8, 9, 10, 11);

#include <VirtualWire.h>

// const int transmit_pin = 12;
const int receive_pin = 7;
// const int transmit_en_pin = 10;

int t = 1000;
int led = 13;
int red = 12;

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
  pinMode(led, OUTPUT);
  pinMode(red, OUTPUT);

  vw_set_ptt_inverted(true); // Required for DR3100
  vw_set_rx_pin(12);
  vw_setup(4000); // Bits per sec
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
  digitalWrite(led, LOW);
  digitalWrite(red, LOW);

  uint8_t buf[VW_MAX_MESSAGE_LEN];
  uint8_t buflen = VW_MAX_MESSAGE_LEN;

  lcd.setCursor(0, 0);
  lcd.print("CyberOhm Robotics");

  if (vw_get_message(buf, &buflen)) // Non-blocking
  {
    {
      digitalWrite(led, HIGH);
      int i;

      digitalWrite(led, HIGH); // Flash a light to show received good message
      // Message with a good checksum received, dump it.
      lcd.setCursor(0, 2);
      lcd.print("Dominar o mundo!");

      for (i = 0; i < buflen; i++)
      {
        lcd.setCursor(0, 3);
        lcd.print(buf[i], HEX);
        delay(t);
      }
      digitalWrite(led, LOW);
    }
  }
  else
  {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("CyberOhm Robotics");
    digitalWrite(red, HIGH);
    lcd.setCursor(0, 2);
    lcd.print("Sem sinal :[");
    delay(2*t);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("CyberOhm Robotics");
    lcd.setCursor(0, 2);
    lcd.print("Ainda nao :[");
    delay(2*t);
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
