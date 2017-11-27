int t = 250;

int vetor{2, 9, 3, 8, 4, 7, 5, 6}
void setup()
{
  for (int led = 2; x < 10; x++)
  {
    pinMode(led, OUTPUT);
  }
}
void loop()
{
  for (int x = 0; x < 8; x++)
  {
    digitalWrite(vetor[x], HIGH);
    delay(t);
    digitalWrite(vetor[x], LOW);
  }
}
