/*
Desenvolvido por Alexandre Aravecchia
aravecchia@gmail.com
www.aravecchia.weebly.com
*/
#include <Arduino.h>

int LATCH = 2; 
int DATA = 3;
int CLOCK = 4;

//Mux control pins
int s0 = 5;
int s1 = 6;
int s2 = 7;
int s3 = 8;

// Declara o pino de leitura analogica
int AnPin = A0;

// Um led para conferir o fim do processo
int led;
int ldr;

// O delay entre uma leitura e outra
int T=100;

int matriz[16][4] = {
  {
    0,0,0,0                      }
  ,
  {
    0,0,0,1                      }
  ,
  {
    0,0,1,0                      }
  ,
  {
    0,0,1,1                      }
  ,
  {
    0,1,0,0                      }
  ,
  {
    0,1,0,1                      }
  ,
  {
    0,1,1,0                      }
  ,
  {
    0,1,1,1                      }
  ,
  {
    1,0,0,0                      }
  ,
  {
    1,0,0,1                      }
  ,
  {
    1,0,1,0                      }
  ,
  {
    1,0,1,1                      }
  ,
  {
    1,1,0,0                      }
  ,
  {
    1,1,0,1                      }
  ,
  {
    1,1,1,0                      }
  ,
  {
    1,1,1,1                      }
  ,
};


void setup()
{
  // Inicia a comunicacao serial
  Serial.begin(9600);

  // Define os modos de cada pino como entrada ou saida
  pinMode(LATCH, OUTPUT);
  pinMode(CLOCK, OUTPUT);
  pinMode(DATA, OUTPUT);

  pinMode(AnPin, INPUT);

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
  int x= 0xb0000000000000001;
  for(int i = 0; i<16; i++)
  {
    seletor(matriz[i]);
    leitura(i);

    //----->>>>>>leitura do sensor aqui
    int sensor = map(analogRead(AnPin), 0, 1023, 0,16);  

    digitalWrite(LATCH, LOW);


    if (sensor==0)
    {
      // Envia 2 Bytes para o DATA, um para cada HC-595, desligando todos os LEDs.
      shiftOut(DATA, CLOCK, MSBFIRST, 0);
      shiftOut(DATA, CLOCK, MSBFIRST, 0);
    }

    else
    {
      // Como estamos usando MSBFIRST, mandamos o primeiro Byte para o ultimo CI:
      shiftOut(DATA, CLOCK, MSBFIRST, (x<<(sensor-8))-1);

      // E o ultimo Byte para o mestre:
      shiftOut(DATA, CLOCK, MSBFIRST, (x<<sensor)-1);
    }
    // Levanta o muro LATCH, fecha a transmissao (represam os bits)
    digitalWrite(LATCH, HIGH);

    // Escreve na serial o resultado e confere o codigo:
    Serial.print("sensor = ");
    Serial.print(((x<<sensor-8)-1), BIN);
    Serial.print(" - "); 
    Serial.println(((x<<sensor)-1), BIN);


    digitalWrite(led, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(T);               // wait for a second
    digitalWrite(led, LOW);    // turn the LED off by making the voltage LOW
    delay(T);               // wait for a second
  }
}

void seletor( int m[] )
{
  digitalWrite(s0, m[0]);
  digitalWrite(s1, m[1]);
  digitalWrite(s2, m[2]);
  digitalWrite(s3, m[3]);   
}

void leitura(int ldr)
{
  Serial.print("Ldr ativo: ");
  Serial.print(ldr);
  Serial.print(" - ");
  Serial.print(matriz[ldr][0]);
  Serial.print(matriz[ldr][1]);
  Serial.print(matriz[ldr][2]);
  Serial.print(matriz[ldr][3]);  
  Serial.print(" - Leitura: ");  
}










