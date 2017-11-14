#include <Arduino.h>

//#include <LiquidCrystal.h>
#include <Wire.h>
//LiquidCrystal lcd(8, 9, 4, 5, 6, 7);
//Estes valores quando trabalhar na protoboard
//LiquidCrystal lcd(13, 12, 11, 10, 9, 8);
//Estes valores quando trabalhar no proteus

//Mux control pins
//int r0 = 2;
//int r1 = 3;
//int r2 = 4;

int s0 = 5;
int s1 = 6;
int s2 = 7;


int entrada = A0;
int saida = A1;
int x;
int t=500;

void setup()

{
  //  pinMode(r0, OUTPUT); 
  //  pinMode(r1, OUTPUT); 
  //  pinMode(r2, OUTPUT); 
  pinMode(s0, OUTPUT); 
  pinMode(s1, OUTPUT); 
  pinMode(s2, OUTPUT);
  pinMode(entrada, INPUT); 
  pinMode(saida, OUTPUT);

  //  digitalWrite(r0, LOW);
  //  digitalWrite(r1, LOW);
  //  digitalWrite(r2, LOW);
  digitalWrite(s0, LOW);
  digitalWrite(s1, LOW);
  digitalWrite(s2, LOW);

  Serial.begin(9600);


}

void loop()

{
  for (x=0; x<8; x++)
  {
    toca();
    //   digitalWrite(saida, digitalRead(A0));
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
      Serial.print("T");
      Serial.print(x+1);
      Serial.print(" = ");
      Serial.print(periodo,0);
      Serial.print(" us - ");

      Serial.print("F");

      Serial.print(" = ");
      Serial.print(frequencia,0);
      Serial.println(" Hz");

      //    lcd.setCursor(0,0);
      //    lcd.print("T=");
      //    lcd.print(periodo);
      //    lcd.print("us");
      //    lcd.setCursor(0,1);
      //    lcd.print("f=");
      //    lcd.print(frequencia,2);
      //    lcd.print("Hz");
      delay(t);
    }



  }
}
void toca()
{
  switch (x)
  {
  case 0:
    {
      //      digitalWrite(r0, LOW);
      //      digitalWrite(r1, LOW);
      //      digitalWrite(r2, LOW);
      digitalWrite(s0, LOW);
      digitalWrite(s1, LOW);
      digitalWrite(s2, LOW);
    }
    break;
  case 1:
    {
      //      digitalWrite(r0, HIGH);
      //      digitalWrite(r1, LOW);
      //      digitalWrite(r2, LOW);
      digitalWrite(s0, HIGH);
      digitalWrite(s1, LOW);
      digitalWrite(s2, LOW);
    }
    break;
  case 2:  
    {
      //      digitalWrite(r0, LOW);
      //      digitalWrite(r1, HIGH);
      //      digitalWrite(r2, LOW);
      digitalWrite(s0, LOW);
      digitalWrite(s1, HIGH);
      digitalWrite(s2, LOW);
    }
    break;
  case 3:
    {
      //      digitalWrite(r0, HIGH);
      //      digitalWrite(r1, HIGH);
      //      digitalWrite(r2, LOW);
      digitalWrite(s0, HIGH);
      digitalWrite(s1, HIGH);
      digitalWrite(s2, LOW);
    }
    break;
  case 4:
    {
      //      digitalWrite(r0, LOW);
      //      digitalWrite(r1, LOW);
      //      digitalWrite(r2, HIGH);
      digitalWrite(s0, LOW);
      digitalWrite(s1, LOW);
      digitalWrite(s2, HIGH);
    }
    break;
  case 5:
    {
      //      digitalWrite(r0, HIGH);
      //      digitalWrite(r1, LOW);
      //      digitalWrite(r2, HIGH);
      digitalWrite(s0, HIGH);
      digitalWrite(s1, LOW);
      digitalWrite(s2, HIGH);
    }
    break;
  case 6:
    {
      //      digitalWrite(r0, LOW);
      //      digitalWrite(r1, HIGH);
      //      digitalWrite(r2, HIGH);
      digitalWrite(s0, LOW);
      digitalWrite(s1, HIGH);
      digitalWrite(s2, HIGH);
    }
    break;
  case 7:
    {
      //      digitalWrite(r0, HIGH);
      //      digitalWrite(r1, HIGH);
      //      digitalWrite(r2, HIGH);
      digitalWrite(s0, HIGH);
      digitalWrite(s1, HIGH);
      digitalWrite(s2, HIGH);
    }
    break;
  }
}







