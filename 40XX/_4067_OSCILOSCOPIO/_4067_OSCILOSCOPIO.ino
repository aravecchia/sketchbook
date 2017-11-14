#include <Arduino.h>
/*Desenvolvido por Alexandre Aravecchia
  Projetista, desenvolvedor, programador
 aravecchia@gmail.com
 www.aravecchia.weebly.com
 */
//pinos do multiplexador de escrita
int w0 = 8;
int w1 = 7;
int w2 = 3;
int w3 = 2;
int Wcomum = A1;
//pinos do multiplexador de leitura
int r0 = 11;
int r1 = 12;
int r2 = 9;
int r3 = 10;
int Rcomum = A0;

int led;

int T = 200;
// tempo que o pino do mux fica ON

// Matriz de 16 linhas com 4 itens cada
// Cada linha da matriz eh um pino do multiplexador
// Cada conjunto de 4 itens eh o endereco do pino
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
  //Define os modos de cada pino
  pinMode(w0, OUTPUT);
  pinMode(w1, OUTPUT);
  pinMode(w2, OUTPUT);
  pinMode(w3, OUTPUT);
  pinMode(r0, OUTPUT);
  pinMode(r1, OUTPUT);
  pinMode(r2, OUTPUT);
  pinMode(r3, OUTPUT);
  // Todos os pinos digitais estao em modo de saida porque todos
  // escrevem um conjunto de 4 binarios, q fazem o enderecamento
  // do pino ativo no multiplexador
  pinMode(Wcomum, OUTPUT);
  // Rcomum equivale ao pino analogico do multiplexador de saida
  pinMode(Rcomum, INPUT);
  // Rcomum equivale ao pino analogico do multiplexador de entrada
  digitalWrite(w0, LOW);
  digitalWrite(w1, LOW);
  digitalWrite(w2, LOW);
  digitalWrite(w3, LOW);
  digitalWrite(r0, LOW);
  digitalWrite(r1, LOW);
  digitalWrite(r2, LOW);
  digitalWrite(r3, LOW);
  // analogWrite(Wcomum, 0);
  //Coloca todos os pinos em LOW
  Serial.begin(9600);
}

void loop()
{
  {
    for(int i = 0; i<16; i++)
    {
      int sensor = analogRead(Rcomum);
      float led = sensor / 1023.0;
      //map(sensor, 0, 1023, 0, 100);
      acender(matriz[i]);
      escreve(i);
      Serial.print(" - Leitura: ");  
      Serial.print(sensor);
      Serial.print(" - ");
      Serial.println(led);
      delay(T);              // tempo que o pino dfica ON
      analogWrite(Wcomum, led);    // escreve o valor do LDR no LED
    }
  }
}


void acender( int m[] )
{
  digitalWrite(w0, m[0]);
  digitalWrite(w1, m[1]);
  digitalWrite(w2, m[2]);
  digitalWrite(w3, m[3]);
  digitalWrite(r0, m[0]);
  digitalWrite(r1, m[1]);
  digitalWrite(r2, m[2]);
  digitalWrite(r3, m[3]);
}

void escreve(int seletor)
{
  Serial.print("Led ativo: ");
  Serial.print(seletor);
  Serial.print(" - ");
  Serial.print(matriz[seletor][0]);
  Serial.print(matriz[seletor][1]);
  Serial.print(matriz[seletor][2]);
  Serial.print(matriz[seletor][3]);  
}











