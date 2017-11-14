/*
 * codeexample for useing a 4051 * analog multiplexer / demultiplexer
 * by david c. and tomek n.* for k3 / malm� h�gskola
 *
 * edited by Ross R.
 */


void setup()
{
  Serial.begin(9600);
  // turn on LED to signal the start of the calibration period
}

void loop ()
{


  int i;
  for (i=2; i<=7; i++)
  {
    pinMode(i, OUTPUT);    // s0 s1 s2 s0a s1a s2a
  }

  int LED;
  for (LED=30; LED<=45; LED++)
  {
    pinMode(LED, OUTPUT);    // s0 s1 s2 s0a s1a s2a
  }



  int x = 1000;
  //delay
  int y = 0;
  //numero da porta no 4051

  digitalWrite(5, LOW);
  digitalWrite(6, LOW);
  digitalWrite(7, LOW);  
  Serial.println("Slave 1");
  { 
    { 
      digitalWrite(2, LOW);
      digitalWrite(3, LOW);
      digitalWrite(4, LOW);
      for (y; y<=7; y++)
      {
        Serial.print("y=");
        Serial.println(y);
        Serial.print("L=");
        Serial.println(analogRead(A0));
        delay(x);
        if (analogRead(A0)>=400)
        {
          digitalWrite(30, HIGH); 
        }
        else
        {
          digitalWrite(30, LOW); 
        }
      }
    }

    { 
      digitalWrite(2, HIGH);
      digitalWrite(3, LOW);
      digitalWrite(4, LOW);

      for (y; y<=7; y++)
      {
        Serial.print("y=");
        Serial.println(y);
        Serial.print("L=");
        Serial.println(analogRead(A0));
        delay(x);
        if (analogRead(A0)>=400)
        {
          digitalWrite(31, HIGH); 
        }
        else
        {
          digitalWrite(31, LOW); 
        }
      }
    }

    { 
      digitalWrite(2, LOW);
      digitalWrite(3, HIGH);
      digitalWrite(4, LOW);

      for (y; y<=7; y++)
      {
        Serial.print("y=");
        Serial.println(y);
        Serial.print("L=");
        Serial.println(analogRead(A0));
        delay(x);
        if (analogRead(A0)>=400)
        {
          digitalWrite(32, HIGH); 
        }
        else
        {
          digitalWrite(32, LOW); 
        }
      }
    }

    { 
      digitalWrite(2, HIGH);
      digitalWrite(3, HIGH);
      digitalWrite(4, LOW);

      for (y; y<=7; y++)
      {
        Serial.print("y=");
        Serial.println(y);
        Serial.print("L=");
        Serial.println(analogRead(A0));
        delay(x);
        if (analogRead(A0)>=400)
        {
          digitalWrite(33, HIGH); 
        }
        else
        {
          digitalWrite(33, LOW); 
        }
      }
    }

    { 
      digitalWrite(2, LOW);
      digitalWrite(3, LOW);
      digitalWrite(4, HIGH);

      for (y; y<=7; y++)
      {
        Serial.print("y=");
        Serial.println(y);
        Serial.print("L=");
        Serial.println(analogRead(A0));
        delay(x);
        if (analogRead(A0)>=400)
        {
          digitalWrite(34, HIGH); 
        }
        else
        {
          digitalWrite(34, LOW); 
        }
      }
    }

    { 
      digitalWrite(2, HIGH);
      digitalWrite(3, LOW);
      digitalWrite(4, HIGH);

      for (y; y<=7; y++)
      {
        Serial.print("y=");
        Serial.println(y);
        Serial.print("L=");
        Serial.println(analogRead(A0));
        delay(x);
        if (analogRead(A0)>=400)
        {
          digitalWrite(35, HIGH); 
        }
        else
        {
          digitalWrite(35, LOW); 
        }
      }
    }

    { 
      Serial.print("y=");
      digitalWrite(2, LOW);
      digitalWrite(3, HIGH);
      digitalWrite(4, HIGH);

      for (y; y<=7; y++)
      {
        Serial.print("y=");
        Serial.println(y);
        Serial.print("L=");
        Serial.println(analogRead(A0));
        delay(x);
        if (analogRead(A0)>=400)
        {
          digitalWrite(36, HIGH); 
        }
        else
        {
          digitalWrite(36, LOW); 
        }
      }
    }

    { 
      digitalWrite(2, HIGH);
      digitalWrite(3, HIGH);
      digitalWrite(4, HIGH);

      for (y; y<=7; y++)
      {
        Serial.print("y=");
        Serial.println(y);
        Serial.print("L=");
        Serial.println(analogRead(A0));
        delay(x);
        if (analogRead(A0)>=400)
        {
          digitalWrite(37, HIGH); 
        }
        else
        {
          digitalWrite(37, LOW); 
        }
      }
    }
  }
  digitalWrite(5, HIGH);
  digitalWrite(6, LOW);
  digitalWrite(7, LOW);  
  Serial.println("Slave 2");
  { 
    { 
      digitalWrite(2, LOW);
      digitalWrite(3, LOW);
      digitalWrite(4, LOW);

      for (y; y<=7; y++)
      {
        Serial.print("y=");
        Serial.println(y);
        Serial.print("L=");
        Serial.println(analogRead(A0));
        delay(x);
        if (analogRead(A0)>=400)
        {
          digitalWrite(38, HIGH); 
        }
        else
        {
          digitalWrite(38, LOW); 
        }
      }
    }

    { 
      digitalWrite(2, HIGH);
      digitalWrite(3, LOW);
      digitalWrite(4, LOW);

      for (y; y<=7; y++)
      {
        Serial.print("y=");
        Serial.println(y);
        Serial.print("L=");
        Serial.println(analogRead(A0));
        delay(x);
        if (analogRead(A0)>=400)
        {
          digitalWrite(39, HIGH); 
        }
        else
        {
          digitalWrite(39, LOW); 
        }
      }
    }

    { 
      digitalWrite(2, LOW);
      digitalWrite(3, HIGH);
      digitalWrite(4, LOW);

      for (y; y<=7; y++)
      {
        Serial.print("y=");
        Serial.println(y);
        Serial.print("L=");
        Serial.println(analogRead(A0));
        delay(x);
        if (analogRead(A0)>=400)
        {
          digitalWrite(40, HIGH); 
        }
        else
        {
          digitalWrite(40, LOW); 
        }
      }
    }

    { 
      digitalWrite(2, HIGH);
      digitalWrite(3, HIGH);
      digitalWrite(4, LOW);

      for (y; y<=7; y++)
      {
        Serial.print("y=");
        Serial.println(y);
        Serial.print("L=");
        Serial.println(analogRead(A0));
        delay(x);
        if (analogRead(A0)>=400)
        {
          digitalWrite(41, HIGH); 
        }
        else
        {
          digitalWrite(41, LOW); 
        }
      }
    }

    { 
      digitalWrite(2, LOW);
      digitalWrite(3, LOW);
      digitalWrite(4, HIGH);

      for (y; y<=7; y++)
      {
        Serial.print("y=");
        Serial.println(y);
        Serial.print("L=");
        Serial.println(analogRead(A0));
        delay(x);
        if (analogRead(A0)>=400)
        {
          digitalWrite(42, HIGH); 
        }
        else
        {
          digitalWrite(42, LOW); 
        }
      }
    }

    { 
      digitalWrite(2, HIGH);
      digitalWrite(3, LOW);
      digitalWrite(4, HIGH);

      for (y; y<=7; y++)
      {
        Serial.print("y=");
        Serial.println(y);
        Serial.print("L=");
        Serial.println(analogRead(A0));
        delay(x);
        if (analogRead(A0)>=400)
        {
          digitalWrite(43, HIGH); 
        }
        else
        {
          digitalWrite(43, LOW); 
        }
      }
    }

    { 
      digitalWrite(2, LOW);
      digitalWrite(3, HIGH);
      digitalWrite(4, HIGH);

      for (y; y<=7; y++)
      {
        Serial.print("y=");
        Serial.println(y);
        Serial.print("L=");
        Serial.println(analogRead(A0));
        delay(x);
        if (analogRead(A0)>=400)
        {
          digitalWrite(44, HIGH); 
        }
        else
        {
          digitalWrite(44, LOW); 
        }
      }
    }

    { 
      digitalWrite(2, HIGH);
      digitalWrite(3, HIGH);
      digitalWrite(4, HIGH);

      for (y; y<=7; y++)
      {
        Serial.print("y=");
        Serial.println(y);
        Serial.print("L=");
        Serial.println(analogRead(A0));
        delay(x);
        if (analogRead(A0)>=400)
        {
          digitalWrite(45, HIGH); 
        }
        else
        {
          digitalWrite(45, LOW); 
        }
      }
    }
  }
  {
  int x = 49;
  // tempo que o LED fica acesso
  int y = 1;
  // tempo que o LED fica apagado  
  int i;
  for (i=30;i<=45;i++)
  {
    Serial.println(i);
    digitalWrite(i, HIGH);
    delay(x);
    digitalWrite(i, LOW);
    delay(y);
  }
  for (i--;i>=30;i--)
  {
    Serial.println(i);
    digitalWrite(i, HIGH);
    delay(x);
    digitalWrite(i, LOW);
    delay(y);
  }
}

}





