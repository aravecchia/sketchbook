
#include <Arduino.h>

/*Desenvolvido por Alexandre Aravecchia
  Projetista, desenvolvedor, programador
 aravecchia@gmail.com
 www.aravecchia.weebly.com
 */
// Apoio:
//   Laboratorio de Garagem - www.labdegaragem.com
//   Labirito - www.labirito.com

int t=500;
int LATCH = 2; 
int DATA = 3;
int CLK = 4;
// define os pinos de latch, data e clock do 74HC595 que controla o display da temperatura do ambiente
// ver datasheet {boa sorte!)

int botao = 5;
int led=13;

// temperatura-base, notem que estou trabalhando com 10x a temperatura real
// para facilitar a codificacao dos displays de 7 segmentos, que so trabalha com numeros binarios e inteiros

byte sensor = A0;
byte trimpot = A1;
byte digito[10]= {
  B11111100,B01100000,B11011010,B11110010,B01100110,B10110110,B10111110,B11100000,B11111110,B11110110};


// matrizes de 10 termos, cada um define um Byte diferente para cada
// digito de 0 a 9 no display, ou seja, liga um conjunto especifico de portas do 74hc595
// que acende um conjunto especifico de LEDs.

void setup()
{
  Serial.begin(9600);
  pinMode(sensor, INPUT);
  pinMode(trimpot, INPUT);
  pinMode(botao, INPUT);
  pinMode(led, OUTPUT);
  pinMode(LATCH, OUTPUT);
  pinMode(CLK, OUTPUT);
  pinMode(DATA, OUTPUT);
}

void loop()
{
  int leitura = analogRead(sensor);
  int regulagem = analogRead(trimpot);

  int temperatura=map(leitura, 0, 1023, 999,0);
  int tempbase=map(regulagem, 0, 1023, 999,0); 
  tempbase = tempbase/10;
  tempbase = 10*tempbase;

  boolean State = digitalRead(botao);

  int z = temperatura/100;
  int y = (temperatura - 100*z)/10;
  int x = temperatura - 100*z - 10*y;

  int c = tempbase/100;
  int b = (tempbase - 100*c)/10;
  int a = tempbase - 100*c - 10*b;


  if(State == 0)
  {
    digitalWrite(LATCH, LOW);
    shiftOut(DATA, CLK, LSBFIRST, digito[x]); //primeiro CI recebe 1 Byte
    shiftOut(DATA, CLK, LSBFIRST, digito[y]+1);  //segundo CI recebe 1 Byte
    if (z==0)
    {
      shiftOut(DATA, CLK, LSBFIRST, 0); //terceiro CI recebe 1 Byte
    }
    else
    {
      shiftOut(DATA, CLK, LSBFIRST, digito[z]); //terceiro CI recebe 1 Byte
    }
    digitalWrite(LATCH, HIGH);
  }

  else
  {
    digitalWrite(LATCH, LOW);
    shiftOut(DATA, CLK, LSBFIRST, digito[a]); //primeiro CI recebe 1 Byte
    shiftOut(DATA, CLK, LSBFIRST, digito[b]+1);  //segundo CI recebe 1 Byte
    shiftOut(DATA, CLK, LSBFIRST, digito[c]); //terceiro CI recebe 1 Byte
    digitalWrite(LATCH, HIGH);
  }

  Serial.print("Base: ");
  Serial.print(tempbase);
  Serial.print(" - Temp: ");
  Serial.print(temperatura);
  Serial.print(" - ");
  Serial.print(" Botao: ");
  Serial.print(State);
  Serial.print(" - Led: ");
  if (temperatura<tempbase-3)
  {
    Serial.println("HIGH");
    digitalWrite(led, HIGH);
  }
  else
  {
    Serial.println("LOW");
    digitalWrite(led,LOW);  
  }
  delay(t);
}



















