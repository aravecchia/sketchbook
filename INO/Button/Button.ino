int botao = 8;
int t = 10;
void setup()
{
  Serial.begin(9600);
  pinMode(botao, INPUT);
    }
  
void loop()
{
  boolean estado = digitalRead(botao);
  Serial.println(estado);
  delay(t);
  }
