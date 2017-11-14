
#include <Arduino.h>
#include <math.h>
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
// define os pinos de latch, data e clock do 74HC595 que controla o display da Celsius do ambiente
// ver datasheet {boa sorte!)

int botao = 5;
int led=13;

// Celsius-base, notem que estou trabalhando com 10x a Celsius real
// para facilitar a codificacao dos displays de 7 segmentos, que so trabalha com numeros binarios e inteiros

byte sensor = 6;
byte trimpot = A0;
byte digito[10]= {
  B11111100,B01100000,B11011010,B11110010,B01100110,B10110110,B10111110,B11100000,B11111110,B11110110};
// matrizes de 10 termos, cada um define um Byte diferente para cada
// digito de 0 a 9 no display, ou seja, liga um conjunto especifico de portas do 74hc595
// que acende um conjunto especifico de LEDs.


//int BETA =  3870; //Calibrar este valor utilizando um termometro de precisao externo como comparacao
int BETA = 3870;
float Ro = 90000; //Resistencia tpica de um termistor de 100k
float To = 25 + 273; //Transforma Celsius de referencia do Termistor de Celsius para Kelvin

float pico; //Tempo
float vale;
float Periodo;
float Frequencia;

float Kelvin;
float Celsius = Kelvin - 273;


float R; // Resistencia do Termistor
float R2 = 10000; //Segundo resistor do NE-222
float C1 = 1; // Capacitor principal em MICROFARADAY;

void setup()
{
  Serial.begin(9600);
  pinMode(sensor, INPUT_PULLUP);
  pinMode(trimpot, INPUT);
  pinMode(botao, INPUT);
  pinMode(led, OUTPUT);
  pinMode(LATCH, OUTPUT);
  pinMode(CLK, OUTPUT);
  pinMode(DATA, OUTPUT);

}

void loop()
{
    delay(t);

  pico = pulseIn(sensor, HIGH);
  vale = pulseIn(sensor, LOW);
  Periodo = (pico + vale);
  Frequencia = 1000000 / Periodo;

  // Calcula a resistencia do termistor ligado ao NE-555
  R = ((1.44 * Periodo) / C1) - (2 * R2);

  // Calcula a Celsius pela equacao reduzida de Steinhart-Hart
  //para sensores NTC
  Kelvin = 1 / ( (1 / To) + ((log(R / Ro) / BETA)));

  // Converte Kelvin para Celsius e multiuplica por 10 para facilitar a leitura pelo display
  Celsius = 10*(Kelvin - 273);
 // int leitura = analogRead(sensor);
  int regulagem = analogRead(trimpot);

  int tempbase=map(regulagem, 0, 1023, 999,0); 
  tempbase = tempbase/10;
  tempbase = 10*tempbase;

  boolean State = digitalRead(botao);

  int z = Celsius/100;
  int y = (Celsius - 100*z)/10;
  int x = Celsius - 100*z - 10*y;

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
  Serial.print(Celsius);
  Serial.print(" - ");
  Serial.print(" Botao: ");
  Serial.print(State);
  Serial.print(" - Led: ");
  if (Celsius<tempbase-3)
  {
    Serial.println("HIGH");
    digitalWrite(led, HIGH);
  }
  else
  {
    Serial.println("LOW");
    digitalWrite(led,LOW);  
  }
}




















