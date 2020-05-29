#include <Wire.h>

void setup() {
  Wire.begin();        // join i2c bus (address optional for master)
  Serial.begin(115200);  // start serial for output
  delay(500);
  Serial.println("Master I2C request");
}

void loop() 
{
  Wire.requestFrom(9, 6);    // request 6 bytes from slave device #8

  while (Wire.available()) 
  { // slave may send less than requested
    char c = Wire.read(); // receive a byte as character
    Serial.print(c);         // print the character
  }

  delay(500);
}
