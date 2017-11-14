#include <Arduino.h>

// Inclui as Libs necessarias.
#include <LiquidCrystal.h>
#include <Wire.h>
 
//LiquidCrystal lcd(8, 9, 4, 5, 6, 7);
//Estes valores quando trabalhar na protoboard
LiquidCrystal lcd(13, 12, 11, 10, 9, 8);
//Estes valores quando trabalhar no proteus
 
//Mux control pins
int r0 = 2;
int r1 = 3;
int r2 = 4;
int r3 = 5;
 
int comum = 6;
 
int led;
 
int fator = 10;
int Taceso = 200;
int Tapagado = Taceso/fator;
 
// Observação: O quatro é a quantidade de itens que haverá no eixo X da matriz;
int matriz[16][4] = {
{0,0,0,0},
{0,0,0,1},
{0,0,1,0},
{0,0,1,1},
{0,1,0,0},
{0,1,0,1},
{0,1,1,0},
{0,1,1,1},
{1,0,0,0},
{1,0,0,1},
{1,0,1,0},
{1,0,1,1},
{1,1,0,0},
{1,1,0,1},
{1,1,1,0},
{1,1,1,1},
};
 
 
void setup() {
  pinMode(r0, OUTPUT);
  pinMode(r1, OUTPUT);
  pinMode(r2, OUTPUT);
  pinMode(r3, OUTPUT);
  pinMode(comum, OUTPUT);
  digitalWrite(r0, LOW);
  digitalWrite(r1, LOW);
  digitalWrite(r2, LOW);
  digitalWrite(r3, LOW);
  digitalWrite(comum, LOW);
 
  Serial.begin(9600);
}
 
void loop() {
   for(int i =0; i<16; i++){
    acender(matriz[i]);
    escreve(i);
   }
}
 
void acender( int m[] ) {
    digitalWrite(r0, m[0]);
    digitalWrite(r1, m[1]);
    digitalWrite(r2, m[2]);
    digitalWrite(r3, m[3]);
}
 
void escreve(int led ) {
  digitalWrite(comum, HIGH);   // turn the LED on (HIGH is the voltage level)
  {
    ///Serial.print("Led ativo: ");
    //Serial.print(led);
    Serial.print(matriz[led][0]);
    Serial.print(matriz[led][1]);
    Serial.print(matriz[led][2]);
    Serial.print(matriz[led][3]);        
    Serial.println(".");
 
    lcd.setCursor(0,0);
    lcd.print("Led ativo:");
    lcd.setCursor(0,1);
    lcd.print(led);
    lcd.print(".");
  }
  delay(Taceso);              // wait for a second
  digitalWrite(comum, LOW);    // turn the LED off by making the voltage LOW
  delay(Tapagado);
}
