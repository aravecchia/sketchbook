#include <Arduino.h>

/* Nao se esqueca de corrigir o codigo: do jeito que esta, o 595 vai mudar o estado de
todos os relays a cada LDR que o 4067 ler. Ou seja, a cada LDE ele liga a quantidade de relays
correspondente aquela iluminacao.
Tem que criar uma regra para que cada LDR mude o estado de cada rele especifico, quando
a luminosidade atingir um limite pre-determinado.
Quando terminar, diminua o delay pra 1 ms.
Que a Forća esteja com voce.
*/
int led = 13;
int LATCH = 2;
int DATA = 3;
int CLOCK = 4; 

int s0 = 5;
int s1 = 6;
int s2 = 7;
int s3 = 8;

int AnPin = A0;

int sensor;

int t=500;

int matriz[16][4] = {
  {
    0,0,0,0                              }
  ,
  {
    0,0,0,1                              }
  ,
  {
    0,0,1,0                              }
  ,
  {
    0,0,1,1                              }
  ,
  {
    0,1,0,0                              }
  ,
  {
    0,1,0,1                              }
  ,
  {
    0,1,1,0                              }
  ,
  {
    0,1,1,1                              }
  ,
  {
    1,0,0,0                              }
  ,
  {
    1,0,0,1                              }
  ,
  {
    1,0,1,0                              }
  ,
  {
    1,0,1,1                              }
  ,
  {
    1,1,0,0                              }
  ,
  {
    1,1,0,1                              }
  ,
  {
    1,1,1,0                              }
  ,
  {
    1,1,1,1                              }
  ,
};

void setup()
{
  Serial.begin(9600);
  pinMode(led, OUTPUT);
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
   digitalWrite(led, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(t);               // wait for a second
  digitalWrite(led, LOW);    // turn the LED off by making the voltage LOW
  delay(t);       
  int x = 1;

  for(int i = 0; i<16; i++)
  {
    seletor(matriz[i]);
    leitura(i);

    //----->>>>>>leitura do sensor aqui
    sensor = map(analogRead(AnPin), 0, 1023, 0,16);  

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

    // Escreve na serial o resultado e confere o codigo:
    Serial.print("sensor");
    Serial.print(i);
    Serial.print(" = ");
    Serial.print(analogRead(AnPin));
    Serial.print(" = ");
    Serial.println(sensor);
    // Levanta o muro LATCH, fecha a transmissao (represam os bits)
    digitalWrite(LATCH, HIGH);
    delay(t);
  }
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
  Serial.print("Ldr ativo: ");
  Serial.print(pino);
  Serial.print(" - ");
  Serial.print(matriz[pino][0]);
  Serial.print(matriz[pino][1]);
  Serial.print(matriz[pino][2]);
  Serial.print(matriz[pino][3]);  
  Serial.print(" - Leitura: ");  
}





