#include <Arduino.h>
#include <VirtualWire.h>
/*Desenvolvido por Alexandre Aravecchia
  Projetista, desenvolvedor, programador
 aravecchia@gmail.com
 www.aravecchia.weebly.com
 */
// Apoio: Laboratorio de Garagem - www.labdegaragem.com
// Apoio: Labirito - www.labirito.com
// Agradecimentos a valiosa ajuda dos amigos:
// Almir, Jonatas, Jucelei, Rogerio, Marcelo, Renyer, fredsant, Wiechert, Rui Viana de Aldebaran
// alem da tremenda paciencia da minha esposa pra me aguentar falando nisso dia e noite :D

int t=1000;
int LATCH = 4; 
int DATA = 5;
int CLK = 6;
// define os pinos de latch, data e clock do 74HC595 que controla o display da temperatura do ambiente
// ver datasheet {boa sorte!)

//int tempbase=250;
// temperatura-base, notem que estou trabalhando com 10x a temperatura real
// para facilitar a codificacao dos displays de 7 segmentos, que so trabalha com numeros binarios e inteiros

const int transmit_pin = 12;
const int receive_pin = 11;
const int transmit_en_pin = 3;

const int LedPin=13;

byte digito[10]= {
  B11111100,B01100000,B11011010,B11110010,B01100110,B10110110,B10111110,B11100000,B11111110,B11110110};
// matrizes de 10 termos, cada um define um Byte diferente para cada
// digito de 0 a 9 no display, ou seja, liga um conjunto especifico de portas do 74hc595
// que acende um conjunto especifico de LEDs.

void setup()
{
  delay(t);
  Serial.begin(9600);
  //  pinMode(sensor, INPUT);
  pinMode(LATCH, OUTPUT);
  pinMode(CLK, OUTPUT);
  pinMode(DATA, OUTPUT);

  // Initialise the IO and ISR
  Serial.println("setup");
  vw_set_tx_pin(transmit_pin);
  vw_set_rx_pin(receive_pin);
  vw_set_ptt_pin(transmit_en_pin);
  vw_set_ptt_inverted(true); // Required for DR3100
  vw_setup(2000);	 // Bits per sec
  vw_rx_start();       // Start the receiver PLL running
}

void loop()
{
  uint8_t buf[VW_MAX_MESSAGE_LEN];
  uint8_t buflen = VW_MAX_MESSAGE_LEN;

  if (vw_get_message(buf, &buflen)) // Non-blocking
  {
    int i;

    digitalWrite(LedPin, HIGH); // Flash a light to show received good message
    // Message with a good checksum received, dump it.
    Serial.print("Got: ");

    for (i = 0; i < buflen; i++)
    {
      if (i==1)
      {
        Serial.print(char(buf[i]));//, HEX);
      }
      else
      {
        Serial.print(int(buf[i]));//, HEX);
      }
      Serial.print('Not...');
    }
    Serial.println();
    digitalWrite(LedPin, LOW);
  }

  for (int z=0; z<10; z++)
  {
    for (int y=0; y<10; y++)
    {
      for (int x=0; x<10; x++)
      {
        digitalWrite(LATCH, LOW);
        shiftOut(DATA, CLK, LSBFIRST, digito[x]); //primeiro CI recebe 1 Byte
        shiftOut(DATA, CLK, LSBFIRST, digito[y]+1);  //segundo CI recebe 1 Byte
        shiftOut(DATA, CLK, LSBFIRST, digito[z]); //terceiro CI recebe 1 Byte
        digitalWrite(LATCH, HIGH); 
        delay(t);
      }
    }
  } 
}






