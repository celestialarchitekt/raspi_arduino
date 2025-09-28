/*
	Button LED Raspi Arduino

*/



const int BUTTON = 49; // digitalPWM
const int LED = 51;    // digitalPWM

bool ledState = false;

unsigned long debounceTime = 50;
unsigned long lastTime = 0;

int lastButtonState = 0;
int buttonState = 0;


void setup() {
  Serial.begin(9600);
  
  pinMode(BUTTON, INPUT_PULLUP);
  pinMode(LED, OUTPUT);
  
}

void loop() {
  int reading = digitalRead(BUTTON);
  
   if(reading!=lastButtonState)
   {
     lastTime = millis();
   }
  
   if(millis() - lastTime > debounceTime)
   {
    if(buttonState != reading)
    {
      buttonState = reading;
      if(buttonState == LOW)
      {
        ledState = !ledState;
       }
    }
   }

  lastButtonState = reading;
  // analogWrite(LED, ledState ? 50 : 0); 
  Serial.println(ledState);


 //***********  Raspi Arduino Logic *********** //

 if(Serial.available()>0)
 {
   String message = Serial.readStringUntil('\n');
   if(message.equals("on"))
   {
     analogWrite(LED,50);
   }
   else if(message.equals("off"))
   {
     analogWrite(LED,0);
   }
   
 }


}

