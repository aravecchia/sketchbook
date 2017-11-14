#include <Arduino.h>
/*Desenvolvido por Alexandre Aravecchia
  Projetista, desenvolvedor, programador
 aravecchia@gmail.com
 www.aravecchia.weebly.com
 */
// Inclui as Libs necessarias.
#include <LiquidCrystal.h>
#include <Wire.h>

//LiquidCrystal lcd(8, 9, 4, 5, 6, 7);
//Estes valores quando trabalhar na protoboard
//LiquidCrystal lcd(13, 12, 11, 10, 9, 8);
//Estes valores quando trabalhar no proteus

//Pinos de enderecamento do mux
int r0 = 2;    //master
int r1 = 3;    //master
int r2 = 4;    //master
int r3 = 5;    //master
int r4 = 6;    //slave
int r5 = 7;    //slave
int r6 = 8;    //slave
int r7 = 9;    //slave


//Declara pino A0 como leitura analogica
int comum = A0;

// Declara a variavel que controla o pino do multiplexador:
int led;

int fator = 10;
int Taceso = 100;
int Tapagado = Taceso/fator;

// Observação: O quatro é a quantidade de itens que haverá no eixo X da matriz;
int matriz[16][4] =
{
  {
    0,0,0,0  }
  ,
  {
    0,0,0,1  }
  ,
  {
    0,0,1,0  }
  ,
  {
    0,0,1,1  }
  ,
  {
    0,1,0,0  }
  ,
  {
    0,1,0,1  }
  ,
  {
    0,1,1,0  }
  ,
  {
    0,1,1,1  }
  ,
  {
    1,0,0,0  }
  ,
  {
    1,0,0,1  }
  ,
  {
    1,0,1,0  }
  ,
  {
    1,0,1,1  }
  ,
  {
    1,1,0,0  }
  ,
  {
    1,1,0,1  }
  ,
  {
    1,1,1,0  }
  ,
  {
    1,1,1,1  }
  ,
};


void setup()
{
  //Define os pinos de enderecamento e comum como saida:
  pinMode(r0, OUTPUT); 
  pinMode(r1, OUTPUT); 
  pinMode(r2, OUTPUT); 
  pinMode(r3, OUTPUT); 
  pinMode(r4, OUTPUT); 
  pinMode(r5, OUTPUT); 
  pinMode(r6, OUTPUT); 
  pinMode(r7, OUTPUT);
  pinMode(comum, OUTPUT); 

  //Desliga os pinos de enderecamento e os coloca em estado 0000
  digitalWrite(r0, LOW);
  digitalWrite(r1, LOW);
  digitalWrite(r2, LOW);
  digitalWrite(r3, LOW);
  digitalWrite(r4, LOW);
  digitalWrite(r5, LOW);
  digitalWrite(r6, LOW);
  digitalWrite(r7, LOW);
  digitalWrite(comum, LOW);

  //Define a taxa de baud do uC
  Serial.begin(9600);
}

void loop()
{
  for(int i = 0; i<16; i++)
  {
    mux(matriz[i]);
    for(int j = 0; j<16; j++)
    {
      acender(matriz[j]);
      escreve(j);
    }
  }
}


void mux( int m[] ) 
{
  digitalWrite(r0, m[0]);
  digitalWrite(r1, m[1]);
  digitalWrite(r2, m[2]);
  digitalWrite(r3, m[3]);
}

void acender( int p[] )
{
  digitalWrite(r4, p[0]);
  digitalWrite(r5, p[1]);
  digitalWrite(r6, p[2]);
  digitalWrite(r7, p[3]);
      digitalWrite(comum, HIGH);
}

void escreve(int led )
{
  digitalWrite(comum, HIGH);   // turn the LED on (HIGH is the voltage level)
  {
    ///Serial.print("Led ativo: ");
    //Serial.print(led);
    Serial.print(matriz[led][0]);
    Serial.print(matriz[led][1]);
    Serial.print(matriz[led][2]);
    Serial.print(matriz[led][3]);        
    Serial.println(".");

    //    lcd.setCursor(0,0);
    //    lcd.print("Led ativo: ");
    //    lcd.print(led);
    //matriz    lcd.print(".");
  }
  delay(Taceso);              // wait for a second
  digitalWrite(comum, LOW);    // turn the LED off by making the voltage LOW
  delay(Tapagado);
}






