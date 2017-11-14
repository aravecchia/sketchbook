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
 int s0 = 9;
 int s1 = 10;
 int s2 = 11;
 int s3 = 12;
 //define os pinos de controle do CD-4067 - checar ordem dos pinos definidos no shield
 //no esquecer de verificar o jumper (se ele define entrada ou saida em A0)

 int AnPin = A0; //define o pino de leitura do CD-4067
 
 
 // A select determina qual pino do Cd-4067 esta ativado
 int select[16][4] = {
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
  pinMode(LATCH, OUTPUT);
  pinMode(CLOCK, OUTPUT);
  pinMode(DATA, OUTPUT);
  // Define LATCH, DATA e CLOCK como pinos de saida
  
   pinMode(A0, INPUT);
  
// Define os pinos de controle do 4067 como saida e coloca todos em estado LOW.
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
  int t=500;
  // Tempo de delay.
int matriz[16]; //criar uma matriz q receba um valor 0 ou 1 do if-else
int x; //este valor 0-1 eh alocado em x, que eh jogado num unico shiftOut, acendendo somente a lampada correspondente ao sensor.
  
  for(int i = 0; i<16; i++)
 {
 seletor(select[i]);
 leitura(i);
 
 //----->>>>>>leitura do sensor aqui
 int sensor = map(analogRead(AnPin), 0, 1023, 0, 16);  
 int x = map(analogRead(AnPin), 0, 1023, 0, 32768);
 
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
 shiftOut(DATA, CLOCK, MSBFIRST, (x>>sensor));
 }
 else
 {
 shiftOut(DATA, CLOCK, MSBFIRST, (x>>(sensor-8)));
 //00000001<<1=00000010
 // E o ultimo Byte para o mestre:
 shiftOut(DATA, CLOCK, MSBFIRST, (x>>sensor));
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
 Serial.print(pino+1);
 Serial.print(" - ");
 Serial.print(select[pino][0]);
 Serial.print(select[pino][1]);
 Serial.print(select[pino][2]);
 Serial.print(select[pino][3]);  
 Serial.print(" - Leitura: ");  
 }

/* 
 void loop()
 {
    
 int x = 1;
 
 
 
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
 

 
 void leitura(int pino)
 {
 Serial.print("Ldr ativo: ");
 Serial.print(pino);
 Serial.print(" - ");
 Serial.print(select[pino][0]);
 Serial.print(select[pino][1]);
 Serial.print(select[pino][2]);
 Serial.print(select[pino][3]);  
 Serial.print(" - Leitura: ");  
 }
 
 void compara()
 {
 
 }
 */





