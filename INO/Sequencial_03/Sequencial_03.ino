int t;
int sensor=A0;
void setup()
{
  for (int x = 2; x < 10; x++)
  {
    pinMode(x, OUTPUT);
  }
  pinMode(sensor, INPUT);
  Serial.begin(9600);
}

void loop()
{
      for (int x = 2; x < 10; x++)
  {
   t=analogRead(sensor);
  digitalWrite(x, HIGH);
  delay(t);
  digitalWrite(x, LOW);
    Serial.println(t);
  }
      for (int x = 8; x >2 ; x--)
  {
    t=analogRead(sensor);
  digitalWrite(x, HIGH);
  delay(t);
  digitalWrite(x, LOW);
    Serial.println(t);
  }
}
