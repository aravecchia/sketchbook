/*
Desenvolvido por Alexandre Aravecchia
aravecchia@gmail.com
www.aravecchia.weebly.com
*/

#include <Arduino.h>

int sensor = A0;

int Vin = 5;
int Vout;
int R1 = 1000;
int R2;

int botao = 8;
int estado;
int leitura;

int corrente;

int t = 100;

void setup()
{
  pinMode(sensor, INPUT);
  pinMode(botao, INPUT);
  Serial.begin(9600);

}

void loop()
{
  estado = digitalRead(botao);
    leitura = analogRead(sensor);
    Vout = map(leitura, 0, 1023, 0, Vin);
    R2 = (R1 * Vout) / (Vin - Vout);
      if (estado == 0)
  {
    Serial.print("R2 = ");
    Serial.print(R2);
    Serial.println("Ohm - Subindo...");
    delay(t);
  }
  else
   {
    Serial.print("R2 = ");
    Serial.print(R2);
    Serial.println("Ohm - FUSÃO DO ESTANHO!!!");
    delay(300t);
  }
}
