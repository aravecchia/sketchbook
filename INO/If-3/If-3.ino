int botao = 10;
int verde = 11;
int vermelho = 12;
int t = 10;

void setup()
{
  Serial.begin(9600);
    pinMode(botao, INPUT);
    pinMode(verde, OUTPUT);
    pinMode(vermelho, OUTPUT);
}

void loop()
{
    boolean estado = digitalRead(botao);
    digitalWrite(verde, estado);
    digitalWrite(vermelho, !estado);
    Serial.print("Botao no estado: ");
    Serial.print(estado);
    if (estado == 1)
    {
        Serial.println(" - verde - garagem fechada");
    }
    else
    {
        Serial.println(" - vermelho - garagem aberta");
    }
    delay(t);
}
