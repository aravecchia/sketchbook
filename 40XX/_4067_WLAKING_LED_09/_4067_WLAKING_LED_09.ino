#include <Arduino.h>


int w0 = 10;
int w1 = 9;
int w2 = 11;
int w3 = 12;

const int analogInPin = A0;  // Analog input pin that the potentiometer is attached to
const int analogOutPin = 2; // Analog output pin that the LED is attached to

int sensorValue;        // value read from the pot
int outputValue;        // value output to the PWM (analog out)

int T = 1;

int matriz[16][4] = {
  {
    0,0,0,0                              }
  ,
  {
    0,0,0,1                              }
  ,
  {
    0,0,1,0                              }
  ,
  {
    0,0,1,1                              }
  ,
  {
    0,1,0,0                              }
  ,
  {
    0,1,0,1                              }
  ,
  {
    0,1,1,0                              }
  ,
  {
    0,1,1,1                              }
  ,
  {
    1,0,0,0                              }
  ,
  {
    1,0,0,1                              }
  ,
  {
    1,0,1,0                              }
  ,
  {
    1,0,1,1                              }
  ,
  {
    1,1,0,0                              }
  ,
  {
    1,1,0,1                              }
  ,
  {
    1,1,1,0                              }
  ,
  {
    1,1,1,1                              }
  ,
};


void setup()
{

  pinMode(w0, OUTPUT);
  pinMode(w1, OUTPUT);
  pinMode(w2, OUTPUT);
  pinMode(w3, OUTPUT);

  pinMode(sensorValue, INPUT);
  pinMode(outputValue, OUTPUT);
  // initialize serial communications at 9600 bps:
  Serial.begin(9600); 
}

void loop()
{
  for(int i = 0; i<16; i++)
  {
    seletor(matriz[i]);
    //    sensorValue=0;
    sensorValue = analogRead(analogInPin);            
    // map it to the range of the analog out:
    outputValue = map(sensorValue, 50, 1023, 0, 250);  
    // change the analog out value:
    if (outputValue<50)
    {
      outputValue=255;
    }
    else if (outputValue>50 && outputValue < 100)
    {
      outputValue=100;
    }
    else
    {
      outputValue=50;
    }
    analogWrite(analogOutPin, outputValue);  

    escreve(i);
    Serial.print(sensorValue);
    Serial.print(" - ");
    Serial.println(outputValue);
    delay(T); 
  }
}

void seletor( int m[] )
{
  digitalWrite(w0, m[0]);
  digitalWrite(w1, m[1]);
  digitalWrite(w2, m[2]);
  digitalWrite(w3, m[3]);
}

void escreve(int led)
{
  Serial.print("Led ativo: ");
  Serial.print(led);
  Serial.print(" - ");
  Serial.print(matriz[led][0]);
  Serial.print(matriz[led][1]);
  Serial.print(matriz[led][2]);
  Serial.print(matriz[led][3]);  
  Serial.print(" - Leitura: ");  
}




