#include <Arduino.h>

// include the library code:
#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);
//LiquidCrystal lcd(8, 9, 4, 5, 6, 7);
//Estes valores quando trabalhar na protoboard
//LiquidCrystal lcd(13, 12, 11, 10, 9, 8);
//Estes valores quando trabalhar no proteus

int verde=22;
int amarelo=23;
int vermelho=24;
int branco=25;

void setup()
{
  for (int x=22; x<26; x++)
  {
    pinMode(x, OUTPUT);
  }
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.setCursor(0,0);
  lcd.print("cyberohm.com");
  lcd.setCursor(0,1);
  lcd.print("Aperte um botao:");
}

void loop()
{
  int x;
  x = analogRead (0);
  lcd.setCursor(0,1);
  if (x < 60)
  {
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("cyberohm.com");
    lcd.setCursor(0,1);
    lcd.print ("Direita ->");
digitalWrite(verde, LOW);
digitalWrite(amarelo, LOW);
digitalWrite(vermelho, LOW);
digitalWrite(branco, LOW);
  }
  else if (x < 200)
  {
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("cyberohm.com");
    lcd.setCursor(0,1);
    lcd.print ("Sobe");
digitalWrite(verde, LOW);
digitalWrite(amarelo, HIGH);
digitalWrite(vermelho, LOW);
digitalWrite(branco, LOW);
  }
  else if (x < 400)
  {
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("cyberohm.com");
    lcd.setCursor(0,1);
    lcd.print ("Desce");
digitalWrite(verde, HIGH);
digitalWrite(amarelo, LOW);
digitalWrite(vermelho, LOW);
digitalWrite(branco, LOW);
  }
  else if (x < 600)
  {
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("cyberohm.com");
    lcd.setCursor(0,1);
    lcd.print ("Lula 2018! ");
digitalWrite(verde, LOW);
digitalWrite(amarelo, LOW);
digitalWrite(vermelho, HIGH);
digitalWrite(branco, LOW);
  }
  else if (x < 800){
    lcd.setCursor(0,0);
    lcd.print("cyberohm.com");
    lcd.setCursor(0,1);
    lcd.print ("Aperte um botao:");
    digitalWrite(branco, HIGH);
digitalWrite(vermelho, LOW);
digitalWrite(verde, LOW);
digitalWrite(amarelo, LOW);
  }
}

