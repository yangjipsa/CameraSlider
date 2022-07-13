// Arduino Nano
// Stepper 28BYJ-48
// Bluetooth Module HC06 

#include <SoftwareSerial.h>

const int BT_Rx = 2;
const int BT_Tx = 3;

const int IN1 = 8;
const int IN2 = 7;
const int IN3 = 6;
const int IN4 = 5;

int Speed = 1200; //MAX 1200, MIN 9600

int lookup[8] = {B01000,B01100,B00100,B00110,B00010,B00011,B00001,B01001};

SoftwareSerial bt (BT_Rx, BT_Tx);


void setup()
{
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  bt.begin(9600);
  Serial.begin(9600);
}

void loop()
{
 /* for (int i=0 ; i < 8 ; i++)
  {
    digitalWrite(IN1, bitRead(lookup[7-i],0));
    digitalWrite(IN2, bitRead(lookup[7-i],1));
    digitalWrite(IN3, bitRead(lookup[7-i],2));
    digitalWrite(IN4, bitRead(lookup[7-i],3));
    delayMicroseconds(Speed);
  }*/
  if (bt.available())
  {
    char rcvCmd = bt.read();

    if (rcvCmd == 's') { Speed = 9600; } // slow
    else if (rcvCmd == 'n') { Speed = 5400; } // normal
    else if (rcvCmd == 'f') { Speed = 1200; } // fast
    else if (rcvCmd == 'G')
    {
      while(!(bt.read()=='S'))
      {
        for (int i=0 ; i < 8 ; i++)
        {
          digitalWrite(IN1, bitRead(lookup[i],0));
          digitalWrite(IN2, bitRead(lookup[i],1));
          digitalWrite(IN3, bitRead(lookup[i],2));
          digitalWrite(IN4, bitRead(lookup[i],3));
          delayMicroseconds(Speed);
        }
      }
    }
    else if (rcvCmd == 'B')
    {
      while(!(bt.read()=='S'))
      {
        for (int i=0 ; i < 8 ; i++)
        {
          digitalWrite(IN1, bitRead(lookup[7-i],0));
          digitalWrite(IN2, bitRead(lookup[7-i],1));
          digitalWrite(IN3, bitRead(lookup[7-i],2));
          digitalWrite(IN4, bitRead(lookup[7-i],3));
          delayMicroseconds(Speed);
        }
      }
    }
  }
}
  


