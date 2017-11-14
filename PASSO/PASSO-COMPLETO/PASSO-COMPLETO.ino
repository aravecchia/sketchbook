int t=2000;
void setup(){
for (int x=2; x<6; x++)
{
  pinMode(x, OUTPUT);
  }
}

void loop() {
 for (int x=2; x<6; x++)
{
digitalWrite(x, HIGH);
delay(t);
digitalWrite(x, LOW);
  }
}
