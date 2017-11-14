
#include <Arduino.h>
#include <math.h>
#include <VirtualWire.h>
//CYBEROHM Robotics
// Apoio:
//   Laboratorio de Garagem - www.labdegaragem.com
//   Labirito - www.labirito.com

int t=1000;
int LATCH = 4; 
int DATA = 5;
int CLK = 6;
// define os pinos de latch, data e clock do 74HC595 que controla o display da Celsius do ambiente
// ver datasheet {boa sorte!)

int botao = 7;
int led=10;
int LedPin=9;

// Celsius-base, notem que estou trabalhando com 10x a Celsius real
// para facilitar a codificacao dos displays de 7 segmentos, que so trabalha com numeros binarios e inteiros

byte sensor = 8;
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

const int transmit_pin = 12;
const int receive_pin = 11;
const int transmit_en_pin = 3;// era 3,verifique se faz diferenca

void setup()
{
  Serial.begin(9600);
  pinMode(sensor, INPUT_PULLUP);
  pinMode(trimpot, INPUT);
  pinMode(botao, INPUT);
  pinMode(led, OUTPUT);
  pinMode(LedPin, OUTPUT);
  pinMode(LATCH, OUTPUT);
  pinMode(CLK, OUTPUT);
  pinMode(DATA, OUTPUT);

  // Initialise the IO and ISR
  vw_set_tx_pin(transmit_pin);
  //    vw_set_rx_pin(receive_pin);
  vw_set_ptt_pin(transmit_en_pin);
  vw_set_ptt_inverted(true); // Required for DR3100
  vw_setup(2000);       // Bits per sec
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

    char msg[15] = {
      'T', 'e', 'm', 'p', 'e', 'r', 'a', 't', 'u', 'r', 'a', ' ', '=', ' ', '#'    };
    long transmissao = Celsius;
    msg[14] = transmissao;
    digitalWrite(LedPin, HIGH); // Flash a light to show transmitting
    delay(t/10);
    vw_send((uint8_t *)msg, 14);
    vw_wait_tx(); // Wait until the whole message is gone
    digitalWrite(LedPin, LOW);
    delay(t);
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


