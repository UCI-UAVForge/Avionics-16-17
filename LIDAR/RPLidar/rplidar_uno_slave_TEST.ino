// RPLIDAR Arduino Uno slave writer program TEST
// File name: rplidar_uno_slave.ino
// Author: Kyle Lam
// Date: 2/27/16
// Revision: 1.0
// SLAVE WRITER for UNO

#include <Wire.h>

void setup() {
  Wire.begin(8);                // join i2c bus with address #8
  Wire.onRequest(requestEvent); // register event
}

void loop() {
  delay(100);
}

// function that executes whenever data is requested by master
// this function is registered as an event, see setup()
void requestEvent() {
  Wire.write("hello "); // respond with message of 6 bytes
  // as expected by master
}
