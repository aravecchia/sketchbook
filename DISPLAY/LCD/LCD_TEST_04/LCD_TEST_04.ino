/*
Desenvolvido por Alexandre Aravecchia
aravecchia@gmail.com
www.aravecchia.weebly.com
*/

#include <Arduino.h>

// include the library code:
#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.setCursor(0,0);
  lcd.print("cyberohm.com");
  lcd.setCursor(0,1);
  lcd.print("Aperte um botao:");
}

void loop() {
  int x;
  x = analogRead (0);
  lcd.setCursor(0,1);
  if (x < 60) {
    lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("cyberohm.com");
  lcd.setCursor(0,1);
    lcd.print ("Direita ->");
  }
  else if (x < 200) {
        lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("cyberohm.com");
  lcd.setCursor(0,1);
    lcd.print ("Sobe");
  }
  else if (x < 400){
        lcd.clear();
          lcd.setCursor(0,0);
  lcd.print("cyberohm.com");
  lcd.setCursor(0,1);
    lcd.print ("Desce");
  }
  else if (x < 600){
        lcd.clear();
          lcd.setCursor(0,0);
  lcd.print("cyberohm.com");
  lcd.setCursor(0,1);
    lcd.print ("Lula 2018! ");
  }
  else if (x < 800){
      lcd.setCursor(0,0);
  lcd.print("cyberohm.com");
  lcd.setCursor(0,1);
    lcd.print ("Aperte um botao:");
  }
}
