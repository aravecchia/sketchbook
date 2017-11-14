#include <Arduino.h>

#include <math.h>
int sensor = A0;
int PULLUP = 102800;
int CORRECAO = 20;

long Resistance;
double Temp;
/******************************************************************/
/* Utilizes the Steinhart-Hart Thermistor Equation:        */
/*    Temperature in Kelvin = 1 / {A + B[ln(R)] + C[ln(R)]^3}   */
/*    where A = 0.001129148, B = 0.000234125 and C = 8.76741E-08  */
/******************************************************************/

/*
double A = 0.001129148;
double B = 0.000234125;
double C = 8.76741E-08;
*/

double A = -0.0003372631;
double B = 0.0003142615;
double C = 0.00000004908113132270;


// -0.0003372631 0.0003142615  0.00000004908113132270




void setup()
{
  Serial.begin(9600);
}

void loop()
{
  int RawADC = analogRead(sensor);
  // Assuming a 10k Thermistor.  Calculation is actually: Resistance = (1024/ADC)
  Resistance = ((102400000 / RawADC) - PULLUP);

  double LOG = log(Resistance);
  //  Temp = 1 / (0.001129148 + (0.000234125 * Temp) + (8.76741E-08 * Temp * Temp * Temp));

//  double KELVIN = 1 / (-0.0003372631 + (0.0003142615 * LOG) + (0.00000004908113132270 * LOG * LOG * LOG));
double KELVIN = 1 / (A + (B * LOG) + (C * pow(LOG, 3)));
  double CELSIUS = KELVIN - 273.15 + CORRECAO;  // Convert Kelvin to Celsius

  Serial.print("Temperatura: ");
  Serial.print(CELSIUS);
  Serial.print("*C - ");
  Serial.print("ADC: "); Serial.print(RawADC); Serial.print("/1024 - ");  // Print out RAW ADC Number
  Serial.print(" Volts: "); Serial.print (((RawADC * 4.860) / 1024.0), 3); // 4.860 volts is what my USB Port outputs.
  Serial.print(" Resistance: "); Serial.print(Resistance); Serial.println(" ohms");
  delay(250);
}



/* - TESTING OUTPUT - remove lines with * to get serial print of data
  Serial.print("ADC: "); Serial.print(RawADC); Serial.print("/1024");  // Print out RAW ADC Number
  Serial.print(", Volts: "); printDouble(((RawADC*4.860)/1024.0),3);   // 4.860 volts is what my USB Port outputs.
  Serial.print(", Resistance: "); Serial.print(Resistance); Serial.print("ohms");
*/
