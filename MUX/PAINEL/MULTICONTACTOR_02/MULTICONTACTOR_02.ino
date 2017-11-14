#include <Arduino.h>


// Apoio: Laboratorio de Garagem - labdegaragem.com
// Agradecimentos a valiosa ajuda dos amigos:
// Almir, Jonatas, Jucelei, Rogerio, Marcelo, Renyer, fredsant, OraculoX, Wiechert, Rui Viana, Celso Eiji Ito
// alem da tremenda paciencia da minha esposa pra me aguentar falando nisso dia e noite :D

int t=10;
// Tempo de delay.

int LATCH = 6; 
int DATA = 7;
int CLOCK = 8;
// define os pinos de latch, data e clock do 74HC595 que controlam o display da temperatura do ambiente
int s0 = 9;
int s1 = 10;
int s2 = 11;
int s3 = 12;
//define os pinos de controle do CD-4067 - checar ordem dos pinos definidos no shield
//no esquecer de verificar o jumper (se ele define entrada ou saida em A0)

int LDR = A0; //define o pino de leitura do CD-4067
int REGULADOR = A1; //define o pino de leitura do botao de regulagem

// A select determina qual pino do Cd-4067 esta ativado
int select[16][4] = {
  {
    0,0,0,0                                                        }
  ,
  {
    0,0,0,1                                                        }
  ,
  {
    0,0,1,0                                                        }
  ,
  {
    0,0,1,1                                                        }
  ,
  {
    0,1,0,0                                                        }
  ,
  {
    0,1,0,1                                                        }
  ,
  {
    0,1,1,0                                                        }
  ,
  {
    0,1,1,1                                                        }
  ,
  {
    1,0,0,0                                                        }
  ,
  {
    1,0,0,1                                                        }
  ,
  {
    1,0,1,0                                                        }
  ,
  {
    1,0,1,1                                                        }
  ,
  {
    1,1,0,0                                                        }
  ,
  {
    1,1,0,1                                                        }
  ,
  {
    1,1,1,0                                                        }
  ,
  {
    1,1,1,1                                                        }
  ,
};

void setup()
{
  Serial.begin(9600);
  pinMode(LATCH, OUTPUT);
  pinMode(CLOCK, OUTPUT);
  pinMode(DATA, OUTPUT);
  // Define LATCH, DATA e CLOCK como pinos de saida

  pinMode(A0, INPUT);
  pinMode(A1, INPUT);

  // Define os pinos de controle do 4067 como saida e coloca todos em estado LOW.
  pinMode(s0, OUTPUT); 
  pinMode(s1, OUTPUT); 
  pinMode(s2, OUTPUT); 
  pinMode(s3, OUTPUT); 

  digitalWrite(s0, LOW);
  digitalWrite(s1, LOW);
  digitalWrite(s2, LOW);
  digitalWrite(s3, LOW);
}

void loop()
{
  byte byte1=0;
  byte byte2=0;

  boolean LEDState;

  for(int pino = 0; pino<16; pino++)
  {
    seletor(select[pino]);
    //    leitura(pino);
    Serial.print("LDR: ");
    Serial.print(pino+1);
    Serial.print(" - ");
    for (int x=0; x<4; x++)
    {
      Serial.print(select[pino][x]);
    } 
    Serial.print(": "); 

    //----->>>>>>leitura do sensor aqui
    int sensor = analogRead(LDR);  
    int regulador = analogRead(REGULADOR); 

    if (pino<8)
    {
      if (sensor>regulador)
      {
        LEDState=1;
        byte1=(LEDState<<pino)+byte1;
      }
      else
      {
        LEDState=0;
        byte1=(LEDState<<pino)+byte1;
      }
    }
    else
    {
      if (sensor>regulador)
      {
        LEDState=1;
        byte2=(LEDState<<(pino-8))+byte2;
      }
      else
      {
        LEDState=0;
        byte2=(LEDState<<(pino-8))+byte2;
      }
    }


    // Escreve na serial o resultado e confere o codigo:
    Serial.print("Luz = ");
    Serial.println(float(sensor)/float(regulador));

  }
  digitalWrite(LATCH, LOW);
  shiftOut(DATA, CLOCK, MSBFIRST, byte2);
  shiftOut(DATA, CLOCK, MSBFIRST, byte1);
  // Levanta o muro LATCH, fecha a transmissao (represam os bits)
  digitalWrite(LATCH, HIGH);
  Serial.print("Relays: ");
  Serial.print(byte1, BIN);
  Serial.print("-");
  Serial.println(byte2, BIN);
  delay(t);
}

void seletor( int m[] )
{
  digitalWrite(s0, m[0]);
  digitalWrite(s1, m[1]);
  digitalWrite(s2, m[2]);
  digitalWrite(s3, m[3]);   
}

void leitura(int pino)
{
  Serial.print("LDR ");
  Serial.print(pino+1);
  Serial.print(": ");
  for (int x=0; x<4; x++)
  {
    Serial.print(select[pino][x]);
  } 
  Serial.print(" - ");  
}







