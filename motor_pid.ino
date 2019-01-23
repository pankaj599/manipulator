float base_speed=90.0;
#include <TimerOne.h>
int outputA=2;                                                                                                           //pins of encoders
int outputB=4;                                                                                                           //pin of encoder
int dir1=7,p=0;                                                                                                          //direction pin of cytron
int pwm1=6;                                                                                                              //pwm pin cytron
float Rpm=0.00;                                                                                                          //variable for rpm
float ppr=600.00;                                                                                                        //pulse per revolution
volatile long long int Count=0;                                                                                          //variable for count
volatile long long int previousCount=0;                                                                                  //variable for placing previous count
#define timer .1                                                                                                         //timer=.1 second
float kp=0.09,ki=0.001,kd=0.55,total_error=0.0, p_error=0.0,d_error=0.0,i_error=0.0,previous_error=0.0,a=0.0,error=0.0;
float desired_rpm=150.0;

void setup() 
{
initEncoders();                                                    //function for encoder
Serial.begin(9600);    
                                                                
 Timer1.attachInterrupt(Timerhandler);                            //timer interrupt
 Timer1.initialize(1000000*timer);                                //time at which we required pulse (in microsecond)
}




/*PID*/

void loop()
{
    Serial.println("Rpm= "+String(Rpm)); //printing rpm
    error=desired_rpm-Rpm;

    d_error=error-previous_error;
    
    i_error=error+previous_error;
    
    total_error=kp*error+kd*d_error+ki*error;
    
    previous_error=error;
  
    if(total_error>0)                                              
    {
      digitalWrite(dir1,0);
      a =base_speed+total_error;
      analogWrite(pwm1,a);
    
    } 
   
    else if(total_error<0)
    {
      digitalWrite(dir1,0);
      a=base_speed-total_error;
      analogWrite(pwm1,a);
    }
        Serial.println("error= "+String(total_error));
            Serial.println("error before= "+String(error));
   
}



 void Timerhandler()
{
    noInterrupts();//detaching interrupts
    
    Rpm = ((Count -previousCount) * 60.0) / (timer * ppr);             //formula for rpm
    previousCount=Count;                                               //value for storing count
 
    interrupts();                                                      //enabling interrupts
    
}







void initEncoders()
{
  
  pinMode(outputA, INPUT);                                             //pin of encoder as input
  pinMode(outputB, INPUT);
  
pinMode(dir1,OUTPUT);                                                    //pin of cytron
pinMode(12,OUTPUT);
                                                                        //digitalWrite(dir,1);
//analogWrite(12,127);




attachInterrupt(digitalPinToInterrupt(outputA), TicksA, RISING);       //interrupt

}

  
  void TicksA()                                                          //ISR
  {
    
    
  if (digitalRead(outputB))
    {
       Count =Count+1;
          }
  else
  {
   
    Count =Count-1;
    
  }
 
   interrupts();                                                        // interrupts enabled after the ticks interrupts so that timerhandler is not missed or ignored.
}

