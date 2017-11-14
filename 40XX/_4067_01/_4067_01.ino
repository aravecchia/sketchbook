#include <Arduino.h>

#include <LiquidCrystal.h>
#include <Wire.h>
//LiquidCrystal lcd(8, 9, 4, 5, 6, 7);
//Estes valores quando trabalhar na protoboard
LiquidCrystal lcd(13, 12, 11, 10, 9, 8);
//Estes valores quando trabalhar no proteus


//Mux control pins
int r0 = 2;
int r1 = 3;
int r2 = 4;
int r3 = 5;

int comum = 6;

int led;

int fator = 1;
int Taceso = 250;
int Tapagado = Taceso/fator;


void setup()

{
  pinMode(r0, OUTPUT); 
  pinMode(r1, OUTPUT); 
  pinMode(r2, OUTPUT); 
  pinMode(r3, OUTPUT); 

  pinMode(comum, OUTPUT); 

  digitalWrite(r0, LOW);
  digitalWrite(r1, LOW);
  digitalWrite(r2, LOW);
  digitalWrite(r3, LOW);

  Serial.begin(9600);
}

void loop()

{
  for (led=1; led<17; led++)
  {
    switch (led)
    {
    case 1:
      {
        digitalWrite(r0, LOW);
        digitalWrite(r1, LOW);
        digitalWrite(r2, LOW);
        digitalWrite(r3, LOW);  
        //0000      
      }
      break;
    case 2:
      {
        digitalWrite(r0, HIGH);
        digitalWrite(r1, LOW);
        digitalWrite(r2, LOW);
        digitalWrite(r3, LOW); 
        //0001     
      }
      break;
    case 3:  
      {
        digitalWrite(r0, LOW);
        digitalWrite(r1, HIGH);
        digitalWrite(r2, LOW);
        digitalWrite(r3, LOW);
        //0010       
      }
      break;
    case 4:
      {
        digitalWrite(r0, HIGH);
        digitalWrite(r1, HIGH);
        digitalWrite(r2, LOW);
        digitalWrite(r3, LOW); 
        //0011     
      }
      break;
    case 5:
      {
        digitalWrite(r0, LOW);
        digitalWrite(r1, LOW);
        digitalWrite(r2, HIGH);
        digitalWrite(r3, LOW); 
        //0100      
      }
      break;
    case 6:
      {
        digitalWrite(r0, HIGH);
        digitalWrite(r1, LOW);
        digitalWrite(r2, HIGH);
        digitalWrite(r3, LOW);  
        //0101      
      }
      break;
    case 7:
      {
        digitalWrite(r0, LOW);
        digitalWrite(r1, HIGH);
        digitalWrite(r2, HIGH);
        digitalWrite(r3, LOW);  
        //0110    
      }
      break;
    case 8:
      {
        digitalWrite(r0, HIGH);
        digitalWrite(r1, HIGH);
        digitalWrite(r2, HIGH);
        digitalWrite(r3, LOW);
        //0111     
      }
    case 9:
      {
        digitalWrite(r0, LOW);
        digitalWrite(r1, LOW);
        digitalWrite(r2, LOW);
        digitalWrite(r3, HIGH); 
        //1000      
      }
    case 10:
      {
        digitalWrite(r0, HIGH);
        digitalWrite(r1, LOW);
        digitalWrite(r2, LOW);
        digitalWrite(r3, HIGH); 
        //1001      
      }
    case 11:
      {
        digitalWrite(r0, LOW);
        digitalWrite(r1, HIGH);
        digitalWrite(r2, LOW);
        digitalWrite(r3, HIGH); 
        //1010    
      }
    case 12:
      {
        digitalWrite(r0, HIGH);
        digitalWrite(r1, HIGH);
        digitalWrite(r2, LOW);
        digitalWrite(r3, HIGH); 
        //1011     
      }
    case 13:
      {
        digitalWrite(r0, LOW);
        digitalWrite(r1, LOW);
        digitalWrite(r2, HIGH);
        digitalWrite(r3, HIGH);  
        //1100     
      }
    case 14:
      {
        digitalWrite(r0, HIGH);
        digitalWrite(r1, LOW);
        digitalWrite(r2, HIGH);
        digitalWrite(r3, HIGH);  
        //1101    
      }
    case 15:
      {
        digitalWrite(r0, LOW);
        digitalWrite(r1, HIGH);
        digitalWrite(r2, HIGH);
        digitalWrite(r3, HIGH);
        //1110     
      }
    case 16:
      {
        digitalWrite(r0, HIGH);
        digitalWrite(r1, HIGH);
        digitalWrite(r2, HIGH);
        digitalWrite(r3, HIGH);  
        //1111     
      }
      break;
    }
    conta();
  }
}


void conta()
{
  digitalWrite(comum, HIGH);   // turn the LED on (HIGH is the voltage level)
  {
    Serial.print("Led ativo: ");
    Serial.print(led);
    Serial.println(".");

    lcd.setCursor(0,0);
    lcd.print("Led ativo:");
    lcd.setCursor(0,1);
    lcd.print(led);
    lcd.print(".");
  }
  delay(Taceso);              // wait for a second
  digitalWrite(comum, LOW);    // turn the LED off by making the voltage LOW
  delay(Tapagado);
}

//void escreve()
//{
//  {
//    Serial.print("Led ativo: ");
//    Serial.print(led);
//    Serial.println(".");

//    lcd.setCursor(0,0);
//    lcd.print("Led ativo:");
//    lcd.setCursor(1,0);
//    lcd.print(led);
//    lcd.print(".");
//  }
//}












