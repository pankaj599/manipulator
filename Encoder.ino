
 int CLK = 9;  // Pin 9 to clk on encoder
 int DT = 8;  // Pin 8 to DT on encoder
 int RotPosition = 0; 
 int rotation;  
 int value;
 boolean LeftRight;
 void setup() { 
   Serial.begin (9600);
   pinMode (CLK,INPUT);
   pinMode (DT,INPUT);                                                          
   rotation = digitalRead(CLK); 
     
 } 
 void loop()
 {
  float t1,t2 , rpm; 
   t1 = millis();
   value = digitalRead(CLK);
     if (value != rotation)
     {                                                    // we use the DT pin to find out which way we turning.
      if (digitalRead(DT) != value)
      {                                                  // Clockwise
       RotPosition ++;
       LeftRight = true;
      }
      else
      {                                                 //Counterclockwise
       LeftRight = false;
       RotPosition--;
      }                                             
     t2 = millis();                                             
     Serial.println(RotPosition);
                                                      
   } 
   rotation = value;
      
 } 
