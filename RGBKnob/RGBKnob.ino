#include <Arduino.h>
#include <Wire.h>

void setup() 
{
  Serial.begin(57600);
  Wire.begin(9);                // join i2c bus with address #8
  Wire.onRequest(requestEvent); // register event
  delay(500);
  Serial.println("Slave I2C send on request");
}

void loop() 
{
  delay(100);
}

// function that executes whenever data is requested by master
// this function is registered as an event, see setup()
void requestEvent() 
{
  Wire.write("hello\n"); // respond with message of 6 bytes
  // as expected by master
  Serial.println("sent");
}
