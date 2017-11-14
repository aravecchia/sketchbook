int t = 100;

void setup()
{
  for (int x = 2; x < 10; x++)
  {
    pinMode(x, OUTPUT);
  }
}

void loop()
{
  for (int x = 2; x < 10; x++)
  {
    digitalWrite(x, HIGH);
    delay(t);
    digitalWrite(x, LOW);
  }
for(int x=8; x>2; x--)
 {
    digitalWrite(x, HIGH);
    delay(t);
    digitalWrite(x, LOW);
  }  
}
