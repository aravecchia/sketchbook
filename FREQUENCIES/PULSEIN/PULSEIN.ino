#include <Arduino.h>

int pin = 2;

unsigned long pico;
unsigned long vale;
unsigned long periodo;

void setup()

{
  pinMode(pin, INPUT);
  Serial.begin(9600);
}

void loop()
{
  pico = pulseIn(pin, HIGH);
  vale = pulseIn(pin, LOW);
  periodo = pico + vale;
  Serial.print(pico);
  Serial.print(" + ");
  Serial.print(vale);
  Serial.print(" = ");
  Serial.println(periodo);
}

