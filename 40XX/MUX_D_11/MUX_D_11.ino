#include <Arduino.h>

#include <Wire.h>

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
    Serial.begin(9600);
}

void loop()
{
  int tempo = 100;
  int x;
  int numero = 1;
  {
    for (x = 0; x <= 255; x++)
    {
      Wire.beginTransmission(mux1);
      Wire.write(x);
      Wire.endTransmission(x);
      Serial.print("mux");
      Serial.print(numero);
      Serial.print(" = ");
      Serial.print(x);
      Serial.print(" = ");
      Serial.println(x, BIN);
      delay(tempo);
      numero++;
    }
    {
      Wire.beginTransmission(mux2);
      Wire.write(x);
      Wire.endTransmission(x);
      Serial.print("mux");
      Serial.print(numero);
      Serial.print(" = ");
      Serial.print(x);
      Serial.print(" = ");
      Serial.println(x, BIN);
      delay(tempo);
      numero++;
    }
        {
      Wire.beginTransmission(mux3);
      Wire.write(x);
      Wire.endTransmission(x);
      Serial.print("mux");
      Serial.print(numero);
      Serial.print(" = ");
      Serial.print(x);
      Serial.print(" = ");
      Serial.println(x, BIN);
      delay(tempo);
      numero++;
    }
        {
      Wire.beginTransmission(mux4);
      Wire.write(x);
      Wire.endTransmission(x);
      Serial.print("mux");
      Serial.print(numero);
      Serial.print(" = ");
      Serial.print(x);
      Serial.print(" = ");
      Serial.println(x, BIN);
      delay(tempo);
      numero++;
    }
        {
      Wire.beginTransmission(mux5);
      Wire.write(x);
      Wire.endTransmission(x);
      Serial.print("mux");
      Serial.print(numero);
      Serial.print(" = ");
      Serial.print(x);
      Serial.print(" = ");
      Serial.println(x, BIN);
      delay(tempo);
      numero++;
    }
        {
      Wire.beginTransmission(mux6);
      Wire.write(x);
      Wire.endTransmission(x);
      Serial.print("mux");
      Serial.print(numero);
      Serial.print(" = ");
      Serial.print(x);
      Serial.print(" = ");
      Serial.println(x, BIN);
      delay(tempo);
      numero++;
    }
        {
      Wire.beginTransmission(mux7);
      Wire.write(x);
      Wire.endTransmission(x);
      Serial.print("mux");
      Serial.print(numero);
      Serial.print(" = ");
      Serial.print(x);
      Serial.print(" = ");
      Serial.println(x, BIN);
      delay(tempo);
      numero++;
    }
  }
      {
      Wire.beginTransmission(mux8);
      Wire.write(x);
      Wire.endTransmission(x);
      Serial.print("mux");
      Serial.print(numero);
      Serial.print(" = ");
      Serial.print(x);
      Serial.print(" = ");
      Serial.println(x, BIN);
      delay(tempo);
      numero++;
    }
}

