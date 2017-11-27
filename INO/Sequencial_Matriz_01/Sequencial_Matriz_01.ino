int t = 200;

//boolean matriz[y][x]
boolean matriz[8][4] =
{
  {
    1, 0, 0, 0
  }//0
  ,
  {
    1, 1, 0, 0
  }//1
  ,
  {
    0, 1, 0, 0
  }//2
  ,
  {
    0, 1, 1, 0
  }//3
  ,
  {
    0, 0, 1, 0
  }//4
  ,
  {
    0, 0, 1, 1
  }//5
  ,
  {
    0, 0, 0, 1
  }//6
  ,
  {
    1, 0, 0, 1
  }//7
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
    for (int x = 0; x < 4; x++)
    {
      digitalWrite(x + 2, matriz[y][x]);
      delay(t);
    }
  }
}
