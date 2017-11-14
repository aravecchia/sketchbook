#include <Arduino.h>
/*
Desenvolvido por Alexandre Aravecchia
aravecchia@gmail.com
www.aravecchia.weebly.com
*/
/*
O Fantastico, Incrivel e Ultra-Revolucionario
 ESCOVADOR DE BITS
 */

// Define uma variavel para cada pino.
boolean a=2;
boolean b=3;
boolean c=4;
boolean d=5;
boolean e=6;
boolean f=7;
boolean g=8;
boolean h=9;
boolean i=10;
boolean j=11;
boolean k=12;
boolean l=13;
boolean m=14;
boolean n=15;
boolean o=16;
boolean p=17;
boolean q=18;
boolean r=19;
boolean s=20;
boolean t=21;
boolean u=22;
boolean v=23;
boolean w=24;
boolean x=25;

// Define uma variavel para a leitura digital de cada pino
boolean A;
boolean B;
boolean C;
boolean D;
boolean E;
boolean F;
boolean G;
boolean H;
boolean I;
boolean J;
boolean K;
boolean L;
boolean M;
boolean N;
boolean O;
boolean P;
boolean Q;
boolean R;
boolean S;
boolean T;
boolean U;
boolean V;
boolean W;
boolean X;

boolean chave=26;

void setup() 
{
  for (int pino=2;pino<18; pino++)
  {
    pinMode(pino, INPUT);
  }
  for (int pino=18;pino<26; pino++)
  {
    pinMode(pino, OUTPUT);
  }

  pinMode(chave, INPUT);

  Serial.begin(9600);
}

void loop()
{
  boolean Pino[16]={
    a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p            }; // insere os pinos de leitura numa matriz

  boolean State[16]={
    A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P            }; // insere as variaveis de leitura de estado de cada pino numa matriz
  for (boolean z=0; z<16; z++)
  {
    State[z]=digitalRead(Pino[z]);
  }


  boolean Led[8]={
    Q, R, S, T, U, V, W, X          }; // insere as variaveis de escrita, referentes aos Leds, numa matriz

  if (digitalRead(chave)==0)
  {
    for (boolean ponto=0; ponto<8; ponto++)
    {
      int Estado=(State[ponto] && State[ponto+8]);
      digitalWrite(Led[ponto], Estado);
      Serial.print(State[ponto]);
      Serial.print(" && ");
      Serial.print(State[ponto+8]);
      Serial.print(" = ");
      Serial.println(State[ponto] && State[ponto+8]);
    }
  }

  else
  {
    for (boolean ponto=0; ponto<8; ponto++)
    {
      int Estado=(State[ponto] || State[ponto+8]);
      digitalWrite(Led[ponto], Estado);
      Serial.print(State[ponto]);
      Serial.print(" || ");
      Serial.print(State[ponto+8]);
      Serial.print(" = ");
      Serial.println(State[ponto] || State[ponto+8]);
    }
  }
}








