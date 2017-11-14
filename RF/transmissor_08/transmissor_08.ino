#include <Arduino.h>


/*
  Programa : Módulo RF Transmissor com Arduino Mega.
  Testado com modelo generico marca: Wayduino.
  Autor : aravecchia@gmail.com

  Ligar o Pino Data do transmissor ao pino 12 do Arduino Mega.
  Le um keypad de 16 botoes, acende o led correspondente e
  envia um Byte por radiofrequencia para outro Arduino.

  Keypad em INPUT nos pinos 22 a 25, e em OUTPUT nos pinos 26 a 29
  Leds nos pinos 30 a 46
  Pino DATA do Transmissor no pino 12 do Arduino Mega.
*/

//delay
int t = 100;
int led=13;
//Biblioteca
#include <VirtualWire.h>

void setup()
{
  pinMode(led, OUTPUT); // Led que vai piscar se a mensagem for transmitida

  Serial.begin(9600); // Inicializa a serial
  Serial.println("Inicializando...");
  // Initialise the IO and ISR
  vw_set_ptt_inverted(true); // Required for DR3100
  vw_setup(2000);
  // Bits per sec
}

void loop()
{
  // Loop para a linha
  for (int x = 0; x < 256; x++)
  {
char * msg = char(x);
    //Pisca o Led 13 para avisar que uma transmissao sera realizada
    digitalWrite(led, HIGH);
    // Envia o Byte (poderia ser uma string, sem problema) para o transmissor
    vw_send(( uint8_t * )msg, strlen(msg));
    // Espera ate a mensagem ser transmitida
    vw_wait_tx();
    // Apaga o Led para mostrar que a transmissao foi concluida
    digitalWrite(led, LOW);
    // Avisa pela serial qual string foi enviada
    Serial.print("x= ");
    Serial.println(x);
  }
  // Coloca a linha de botoes do keypad em LOW, antes do Loop ir para a proxima linha.
  digitalWrite((linha + 26), LOW);
}
}


