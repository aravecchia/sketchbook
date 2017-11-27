int botao = A0; //comentario
int verde = 11;
int vermelho = 12;
int t = 100;
void setup()
{
  Serial.begin(9600);
  pinMode(botao, INPUT);
  pinMode(verde, OUTPUT);
  pinMode(vermelho, OUTPUT);
}
void loop()
{
  int leitura = analogRead(botao);
  Serial.print(leitura);
  if (leitura > 512)
  {
    Serial.println(" - vermelho - mesa aquecida");
    digitalWrite(verde, LOW);
    digitalWrite(vermelho, HIGH);
  }
  else
  {
    Serial.println(" - verde - mesa fria");
    digitalWrite(verde, HIGH);
    digitalWrite(vermelho, LOW);
  }
  delay(t);
}
