int botao = 10;
int verde = 11;
int vermelho = 12;
int t = 10;
void setup()
{
    pinMode(botao, INPUT);
    pinMode(verde, OUTPUT);
    pinMode(vermelho, OUTPUT);
}
void loop()
{
    boolean estado = digitalRead(botao);
    if (estado == 1)
    {
        digitalWrite(verde, HIGH);
        digitalWrite(vermelho, LOW);
    }
    else
    {
        digitalWrite(verde, LOW);
        digitalWrite(vermelho, HIGH);
    }
    delay(t);
}
