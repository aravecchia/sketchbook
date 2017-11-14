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
LiquidCrystal lcd(2,3,4,5,6,7);

#include <Adafruit_ADS1015.h>

Adafruit_ADS1115 ads(0x48);

  float TENSAO = 4.48; // tensao entre A0 e gnd no sensor
  float valorAD = 23992; // valor obtido no AD para fator = 1
    float fator = TENSAO/valorAD; // fator de correção: transforma o valor do AD em tensão.
    // Aplicar equação de Steinhart-Hart para termistores.
    
int t = 1000;
int led = 13;
void setup()
{
  Serial.begin(9600);

  // set up the LCD's number of columns and rows and:
  lcd.begin(20, 4);
  // Print a message to the LCD.
  lcd.print("OpenCLP CyberOhm 2.0");
  lcd.blink();
  displayBlink(2, t / 2); // blink twice
  lcd.noBlink();
  delay(t / 2);
  lcd.clear();

  ads.begin(); // ADC Range: +/- 6.144V (1 bit = 3mV)

  pinMode(led, OUTPUT);

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
  int16_t adc0, adc1, adc2, adc3;  
/*
  adc0 = ads.readADC_SingleEnded(0);
  adc1 = ads.readADC_SingleEnded(1);
  adc2 = ads.readADC_SingleEnded(2);
  adc3 = ads.readADC_SingleEnded(3);

  int matriz[] = {adc0, adc1, adc2, adc3};
  */
  
  for (int x = 0; x <=3; x++)
  {
    lcd.setCursor(0, x);
    lcd.print("Sensor ");
    lcd.print(x);
    lcd.print(":");
    
    lcd.setCursor(10, x);
    lcd.print(ads.readADC_SingleEnded(x)*fator);
    lcd.setCursor(14, x);
    lcd.print(" V");
  }
  delay(t/4);
 digitalWrite(led, HIGH);
 delay(t/4);
 digitalWrite(led, LOW);
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
