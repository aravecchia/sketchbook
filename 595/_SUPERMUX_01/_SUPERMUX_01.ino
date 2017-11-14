#include <Arduino.h>

/*Desenvolvido por Alexandre Aravecchia
  Projetista, desenvolvedor, programador
 aravecchia@gmail.com
 www.aravecchia.weebly.com
 */
// Apoio: Laboratorio de Garagem - labdegaragem.com
// Agradecimentos a valiosa ajuda dos amigos:
// Almir, Jonatas, Jucelei, Rogerio, Marcelo, Renyer, fredsant, (o cara daquele site de mecatronica, esqueci os dois nomes) (esqueci alguem???)
// alem da tremenda paciencia da minha esposa pra me aguentar falando nisso dia e noite :D

int LATCH = 2; 
int DATA = 3;
int CLOCK = 4;
// define os pinos de latch, data e clock do 74HC595 que controlam o display da temperatura do ambiente


void setup()
{
  Serial.begin(9600);
  pinMode(LATCH, OUTPUT);
  pinMode(CLOCK, OUTPUT);
  pinMode(DATA, OUTPUT);
  // Define LATCH, DATA e CLOCK como pinos de saida
}

void loop()
{
  int t=5;
  // Tempo de delay.
  for (int i=1; i<256; i=i<<1)
    // inicia a contagem.
  {
    digitalWrite(LATCH, LOW);
    // inicia a transmissao de DATA.
    for (int y=0; y<64; y++)
    {
        shiftOut(DATA, CLOCK, MSBFIRST, i);
    // DATA recebe o 1o. bit e envia para a 1a. porta do registrador.
    // CLOCK muda de estado para avisar que o bit foi recebido.
    // DATA recebe o 2o. bit e envia para 2a. porta do registrador
    // CLOCK muda de estado novamente.
    // Apos 8 bits, as 8 portas foram preenchidas.
    // O registrador envia os 8 bits (1 Byte) para os 8 pinos de saida, na ordem:
    // LSBFIRST - 00000001 - envio comecando pelo bit menos significante ou 
    // MSBFIRST - 10000000 - envio comecando pelo bit mais significante.
    // DATA entra em modo de espera e aguarda o LATCH entrar em HIGH novamente
    // para encerrar a transmissao.
    }
    digitalWrite(LATCH, HIGH);
    // Fim da transmissao, DATA envia o Byte para o SERIAL DATA (pino 9 do registrador)
    // SERIAL DATA envia o BYTE para o pino 14 (DATA) do proximo registrador.
    // DATA do 1o. registrador eh limpo para o recebimento do proximo Byte.
    Serial.print("i= ");
    Serial.println(i);
    delay(t);
  }
}


