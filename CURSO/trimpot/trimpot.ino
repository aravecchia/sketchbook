int botao = A0;
int t = 100;

void setup()
{
  Serial.begin(9600);
  pinMode(botao, INPUT);
}

void loop()
{
  int sensor = analogRead(botao);
  Serial.println(sensor);
  delay(t);
}
