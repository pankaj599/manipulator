#include <PWM.h>
int32_t frequency=1000;                       //setting up a frequency

//int dir1=4;
int dir2=2;
int pwm1=3;

void setup()
{

  Serial.begin(9600);
  InitTimersSafe();
  SetPinFrequencySafe(pwm1,frequency);        //providing that frequency to pwm
  //pinMode(dir1,OUTPUT);
 pinMode(dir2,OUTPUT);
  pinMode(pwm1,OUTPUT);

 
}
void loop()
{
   //digitalWrite(dir1,0);
  digitalWrite(dir2,1);
   analogWrite(pwm1,255);
}

