
/*
 switch LED ON/OFF from Raspi 
*/


const int LED = 51; // digital pwm pin


void setup() 
{
 Serial.begin(9600);
 pinMode(LED,OUTPUT);

}

void loop()
{

 if(Serial.available()>0)
 {
   String message = Serial.readStringUntil('\n');
   Serial.println(message);
   if(message=="ON")
   {
     digitalWrite(LED, 50);
   }
   else if(message=="OFF")
   {
    digitalWrite(LED,0);
   }
	
 }

}
