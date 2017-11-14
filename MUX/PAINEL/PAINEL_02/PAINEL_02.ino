#include <Arduino.h>

// Laboratorio J011y R0g3r
// ta na hora de pensar num nome serio pra esse Laboratorio :D
// Apoio: Laboratorio de Garagem - labdegaragem.com
// Agradecimentos a valiosa ajuda dos amigos:
// Almir, Jonatas, Jucelei, Rogerio, Marcelo, Renyer, fredsant, OraculoX, Wiechert (esqueci alguem???)
// alem da tremenda paciencia da minha esposa pra me aguentar falando nisso dia e noite :D

int LATCH = 6; 
int DATA = 7;
int CLOCK = 8;
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
  int t=10000;
  // Tempo de delay.
  
  for (long i=1; i<=32768; i=i<<1)
  { 
    digitalWrite(LATCH, LOW);
    {
      shiftOut(DATA, CLOCK, MSBFIRST, i>>8);
      shiftOut(DATA, CLOCK, MSBFIRST, i);
      Serial.print(i>>8, BIN);
      Serial.print(" - ");
      Serial.println(i,BIN);
    }
    digitalWrite(LATCH, HIGH);
    delay(t);
  }
  delay(t);
    for (long i=32768; i>=1; i=i>>1)
  { 
    digitalWrite(LATCH, LOW);
    {
      shiftOut(DATA, CLOCK, MSBFIRST, i>>8);
      shiftOut(DATA, CLOCK, MSBFIRST, i);
      Serial.print(i>>8, BIN);
      Serial.print(" - ");
      Serial.println(i,BIN);
    }
    digitalWrite(LATCH, HIGH);
    delay(t);
  }
  delay(t);
}

/* 
 Nao se esqueca de corrigir o codigo: do jeito que esta, o 595 vai mudar o estado de
 todos os relays a cada LDR que o 4067 ler. Ou seja, a cada LDE ele liga a quantidade de relays
 correspondente aquela iluminacao.
 Tem que criar uma regra para que cada LDR mude o estado de cada rele especifico, quando
 a luminosidade atingir um limite pre-determinado.
 Quando terminar, diminua o delay pra 1 ms.
 Que a Forća esteja com voce.
 
 int led = 13;
 int LATCH = 6;
 int DATA = 7;
 int CLOCK = 8; 
 
 int s0 = 5;
 int s1 = 6;
 int s2 = 7;
 int s3 = 8;
 
 int AnPin = A0;
 
 int sensor;
 
 int t=1;
 
 int matriz[16][4] = {
 {
 0,0,0,0                                      }
 ,
 {
 0,0,0,1                                      }
 ,
 {
 0,0,1,0                                      }
 ,
 {
 0,0,1,1                                      }
 ,
 {
 0,1,0,0                                      }
 ,
 {
 0,1,0,1                                      }
 ,
 {
 0,1,1,0                                      }
 ,
 {
 0,1,1,1                                      }
 ,
 {
 1,0,0,0                                      }
 ,
 {
 1,0,0,1                                      }
 ,
 {
 1,0,1,0                                      }
 ,
 {
 1,0,1,1                                      }
 ,
 {
 1,1,0,0                                      }
 ,
 {
 1,1,0,1                                      }
 ,
 {
 1,1,1,0                                      }
 ,
 {
 1,1,1,1                                      }
 ,
 };
 
 void setup()
 {
 Serial.begin(9600);
 pinMode(led, OUTPUT);
 pinMode(LATCH, OUTPUT);
 pinMode(CLOCK, OUTPUT);
 pinMode(DATA, OUTPUT);
 
 pinMode(AnPin, INPUT);
 
 
 pinMode(s0, OUTPUT); 
 pinMode(s1, OUTPUT); 
 pinMode(s2, OUTPUT); 
 pinMode(s3, OUTPUT); 
 
 digitalWrite(s0, LOW);
 digitalWrite(s1, LOW);
 digitalWrite(s2, LOW);
 digitalWrite(s3, LOW);
 }
 
 void loop()
 {
 digitalWrite(led, HIGH);   // turn the LED on (HIGH is the voltage level)
 delay(t);               // wait for a second
 digitalWrite(led, LOW);    // turn the LED off by making the voltage LOW
 delay(t);       
 int x = 1;
 
 for(int i = 0; i<16; i++)
 {
 seletor(matriz[i]);
 leitura(i);
 
 //----->>>>>>leitura do sensor aqui
 sensor = map(analogRead(AnPin), 0, 1023, 0,16);  
 
 compara;
 
 digitalWrite(LATCH, LOW);
 if (sensor==0)
 {
 // Envia 2 Bytes para o DATA, um para cada HC-595, desligando todos os LEDs.
 shiftOut(DATA, CLOCK, MSBFIRST, 0);
 shiftOut(DATA, CLOCK, MSBFIRST, 0);
 }
 
 else if (sensor!=0 && sensor<8)
 {
 // Como estamos usando MSBFIRST, mandamos o primeiro Byte para o ultimo CI:
 shiftOut(DATA, CLOCK, MSBFIRST, 0);
 shiftOut(DATA, CLOCK, MSBFIRST, (x<<sensor));
 }
 else
 {
 shiftOut(DATA, CLOCK, MSBFIRST, (x<<(sensor-8)));
 //00000001<<1=00000010
 // E o ultimo Byte para o mestre:
 shiftOut(DATA, CLOCK, MSBFIRST, (x<<sensor));
 }
 
 // Escreve na serial o resultado e confere o codigo:
 Serial.print("sensor");
 Serial.print(i);
 Serial.print(" = ");
 Serial.print(analogRead(AnPin));
 Serial.print(" = ");
 Serial.println(sensor);
 // Levanta o muro LATCH, fecha a transmissao (represam os bits)
 digitalWrite(LATCH, HIGH);
 delay(t);
 
 }
 }
 
 void seletor( int m[] )
 {
 digitalWrite(s0, m[0]);
 digitalWrite(s1, m[1]);
 digitalWrite(s2, m[2]);
 digitalWrite(s3, m[3]);   
 }
 
 void leitura(int pino)
 {
 Serial.print("Ldr ativo: ");
 Serial.print(pino);
 Serial.print(" - ");
 Serial.print(matriz[pino][0]);
 Serial.print(matriz[pino][1]);
 Serial.print(matriz[pino][2]);
 Serial.print(matriz[pino][3]);  
 Serial.print(" - Leitura: ");  
 }
 
 void compara()
 {
 
 }
 */





