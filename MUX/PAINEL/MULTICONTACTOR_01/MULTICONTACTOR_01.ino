#include <Arduino.h>

/*
Desenvolvido por Alexandre Aravecchia
aravecchia@gmail.com
www.aravecchia.weebly.com
*/
// Apoio: Laboratorio de Garagem - labdegaragem.com
// Agradecimentos a valiosa ajuda dos amigos:
// Almir, Jonatas, Jucelei, Rogerio, Marcelo, Renyer, fredsant, OraculoX, Wiechert, Rui Viana, Celso Eiji Ito
// alem da tremenda paciencia da minha esposa pra me aguentar falando nisso dia e noite :D

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

int AnalogPin1 = A0; //define o pino de leitura do CD-4067
int AnalogPin2 = A1; //define o pino de leitura do botao de regulagem

// A select determina qual pino do Cd-4067 esta ativado
int select[16][4] = {
  {
    0,0,0,0                                              }
  ,
  {
    0,0,0,1                                              }
  ,
  {
    0,0,1,0                                              }
  ,
  {
    0,0,1,1                                              }
  ,
  {
    0,1,0,0                                              }
  ,
  {
    0,1,0,1                                              }
  ,
  {
    0,1,1,0                                              }
  ,
  {
    0,1,1,1                                              }
  ,
  {
    1,0,0,0                                              }
  ,
  {
    1,0,0,1                                              }
  ,
  {
    1,0,1,0                                              }
  ,
  {
    1,0,1,1                                              }
  ,
  {
    1,1,0,0                                              }
  ,
  {
    1,1,0,1                                              }
  ,
  {
    1,1,1,0                                              }
  ,
  {
    1,1,1,1                                              }
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
  int t=10;
  // Tempo de delay.
  int byte1=0; //este valor 0-1 eh alocado em x, que eh jogado num unico shiftOut, acendendo somente a lampada correspondente ao sensor.
  int byte2=0;
  boolean relayState;

  for(int pino = 0; pino<16; pino++)
  {
    seletor(select[pino]);
//    leitura(pino);
    Serial.print("LDR: ");
    Serial.print(pino+1);
    Serial.print(" - ");
    Serial.print(select[pino][0]);
    Serial.print(select[pino][1]);
    Serial.print(select[pino][2]);
    Serial.print(select[pino][3]);  
    Serial.print(": "); 

    //----->>>>>>leitura do sensor aqui
    int sensor = map(analogRead(AnalogPin1), 0, 1023, 0, 15);  
    int regulador = map(analogRead(AnalogPin2), 0, 1023, 0, 15); 
    if (pino<8)
    
    //AJEITE ESSES IF-ELSES USANDO && NAS CONDICOES. TA UMA MERDA!
    {
      if (sensor>regulador)
      {
        relayState=1;
        byte1=(relayState<<pino)+byte1;
      }
      else
      {
        relayState=0;
        byte1=(relayState<<pino)+byte1;
      }
    }
    else
    {
      if (sensor>regulador)
      {
        relayState=1;
        byte2=(relayState<<(pino-8))+byte2;
      }
      else
      {
        relayState=0;
        byte2=(relayState<<(pino-8))+byte2;
      }
    }
    // Escreve na serial o resultado e confere o codigo:
    Serial.print("sensor ");
    Serial.print(pino+1);
    Serial.print(" = ");
    Serial.print(analogRead(AnalogPin1));
    Serial.print(" = ");
    Serial.print(sensor);
      Serial.print(" - ");
  Serial.println(analogRead(AnalogPin2));

  }
  digitalWrite(LATCH, LOW);
  shiftOut(DATA, CLOCK, MSBFIRST, byte1);
  shiftOut(DATA, CLOCK, MSBFIRST, byte2);
  // Levanta o muro LATCH, fecha a transmissao (represam os bits)
  digitalWrite(LATCH, HIGH);
  Serial.print("Relays: ");
  Serial.print(byte1, BIN);
  Serial.print(" - ");
  Serial.println(byte2, BIN);
  byte1=0;
  byte2=0;
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
  Serial.print(" - ");
  Serial.print(select[pino][0]);
  Serial.print(select[pino][1]);
  Serial.print(select[pino][2]);
  Serial.print(select[pino][3]);  
  Serial.print(" : ");  
}


