int botao = 6;
int red = 11;
int green = 12
int t = 10;
void setup()
{
  pinMode(botao, OUTPUT);
  pinMode(led, INPUT);
}

void loop()
{
  if (digitalRead(botao) == 1)
  {
    digitalWrite(red, HIGH);
    digitalWrite(green, LOW);
  }
  else
    {
    digitalWrite(red, LOW);
    digitalWrite(green, HIGH);
  }
}
