/*
   Telegram Raspi Arduino LED ON/OFF
*/


const int LED = 51; // digitalPWM



void setup() {
   Serial.begin(9600);
   pinMode(LED, OUTPUT);
   

}

void loop() {
   if(Serial.available()>0)
   {
      String cmd = Serial.readStringUntil('\n');
      if(cmd.equals("ON"))
      {
        analogWrite(LED,50);
      }
      else if(cmd.equals("OFF"))
      {

        analogWrite(LED,0);
      }

   }
  
}
