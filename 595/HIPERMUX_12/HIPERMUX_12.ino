#include <Arduino.h>

// Laboratorio J011y R0g3r
// ta na hora de pensar num nome serio pra esse Laboratorio :D
// Apoio: Laboratorio de Garagem - labdegaragem.com
// Agradecimentos a valiosa ajuda dos amigos:
// Almir, Jonatas, Jucelei, Rogerio, Marcelo, Renyer, fredsant, (o cara daquele site de mecatronica, esqueci os dois nomes) (esqueci alguem???)
// alem da tremenda paciencia da minha esposa pra me aguentar falando nisso dia e noite :D

int LATCH = 2; 
int DATA = 3;
int CLOCK = 4;
int t=500;
// define os pinos de latch, data e clock do 74HC595 que controla o display da temperatura do ambiente
int a = 0;
int b = 0;
int c = 0;
int d = 0;
int e = 0;
int f = 0;
int g = 0;
int h = 0;

int matriz[]={
  a, b, c, d, e, f, g, h};

void setup()
{
  Serial.begin(9600);
  pinMode(LATCH, OUTPUT);
  pinMode(CLOCK, OUTPUT);
  pinMode(DATA, OUTPUT);
}

void loop()
{
  digitalWrite(LATCH, HIGH);
  for(int x=0; x<8; x++)
  {
    shiftOut(DATA, CLOCK, MSBFIRST, matriz[x]); //primeiro CI recebe 1 Byte 
  }
  digitalWrite(LATCH, LOW);
  delay(t);

  for (int x=1; x<8; x++)
  {
          matriz[x] = (!matriz[x])<<x;
    digitalWrite(LATCH, HIGH);
    for (int y=1; y<8; y++)
    {
      shiftOut(DATA, CLOCK, MSBFIRST, matriz[x]); 
    }
    digitalWrite(LATCH, LOW);
        delay(t);
  }
}



/*
1. zera tudo
 2. 
 
 
 */










