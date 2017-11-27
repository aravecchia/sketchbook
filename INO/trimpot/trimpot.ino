int botao = A0;
int led=13;

void setup()
{
  Serial.begin(9600);
  pinMode(botao, INPUT);
    pinMode(led, OUTPUT);
}

void loop()
{
  int t = analogRead(botao)/5;
digitalWrite(led, HIGH);
  delay(t);
  digitalWrite(led, LOW);
  delay(t);
}
