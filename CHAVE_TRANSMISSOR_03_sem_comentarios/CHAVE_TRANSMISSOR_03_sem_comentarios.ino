#include <Arduino.h>

// Codigo para gerar um contador de 4 bits, usando vetores.

//Declaracao para os pinos A, B, C e D (leds)
int A=2;
int B=3;
int C=4;
int D=5;

int t = 1; //Delay


// Matriz onde serao alocados os enderecos dos pinos.
int ledPin[] = {
  A, B, C, D}; 


// Matriz onde estao alocados os bits a serem enviados para cada pino.
// O primeiro bit deve ir para o led A, o segundo para B e assim por diante.
int matriz[16][4] = {  
  {
    0,0,0,0                          }
  , {
    0,0,0,1                          }
  , {
    0,0,1,0                          }
  , {
    0,0,1,1                          }
  , {
    0,1,0,0                          }
  , {
    0,1,0,1                          }
  , {
    0,1,1,0                          }
  , {
    0,1,1,1                          }
  , {
    1,0,0,0                          }
  , {
    1,0,0,1                          }
  , {
    1,0,1,0                          }
  , {
    1,0,1,1                          }
  , {
    1,1,0,0                          }
  , {
    1,1,0,1                          }
  , {
    1,1,1,0                          }
  , {
    1,1,1,1                          }
};


void setup ()
{
  Serial.begin(9600);
  // Declara A, B, C e D como saidas. 
  for (int pino=0; pino<4; pino++)
  {
    pinMode(ledPin[pino], OUTPUT);
  }
}

void loop ()
{

  for (int line=0; line<16; line++)  // Para a linha 0 da matriz de bits ate a linha 15...
  {
    for (int i=0; i<4; i++)      //Comecando pela linha 0, para o pino 0 ao 3...
    {
      digitalWrite(ledPin[i], matriz[line][i]); //Escreve no pino A o bit 0, linha 0 da matriz de bits...
      //o pino i sobe 1 posicao (pino B), bit 1, linha 0 da matriz...
      //o pino i sobe 1 posicao (pino C), bit 2, linha 0 da matriz...
      //o pino i sobe 1 posicao (pino D), bit 3, linha 0 da matriz.
      //Fim da contagem, line sobe uma posicao (linha 1) e repete a contagem.
      Serial.print("ledPin ");
      Serial.print(i);
      Serial.print(" - matriz ");
      Serial.print(i);
      Serial.print("-");
      Serial.print(line);
      Serial.print("-");
      Serial.println(matriz[line][i]);
    }
    delay(t);
  }
}








