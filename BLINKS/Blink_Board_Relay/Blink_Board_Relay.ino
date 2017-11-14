#include <Arduino.h>

int led=13;
int x;
int t=500;

void setup() {  
  Serial.begin(9600);  
  pinMode(led, OUTPUT);     
  pinMode(x, OUTPUT);
}
void loop() 
{
  for (x=22; x < 38; x++)
  {
    digitalWrite(x, LOW);
 Serial.println(x);
    delay(t);   
    // wait for a second
    digitalWrite(x, HIGH);
    delay(t);
  }
  digitalWrite(led, HIGH); 
  delay(t);
  digitalWrite(led, LOW);
  delay(t);
}

