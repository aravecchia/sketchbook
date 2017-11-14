#include <Arduino.h>
/*Desenvolvido por Alexandre Aravecchia
  Projetista, desenvolvedor, programador
 aravecchia@gmail.com
 www.aravecchia.weebly.com
 */
//pinos do multiplexador de leitura
int r0 = 8;
int r1 = 7;
int r2 = 3;
int r3 = 2;
int Rcomum = A0;
//pinos do multiplexador de escrita
int s0 = 11;
int s1 = 12;
int s2 = 9;
int s3 = 10;
int Scomum = A1;

int led;
int controle = 13;
int T = 100;
// tempo que o pino do mux fica ON

// Matriz de 16 linhas com 4 itens cada
// Cada linha da matriz eh um pino do multiplexador
// Cada conjunto de 4 itens eh o endereco do pino
int matriz[16][4] = {
  {
    0,0,0,0            }
  ,
  {
    0,0,0,1            }
  ,
  {
    0,0,1,0            }
  ,
  {
    0,0,1,1            }
  ,
  {
    0,1,0,0            }
  ,
  {
    0,1,0,1            }
  ,
  {
    0,1,1,0            }
  ,
  {
    0,1,1,1            }
  ,
  {
    1,0,0,0            }
  ,
  {
    1,0,0,1            }
  ,
  {
    1,0,1,0            }
  ,
  {
    1,0,1,1            }
  ,
  {
    1,1,0,0            }
  ,
  {
    1,1,0,1            }
  ,
  {
    1,1,1,0            }
  ,
  {
    1,1,1,1            }
  ,
};


void setup()
{
  //Define os modos de cada pino
  pinMode(r0, OUTPUT);
  pinMode(r1, OUTPUT);
  pinMode(r2, OUTPUT);
  pinMode(r3, OUTPUT);
  pinMode(s0, OUTPUT);
  pinMode(s1, OUTPUT);
  pinMode(s2, OUTPUT);
  pinMode(s3, OUTPUT);
  // Todos os pinos digitais estao em modo de saida porque todos
  // escrevem um conjunto de 4 binarios, q fazem o enderecamento
  // do pino ativo no multiplexador
  pinMode(Rcomum, OUTPUT);
  // Rcomum equivale ao pino analogico do multiplexador de saida
  pinMode(Scomum, INPUT);
  // Rcomum equivale ao pino analogico do multiplexador de entrada
  pinMode(controle, INPUT);
  digitalWrite(r0, LOW);
  digitalWrite(r1, LOW);
  digitalWrite(r2, LOW);
  digitalWrite(r3, LOW);
  digitalWrite(s0, LOW);
  digitalWrite(s1, LOW);
  digitalWrite(s2, LOW);
  digitalWrite(s3, LOW);
  digitalWrite(Rcomum, LOW);
  digitalWrite(Scomum, LOW);
  //Coloca todos os pinos em LOW
  Serial.begin(9600);
}

void loop()
{
  {
    for(int i = 0; i<16; i++)
    {
      acender(matriz[i]);
      escreve(i);
      Serial.println(analogRead(Scomum));
      delay(T);              // tempo que o pino dfica ON                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                             );
      analogWrite(Rcomum, (map((analogRead(Scomum)), 0, 1023, 0, 255)));    // escreve o valor do LDR no LED
    }
      digitalWrite(controle, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);               // wait for a second
  digitalWrite(controle, LOW);    // turn the LED off by making the voltage LOW
  delay(1000);               // wait for a second
  }
}


void acender( int m[] )
{
  digitalWrite(r0, m[0]);
  digitalWrite(r1, m[1]);
  digitalWrite(r2, m[2]);
  digitalWrite(r3, m[3]);
  digitalWrite(s0, m[0]);
  digitalWrite(s1, m[1]);
  digitalWrite(s2, m[2]);
  digitalWrite(s3, m[3]);
}

void escreve(int led)
{
  Serial.print("Led ativo: ");
 Serial.print(led);
   Serial.print(" - ");
  Serial.print(matriz[led][0]);
  Serial.print(matriz[led][1]);
  Serial.print(matriz[led][2]);
  Serial.print(matriz[led][3]);  
   Serial.print(" - Leitura: ");  
}






