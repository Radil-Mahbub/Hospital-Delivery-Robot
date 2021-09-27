#include <Arduino.h>

//IR sensor pins
#define LeftPin A0
#define RightPin A1

//color sensor settings
#define S0 2
#define S1 3
#define S2 4
#define S3 5
#define sensorOut A2
int frequency = 0;
const int lightLimit = 50;
#define buzzer 13

//motor settings
#define enA 11
#define enB 10
#define in1 9
#define in2 8
#define in3 7
#define in4 6
const int MaxSpeed = 100;

//To check for a blue light
void BlueColorDetect()
{
  // Setting red filtered photodiodes to be read
  digitalWrite(S2, LOW);
  digitalWrite(S3, HIGH);
  // Reading the output frequency
  frequency = pulseIn(sensorOut, LOW);

  
  while (frequency <= lightLimit)
  {
    analogWrite (enA, 0);
    analogWrite (enB, 0);

    tone (buzzer, 1000);
    delay (500);
    noTone (buzzer);
    delay (500);

    delay (5000);
  }

  if (frequency > lightLimit)
  {
     noTone (buzzer);

     analogWrite (enA, MaxSpeed);
     analogWrite (enB, MaxSpeed);


     digitalWrite (in1, HIGH );
     digitalWrite (in2, LOW);

     digitalWrite (in3, HIGH );
     digitalWrite (in4, LOW);
  }
}

void LineFollow()
{
  int Left = digitalRead (LeftPin);
  int Right= digitalRead (RightPin);

  if (Left == HIGH  && Right == LOW) //left turn
  {
   analogWrite (enA, MaxSpeed);
   analogWrite (enB, MaxSpeed);

   digitalWrite (in1, HIGH );
   digitalWrite (in2, LOW);

                  
   digitalWrite (in3, LOW );
   digitalWrite (in4, HIGH);
  }

  else if (Right == HIGH && Left == LOW)
  {
   analogWrite (enA, MaxSpeed);
   analogWrite (enB, MaxSpeed);

   digitalWrite (in1, LOW );
   digitalWrite (in2, HIGH);

   digitalWrite (in3, HIGH );
   digitalWrite (in4, LOW);
  }
  
  else
  {
    analogWrite (enA, MaxSpeed);
    analogWrite (enB, MaxSpeed);

    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
  
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
 
  }
}


void setup() 
{
  for (int i=enA; i<=in4; i++)
  {
    pinMode (i, OUTPUT);
  }

  for (int i=S0; i<=S3; i++)
  {
    pinMode (i, OUTPUT);
  }
  
  // Setting frequency-scaling to 20%
  digitalWrite(S0,HIGH);
  digitalWrite(S1,LOW);
  pinMode(buzzer, OUTPUT);

  //motors set to forward
  digitalWrite (in1, HIGH);
  digitalWrite (in2, LOW);

  digitalWrite (in3, HIGH);
  digitalWrite (in4, LOW);
}

void loop() 
{
   BlueColorDetect();
   LineFollow();
}