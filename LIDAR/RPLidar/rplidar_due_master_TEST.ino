// RPLIDAR Arduino Due master reader program TEST
// File name: rplidar_due_master.ino
// Author: Kyle Lam
// Date: 2/27/16
// Revision: 1.0
// MASTER READER for DUE

#include <Wire.h>

void setup() {
  Wire.begin();        // join i2c bus (address optional for master)
  Serial.begin(115200);  // start serial for output
}

void loop() {
  Wire.requestFrom(8, 6);    // request 6 bytes from slave device #8

  while (Wire.available()) { // slave may send less than requested
    char c = Wire.read(); // receive a byte as character
    Serial.print(c);         // print the character
  }

  delay(500);
}
