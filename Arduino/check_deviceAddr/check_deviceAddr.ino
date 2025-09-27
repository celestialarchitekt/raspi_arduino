#include <Wire.h>
void setup() {
  Wire.begin();
  Serial.begin(115200);
  while (!Serial); // wait for serial monitor
  Serial.println("\nI2C Scanner");
}
void loop() {
  byte error, address;
  for (address = 1; address < 127; address++ ) {
    Wire.beginTransmission(address);
    error = Wire.endTransmission();
    if (error == 0) {
      Serial.print("I2C device found at 0x");
      Serial.println(address, HEX);
    }
  }
  delay(2000);
}

