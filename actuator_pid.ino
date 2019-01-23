/*the actuator that we used is a closed loop actuator which gives positional feedback (it is basically its rheostat value)*/
 
 int desired_value=500;                                           //the feedback value where we need to stop it 
int error=0;

int dir1=5;                                                        //setting directional pin of hercules
int dir2=7;                                                        //setting directional pin of hercules
int pwm1=6;                                                        //setting pwm pin of hercules
int analog_pin=1;                                                  //analog pin of actuator for positional feedback
int digital_value;                                                 //variable to store current value of feedback
int distance=0;
float base_speed=100.0;                                            //base speed of actuator on ehich error is added (it is placed by hit and try)
float a=0.0;
float kp=0.15,ki=0,kd=0.10;
float total_error=0.0,previous_error=0.0,d_error=0.0, i_error=0.0;


void setup()
          {
            Serial.begin(9600);
            pinMode(dir1,OUTPUT);                                             //setting dir1, dir2, analog_pin and pwm1 as output pin
            pinMode(pwm1,OUTPUT);                                             
            pinMode(analog_pin,OUTPUT);
            pinMode(dir2,OUTPUT); 
          }



  /*PID*/

  
void loop()
        { 
         
          digital_value=analogRead(analog_pin);                               //taking data from analog pin and stored it in variable
          
          error=-desired_value+digital_value;                                 //error= current - required
        
          d_error=error- previous_error;
          i_error=error+previous_error;
          
          total_error=kp*error+kd*d_error+i_error*ki;
          previous_error=error;                                              
                  if(error<-3)                                                //setting an acceptable range of error 
                     {
                        
                        digitalWrite(dir1,1);
                        digitalWrite(dir2,0);
                        
                        a=base_speed-total_error;
                        analogWrite(pwm1,a);                                 //passing the value to pwm
                      }
            else if(error>3)
                    {    //delay(10);
                        digitalWrite(dir1,0);
                        digitalWrite(dir2,1);
                        a=base_speed+total_error;
                       
                        analogWrite(pwm1,a);
                   }
            else 
                  {
                    digitalWrite(pwm1,0);
                  }
              
             Serial.println("digital_value=" +String(digital_value));
             
             distance=map(digital_value,25,942,20,320);                       //conversion of resistance value to its equivalent length (actuator dependent) 
             Serial.println("distance=" +String(distance));
       }
 
