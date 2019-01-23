/*this code is for taking data from potentiometer and use it as a pwm*/

int pot=0;                                                         //analog pin 0 is assign to potentiometer  
int pot_val=0;  
int dir=7;                                                        //setting directional pin of cytron
int pwm1=6;                                                        //setting pwm pin of cytron
int pwm_i=0; 
int pwm_b=0;
int p;
void setup()
{
  Serial.begin(9600);
  pinMode(dir,OUTPUT);                                             //setting pin 7 as output pin
  pinMode(pwm1,OUTPUT);
  }
void loop()
{
  pwm_b=pwm_i;

pot_val = analogRead(pot);
p=map(pot_val,0,1023,1,255);
analogWrite(pwm1,p);                                               //pwm 


pwm_i=analogRead(pwm1);                                            //assigning pwm reading to a variable
Serial.println("pwm=" +String(pwm_i));

if(pwm_i>pwm_b)
digitalWrite(dir,1);
else
digitalWrite(dir,0);
}




