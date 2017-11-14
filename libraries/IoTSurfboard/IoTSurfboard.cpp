#include <Arduino.h>
#include <Servo.h> 
#include <NewPing.h>
#include <DHT.h>
#include <EEPROM.h>
#include <DHT.h>
#include <IRremote.h>
#include <NewPing.h>
#include <Servo.h> 
#include <DS1307RTC.h>
#include <Time.h>
#include <Wire.h>
#include "IoTSurfboard.h"


IoTSurfboard board;

Servo servo_1; 
DHT dht(DHTPIN, DHTTYPE);
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); 
IRrecv irrecv(7);
decode_results results; 

void IoTSurfboard::setup() {
  Serial.begin(9600);
  pinMode(RELAY, OUTPUT);
  pinMode(SPEAKER, OUTPUT);
  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(BLUE, OUTPUT);

  dht.begin();
  servo_1.attach(SERVO);  
}
float IoTSurfboard::temperature() {
  return dht.readTemperature();
}
float IoTSurfboard::temperatureC() {
  return dht.readTemperature();
}
float IoTSurfboard::temperatureF() {
  return dht.readTemperature(true);
}
float IoTSurfboard::humidity() {
  return dht.readHumidity();
}
int IoTSurfboard::alcohol() {
  return analogRead(ALCOHOL);
}
int IoTSurfboard::potenciometer() {
  return analogRead(POTENCIOMETER);
}
int IoTSurfboard::light() {
  return analogRead(LDR);
}
void IoTSurfboard::relay(boolean b) {
  digitalWrite(RELAY, b);
}
void IoTSurfboard::speaker(boolean b) {
  digitalWrite(SPEAKER, b);
}

void IoTSurfboard::red(int b) {
  analogWrite(10, b);
}
void IoTSurfboard::green(int b) {
  analogWrite(6, b);
}
void IoTSurfboard::blue(int b) {
  analogWrite(5, b);
} 
void IoTSurfboard::rgb(int r, int g, int b) {
  red(r);
  green(g);
  blue(b);
}
void IoTSurfboard::printJSON(char* n, char* v) {
  Serial.print("{");
  Serial.print(n);
  Serial.print(":\"");
  Serial.print(v);
  Serial.println("\"}");
}
void IoTSurfboard::printJSON(char* n, int v1) {
  Serial.print("{");
  Serial.print(n);
  Serial.print(":\"");
  Serial.print(v1);
  Serial.println("\"}");
}

int IoTSurfboard::distance() {
  unsigned int uS = sonar.ping(); 
  return uS / US_ROUNDTRIP_CM;
}

void IoTSurfboard::servo(int pos) {
  servo_1.write(pos);
}

//WRAPER

char* humidity(char* args) {
  Serial.print(board.humidity());
  return "";
}
char* distance(char* args) {
  Serial.print(board.distance());
  return "";
}

char* temperature(char* args) {
  Serial.print(board.temperature());
  return "";
}

char* servo1(char* args) {
  int pos = atoi(args);
  board.servo(pos);
  return args;
}

void print2digits(int number) {
  if (number >= 0 && number < 10) {
    Serial.write('0');
  }
  Serial.print(number);
}

char* rtc(char* args) {
  tmElements_t tm;
  if (RTC.read(tm)) {
    Serial.print(tm.Month);
    Serial.write('/');
    Serial.print(tm.Day);
    Serial.write('/');
    Serial.print(tmYearToCalendar(tm.Year));
    Serial.print(' ');
    print2digits(tm.Hour);
    Serial.write(':');
    print2digits(tm.Minute);
    Serial.write(':');
    print2digits(tm.Second);

  } else {
    if (RTC.chipPresent()) {
      Serial.print("RTC-ERROR1");

    } else {
      Serial.print("RTC-ERROR2");

    }
  }
  return "";
}



void dump(decode_results *results) {
  int count = results->rawlen;
  if (results->decode_type == UNKNOWN) {
    Serial.print("Unknown encoding: ");
  } 
  else if (results->decode_type == NEC) {
    Serial.print("Decoded NEC: ");
  } 
  else if (results->decode_type == SONY) {
    Serial.print("Decoded SONY: ");
  } 
  else if (results->decode_type == RC5) {
    Serial.print("Decoded RC5: ");
  } 
  else if (results->decode_type == RC6) {
    Serial.print("Decoded RC6: ");
  }
  else if (results->decode_type == PANASONIC) {  
    Serial.print("Decoded PANASONIC - Address: ");
    Serial.print(results->panasonicAddress,HEX);
    Serial.print(" Value: ");
  }
  else if (results->decode_type == JVC) {
     Serial.print("Decoded JVC: ");
  }
  Serial.print(results->value, HEX);
  Serial.print(" (");
  Serial.print(results->bits, DEC);
  Serial.println(" bits)");
  Serial.print("Raw (");
  Serial.print(count, DEC);
  Serial.print("): ");
  Serial.println("");
}

void ir_receiver(){
  Serial.println("Aguardando comando IR .....");
  while (!Serial.available()) {
    if (irrecv.decode(&results)) {
      Serial.println(results.value, HEX);
      dump(&results);
      irrecv.resume(); // Receive the next value
    }
    delay(100);
  } 
}