
/*
 Bi-directional communication
 Receive LED ON OFF command from Raspi, to the task, send a response to Raspi which it can process.   
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
     Serial.write("success");
   }
   else if(message=="OFF")
   {
    digitalWrite(LED,0);
    Serial.write("fail");
   }
	
 }

}
