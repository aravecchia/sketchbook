#include <Arduino.h>

// the value of the 'other' resistor
#define SERIESRESISTOR 100000

// What pin to connect the sensor to
#define sensor A0
// resistance at 25 degrees C
#define THERMISTORNOMINAL 100000
// temp. for nominal resistance (almost always 25 C)
#define TEMPERATURENOMINAL 25
// The beta coefficient of the thermistor (usually 3000-4000)
#define BCOEFFICIENT 4000
// the value of the 'other' resistor
#define SERIESRESISTOR 102800
#define led 13

void setup(void)
{
  pinMode(led, OUTPUT);
  Serial.begin(9600);
}

void loop()
{
  int x = 0;
  float soma;
  float media;
  float reading;
  float matriz[60];
  for (x = 0; x < 60; x++);
  {
    reading = analogRead(sensor);

    // convert the value to resistance
    reading = (1023 / reading) - 1;
    reading = SERIESRESISTOR / reading;

    float steinhart = (1 / (((log(reading / THERMISTORNOMINAL)) / BCOEFFICIENT) + (1.0 / (TEMPERATURENOMINAL + 273.15)))) - 273.15;
    matriz[x] = steinhart;
        Serial.print(x);
         Serial.print(" = ");
    Serial.println(matriz[x]);
  }
  /*for (x = 0; x < 60; x++);
  {
    soma = matriz[x] + soma;
  }
  media = soma/60;
  Serial.println(media);
  */
  delay(50);
}

