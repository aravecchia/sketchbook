int t=500;

void setup()
{
pinMode(2, OUTPUT);
pinMode(3, OUTPUT);
pinMode(4, OUTPUT);
pinMode(5, OUTPUT);
pinMode(6, OUTPUT);
pinMode(7, OUTPUT);
pinMode(8, OUTPUT);
pinMode(9, OUTPUT);
}

void loop()
{
digitalWrite(2, HIGH);
delay(t);
digitalWrite(2, LOW);

digitalWrite(3, HIGH);
delay(t);
digitalWrite(3, LOW);

digitalWrite(4, HIGH);
delay(t);
digitalWrite(4, LOW);

digitalWrite(5, HIGH);
delay(t);
digitalWrite(5, LOW);

digitalWrite(6, HIGH);
delay(t);
digitalWrite(6, LOW);

digitalWrite(7, HIGH);
delay(t);
digitalWrite(7, LOW);

digitalWrite(8, HIGH);
delay(t);
digitalWrite(8, LOW);

digitalWrite(9, HIGH);
delay(t);
digitalWrite(9, LOW);
}
