// RPLIDAR Arduino Due master reader program
// File name: rplidar_due_master.ino
// Author: Kyle Lam
// Date: 2/27/16
// Revision: 1.1
// MASTER READER for DUE

#include <Wire.h>

// vars
byte allData[8];
float distance;
float angle;
bool  startBit;
byte  quality;

void setup() {
  Wire.begin();
  Serial.begin(115200);  // start serial for output
}

void loop() {
  Wire.beginTransmission(8);
  Wire.requestFrom(8, 8);    // request 10 bytes from slave device #8

  // receive all sent data
  if (Wire.available()) {
    int i = 0;
    while (Wire.available()) {
      allData[i] = Wire.read();
      i++;
    }
  }

  // store data
  dataToFloat(allData, distance, angle);
//  quality = allData[10];

  Wire.endTransmission();

  Serial.println(distance);
  Serial.println(angle);

  delay(500);
}

// function for converting distance/angle bytes to float
void dataToFloat (byte* data, float distance, float angle) {
  // get distance bytes into union
  union distanceData {
    byte distanceBytes[4];
    float distanceValue;
  } dData;
  dData.distanceBytes[0] = data[0];
  dData.distanceBytes[1] = data[1];
  dData.distanceBytes[2] = data[2];
  dData.distanceBytes[3] = data[3];
  // set distance
  distance = dData.distanceValue;

  // get angle bytes into union
  union angleData {
    byte angleBytes[4];
    float angleValue;
  } aData;
  aData.angleBytes[0] = data[4];
  aData.angleBytes[1] = data[5];
  aData.angleBytes[2] = data[6];
  aData.angleBytes[3] = data[7];
  // set angle
  angle = aData.angleValue;

//  // get start bytes into union
//  union startData {
//    byte startBytes[2];
//    bool startValue;
//  } sData;
//  sData.startBytes[0] = data[8];
//  sData.startBytes[1] = data[9];
//  // set start
//  startBit = sData.startValue;
}

