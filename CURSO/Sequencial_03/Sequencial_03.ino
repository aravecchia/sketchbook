int t;
int tmax=1000;
int sensor=A0;
void setup()
{
  for (int x = 0; x < 10; x++)
  {
    pinMode(x, OUTPUT);
  }
  Serial.begin(9600);
}

void loop()
{
      for (int x = 2; x < 10; x++)
  {
   t=map(analogRead(sensor), 0,1023, tmax, 0);
  digitalWrite(x, HIGH);
  delay(t);
  digitalWrite(x, LOW);
    Serial.println(t);
  }
      for (int x = 8; x >2 ; x--)
  {
    t=map(analogRead(sensor), 0,1023, tmax, 0);
  digitalWrite(x, HIGH);
  delay(t);
  digitalWrite(x, LOW);
    Serial.println(t);
  }
}
