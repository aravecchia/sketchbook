#include <Arduino.h>

/*
  CLP para máquina de termoformagem a vácuo.
  Desenvolvido por https://cyberohm.com
  com apoio de www.labdegaragem.com.br
  Agradecimentos a Rui Viana, Wiechert, Celso Ito, Oraculo X, Guilherme Razgriz e Rafael Maciel.
  Fique a vontade para baixar, usar, melhorar e compartilhar!
  1 de junho de 2016.
*/
#include <math.h>
// the value of the 'other' resistor
#define SERIESRESISTOR 100000

// What pin to connect the sensor to
#define sensor A0
// resistance at 25 degrees C
#define trimpot A1
// potenciometro de controle
#define THERMISTORNOMINAL 100000
// temp. for nominal resistance (almost always 25 C)
#define TEMPERATURENOMINAL 25
// The beta coefficient of the thermistor (usually 3000-4000)
#define BCOEFFICIENT 4000
// the value of the 'other' resistor
#define SERIESRESISTOR 102800
#define led 13
#define triac 5
#define motor 6
int t = 100;

//_________________________________________________________________________VOID SETUP()
void setup()
{
  pinMode(sensor, INPUT);
  pinMode(trimpot, INPUT);
  pinMode(triac, OUTPUT);  //
  pinMode(motor, OUTPUT);  //
  pinMode(led, OUTPUT);

  Serial.begin(9600);

  attachInterrupt(0, corte, RISING); // Interrupção no pino 2(0) ou 3(1)
  // RISING FALLING CHANGE
}


//_________________________________________________________________________VOID corte()
void corte()
{
  int leitura = map(analogRead(trimpot), 0, 1023, 0, 8000); // o delay de controle
  delayMicroseconds(leitura);
  digitalWrite(triac, HIGH);
  delayMicroseconds(t / 2);
  digitalWrite(triac, LOW);
  cli();
 /* Serial.println(leitura);
  if (temperatura > 10);
  
  {
    cli();
  }
  */
}


//_________________________________________________________________________VOID LOOP()
void loop()
{
  uint8_t oldSREG = SREG; //Armazena variavel para reiniciar attachInterrupt
// cli();  // Interrompe a interrupcao ;) Lembre-se: !(!0)=0

/*
  float reading = SERIESRESISTOR / (1023 / analogRead(sensor)) - 1;

  float temperatura = (1 / (((log(reading / THERMISTORNOMINAL)) / BCOEFFICIENT) + (1.0 / (TEMPERATURENOMINAL + 273.15)))) - 273.15;


  
    Serial.print("Analog reading: ");
    Serial.print(analogRead(sensor));
    Serial.print(" - R = ");
    Serial.print(reading);
    Serial.print(" Ohm - ");
  
  Serial.print("T = ");
  Serial.print(temperatura);
  Serial.println(" *C");

  if (temperatura > 30)
  {
    digitalWrite(led, HIGH);
  }
  else
  {
    digitalWrite(led, LOW);
  }
 // delay(10*t);
  // (R/Ro)
  // ln(R/Ro)
  // 1/B * ln(R/Ro)
  // + (1/To)
  // Invert
  // convert to C
 */
  SREG = oldSREG;  //Reinicia attachInterrupt
 // delayMicroseconds(20000);
}
