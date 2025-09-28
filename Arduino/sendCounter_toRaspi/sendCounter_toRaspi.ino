/*
	SEND COUNTER TO SERIAL PORT
*/


unsigned int counter = 0;
unsigned int lastTime = 0;
const int D = 1000; // send every 1seconds

void setup() {
 Serial.begin(9600);

}

void loop() {

 // every 500ms we send a the counter to the serial port and increment it
 if(millis()-lastTime>D)
 {
   Serial.println(counter);
   counter++;

   lastTime=millis();
 }

 if(Serial.available()>0)
 {
    String command = Serial.readStringUntil('\n');
    //Serial.print("command: ");
    // Serial.print(command); 
    if(command.equals("reset"))
    {
       counter = 0;
    }
 }


}
