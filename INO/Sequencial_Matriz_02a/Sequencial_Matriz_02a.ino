int t = 10;
int sensor = A0;

boolean matriz[16][8] =
{
  {
    1, 0, 0, 0, 0, 0, 0, 0
  }
  ,
  {
    1, 1, 0, 0, 0, 0, 0, 0
  }
  ,
  {
    0, 1, 0, 0, 0, 0, 0, 0
  }
  ,
  {
    0, 1, 1, 0, 0, 0, 0, 0
  }
  ,
  {
    0, 0, 1, 0, 0, 0, 0, 0
  }
  ,
  {
    0, 0, 1, 1, 0, 0, 0, 0
  }
  ,
  {
    0, 0, 0, 1, 0, 0, 0, 0
  }
  ,
  {
    0, 0, 0, 1, 1, 0, 0, 0
  }
  ,
  {
    0, 0, 0, 0, 1, 0, 0, 0
  }
  ,
  {
    0, 0, 0, 0, 1, 1, 0, 0
  }
  ,
  {
    0, 0, 0, 0, 0, 1, 0, 0
  }
  ,
  {
    0, 0, 0, 0, 0, 1, 1, 0
  }
  ,
  {
    0, 0, 0, 0, 0, 0, 1, 0
  }
  ,
  {
    0, 0, 0, 0, 0, 0, 1, 1
  }
  ,
  {
    0, 0, 0, 0, 0, 0, 0, 1
  }
  ,
  {
    1, 0, 0, 0, 0, 0, 0, 1
  }
};

void setup()
{
  for (int led = 2; led < 10; led++)
  {
    pinMode(led, OUTPUT);
  }
  pinMode(sensor, INPUT);
}

void loop()
{
  int  valor = analogRead(sensor);
  int  y = map(valor, 0, 1023, 0, 15);
  for (int x = 0; x < 8; x++)
  {
    digitalWrite(x + 2, matriz[y][x]);
  }
  delay(t);
}
