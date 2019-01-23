#include <TimerOne.h>
int outputA=2;                                                   //pins of encoders
int outputB=4;                                                   //pin of encoder
        
float Rpm=0.00;                                                   //variable for rpm
float ppr=20.00;                                                  //pulse per revolution
volatile long long int Count=0;
#define timer 0.2                                                //timer=0.2 set accordingly
volatile long long int previousCount=0.0;
int dir=7;                                                       //direction pin of cytron
int pwm1=6;                                                      //pwm pin cytron+


void setup() 
{
  initEncoders();                                                 //function for encoder
  Serial.begin(9600);    
  interrupts();                                                     
                                                    
 Timer1.attachInterrupt(Timerhandler);                            //timer interrupt
 Timer1.initialize(1000000*timer);                                //time at which we required pulse (in microsecond)
}


void initEncoders()
{
  
  pinMode(outputA, INPUT);                                             //pin of encoder as input
  pinMode(outputB, INPUT);
 pinMode(dir,OUTPUT);                                                    //pin of cytron
pinMode(pwm1,OUTPUT);
                                                                        //digitalWrite(dir,1)                      
analogWrite(pwm1,127);
                                              
attachInterrupt(digitalPinToInterrupt(outputA), TicksA, RISING);       //interrupt
}

  void TicksA()                                                          //ISR
  {
    
   
  if (digitalRead(outputB))                                             //since interrupt is applied on A, take reading on B
    {
       Count =Count+1;
        
      // Serial.println("count=" +String(Count));
    }
  else
  {
   
    Count =Count-1;
  // Serial.println("count=" +String(Count));
  }
 
 //  interrupts();                                                        // interrupts enabled after the ticks interrupts so that timerhandler is not missed or ignored.
}



 void Timerhandler()
{
  noInterrupts();                                                     //detaching interrupts
    Rpm = ((Count -previousCount) * 60.0) / (timer * ppr);             //formula for rpm
   
     previousCount=Count;                                             //variable for storing count
   // Serial.println("Rpm= "+String(Rpm));  
interrupts();                                                        //enabling interrupts
     
}
void loop()
{
   Serial.println("Rpm= "+String(Rpm)); 


}
