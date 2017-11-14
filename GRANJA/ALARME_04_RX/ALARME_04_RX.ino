/*Desenvolvido por Alexandre Aravecchia
  Projetista, desenvolvedor, programador
 aravecchia@gmail.com
 www.aravecchia.weebly.com
 */
// Apoio:
//   Laboratorio de Garagem - www.labdegaragem.com
//   Labirito - www.labirito.com
//   junho/2017
#include <Arduino.h>
#include <VirtualWire.h>
#include <VirtualWire.h>

const int LedRX = 13;
const int LedAlarme = 12;
const int Alarme = 10;
//const int transmit_pin = 12;
const int receive_pin = 11;
//const int transmit_en_pin = 3;

int t=500;
int LATCH = 4; 
int DATA = 5;
int CLK = 6;

byte digito[10]= { 
  B11111100,B01100000,B11011010,B11110010,B01100110,B10110110,B10111110,B11100000,B11111110,B11110110};
// matrizes de 10 termos, cada um define um Byte diferente para cada
// digito de 0 a 9 no display, ou seja, liga um conjunto especifico de portas do 74hc595
// que acende um conjunto especifico de LEDs.

float Celsius;
int tempbase;
int x;
int y;
int z;

void setup()
{
  delay(t);
  Serial.begin(9600);	// Debugging only
  Serial.println("Iniciando recepcao...");

  // Initialise the IO and ISR
  //  vw_set_tx_pin(transmit_pin);
  vw_set_rx_pin(receive_pin);
  //  vw_set_ptt_pin(transmit_en_pin);
  vw_set_ptt_inverted(true); // Required for DR3100
  vw_setup(2000);	 // Bits per sec
  vw_rx_start();       // Start the receiver PLL running

  pinMode(LedRX, OUTPUT);
  pinMode(LedAlarme, OUTPUT);
  pinMode(LATCH, OUTPUT);
  pinMode(CLK, OUTPUT);
  pinMode(DATA, OUTPUT);
}

void loop()
{
  uint8_t buf[VW_MAX_MESSAGE_LEN];
  uint8_t buflen = VW_MAX_MESSAGE_LEN;

  if (vw_get_message(buf, &buflen)) // Non-blocking
  {
    int i;

    digitalWrite(LedRX, HIGH); // Flash a light to show received good message
    // Message with a good checksum received, dump it.
    //Serial.print("Got: ");

    digitalWrite(LATCH, LOW);
    for (i = 0; i < buflen; i++)
    {
      if (i==2)
      {
        z = (buf[i]);
        if (z==0)
        {
          shiftOut(DATA, CLK, LSBFIRST, 0); //terceiro CI recebe 1 Byte
        }
        else
        {
          shiftOut(DATA, CLK, LSBFIRST, digito[z]); //terceiro CI recebe 1 Byte
        }
        Serial.print((buf[i]));//, INT);
        Celsius = 10*z;
      }
      else if (i==3)
      {
        y = (buf[i]);
        shiftOut(DATA, CLK, LSBFIRST, digito[y]+1);  //segundo CI recebe 1 Byte
        Serial.print((buf[i]));//, INT);
        Serial.print(".");
        Celsius = Celsius + y;
      }
      else if (i==4)
      {
        x = (buf[i]);
        shiftOut(DATA, CLK, LSBFIRST, digito[x]); //primeiro CI recebe 1 Byte
        Serial.print((buf[i]));//, INT);
        Celsius = Celsius + ((float(x))/10);
      }
      else if (i==11)
      {
                tempbase = buf[i];
        Serial.print(buf[i]);//, INT);
      }
      else
      {
        Serial.print(char(buf[i]));//, HEX);
      }
    }
     Serial.print("");



    digitalWrite(LATCH, HIGH);
    digitalWrite(LedRX, LOW);

    if ((Celsius)<(tempbase-2))
    {
      digitalWrite(LedAlarme, HIGH);
      tone(Alarme, 350, 5*t); //int duration = 250;
      // how long the tone(speakerPin, frequency, duration);delay(1000);
      delay(t);
      digitalWrite(LedAlarme, LOW);
      noTone(Alarme);
    }
    else
    {
      digitalWrite(LedAlarme, LOW);
    }
  }
}



















