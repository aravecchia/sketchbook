#include <Arduino.h>
/*Desenvolvido por Alexandre Aravecchia
  Projetista, desenvolvedor, programador
 aravecchia@gmail.com
 www.aravecchia.weebly.com
 */
//pinos do multiplexador de leitura
int r1 = 2;
int r2 = 3;
int r3 = 4;
int leitura;
int t = 100;
// tempo que o pino do mux fica ON

// Matriz de 16 linhas com 4 itens cada
// Cada linha da matriz eh um pino do multiplexador
// Cada conjunto de 4 itens eh o endereco do pino
int matriz[8][3] = {
  {
    0, 0, 0
  }
  ,
  {
    0, 0, 1
  }
  ,
  {
    0, 1, 0
  }
  ,
  {
    0, 1, 1
  }
  ,
  {
    1, 0, 0
  }
  ,
  {
    1, 0, 1
  }
  ,
  {
    1, 1, 0
  }
  ,
  {
    1, 1, 1
  }
};
int pinos[3] = {r1, r2, r3};

void setup()
{
  //Define os modos de cada pino
  pinMode(r1, OUTPUT);
  pinMode(r2, OUTPUT);
  pinMode(r3, OUTPUT);


  // Todos os pinos digitais estao em modo de saida porque todos
  // escrevem um conjunto de 4 binarios, q fazem o enderecamento
  // do pino ativo no multiplexador
  pinMode(A0, INPUT);

  //Coloca todos os pinos em LOW
  Serial.begin(9600);
}

void loop()
{
  for (int x = 0; x < 8; x++)
  {
    for (int y = 0; y < 3; y++)
    {
      digitalWrite(pinos[y], matriz[y][x]);
    }
    leitura = digitalRead(A0);
    Serial.print(leitura);
  }
      Serial.println("");
  delay(t);
}

