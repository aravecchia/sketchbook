int t = 10;
boolean sensor = A0;
void setup()
{
  for (int x = 2; x < 10; x++)
  {
    pinMode(x, OUTPUT);
  }
  pinMode(sensor, INPUT);
}

void loop()
{
  for (int x = 2; x < 10; x++)
  {
    int valor = analogRead(sensor);
    int led = map(valor, 0, 1023, 2, 9);
    if (x == led)
    {
      digitalWrite(x, HIGH);
    }
    else
    {
      digitalWrite(x, LOW);
    }
    delay(t);
  }
}
