#include <Arduino.h>
/*Desenvolvido por Alexandre Aravecchia
  Projetista, desenvolvedor, programador
 aravecchia@gmail.com
 www.aravecchia.weebly.com
 */
int t=1000;
void setup()
{                
  for (int pino = 2; pino <10; pino++)
  {
    pinMode(pino, OUTPUT);   
  } 
  Serial.begin(9600);
}

// the loop routine runs over and over again forever:
void loop() 
{
  int matriz[10][8] = {
    { 
      1,1,1,1,1,1,0,1  
    }
    ,
    {   
      0,1,1,0,0,0,0,1  
    }
    ,
    {  
      1,1,0,1,1,0,1,1  
    }
    ,
    { 
      1,1,1,1,0,0,1,1  
    }
    ,
    {
      0,1,1,0,0,1,1,1   
    }
    ,
    {    
      1,0,1,1,0,1,1,1  
    }
    ,
    {  
      1,0,1,1,1,1,1,1  
    }
    ,
    { 
      1,1,1,0,0,0,0,1  
    }
    ,
    { 
      1,1,1,1,1,1,1,1  
    }
    ,
    {
      1,1,1,1,0,1,1,1
    }
  };
  for (int y=0; y<10; y++)
  {  
    Serial.print(y);
    Serial.print(" ELEFANTES");
    for (int z=0; z<=(y-1); z++)
    {
      if (y==1)
      {
       Serial.print(" incomoda"); 
      }
       else
       {
       Serial.print(" INCOMODAM"); 
       }
    }
    Serial.println(" muita gente...");
    for (int x=0; x<9; x++)
    {
      digitalWrite((x+2), matriz[y][x]);   // turn the LED on (HIGH is the voltage level)
    }
    if (y==0)
      delay(3*t);
    else
      delay(2*t);
  }
}















