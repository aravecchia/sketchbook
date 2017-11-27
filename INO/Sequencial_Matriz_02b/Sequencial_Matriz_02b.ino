int t = 100;

int matriz[8][4] =
{
  {
    1, 0, 0, 0
  }
  ,
  {
    1, 0, 0, 0
  }
  ,
  {
    1, 1, 0, 0
  }
  ,
  {
    0, 1, 0, 0
  }
  ,
  {
    0, 1, 1, 0
  }
  ,
  {
    0, 0, 1, 0
  }
  ,
  {
    0, 0, 1, 1
  }
  ,
  {
    0, 0, 0, 1
  }
};

void setup()
{
  for (int led = 2; led < 6; led++)
  {
    pinMode(led, OUTPUT);
  }
}

void loop()
{
  for (int y = 0; y < 8; y++)
  {
    for (int x = 0; x < 8; x++)
    {
      digitalWrite(x + 2, matriz[y][x]);
      delay(t);
      digitalWrite(x + 2, matriz[y][x]);
    }
  }
}
