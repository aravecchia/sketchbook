#include <Arduino.h>


/*
Programa : Módulo RF Transmissor com Arduino Mega.
 Testado com modelo generico marca: Wayduino.
 Autor : TIO DO COMPUTADOR - tiodocomputador@gmail.com
 
 Ligar o Pino Data do transmissor ao pino 12 do Arduino Mega.
 Le um keypad de 16 botoes, acende o led correspondente e 
 envia um Byte por radiofrequencia para outro Arduino.
 
 Keypad em INPUT nos pinos 22 a 25, e em OUTPUT nos pinos 26 a 29
 Leds nos pinos 30 a 46
 Pino DATA do Transmissor no pino 12 do Arduino Mega.
 */

//delay
int t=250;
//Biblioteca
#include <VirtualWire.h>

void setup()
{
  pinMode(13, OUTPUT); // Led que vai piscar se a mensagem for transmitida
  for (int pin=22; pin<26; pin++) //pinos de INPUT do keypad, correspondentes as linhas
  {
    pinMode(pin, INPUT);
  }
  for (int led=26; led<47; led++) //pinos de OUTPUT do keypad (correspondentes as colunas) e dos leds
  {
    pinMode(led, OUTPUT);
  }

  Serial.begin(9600); // Inicializa a serial
  Serial.println("Inicializando...");
  // Initialise the IO and ISR
  vw_set_ptt_inverted(true); // Required for DR3100
  vw_setup(2000);
  // Bits per sec
}

void loop()
{  
  // Matriz de caracteres correspondentes aos botoes do keypad
  const char * matriz[] = {
    "1", "2", "3", "A", "4", "5", "6", "B", "7", "8", "9", "C", "*", "0", "#", "D"          };

  // Loop para a linha
  for (int linha=0; linha<4; linha++)
  {
    // Coloca cada linha do keypad em HIGH
    digitalWrite((linha+26), HIGH);
    // Loop para as colunas
    for (int coluna=0; coluna<4; coluna++)
    {
      // Somente a linha onde o botao se localiza esta toda em HIGH, entao 
      // Se a coluna do botao tambem estiver em HIGH...
      if(digitalRead(coluna+22)==1)
      {
        // ... o botao foi apertado, entao acenda o Led correspondente
        digitalWrite(((4*linha)+30+coluna), HIGH);

        // busque na matriz o Byte correspondente aquele botao
        // e atribua este Byte a constante msg
        const char * msg = matriz[(4*linha)+coluna];
        //Pisca o Led 13 para avisar que uma transmissao sera realizada
        digitalWrite(13, true);
        // Envia o Byte (poderia ser uma string, sem problema) para o transmissor
        vw_send(( uint8_t * )msg, strlen(msg));
        // Espera ate a mensagem ser transmitida
        vw_wait_tx();
        // Apaga o Led para mostrar que a transmissao foi concluida
        digitalWrite(13, false);
        // Avisa pela serial qual string foi enviada
        Serial.print("Mandei a string: ");
        Serial.println(matriz[(4*linha)+coluna]);
        // Um delay, com tempo suficiente para o usuario tirar o dedo do botao
        delay(t);
        // Apaga o Led do mostrador, relativo ao botao apertado
        digitalWrite(((4*linha)+30+coluna), LOW);
      }
    }
    // Coloca a linha de botoes do keypad em LOW, antes do Loop ir para a proxima linha.
    digitalWrite((linha+26), LOW);
  }
}


