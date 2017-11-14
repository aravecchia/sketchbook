#include <Arduino.h>

/*
/*Desenvolvido por Alexandre Aravecchia
  Projetista, desenvolvedor, programador
 aravecchia@gmail.com
 www.aravecchia.weebly.com
 */
  Analog Input
 Demonstrates analog input by reading an analog sensor on analog pin 0 and
 turning on and off a light emitting diode(LED)  connected to digital pin 13. 
 The amount of time the LED will be on and off depends on
 the value obtained by analogRead(). 
 
 The circuit:
 * Potentiometer attached to analog input 0
 * center pin of the potentiometer to the analog pin
 * one side pin (either one) to ground
 * the other side pin to +5V
 * LED anode (long leg) attached to digital output 13
 * LED cathode (short leg) attached to ground
 
 * Note: because most Arduinos have a built-in LED attached 
 to pin 13 on the board, the LED is optional.
 
 
 Created by David Cuartielles
 modified 30 Aug 2011
 By Tom Igoe
 
 This example code is in the public domain.
 
 http://arduino.cc/en/Tutorial/AnalogInput
 
 */

int sensorPin = A0;      // Pino de leitura no sensor de onda
int potPin = A1;        // Pino de leitura do regulador
int triacPin = 2;      // Pino de ativacao do TRIAC
int sensor = 0;       // Variavel para armazenar o valor do sensor de onda
int regulador = 0;   // Variavel para armazenar o valor do regulador de onda

long T0;               //Inicio do semi-ciclo da onda
long T1;              //Final do semi-ciclo da onda
long T = T0 - T1;    // Semi-periodo de onda
long F = 1/T;       // Frequencia de onda


void setup() {
  // declare the ledPin as an OUTPUT:
  Serial.begin(9600);
  pinMode(sensorPin, INPUT);
  pinMode(potPin, INPUT);
  pinMode(triacPin, OUTPUT);
}

void loop()
{
  sensor = map(sensorPin,0,1023,0,100);  //armazena o valor da leitura na variavel sensor 
  regulador = map(potPin,0,1023,0,100);  //armazena o valor da leitura na variavel sensor 
 
  if (sensor = 0);
  {
    // here if the switch is pressed
T0 = millis();
while(sensor) != 0)
; // wait while the switch is still pressed
long T = millis() - T0;
Serial.print(T);
Serial.print( "ms" - );
Serial.print(F);
Serial.println( "Hz" - );

  }
  digitalWrite(triacPin, HIGH);  
  // stop the program for <sensorValue> milliseconds:
  delay(sensor);          
  // turn the ledPin off:        
  digitalWrite(triacPin, LOW);   
  // stop the program for for <sensorValue> milliseconds:
  delay(sensor);  
  Serial.println(sensor);
}

