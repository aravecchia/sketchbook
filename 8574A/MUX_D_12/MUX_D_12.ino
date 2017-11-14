#include <Arduino.h>

#include <Wire.h>  //inclui a biblioteca

#define mux1 56
#define mux2 57
#define mux3 58
#define mux4 59
#define mux5 60
#define mux6 61
#define mux7 62
#define mux8 63

void setup()
{
  {
    Serial.begin(9600);  
    pinMode(13, OUTPUT);   //um led so pra saber se o programa ta rodando
  }
  {
    Wire.begin();                  //registra no bus
    Wire.beginTransmission(mux1);  //inicia a transmissao pro primeiro mux
    Wire.write(B11111111);          //desliga os 8 bytes do mux
    Wire.endTransmission();
    digitalWrite(13, 1);
    delay(t);
    digitalWrite(13, 0);
    delay(t);

  }
  {
    Wire.begin();
    Wire.beginTransmission(mux2);
    Wire.write(B11111111);
    Wire.endTransmission();
    digitalWrite(13, 1);
    delay(t);
    digitalWrite(13, 0);
    delay(t);
  }
  {
    Wire.begin();
    Wire.beginTransmission(mux3);
    Wire.write(B11111111);
    Wire.endTransmission();
    digitalWrite(13, 1);
    delay(t);
    digitalWrite(13, 0);
    delay(t);
  }
  {
    Wire.begin();
    Wire.beginTransmission(mux4);
    Wire.write(B11111111);
    Wire.endTransmission();
    digitalWrite(13, 1);
    delay(t);
    digitalWrite(13, 0);
    delay(t);
  }
  {
    Wire.begin();
    Wire.beginTransmission(mux5);
    Wire.write(B11111111);
    Wire.endTransmission();
    digitalWrite(13, 1);
  }
  {
    Wire.begin();
    Wire.beginTransmission(mux6);
    Wire.write(B11111111);
    Wire.endTransmission();
  }
  {
    Wire.begin();
    Wire.beginTransmission(mux7);
    Wire.write(B11111111);
    Wire.endTransmission();
  }
  {
    Wire.begin();
    Wire.beginTransmission(mux8);
    Wire.write(B11111111);
    Wire.endTransmission();
  }

}
void loop()

{
  int tempo=100;
  //intervalo de tempo
  //numero do byte
  for (int b=(B11111111); b >= (B00000000); b--)  //contando...
  {
    {
      Wire.beginTransmission(mux1);  //inicia a transmissao pro mux
      Wire.write(b);                  //escreve o byte nos leds
      Wire.endTransmission();         //fim da transmissao para o mux
      digitalWrite(13, 0);
      delay(tempo);
      digitalWrite(13, 1);
      delay(t);
    }
    {
      Wire.beginTransmission(mux2);
      Wire.write(b);
      Wire.endTransmission();
      digitalWrite(13, 0);
      delay(tempo);
      digitalWrite(13, 1);
      delay((tempo));
    }
    {
      Wire.beginTransmission(mux3);
      Wire.write(b);
      Wire.endTransmission();
      digitalWrite(13, 0);
      delay((tempo));
      digitalWrite(13, 1);
      delay(tempo);
    }
    {
      Wire.beginTransmission(mux4);
      Wire.write(b);
      Wire.endTransmission();
      digitalWrite(13, 0);
      delay(tempo);
      digitalWrite(13, 1);
      delay(tempo);
    }
    {
      Wire.beginTransmission(mux5);
      Wire.write(b);
      Wire.endTransmission();
      digitalWrite(13, 0);
      delay(tempo);
      digitalWrite(13, 1);
      delay(tempo);
    }
    {
      Wire.beginTransmission(mux6);
      Wire.write(b);
      Wire.endTransmission();
      digitalWrite(13, 0);
      delay(tempo);
      digitalWrite(13, 1);
      delay(tempo);
    }

    {
      Wire.beginTransmission(mux7);
      Wire.write(b);
      Wire.endTransmission();
      digitalWrite(13, 0);
      delay(tempo);
      digitalWrite(13, 1);
      delay(tempo);
    }

    {
      Wire.beginTransmission(mux8);
      Wire.write(b);
      Wire.endTransmission();
      digitalWrite(13, 0);
      delay(tempo);
      digitalWrite(13, 1);
      delay(tempo);
    }
    Serial.print(b);
    Serial.print(" = ");
    Serial.println(b, BIN);
    delay (tempo);
  }
}















