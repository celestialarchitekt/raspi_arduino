/*
   Telegram Raspi Arduino LED ON/OFF
*/

#include<Wire.h>
#include<Adafruit_GFX.h>
#include<Adafruit_SSD1306.h>

const int screen_width = 128;
const int screen_height = 64;

Adafruit_SSD1306 display(screen_width, screen_height, &Wire);

const int LED = 51; // digitalPWM



void setup() {
   Serial.begin(9600);
   pinMode(LED, OUTPUT);
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

void loop() {
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
}
      else if(cmd.equals("OFF"))
      {
      
        analogWrite(LED,0);
	display.clearDisplay();
        display.setCursor(0,0);
        display.println("OFF"); // writes to a buffer
        display.display();     
 }

   }
   //display.display(); //push data from buffer to oled
}
