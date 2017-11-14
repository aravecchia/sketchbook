
//#define PCF8574A_ID 0x70  //01110000 :000 slave address
#define PCF8574_ID_Read 0x36   //01000001 ; 001=slave address  ; Read=1
#define PCF8574_ID_Write 0x40   //01000001 ; 000=slave address  ; Write = 0
// Arduino Pins
#define SDA   0//18                         // Serial data
#define SCL   1//19                         // Serial clock
char outdata;


void i2c_start(void);
void i2c_stop(void);
void i2c_write(unsigned char output_data);
void PCF8574A_Write(unsigned char data);
void i2c_write_bit(int data_bit);


void i2c_start(void)
{
  pinMode(SCL, OUTPUT);
  pinMode(SDA, OUTPUT);
  digitalWrite(SDA, HIGH);
  digitalWrite(SCL, HIGH);
  
  digitalWrite(SDA, LOW);
  delayMicroseconds(1);
  digitalWrite(SCL, LOW);
  delayMicroseconds(1);
}
void i2c_acknowledge(void)
{
  digitalWrite(SDA, LOW);
  delayMicroseconds(1);
  digitalWrite(SCL, HIGH);
  delayMicroseconds(1);
  digitalWrite(SCL, LOW);
  delayMicroseconds(1);
  digitalWrite(SDA, LOW);
  delayMicroseconds(1);
}
void i2c_stop(void)
{
  digitalWrite(SCL, HIGH);
  delayMicroseconds(1);
  digitalWrite(SDA, HIGH);
}
void i2c_write(unsigned char output_data)
{
  int iBit=0;
  for(int iloop = 0 ; iloop < 8 ; iloop++)
  {
    iBit = ((output_data & 0x80) >> 7 ) ; 
    delayMicroseconds(1);
    digitalWrite(SDA,iBit);   // bit output
    delayMicroseconds(1);
    digitalWrite(SCL, HIGH);
    delayMicroseconds(1);
    digitalWrite(SCL, LOW);
    delayMicroseconds(1);
    digitalWrite(SDA, LOW);
    output_data = output_data << 1 ; 
  }
}
byte i2c_read (void)
{
  byte buff_byte_input=0x00;
  for(byte icount=0 ; icount<8 ; icount++)
  {
    pinMode(SDA, INPUT);
    digitalWrite(SDA, LOW);
    digitalWrite(SCL, HIGH);
    buff_byte_input = buff_byte_input << 1 ;
    buff_byte_input |= digitalRead(SDA);
    delayMicroseconds(1);
    digitalWrite(SCL, LOW);
    delayMicroseconds(1);
    digitalWrite(SDA, LOW);
  }
  //Serial.println(buff_byte_input,HEX);  
  return (buff_byte_input);
}
void PCF8574_Write(byte ibuff_write)
{
  i2c_start();
  i2c_write(PCF8574_ID_Write);
  i2c_acknowledge();
  i2c_write(ibuff_write);
  i2c_acknowledge(); 
  i2c_stop();
}
byte PCF8574_Read(void)
{
  byte ibuff;
  i2c_start();
  i2c_write(PCF8574_ID_Read);
  i2c_acknowledge();
  ibuff=i2c_read();
  i2c_acknowledge(); 
  i2c_stop();
  return(ibuff);
}
void setup() 
{ 
  //Serial.begin(9600); 
  pinMode(2, OUTPUT);
}


void loop()
{    
  byte buff;  
  //Serial.println(PCF8574_Read(),HEX);
  buff=PCF8574_Read();
  if(buff==0xF0)  
  digitalWrite(2, LOW);
  else digitalWrite(2, HIGH);
  //delay(1000);
}
