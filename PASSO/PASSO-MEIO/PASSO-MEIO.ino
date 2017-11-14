int t =10;
void setup() {
  for (int x = 2; x < 6; x++)
  {
    pinMode(x, OUTPUT);
  }
}
void loop() {
  for (int x = 2; x < 6; x++)
  {
    if (x == 2)
    {
      digitalWrite(x + 3, HIGH);
      delay(t);
      digitalWrite(x, HIGH);
      delay(t);
      digitalWrite(x + 3, LOW);
    }
    else
    {
      digitalWrite(x - 1, HIGH);
      delay(t);
      digitalWrite(x, HIGH); //liga 4
      delay(t);
      digitalWrite(x - 1, LOW);
    }
  }
}
