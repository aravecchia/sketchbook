int t = 2000;
int vetor[8]={2, 3, 4, 5};

void setup()
{
  for (int led = 2; led < 10; led++)
  {
    pinMode(led, OUTPUT);
  }
}
void loop()
{
  for (int x = 0; x < 4; x++)
  {
    digitalWrite(vetor[x], HIGH);
    delay(t);
    digitalWrite(vetor[x], LOW);
  }
}
