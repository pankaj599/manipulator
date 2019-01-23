int dir1=4;                                  //direction pin of hercules
int dir2=2;                                  // direction pin of hercules
int pwm1=3;                                   // pwm pin of hercules

void setup()
{
  Serial.begin(9600);
  pinMode(dir1,OUTPUT);
  pinMode(dir2,OUTPUT);
  pinMode(pwm1,OUTPUT);
  TCCR2B = TCCR2B & 0b11111000 |0x02;         //pwm prescaling   
 
}
void loop()
{
   digitalWrite(dir1,0);
   digitalWrite(dir2,1);
   analogWrite(pwm1,127
   );
}

