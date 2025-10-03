
/*
	Control Servo via button or telegram bot using Raspi-Arduino
*/

#include<Wire.h>
#include<Adafruit_GFX.h>
#include<Adafruit_SSD1306.h>
#include<Servo.h>

const int screen_width = 128;
const int screen_height = 64;

Adafruit_SSD1306 display(screen_width, screen_height, &Wire);

const int LED = 51; // digitalPWM
const int BUTTON = 49; // button digital pwm
bool ledState = LOW;

unsigned long lastTime = 0;
unsigned int debounceTime = 50; 
int buttonState = LOW;
int lastButtonState = LOW;

Servo myServo;


void setup() {
 
   myServo.attach(45);
   myServo.write(0);

   Serial.begin(9600);
   pinMode(LED, OUTPUT);
   pinMode(BUTTON,INPUT_PULLUP); 
  
    Wire.begin();
  
   if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C))
   {  
     Serial.print("led not found");
   }

   //oled settings
   display.clearDisplay();
   display.setTextSize(4);
   display.setTextColor(SSD1306_WHITE);
   display.setCursor(0,0);
   display.display();
 
}



void loop() 
{

     //commands received from Raspi
     if(Serial.available()>0)
     {
     	 String cmd = Serial.readStringUntil('\n');
     	 if(cmd.equals("ON"))
         {
           analogWrite(LED,50);
           display.clearDisplay();
           display.setCursor(0,0);
	   display.println("ON"); //writes to a buffer
           display.display();
           myServo.write(45);
           ledState = HIGH;      
         }
         else if(cmd.equals("OFF"))
         {
          analogWrite(LED,0);
 	  display.clearDisplay();
          display.setCursor(0,0);
          display.println("OFF"); // writes to a buffer
          display.display();
          myServo.write(0);
          ledState = LOW;     
         }  

     }

    
    //button logic
    int reading = digitalRead(BUTTON);
    
    if(reading!= lastButtonState)
    {
      lastTime = millis();
    }    

    if(millis() - lastTime > debounceTime)
    {
      if(buttonState!=reading)
      {
        buttonState = reading;
        if(buttonState==LOW)
        {
           ledState = !ledState;
           analogWrite(LED, ledState?50:0);
           display.clearDisplay();
           display.setCursor(0,0);
           display.println(ledState?"ON":"OFF");
           display.display();
           myServo.write(ledState?45:0);
          // myServo.write( [](bool s){return s ? 45 :0}(ledState));
          Serial.write("button");
        }
      }
    }
    
   lastButtonState = reading;


}
