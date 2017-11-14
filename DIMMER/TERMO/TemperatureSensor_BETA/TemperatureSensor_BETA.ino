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
  float reading;

  reading = analogRead(sensor);

  // convert the value to resistance
  reading = (1023 / reading) - 1;
  reading = SERIESRESISTOR / reading;


  float steinhart = (1 / (((log(reading / THERMISTORNOMINAL)) / BCOEFFICIENT) + (1.0 / (TEMPERATURENOMINAL + 273.15)))) - 273.15;
  /*
    steinhart = reading / THERMISTORNOMINAL;
    steinhart = log(steinhart);
    steinhart /= BCOEFFICIENT;
    steinhart += 1.0 / (TEMPERATURENOMINAL + 273.15);
    steinhart = 1.0 / steinhart;
    steinhart -= 273.15;
  */

  Serial.print("Analog reading: ");
  Serial.print(analogRead(sensor));
  Serial.print(" - R = ");
  Serial.print(reading);
  Serial.print(" Ohm - ");
  Serial.print("T = ");
  Serial.print(steinhart);
  Serial.println(" *C");

  if (steinhart < 44)
  {
    digitalWrite(led, HIGH);
  }
  else
  {
    digitalWrite(led, LOW);
  }
  delay(500);
  // (R/Ro)
  // ln(R/Ro)
  // 1/B * ln(R/Ro)
  // + (1/To)
  // Invert
  // convert to C

}

